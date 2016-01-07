/*
 * Copyright (C) 2016 The CyanogenMod Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <stdio.h>
#include <stdlib.h>

#include <sys/mount.h>
#include <sys/stat.h>
#include <unistd.h>

#include "init_header.h"

// Constants: bootrec values - Device dependent
#define BOOTREC_EVENT "/dev/input/event0"
#define BOOTREC_EVENT_MAJOR 13
#define BOOTREC_EVENT_MINOR 64
#define BOOTREC_FOTA "/dev/block/mmcblk0p23"
#define BOOTREC_FOTA_MAJOR 179
#define BOOTREC_FOTA_MINOR 23

// Function: color to led - Device dependent
static void led_color(unsigned char r, unsigned char g, unsigned char b)
{
    write_string("/sys/class/led/fih_led/control", r ? "01 0 1" : "01 0 0");
    write_string("/sys/class/led/fih_led/control", g ? "01 1 1" : "01 1 0");
    write_string("/sys/class/led/fih_led/control", b ? "01 2 1" : "01 2 0");
}

// Main: executable - Device dependent
int main(int __attribute__((unused)) argc, char** __attribute__((unused)) argv)
{
    // Execution variables
    bool recoveryBoot;
    pid_t key_check_pid;

    // Generate boot log
    unlink(BOOT_TXT);
    write_string(BOOT_TXT, "SONY INIT");
    write_date(BOOT_TXT, true);

    // Delete /init symlink
    unlink("/init");

    // Mount filesystems
    mkdir("/dev/block", 0755);
    mkdir("/dev/input", 0755);
    mkdir("/proc", 0555);
    mkdir("/sys", 0755);
    mount("proc", "/proc", "proc", 0, NULL);
    mount("sysfs", "/sys", "sysfs", 0, NULL);

    // Create device nodes
    mknod("/dev/block/mmcblk0", S_IFBLK | 0600, makedev(179, 0));
    mknod(BOOTREC_EVENT, S_IFCHR | 0600, makedev(BOOTREC_EVENT_MAJOR,
            BOOTREC_EVENT_MINOR));
    mknod("/dev/null", S_IFCHR | 0666, makedev(1, 3));

    // Check keys for recovery
    const char* argv_key_check[] = { EXEC_BOX, "cp",
            BOOTREC_EVENT, "/dev/keycheck", nullptr };
    key_check_pid = system_exec_bg(argv_key_check);

    // Recovery boot detection
    const char* argv_boot_recovery[] = { EXEC_BOX, "grep",
            "warmboot=0x77665502", "/proc/cmdline", nullptr };
    recoveryBoot = (system_exec(argv_boot_recovery) == 0);

    // Amber LED
    led_color(255, 0, 255);

    // Wait 3 seconds
    sleep(3);

    // Keys boot decision
    if (recoveryBoot || (file_exists(KEY_CHECK) && !file_empty(KEY_CHECK)))
    {
        // Recovery boot
        write_string(BOOT_TXT, "RECOVERY BOOT", true);
        write_int(0, /sys/module/msm_fb/parameters/align_buffer);
        led_color(0, 255, 255);

        // Recovery ramdisk
        mknod(BOOTREC_FOTA, S_IFBLK | 0600, makedev(BOOTREC_FOTA_MAJOR,
                BOOTREC_FOTA_MINOR));
        mount("/", "/", NULL, MS_MGC_VAL | MS_REMOUNT, "");
        const char* argv_extract_elf[] = { "/sbin/extract_elf_ramdisk", "-i",
                BOOTREC_FOTA, "-o", "/sbin/ramdisk-recovery.cpio", "-t", "/",
                "-c", nullptr };
        system_exec(argv_extract_elf);
        const char* argv_ramdiskcpio[] = { EXEC_BOX, "cpio", "-i", "-F",
                "/sbin/ramdisk-recovery.cpio", nullptr };
        system_exec(argv_ramdiskcpio);
    }
    else
    {
        // Android boot
        write_string(BOOT_TXT, "ANDROID BOOT", true);
        led_color(0, 0, 0);

        // Unpack Android ramdisk
        const char* argv_ramdiskcpio[] = { EXEC_BOX, "cpio", "-i", "-F",
                "/sbin/ramdisk.cpio", nullptr };
        system_exec(argv_ramdiskcpio);
    }

    // Kill keycheck process & kill vibrator
    kill(key_check_pid, 1);

    // Unmount filesystems
    umount("/proc");
    umount("/sys");

    // End init_sony
    const char* argv_rm_dev[] = { EXEC_BOX, "rm", "-fr", "/dev/*", nullptr };
    system_exec(argv_rm_dev);
    write_date(BOOT_TXT, true);

    // Launch ramdisk /init
    const char* argv_init[] = { "/init", nullptr };
    system_exec(argv_init);

    return 0;
}

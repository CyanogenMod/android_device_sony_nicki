# Copyright 2013 The Android Open Source Project
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#      http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

# Product-specific compile-time definitions.

BOARD_EGL_CFG := device/sony/nicki/rootdir/system/lib/egl/egl.cfg

include vendor/sony/nicki/BoardConfigVendor.mk

# inherit from Sony common
include device/sony/common/BoardConfigCommon.mk

# inherit from msm8960-common
include device/sony/msm8960-common/BoardConfigCommon.mk

USE_CAMERA_STUB := false

TARGET_SPECIFIC_HEADER_PATH += device/sony/nicki/include

# Platform
TARGET_BOARD_PLATFORM := msm8960
TARGET_CPU_VARIANT := krait
BOARD_VENDOR_PLATFORM := nicki
TARGET_BOOTLOADER_BOARD_NAME := qcom

# OTA Assert
TARGET_OTA_ASSERT_DEVICE := C1904,C1905,C2004,C2005,nicki

# Cflags
TARGET_GLOBAL_CFLAGS += -mfpu=neon-vfpv4 -mfloat-abi=softfp
TARGET_GLOBAL_CPPFLAGS += -mfpu=neon-vfpv4 -mfloat-abi=softfp
COMMON_GLOBAL_CFLAGS += -D__ARM_USE_PLD -D__ARM_CACHE_LINE_SIZE=64
COMMON_GLOBAL_CFLAGS += -DNEEDS_VECTORIMPL_SYMBOLS
COMMON_GLOBAL_CFLAGS += -DSONY_CAM_PARAMS

# Kernel
BOARD_KERNEL_CMDLINE := panic=3 console=ttyHSL0,115200,n8 androidboot.hardware=qcom user_debug=31 msm_rtb.filter=0x3F ehci-hcd.park=3
BOARD_KERNEL_BASE := 0x80200000
BOARD_KERNEL_PAGESIZE := 4096
BOARD_MKBOOTIMG_ARGS := --ramdisk_offset 0x02000000
TARGET_KERNEL_SOURCE := kernel/sony/msm8x27
TARGET_KERNEL_CONFIG := cyanogenmod_nicki_defconfig

# Partitions
TARGET_USERIMAGES_USE_EXT4 := true
BOARD_BOOTIMAGE_PARTITION_SIZE := 0x01400000
BOARD_RECOVERYIMAGE_PARTITION_SIZE := 0x01400000
BOARD_SYSTEMIMAGE_PARTITION_SIZE := 1258291200
BOARD_USERDATAIMAGE_PARTITION_SIZE := 2235547136
BOARD_FLASH_BLOCK_SIZE := 131072

# Vold
BOARD_VOLD_MAX_PARTITIONS := 27
TARGET_USE_CUSTOM_LUN_FILE_PATH := /sys/devices/platform/msm_hsusb/gadget/lun%d/file

# QCOM Hardware
BOARD_USES_QCOM_HARDWARE := true

# QCOM Display and Graphics
TARGET_QCOM_DISPLAY_VARIANT := caf
TARGET_QCOM_MEDIA_VARIANT := caf
TARGET_USES_QCOM_BSP := true
TARGET_DISPLAY_USE_RETIRE_FENCE := true

# Audio
TARGET_QCOM_AUDIO_VARIANT := caf
BOARD_USES_ALSA_AUDIO := true
BOARD_USES_LEGACY_ALSA_AUDIO := true

# QC AV Enhancements
TARGET_ENABLE_QC_AV_ENHANCEMENTS := true

# QC Time
BOARD_USES_QC_TIME_SERVICES := true

# Camera
USE_DEVICE_SPECIFIC_CAMERA := true

# Legacy Ril
BOARD_HAS_RIL_LEGACY_PAP := true

# Fm
QCOM_FM_ENABLED := true

# Wlan
BOARD_HAS_QCOM_WLAN              := true
BOARD_HAS_QCOM_WLAN_SDK          := true
BOARD_WLAN_DEVICE                := qcwcn
WPA_SUPPLICANT_VERSION           := VER_0_8_X
BOARD_WPA_SUPPLICANT_DRIVER      := NL80211
BOARD_WPA_SUPPLICANT_PRIVATE_LIB := lib_driver_cmd_$(BOARD_WLAN_DEVICE)
BOARD_HOSTAPD_DRIVER             := NL80211
BOARD_HOSTAPD_PRIVATE_LIB        := lib_driver_cmd_$(BOARD_WLAN_DEVICE)
WIFI_DRIVER_MODULE_PATH          := "/system/lib/modules/wlan.ko"
WIFI_DRIVER_MODULE_NAME          := "wlan"
WIFI_DRIVER_FW_PATH_STA          := "sta"
WIFI_DRIVER_FW_PATH_AP           := "ap"

# Bluetooth
BOARD_HAVE_BLUETOOTH_QCOM := true
BLUETOOTH_HCI_USE_MCT := true
BOARD_BLUETOOTH_BDROID_BUILDCFG_INCLUDE_DIR := device/sony/nicki/bluetooth

# Recovery
TARGET_RECOVERY_FSTAB = device/sony/nicki/rootdir/root/fstab.qcom
BOARD_HAS_NO_SELECT_BUTTON := true
TARGET_RECOVERY_PIXEL_FORMAT := "RGBX_8888"
BOARD_CUSTOM_BOOTIMG_MK := device/sony/nicki/custombootimg.mk
BOARD_CUSTOM_RECOVERY_KEYMAPPING := ../../device/sony/nicki/recovery/recovery_keys.c
TARGET_RECOVERY_LCD_BACKLIGHT_PATH := \"/sys/class/leds/lcd-backlight/brightness\"

# Override healthd HAL
BOARD_HAL_STATIC_LIBRARIES := libhealthd.qcom

TARGET_UNIFIED_DEVICE := true
TARGET_INIT_VENDOR_LIB := libinit_nicki
TARGET_LIBINIT_DEFINES_FILE := device/sony/nicki/init/init_nicki.c

# Sepolicy
BOARD_SEPOLICY_DIRS += \
    device/sony/nicki/sepolicy

BOARD_SEPOLICY_UNION += \
    file_contexts \
    app.te \
    bluetooth.te \
    device.te \
    domain.te \
    drmserver.te \
    file.te \
    hci_init.te \
    healthd.te \
    init.te \
    init_shell.te \
    keystore.te \
    kickstart.te \
    mediaserver.te \
    netd.te \
    rild.te \
    surfaceflinger.te \
    system.te \
    ueventd.te \
    wpa_supplicant.te

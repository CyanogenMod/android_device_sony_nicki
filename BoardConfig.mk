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

-include vendor/sony/c1905/BoardConfigVendor.mk

# inherit from Sony common
-include device/sony/common/BoardConfigCommon.mk

# inherit from qcom-common
-include device/sony/qcom-common/BoardConfigCommon.mk

BOARD_VENDOR := sony

USE_CAMERA_STUB := false

TARGET_BOARD_PLATFORM := msm8960
TARGET_CPU_VARIANT := krait
TARGET_ARCH_VARIANT_CPU := cortex-a9
BOARD_VENDOR_PLATFORM := c1905
TARGET_CPU_SMP := true
TARGET_BOOTLOADER_BOARD_NAME := qcom

TARGET_GLOBAL_CFLAGS += -mfpu=neon -mfloat-abi=softfp
TARGET_GLOBAL_CPPFLAGS += -mfpu=neon -mfloat-abi=softfp

BOARD_KERNEL_CMDLINE := panic=3 console=ttyHSL0,115200,n8 androidboot.hardware=qcom user_debug=31 msm_rtb.filter=0x3F ehci-hcd.park=3
BOARD_KERNEL_BASE := 0x80200000
BOARD_KERNEL_PAGESIZE := 4096
BOARD_MKBOOTIMG_ARGS := --ramdisk_offset 0x02000000

TARGET_USERIMAGES_USE_EXT4 := true
BOARD_BOOTIMAGE_PARTITION_SIZE := 0x01400000
BOARD_RECOVERYIMAGE_PARTITION_SIZE := 0x01400000
BOARD_SYSTEMIMAGE_PARTITION_SIZE := 1258291200
BOARD_USERDATAIMAGE_PARTITION_SIZE := 2235547136
BOARD_FLASH_BLOCK_SIZE := 131072

BOARD_VOLD_MAX_PARTITIONS := 27
TARGET_USE_CUSTOM_LUN_FILE_PATH := /sys/devices/platform/msm_hsusb/gadget/lun%d/file

TARGET_KERNEL_SOURCE := kernel/sony/nicki
TARGET_KERNEL_CONFIG := cyanogenmod_nicki_defconfig

TARGET_USES_QCOM_BSP := true
COMMON_GLOBAL_CFLAGS += -DQCOM_BSP

TARGET_SPECIFIC_HEADER_PATH += device/sony/c1905/include

TARGET_USES_ION := true
TARGET_USES_C2D_COMPOSITION := true
USE_OPENGL_RENDERER := true
BOARD_EGL_CFG := device/sony/c1905/egl.cfg

ENABLE_WEBGL := true

BOARD_USES_ALSA_AUDIO := true

# Wlan
BOARD_HAS_QCOM_WLAN              := true
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

BOARD_HAVE_BLUETOOTH := true
BOARD_HAVE_BLUETOOTH_QCOM := true
BLUETOOTH_HCI_USE_MCT := true
BOARD_BLUETOOTH_BDROID_BUILDCFG_INCLUDE_DIR := device/sony/c1905/bluetooth

TARGET_RECOVERY_FSTAB = device/sony/c1905/rootdir/root/fstab.qcom

BOARD_HAS_NO_SELECT_BUTTON := true
TARGET_RECOVERY_PIXEL_FORMAT := "RGBX_8888"
BOARD_CUSTOM_BOOTIMG_MK := device/sony/c1905/custombootimg.mk
BOARD_CUSTOM_RECOVERY_KEYMAPPING := ../../device/sony/c1905/recovery/recovery_keys.c
BOARD_CUSTOM_GRAPHICS := ../../../device/sony/c1905/recovery/graphics.c


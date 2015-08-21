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

# Inherit from Sony common
include device/sony/common/BoardConfigCommon.mk

USE_CAMERA_STUB := false

# Architecture
TARGET_ARCH := arm
TARGET_CPU_ABI := armeabi-v7a
TARGET_CPU_ABI2 := armeabi
TARGET_ARCH_VARIANT := armv7-a-neon
TARGET_CPU_VARIANT := krait

# Platform
TARGET_BOARD_PLATFORM := msm8960
BOARD_VENDOR_PLATFORM := nicki
TARGET_BOOTLOADER_BOARD_NAME := qcom

TARGET_NO_BOOTLOADER := true
TARGET_NO_RADIOIMAGE := true

MALLOC_IMPL := dlmalloc

TARGET_SPECIFIC_HEADER_PATH += device/sony/nicki/include

# OTA Assert
TARGET_OTA_ASSERT_DEVICE := C1904,C1905,C2004,C2005,nicki

# Cflags
TARGET_RELEASE_CPPFLAGS += -DNEEDS_VECTORIMPL_SYMBOLS

# Kernel
BOARD_KERNEL_CMDLINE := panic=3 console=ttyHSL0,115200,n8 androidboot.hardware=qcom user_debug=23 msm_rtb.filter=0x3F ehci-hcd.park=3 androidboot.bootdevice=msm_sdcc.1
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

# Font expansion
EXTENDED_FONT_FOOTPRINT := true

# QCOM hardware
BOARD_USES_QCOM_HARDWARE := true

# QCOM Display and Graphics
USE_OPENGL_RENDERER := true
TARGET_USES_ION := true
TARGET_USES_C2D_COMPOSITION := true
TARGET_DISPLAY_USE_RETIRE_FENCE := true

# Audio
BOARD_USES_ALSA_AUDIO := true
BOARD_USES_LEGACY_ALSA_AUDIO := true

# Lights HAL
TARGET_PROVIDES_LIBLIGHT := true

# QC AV Enhancements
TARGET_ENABLE_QC_AV_ENHANCEMENTS := true

# QC Time
BOARD_USES_QC_TIME_SERVICES := true

# Camera
USE_DEVICE_SPECIFIC_CAMERA := true

# Power HAL
TARGET_POWERHAL_VARIANT := qcom
CM_POWERHAL_EXTENSION := qcom

# Fm
QCOM_FM_ENABLED := true
AUDIO_FEATURE_ENABLED_FM := true

# Bluetooth
BOARD_HAVE_BLUETOOTH := true
BOARD_HAVE_BLUETOOTH_QCOM := true
BLUETOOTH_HCI_USE_MCT := true
BOARD_BLUETOOTH_BDROID_BUILDCFG_INCLUDE_DIR := device/sony/nicki/bluetooth

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

# Recovery
TARGET_RECOVERY_FSTAB := device/sony/nicki/rootdir/root/fstab.qcom
BOARD_HAS_NO_SELECT_BUTTON := true
TARGET_RECOVERY_PIXEL_FORMAT := "RGBX_8888"
BOARD_CUSTOM_BOOTIMG_MK := device/sony/nicki/custombootimg.mk

TARGET_UNIFIED_DEVICE := true
TARGET_INIT_VENDOR_LIB := libinit_nicki
TARGET_LIBINIT_DEFINES_FILE := device/sony/nicki/init/init_nicki.c

BOARD_CHARGER_ENABLE_SUSPEND := true
BOARD_CHARGER_SHOW_PERCENTAGE := true

BOARD_HARDWARE_CLASS := device/sony/nicki/cmhw/

# Sepolicy
include device/qcom/sepolicy/sepolicy.mk

BOARD_SEPOLICY_DIRS += \
    device/sony/nicki/sepolicy

BOARD_SEPOLICY_UNION += \
       device.te \
       file_contexts \
       file.te \
       property.te \
       property_contexts \
       healthd.te \
       init_shell.te \
       kernel.te \
       mediaserver.te \
       mm-qcamerad.te \
       mpdecision.te \
       location.te \
       sdcardd.te \
       system_app.te \
       system_server.te \
       thermal-engine.te \
       vold.te

-include vendor/sony/nicki/BoardConfigVendor.mk

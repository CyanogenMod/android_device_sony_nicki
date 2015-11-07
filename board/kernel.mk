# Kernel informations
BOARD_KERNEL_BASE := 0x80200000
BOARD_KERNEL_PAGESIZE := 4096
BOARD_KERNEL_CMDLINE := panic=3 console=ttyHSL0,115200,n8 androidboot.hardware=qcom user_debug=23 msm_rtb.filter=0x3F ehci-hcd.park=3 androidboot.bootdevice=msm_sdcc.1
BOARD_MKBOOTIMG_ARGS := --ramdisk_offset 0x02000000

# Kernel properties
TARGET_KERNEL_SOURCE := kernel/sony/msm8x27
TARGET_KERNEL_CONFIG := cyanogenmod_nicki_defconfig
TARGET_KERNEL_CROSS_COMPILE_PREFIX := arm-linux-androideabi-

# Custom boot
BOARD_CUSTOM_BOOTIMG := true
BOARD_CUSTOM_BOOTIMG_MK := $(DEVICE_PATH)/boot/custombootimg.mk

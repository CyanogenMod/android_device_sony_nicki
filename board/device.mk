# OTA assert
TARGET_OTA_ASSERT_DEVICE := C1904,C1905,C2004,C2005,nicki

# Device init
TARGET_INIT_VENDOR_LIB := libinit_nicki
TARGET_LIBINIT_DEFINES_FILE := $(DEVICE_PATH)/init/init_nicki.cpp

# Device unified
TARGET_UNIFIED_DEVICE := true

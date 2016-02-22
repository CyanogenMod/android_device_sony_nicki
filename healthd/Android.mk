LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)
LOCAL_SRC_FILES := healthd_board_nicki.cpp
LOCAL_MODULE := libhealthd.nicki
LOCAL_CFLAGS := -Werror
LOCAL_C_INCLUDES := system/core/healthd bootable/recovery
include $(BUILD_STATIC_LIBRARY)

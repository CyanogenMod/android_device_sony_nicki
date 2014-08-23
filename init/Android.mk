LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE_TAGS := optional
LOCAL_C_INCLUDES := system/core/init
LOCAL_SRC_FILES := init_nicki.c
LOCAL_MODULE := libinit_nicki
include $(BUILD_STATIC_LIBRARY)

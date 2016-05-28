# Copyright 2013 The Android Open Source Project
# Copyright 2015 The CyanogenMod Project

LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)
LOCAL_SRC_FILES := healthd_board_nicki.cpp
LOCAL_MODULE := libhealthd.nicki
LOCAL_C_INCLUDES := system/core/healthd bootable/recovery
LOCAL_CFLAGS := -Werror
include $(BUILD_STATIC_LIBRARY)
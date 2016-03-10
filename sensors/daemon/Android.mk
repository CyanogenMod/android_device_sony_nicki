LOCAL_PATH := $(call my-dir)

ifeq ($(USE_OSS_SENSORD),true)
include $(CLEAR_VARS)

LOCAL_INCLUDES += $(LOCAL_PATH)

LOCAL_SRC_FILES += \
	src/main.c \
	src/misc.c \
	src/trace.c \
	src/sensor_cfg.c \
	src/event_handler.c \
	src/lib/util_misc.c \
	src/lib/util_time.c \
	src/lib/util_sysfs.c \
	src/lib/util_input_dev.c \
	src/channel_cntl.c \
	src/channel_a.c \
	src/channel_g.c \
	src/channel_m.c \
	src/channel_o.c \
	src/channel_p.c \
	src/channel_vg.c \
	src/channel_vla.c \
	src/channel_vrv.c \
	src/channel_gest_flip.c \
	src/channels.c \
	src/sensor_fusion.c \
	src/sensor_provider.c \
	src/hw/hw_cntl.c


LOCAL_C_INCLUDES += $(LOCAL_PATH) \
		    $(LOCAL_PATH)/inc \
		    $(LOCAL_PATH)/algo/inc \
		    $(LOCAL_PATH)/src/algo \
		    $(LOCAL_PATH)/src/hw


LOCAL_CFLAGS += -Wall \
		-D LOG_TAG=\"bstd\" \
		-D CFG_DATA_INPUT_SRC_DEV \
		-D CFG_TARGET_OS_ANDROID \
		-D CFG_ARCH_ARM \
		-D CFG_LOG_TO_FILE \
		-D CFG_LOG_LEVEL=LOG_LEVEL_I \
		-D CFG_LOG_WITH_TIME \
		-D DISABLE_EARLY_LOG \
		-D CFG_SENSOR_G_EMU=1 \
		-D CFG_BYPASS_PROC_CHANNEL_A \
		-D HW_A_USE_INPUT_EVENT_CACHE

LOCAL_LDFLAGS += $(LOCAL_PATH)/algo/lib/libalgobmc.a

LOCAL_SHARED_LIBRARIES += liblog libcutils libc libm

-include $(addprefix $(LOCAL_PATH)/,$(addsuffix /Android.mk, \
	src/algo\
	src/hw/a\
	src/hw/m\
	   ))

-include $(LOCAL_PATH)/src/hw/Android.mk

LOCAL_MODULE_TAGS := eng
LOCAL_MODULE := sensord
include $(BUILD_EXECUTABLE)
endif

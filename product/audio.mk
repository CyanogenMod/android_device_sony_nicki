# Audio configurations
PRODUCT_COPY_FILES += \
    $(LOCAL_PATH)/audio/audio_effects.conf:system/vendor/etc/audio_effects.conf \
    $(LOCAL_PATH)/audio/audio_platform_info.xml:system/etc/audio_platform_info.xml \
    $(LOCAL_PATH)/audio/audio_policy.conf:system/etc/audio_policy.conf \
    $(LOCAL_PATH)/audio/mixer_paths.xml:system/etc/mixer_paths.xml

PRODUCT_COPY_FILES += \
    frameworks/native/data/etc/android.hardware.audio.low_latency.xml:system/etc/permissions/android.hardware.audio.low_latency.xml

# Bootanimation audio
PRODUCT_PROPERTY_OVERRIDES += \
    qcom.audio.init=complete

# Disbale tunnel mode playback by default
PRODUCT_PROPERTY_OVERRIDES += \
    audio.offload.disable=1

# Multichannel AAC
PRODUCT_PROPERTY_OVERRIDES += \
    media.aac_51_output_enabled=true

# Fluence multi-mic solution
PRODUCT_PROPERTY_OVERRIDES += \
    ro.qc.sdk.audio.fluencetype=fluence \
    persist.audio.fluence.voicecall=true \
    persist.audio.fluence.voicerec=false \
    persist.audio.fluence.audiorec=false \
    persist.audio.fluence.speaker=true


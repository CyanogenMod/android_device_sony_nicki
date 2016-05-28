# Telephony permissions
PRODUCT_COPY_FILES += \
    frameworks/native/data/etc/android.hardware.telephony.gsm.xml:system/etc/permissions/android.hardware.telephony.gsm.xml

# RIL packages
PRODUCT_PACKAGES += \
    libtime_genoff

# RIL properties
PRODUCT_PROPERTY_OVERRIDES += \
    persist.rild.nitz_plmn= \
    persist.rild.nitz_long_ons_0= \
    persist.rild.nitz_long_ons_1= \
    persist.rild.nitz_long_ons_2= \
    persist.rild.nitz_long_ons_3= \
    persist.rild.nitz_short_ons_0= \
    persist.rild.nitz_short_ons_1= \
    persist.rild.nitz_short_ons_2= \
    persist.rild.nitz_short_ons_3= \
    rild.libargs=-d /dev/smd0 \
    rild.libpath=/system/lib/libril-qc-qmi-1.so \
    ro.telephony.ril_class=SonyRIL

# Radio properties
PRODUCT_PROPERTY_OVERRIDES += \
    persist.radio.apm_sim_not_pwdn=1 \
    ril.subscription.types=NV,RUIM \
    telephony.lteOnCdmaDevice=0

# Telephony properties
PRODUCT_PROPERTY_OVERRIDES += \
    ro.telephony.call_ring.multiple=0

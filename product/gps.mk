# GPS packages
PRODUCT_PACKAGES += \
    gps.msm8960 \
    gps.conf \
    sap.conf \
    izat.conf

# SEC configurations
PRODUCT_COPY_FILES += \
    $(LOCAL_PATH)/configs/sec_config:system/etc/sec_config

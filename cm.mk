## Specify phone tech before including full_phone
$(call inherit-product, vendor/cm/config/gsm.mk)

# Inherit CM common GSM stuff.
$(call inherit-product, vendor/cm/config/gsm.mk)

# Enhanced NFC
$(call inherit-product, vendor/cm/config/nfc_enhanced.mk)

# Inherit some common CM stuff.
$(call inherit-product, vendor/cm/config/common_full_phone.mk)

# Inherit device configuration
$(call inherit-product, device/sony/c1905/c1905.mk)

TARGET_SCREEN_HEIGHT := 800
TARGET_SCREEN_WIDTH := 480

## Device identifier. This must come after all inclusions
PRODUCT_DEVICE := c1905
PRODUCT_NAME := cm_c1905
PRODUCT_BRAND := sony
PRODUCT_MODEL := C1905
PRODUCT_MANUFACTURER := sony
PRODUCT_CHARACTERISTICS := phone

PRODUCT_BUILD_PROP_OVERRIDES += \
    PRODUCT_NAME=C1905 \
    BUILD_FINGERPRINT="Sony/C1904_1274-3899/C1904:4.1.2/15.1.C.1.17/3bt96g:user/release-keys" \
    PRIVATE_BUILD_DESC="C1904-user 4.1.2 2.11.J.1.34 3bt96g test-keys"

# Release name
PRODUCT_RELEASE_NAME := Xperiam

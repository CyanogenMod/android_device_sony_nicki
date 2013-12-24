# Copyright (C) 2013 The Android Open Source Project
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#      http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

$(call inherit-product, $(SRC_TARGET_DIR)/product/languages_full.mk)
$(call inherit-product, $(SRC_TARGET_DIR)/product/full_base_telephony.mk)
$(call inherit-product, vendor/sony/c1905/c1905-vendor.mk)
$(call inherit-product, device/sony/common/resources.mk)
$(call inherit-product, device/sony/qcom-common/qcom-common.mk)

$(call inherit-product, device/common/gps/gps_us_supl.mk)

$(call inherit-product-if-exists, frameworks/native/build/phone-xhdpi-1024-dalvik-heap.mk)
$(call inherit-product-if-exists, frameworks/native/build/phone-xhdpi-1024-hwui-memory.mk)

# Permissions
PRODUCT_COPY_FILES += \
    frameworks/native/data/etc/android.hardware.camera.flash-autofocus.xml:system/etc/permissions/android.hardware.camera.flash-autofocus.xml \
    frameworks/native/data/etc/android.hardware.camera.front.xml:system/etc/permissions/android.hardware.camera.front.xml \
    frameworks/native/data/etc/android.hardware.location.gps.xml:system/etc/permissions/android.hardware.location.gps.xml \
    frameworks/native/data/etc/android.hardware.sensor.gyroscope.xml:system/etc/permissions/android.hardware.sensor.gyroscope.xml \
    frameworks/native/data/etc/android.hardware.sensor.light.xml:system/etc/permissions/android.hardware.sensor.light.xml \
    frameworks/native/data/etc/android.hardware.sensor.proximity.xml:system/etc/permissions/android.hardware.sensor.proximity.xml \
    frameworks/native/data/etc/android.hardware.touchscreen.multitouch.jazzhand.xml:system/etc/permissions/android.hardware.touchscreen.multitouch.jazzhand.xml \
    frameworks/native/data/etc/android.hardware.usb.accessory.xml:system/etc/permissions/android.hardware.usb.accessory.xml \
    frameworks/native/data/etc/android.hardware.usb.host.xml:system/etc/permissions/android.hardware.usb.host.xml \
    frameworks/native/data/etc/android.hardware.wifi.direct.xml:system/etc/permissions/android.hardware.wifi.direct.xml \
    frameworks/native/data/etc/android.hardware.bluetooth_le.xml:system/etc/permissions/android.hardware.bluetooth_le.xml \
    frameworks/native/data/etc/android.hardware.wifi.xml:system/etc/permissions/android.hardware.wifi.xml \
    frameworks/native/data/etc/handheld_core_hardware.xml:system/etc/permissions/handheld_core_hardware.xml \
    frameworks/native/data/etc/android.hardware.telephony.gsm.xml:system/etc/permissions/android.hardware.telephony.gsm.xml \
    packages/wallpapers/LivePicker/android.software.live_wallpaper.xml:system/etc/permissions/android.software.live_wallpaper.xml

# Platform specific overlays
DEVICE_PACKAGE_OVERLAYS := device/sony/c1905/overlay

PRODUCT_TAGS += dalvik.gc.type-precise

PRODUCT_COPY_FILES += \
    device/sony/c1905/rootdir/root/init.qcom.rc:root/init.qcom.rc \
    device/sony/c1905/rootdir/root/fstab.qcom:root/fstab.qcom \
    device/sony/c1905/rootdir/root/ueventd.qcom.rc:root/ueventd.qcom.rc \
    device/sony/c1905/rootdir/root/init.qcom.usb.rc:root/init.qcom.usb.rc \
    device/sony/c1905/rootdir/root/init.recovery.qcom.rc:root/init.recovery.qcom.rc \

PRODUCT_COPY_FILES += \
    device/sony/c1905/rootdir/system/etc/init.qcom.bt.sh:system/etc/init.qcom.bt.sh \
    device/sony/c1905/rootdir/system/etc/init.qcom.modem_links.sh:system/etc/init.qcom.modem_links.sh \

PRODUCT_COPY_FILES += \
    device/sony/c1905/rootdir/system/etc/media_profiles.xml:system/etc/media_profiles.xml \
    device/sony/c1905/rootdir/system/etc/media_codecs.xml:system/etc/media_codecs.xml \
    device/sony/c1905/rootdir/system/etc/audio_policy.conf:system/etc/audio_policy.conf \
    device/sony/c1905/rootdir/system/etc/snd_soc_msm/snd_soc_msm_Sitar:system/etc/snd_soc_msm/snd_soc_msm_Sitar \

PRODUCT_COPY_FILES += \
    device/sony/c1905/rootdir/system/etc/thermald.conf:system/etc/thermald.conf \

PRODUCT_COPY_FILES += \
    device/sony/c1905/rootdir/system/usr/keychars/sensor00fn11.kcm:system/usr/keychars/sensor00fn11.kcm \
    device/sony/c1905/rootdir/system/usr/keychars/fih_gpio-keys.kcm:system/usr/keychars/fih_gpio-keys.kcm \
    device/sony/c1905/rootdir/system/usr/keylayout/gpio-keys.kl:system/usr/keylayout/gpio-keys.kl \
    device/sony/c1905/rootdir/system/usr/keylayout/cyttsp-i2c.kl:system/usr/keylayout/cyttsp-i2c.kl \
    device/sony/c1905/rootdir/system/usr/keylayout/keypad_8960.kl:system/usr/keylayout/keypad_8960.kl \
    device/sony/c1905/rootdir/system/usr/keylayout/keypad_8960_liquid.kl:system/usr/keylayout/keypad_8960_liquid.kl \
    device/sony/c1905/rootdir/system/usr/keylayout/philips_remote_ir.kl:system/usr/keylayout/philips_remote_ir.kl \
    device/sony/c1905/rootdir/system/usr/keylayout/samsung_remote_ir.kl:system/usr/keylayout/samsung_remote_ir.kl \
    device/sony/c1905/rootdir/system/usr/keylayout/ue_rf4ce_remote.kl:system/usr/keylayout/ue_rf4ce_remote.kl \
    device/sony/c1905/rootdir/system/usr/keylayout/fih_gpio-keys.kl:system/usr/keylayout/fih_gpio-keys.kl \
    device/sony/c1905/rootdir/system/usr/keylayout/atmel_mxt_ts.kl:system/usr/keylayout/atmel_mxt_ts.kl \
    device/sony/c1905/rootdir/system/usr/keylayout/sensor00fn11.kl:system/usr/keylayout/sensor00fn11.kl \
    device/sony/c1905/rootdir/system/usr/keylayout/Button_Jack.kl:system/usr/keylayout/Button_Jack.kl

PRODUCT_COPY_FILES += \
    $(LOCAL_PATH)/rootdir/system/etc/wifi/p2p_supplicant_overlay.conf:system/etc/wifi/p2p_supplicant_overlay.conf \
    $(LOCAL_PATH)/rootdir/system/etc/wifi/wpa_supplicant_overlay.conf:system/etc/wifi/wpa_supplicant_overlay.conf

PRODUCT_COPY_FILES += \
    $(LOCAL_PATH)/prima_fw/WCNSS_cfg.dat:system/etc/firmware/wlan/prima/WCNSS_cfg.dat \
    $(LOCAL_PATH)/prima_fw/WCNSS_qcom_cfg.ini:system/etc/firmware/wlan/prima/WCNSS_qcom_cfg.ini \
    $(LOCAL_PATH)/prima_fw/WCNSS_qcom_wlan_nv.bin:system/etc/firmware/wlan/prima/WCNSS_qcom_wlan_nv.bin

PRODUCT_COPY_FILES += \
    $(LOCAL_PATH)/recovery/postrecoveryboot.sh:recovery/root/sbin/postrecoveryboot.sh \
    $(LOCAL_PATH)/recovery/remap.sh:recovery/root/sbin/remap.sh

PRODUCT_COPY_FILES += \
    $(LOCAL_PATH)/recovery/bootrec-device:recovery/bootrec-device

PRODUCT_PACKAGES += \
    charger \
    charger_res_images \
    libnl_2 \
    bttest \
    libtinyxml

PRODUCT_PACKAGES += \
    libnfc \
    libnfc_jni \
    Nfc \
    Tag \
    com.android.nfc_extras

ifeq ($(TARGET_BUILD_VARIANT),user)
    NFCEE_ACCESS_PATH := device/sony/c1905/rootdir/system/etc/nfcee_access.xml
else
    NFCEE_ACCESS_PATH := device/sony/c1905/rootdir/system/etc/nfcee_access_debug.xml
endif
PRODUCT_COPY_FILES += \
    $(NFCEE_ACCESS_PATH):system/etc/nfcee_access.xml

PRODUCT_PACKAGES += \
    alsa.msm8960 \
    audio_policy.msm8960 \
    audio.primary.msm8960 \
    audio.a2dp.default \
    audio.usb.default \
    audio.r_submix.default \
    libaudio-resampler \
    tinymix

PRODUCT_PACKAGES += \
    hwcomposer.msm8960 \
    gralloc.msm8960 \
    copybit.msm8960 \
    libqdMetaData

PRODUCT_PACKAGES += \
    extract_elf_ramdisk

PRODUCT_PACKAGES += \
    librs_jni \
    com.android.future.usb.accessory

PRODUCT_PACKAGES += \
    setup_fs \
    e2fsck

# Omx
PRODUCT_PACKAGES += \
    libOmxAacEnc \
    libOmxAmrEnc \
    libOmxCore \
    libOmxEvrcEnc \
    libOmxQcelp13Enc \
    libOmxVdec \
    libOmxVenc \
    libc2dcolorconvert \
    libdashplayer \
    libdivxdrmdecrypt \
    libmm-omxcore \
    libstagefrighthw

# GPS
PRODUCT_PACKAGES += \
    libloc_adapter \
    libloc_eng \
    libloc_api_v02 \
    libgps.utils \
    gps.msm8960

PRODUCT_DEFAULT_PROPERTY_OVERRIDES += \
    persist.sys.usb.config=mtp,adb

PRODUCT_PROPERTY_OVERRIDES += \
    ro.ril.transmitpower=true \
    persist.radio.apm_sim_not_pwdn=1 \
    ro.telephony.ril.v3=qcomdsds \
    DEVICE_PROVISIONED=1 \
    rild.libpath=/system/lib/libril-qc-qmi-1.so \
    ril.subscription.types=NV,RUIM \
    telephony.lteOnCdmaDevice=0 \
    ro.use_data_netmgrd=true

PRODUCT_PROPERTY_OVERRIDES += \
    ro.qualcomm.cabl=0 \
    ro.opengles.version=196608 \
    af.resampler.quality=255 \
    persist.audio.fluence.mode=endfire \
    persist.audio.vr.enable=false \
    persist.audio.handset.mic=digital \
    lpa.decode=true \
    lpa.use-stagefright=true \
    ro.gps.agps_provider=customized \
    persist.gps.qmienabled=true \
    persist.fuse_sdcard=true \
    ro.cwm.enable_key_repeat=true \
    persist.debug.wfd.enable=1 \
    persist.sys.wfd.virtual=0 \
    ro.qualcomm.bt.hci_transport=smd

PRODUCT_AAPT_CONFIG := normal hdpi
PRODUCT_AAPT_PREF_CONFIG := hdpi

# Product attributes
PRODUCT_BUILD_PROP_OVERRIDES += BUILD_UTC_DATE=0
PRODUCT_NAME := c1905
PRODUCT_DEVICE := c1905
PRODUCT_MODEL := c1905
PRODUCT_BRAND := Sony
PRODUCT_MANUFACTURER := Sony
PRODUCT_CHARACTERISTICS := phone


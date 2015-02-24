# Copyright (C) 2013 The CyanogenMod Project
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

# Boot Animation
TARGET_SCREEN_HEIGHT := 854
TARGET_SCREEN_WIDTH := 480

# Inherit from those products. Most specific first.
$(call inherit-product, $(SRC_TARGET_DIR)/product/full_base_telephony.mk)

# Inherit nicki device
$(call inherit-product, device/sony/nicki/nicki.mk)

# Inherit common Sony resources
$(call inherit-product, device/sony/common/resources.mk)

## Device identifier. This must come after all inclusions
PRODUCT_DEVICE := nicki
PRODUCT_NAME := full_nicki
PRODUCT_BRAND := Sony
PRODUCT_MODEL := Xperia M
PRODUCT_MANUFACTURER := Sony

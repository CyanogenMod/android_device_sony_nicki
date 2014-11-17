/*
 * Copyright (C) 2014 The CyanogenMod Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#define CAMERA_PARAMETERS_EXTRA_C \
const char CameraParameters::KEY_SONY_ISO[] = "sony-iso"; \
const char CameraParameters::KEY_SONY_METERING_MODE[] = "sony-metering-mode"; \
const char CameraParameters::KEY_SONY_VS[] = "sony-vs"; \
const char CameraParameters::KEY_SONY_MAX_BURST_SHOT_SIZE[] = "sony-max-burst-shot-size"; \
const char CameraParameters::KEY_SONY_BURST_SHOT_VALUES[] = "sony-burst-shot-values"; \
const char CameraParameters::KEY_SONY_VS_VALUES[] = "sony-vs-values"; \
const char CameraParameters::KEY_SONY_METERING_MODE_VALUES[] = "sony-metering-mode-values"; \
const char CameraParameters::KEY_SONY_AE_MODE[] = "sony-ae-mode"; \
const char CameraParameters::KEY_SONY_AE_MODE_VALUES[] = "sony-ae-mode-values"; \
const char CameraParameters::KEY_SONY_ISO_VALUES[] = "sony-iso-values"; \
const char CameraParameters::KEY_SONY_IS[] = "sony-is"; \
const char CameraParameters::KEY_SONY_IS_VALUES[] = "sony-is-values"; \
const char CameraParameters::KEY_SONY_EXTENSION_VERSION[] = "sony-extension-version"; \
const char CameraParameters::KEY_SONY_FOCUS_AREA[] = "sony-focus-area"; \
const char CameraParameters::KEY_SONY_FOCUS_AREA_VALUES[] = "sony-focus-area-values"; \
const char CameraParameters::KEY_SONY_MAX_MULTI_FOCUS_NUM[] = "sony-max-multi-focus-num"; \
const char CameraParameters::KEY_SONY_SCENE_DETECT_SUPPORTED[] = "sony-scene-detect-supported"; \
const char CameraParameters::KEY_GPS_LATITUDE_REF[] = "gps-latitude-ref"; \
const char CameraParameters::KEY_GPS_LONGITUDE_REF[] = "gps-longitude-ref"; \
const char CameraParameters::KEY_GPS_ALTITUDE_REF[] = "gps-altitude-ref";


#define CAMERA_PARAMETERS_EXTRA_H \
    static const char KEY_SONY_ISO[]; \
    static const char KEY_SONY_METERING_MODE[]; \
    static const char KEY_SONY_VS[]; \
    static const char KEY_SONY_MAX_BURST_SHOT_SIZE[]; \
    static const char KEY_SONY_BURST_SHOT_VALUES[]; \
    static const char KEY_SONY_VS_VALUES[]; \
    static const char KEY_SONY_METERING_MODE_VALUES[]; \
    static const char KEY_SONY_AE_MODE[]; \
    static const char KEY_SONY_AE_MODE_VALUES[]; \
    static const char KEY_SONY_ISO_VALUES[]; \
    static const char KEY_SONY_IS[]; \
    static const char KEY_SONY_IS_VALUES[]; \
    static const char KEY_SONY_EXTENSION_VERSION[]; \
    static const char KEY_SONY_FOCUS_AREA[]; \
    static const char KEY_SONY_FOCUS_AREA_VALUES[]; \
    static const char KEY_SONY_MAX_MULTI_FOCUS_NUM[]; \
    static const char KEY_SONY_SCENE_DETECT_SUPPORTED[];; \
    static const char KEY_GPS_LATITUDE_REF[]; \
    static const char KEY_GPS_LONGITUDE_REF[]; \
    static const char KEY_GPS_ALTITUDE_REF[];

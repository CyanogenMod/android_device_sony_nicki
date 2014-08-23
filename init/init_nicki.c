/*
   Copyright (c) 2013, The Linux Foundation. All rights reserved.

   Redistribution and use in source and binary forms, with or without
   modification, are permitted provided that the following conditions are
   met:
    * Redistributions of source code must retain the above copyright
      notice, this list of conditions and the following disclaimer.
    * Redistributions in binary form must reproduce the above
      copyright notice, this list of conditions and the following
      disclaimer in the documentation and/or other materials provided
      with the distribution.
    * Neither the name of The Linux Foundation nor the names of its
      contributors may be used to endorse or promote products derived
      from this software without specific prior written permission.

   THIS SOFTWARE IS PROVIDED "AS IS" AND ANY EXPRESS OR IMPLIED
   WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
   MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT
   ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS
   BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
   CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
   SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR
   BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
   WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
   OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN
   IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#include <stdlib.h>
#include <stdio.h>

#include "vendor_init.h"
#include "property_service.h"
#include "log.h"
#include "util.h"

void vendor_load_properties()
{
    char device[PROP_VALUE_MAX];
    char bbversion[92];
    FILE *fp;

    fp = popen("/system/xbin/strings /dev/block/platform/msm_sdcc.1/by-name/modem | /system/bin/grep M8930B-", "r");
    fgets(bbversion, sizeof(bbversion), fp);
    pclose(fp);

    if (strstr(bbversion, "M8930B-AAAATAZM-3.2.25121") ||
            strstr(bbversion, "M8930B-AAAATAZM-3.2.25126")) { //single sim 4.3 basebands
        property_set("ro.product.device", "C1905");
        property_set("ro.product.model", "C1905");
        property_set("ro.build.description", "C1905-user 4.3 2.22.J.1.18 eng.user.20140509.125022 test-keys");
        property_set("ro.build.fingerprint", "Sony/C1905/C1905:4.3/15.4.A.1.9/eng.user.20140509.125022:user/release-keys");
        property_set("persist.radio.multisim.config", "");
    } else if (strstr(bbversion, "M8930B-AAAATAZM-4.5.21264") ||
            strstr(bbversion, "M8930B-AAAATAZM-4.5.21266")) { //dual sim 4.3 basebands
        property_set("ro.product.device", "C2005");
        property_set("ro.product.model", "C2005");
        property_set("ro.build.description", "C2005-user 4.3 2.23.J.1.14 eng.user.20140430.172301 test-keys");
        property_set("ro.build.fingerprint", "Sony/C2005/C2005:4.3/15.5.A.1.5/eng.user.20140430.172301:user/release-keys");
        property_set("persist.radio.multisim.config", "dsds");
        property_set("persist.radio.dont_use_dsd", "true");
    };

    property_get("ro.product.device", device);
    ERROR("Found %s baseband setting build properties for %s device\n", bbversion, device);
}

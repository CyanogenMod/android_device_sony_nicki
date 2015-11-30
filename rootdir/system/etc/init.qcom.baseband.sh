#!/system/bin/sh

setprop gsm.version.baseband `busybox strings /dev/block/platform/msm_sdcc.1/by-name/modem  | busybox grep "M8930B-" | head -1`

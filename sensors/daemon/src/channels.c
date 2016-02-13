/*!
 * @section LICENSE
 *
 * (C) Copyright 2013 Bosch Sensortec GmbH All Rights Reserved
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
 *
 *------------------------------------------------------------------------------
 * Disclaimer
 *
 * Common: Bosch Sensortec products are developed for the consumer goods
 * industry. They may only be used within the parameters of the respective valid
 * product data sheet.  Bosch Sensortec products are provided with the express
 * understanding that there is no warranty of fitness for a particular purpose.
 * They are not fit for use in life-sustaining, safety or security sensitive
 * systems or any system or device that may lead to bodily harm or property
 * damage if the system or device malfunctions. In addition, Bosch Sensortec
 * products are not fit for use in products which interact with motor vehicle
 * systems.  The resale and/or use of products are at the purchaser's own risk
 * and his own responsibility. The examination of fitness for the intended use
 * is the sole responsibility of the Purchaser.
 *
 * The purchaser shall indemnify Bosch Sensortec from all third party claims,
 * including any claims for incidental, or consequential damages, arising from
 * any product use not covered by the parameters of the respective valid product
 * data sheet or not approved by Bosch Sensortec and reimburse Bosch Sensortec
 * for all costs in connection with such claims.
 *
 * The purchaser must monitor the market for the purchased products,
 * particularly with regard to product safety and inform Bosch Sensortec without
 * delay of all security relevant incidents.
 *
 * Engineering Samples are marked with an asterisk (*) or (e). Samples may vary
 * from the valid technical specifications of the product series. They are
 * therefore not intended or fit for resale to third parties or for use in end
 * products. Their sole purpose is internal client testing. The testing of an
 * engineering sample may in no way replace the testing of a product series.
 * Bosch Sensortec assumes no liability for the use of engineering samples. By
 * accepting the engineering samples, the Purchaser agrees to indemnify Bosch
 * Sensortec from all claims arising from the use of engineering samples.
 *
 * Special: This software module (hereinafter called "Software") and any
 * information on application-sheets (hereinafter called "Information") is
 * provided free of charge for the sole purpose to support your application
 * work. The Software and Information is subject to the following terms and
 * conditions:
 *
 * The Software is specifically designed for the exclusive use for Bosch
 * Sensortec products by personnel who have special experience and training. Do
 * not use this Software if you do not have the proper experience or training.
 *
 * This Software package is provided `` as is `` and without any expressed or
 * implied warranties, including without limitation, the implied warranties of
 * merchantability and fitness for a particular purpose.
 *
 * Bosch Sensortec and their representatives and agents deny any liability for
 * the functional impairment of this Software in terms of fitness, performance
 * and safety. Bosch Sensortec and their representatives and agents shall not be
 * liable for any direct or indirect damages or injury, except as otherwise
 * stipulated in mandatory applicable law.
 *
 * The Information provided is believed to be accurate and reliable. Bosch
 * Sensortec assumes no responsibility for the consequences of use of such
 * Information nor for any infringement of patents or other rights of third
 * parties which may result from its use.
 *
 * @file         channels.c
 * @date         "Tue Mar 12 17:11:32 2013 +0800"
 * @commit       "81910b2"
 *
 * @brief
 *
 * @detail
 *
 */



#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <stdlib.h>
#include <linux/ioctl.h>
#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>
#include <time.h>
#include <sys/time.h>

#define LOG_TAG_MODULE "<channels.c>"
#include "sensord.h"

struct channel g_list_ch[] = {
#if SPT_SENSOR_A
	{
		name: "ACCELERATION",
		type: SENSOR_TYPE_A,
		handle: SENSOR_HANDLE_ACCELERATION,

		cfg:
			{
				availability: AVAILABLE,
				calib_bg: 0,
				sp_name: "SP_FUSION",
#ifdef CFG_BYPASS_PROC_CHANNEL_A
				bypass_proc:1
#endif
			},

		init: channel_init_a,
		get_data: get_data_a,
	},
#endif


#if SPT_SENSOR_G
	{
		name: "GYROSCOPE",
		type: SENSOR_TYPE_G,
		handle: SENSOR_HANDLE_GYROSCOPE,

		cfg:
			{
#if CFG_SENSOR_G_EMU
				availability: VIRTUAL,
#else
				availability: AVAILABLE,
#endif
				calib_bg: 0,
				sp_name: "SP_FUSION"
			},

		init: channel_init_g,
		get_data: get_data_g,
	},
#endif


#if SPT_SENSOR_M
	{
		name: "MAGNETIC",
		type: SENSOR_TYPE_M,
		handle: SENSOR_HANDLE_MAGNETIC_FIELD,

		cfg:
			{
				availability: AVAILABLE,
				calib_bg: 0,
				sp_name: "SP_FUSION"
			},

		init: channel_init_m,
		get_data: get_data_m,
	},
#endif

#if SPT_SENSOR_O
	{
		name: "ORIENTATION",
		type: SENSOR_TYPE_O,
		handle: SENSOR_HANDLE_ORIENTATION,

		cfg:
			{
				availability: VIRTUAL,
				calib_bg: 0,
				sp_name: "SP_FUSION"
			},

		init: channel_init_o,
		get_data: get_data_o,
	},
#endif


#if SPT_SENSOR_P
	{
		name: "PRESSURE",
		type: SENSOR_TYPE_P,
		handle: SENSOR_HANDLE_PRESSURE,

		cfg:
			{
				availability: AVAILABLE,
				calib_bg: 0,
				sp_name: "SP_PRESSURE"
			},

		init: channel_init_p,
		get_data: get_data_p,
	},
#endif


#if SPT_SENSOR_VG
	{
		name: "GRAVITY",
		type: SENSOR_TYPE_VG,
		handle: SENSOR_HANDLE_GRAVITY,

		cfg:
			{
				availability: VIRTUAL,
				calib_bg: 0,
				sp_name: "SP_FUSION"
			},

		init: channel_init_vg,
		get_data: get_data_vg,
	},
#endif

#if SPT_SENSOR_VLA
	{
		name: "LINEAR_ACCELERATION",
		type: SENSOR_TYPE_VLA,
		handle: SENSOR_HANDLE_LINEAR_ACCELERATION,

		cfg:
			{
				availability: VIRTUAL,
				calib_bg: 0,
				sp_name: "SP_FUSION"
			},

		init: channel_init_vla,
		get_data: get_data_vla,
	},
#endif

#if SPT_SENSOR_VRV
	{
		name: "ROTATION_VECOTR",
		type: SENSOR_TYPE_VRV,
		handle: SENSOR_HANDLE_ROTATION_VECTOR,

		cfg:
			{
				availability: VIRTUAL,
				calib_bg: 0,
				sp_name: "SP_FUSION"
			},

		init: channel_init_vrv,
		get_data: get_data_vrv,
	},
#endif

#if SPT_SENSOR_GEST_FLIP
	{
		name: "GEST_FLIP",
		type: SENSOR_TYPE_GEST_FLIP,
		handle: SENSOR_HANDLE_GEST_FLIP,

		cfg:
			{
				availability: VIRTUAL,
				calib_bg: 0,
				sp_name: "SP_FUSION"
			},

		init: channel_init_gest_flip,
		get_data: get_data_gest_flip,
	},
#endif
};


int channel_get_num()
{
	return ARRAY_SIZE(g_list_ch);
}

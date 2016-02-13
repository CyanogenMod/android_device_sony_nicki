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
 * @file         sensor_cfg.c
 * @date         "Fri Apr 12 16:09:39 2013 +0800"
 * @commit       "42c61cb"
 *
 * @brief
 *
 * @detail
 *
 */



#include <stdio.h>
#include <errno.h>

#define LOG_TAG_MODULE "<sensor_cfg>"
#include "sensord.h"

#define DEFAULT_INTERVAL 60	 /* in ms */


int g_calib_bg;

int g_interval_calib_bg = 2000;


int g_calib_bg_done_thres = SENSOR_ACCURACY_HIGH;


extern int g_place_a;	/* placement of acc sensor */
extern int g_place_m;	/* placement of mag sensor */
extern int g_place_g;	/* placement of mag sensor */
extern int g_accuracy_thres_m;
extern int g_filter_mode_o;


#ifdef CFG_SET_AXIS_FROM_FILE
static void set_cfg_axis()
{
	int err = 0;
	int fd;
	char magic;
	int count;
	int place;
	char buf[64] = "";
	char *pline = NULL;     /* start of a line */
	char *pline_end = NULL;
	int i;

	fd = open(SENSOR_CFG_FILE_SYS_AXIS, O_RDONLY);

	if (-1 == fd) {
		PERR("axis config file does not exist, assuming no remap is needed");
		err = -EIO;
		goto exit_err_clean;
	} else {
		/* bytes exceeding 63 will be disgarded */
		count = read(fd, buf, ARRAY_SIZE(buf) - 1);
		if (0 < count) {
			buf[count] = '\0';
		}

		for (i = 0; i < count; i++) {
			if ('\r' == buf[i]) {
				buf[i] = '\n';
			}
		}

		pline_end = buf - 1;
		while (NULL != pline_end) {
			pline = pline_end + 1;

			pline_end = strchr(pline, '\n');
			if (NULL != pline_end) {
				*pline_end = '\0';
			}

			if ('\0' == pline[0]) {
				continue;
			}

			count = sscanf(pline, "place_%c=%11d", &magic, &place);
			PDEBUG("count: %d magic: %c place: %d",
						count, magic, place);

			if (2 != count) {
				err = -EINVAL;
				PWARN("invalid line:%s in config file: %s",
				      pline, SENSOR_CFG_FILE_SYS_AXIS);
				goto exit_err_clean;
			}

			PINFO("g_place_%c: %d", magic, place);
			switch(magic) {
			case SENSOR_MAGIC_A:
#if SPT_SENSOR_HW_A
				g_place_a = place;
#endif
				break;
			case SENSOR_MAGIC_M:
#if SPT_SENSOR_HW_M
				g_place_m = place;
#endif
				break;
			case SENSOR_MAGIC_G:
#if SPT_SENSOR_HW_G
				g_place_g = place;
#endif
				break;
			default:
				err = -EINVAL;
				PWARN("Unknown sensor");
				goto exit_err_clean;
				break;
			}
		}
	}

exit_err_clean:
	if (err) {
		PWARN("error reading from config file: %s, using default",
				SENSOR_CFG_FILE_SYS_AXIS);
	}

	if (-1 != fd) {
		close(fd);
	}
}
#endif


static void set_cfg_misc()
{
	struct channel_cfg cfg;

	cfg.no_delay = 0;
#if SPT_SENSOR_A
	channel_get_cfg(SENSOR_HANDLE_ACCELERATION, &cfg);
	cfg.interval_min = CFG_DELAY_A_MIN;
	cfg.interval_max = CFG_DELAY_A_MAX;

	cfg.dep_hw = CFG_HW_DEP_A;
	channel_set_cfg(SENSOR_HANDLE_ACCELERATION, &cfg);
#endif

#if SPT_SENSOR_G
	channel_get_cfg(SENSOR_HANDLE_GYROSCOPE, &cfg);
	cfg.interval_min = CFG_DELAY_G_MIN;
	cfg.interval_max = CFG_DELAY_G_MAX;

	cfg.dep_hw = CFG_HW_DEP_G;
	channel_set_cfg(SENSOR_HANDLE_GYROSCOPE, &cfg);
#endif

#if SPT_SENSOR_M
	channel_get_cfg(SENSOR_HANDLE_MAGNETIC_FIELD, &cfg);
	cfg.interval_min = CFG_DELAY_M_MIN;
	cfg.interval_max = CFG_DELAY_M_MAX;

	cfg.dep_hw = CFG_HW_DEP_M;
	channel_set_cfg(SENSOR_HANDLE_MAGNETIC_FIELD, &cfg);
#endif

#if SPT_SENSOR_O
	channel_get_cfg(SENSOR_HANDLE_ORIENTATION, &cfg);
	cfg.interval_min = CFG_DELAY_O_MIN;
	cfg.interval_max = CFG_DELAY_O_MAX;

	cfg.dep_hw = CFG_HW_DEP_O;
	channel_set_cfg(SENSOR_HANDLE_ORIENTATION, &cfg);
#endif

#if SPT_SENSOR_P
	channel_get_cfg(SENSOR_HANDLE_PRESSURE, &cfg);
	cfg.interval_min = CFG_DELAY_P_MIN;
	cfg.interval_max = CFG_DELAY_P_MAX;

	cfg.dep_hw = CFG_HW_DEP_P;
	channel_set_cfg(SENSOR_HANDLE_PRESSURE, &cfg);
#endif


#if SPT_SENSOR_T
	channel_get_cfg(SENSOR_HANDLE_TEMPERATURE, &cfg);
	cfg.interval_min = CFG_DELAY_T_MIN;
	cfg.interval_max = CFG_DELAY_T_MAX;

	cfg.dep_hw = CFG_HW_DEP_T;
	channel_set_cfg(SENSOR_HANDLE_TEMPERATURE, &cfg);
#endif

#if SPT_SENSOR_VG
	channel_get_cfg(SENSOR_HANDLE_GRAVITY, &cfg);
	cfg.interval_min = CFG_DELAY_VG_MIN;
	cfg.interval_max = CFG_DELAY_VG_MAX;

	cfg.dep_hw = CFG_HW_DEP_VG;
	channel_set_cfg(SENSOR_HANDLE_GRAVITY, &cfg);
#endif

#if SPT_SENSOR_VLA
	channel_get_cfg(SENSOR_HANDLE_LINEAR_ACCELERATION, &cfg);
	cfg.interval_min = CFG_DELAY_VLA_MIN;
	cfg.interval_max = CFG_DELAY_VLA_MAX;

	cfg.dep_hw = CFG_HW_DEP_VLA;
	channel_set_cfg(SENSOR_HANDLE_LINEAR_ACCELERATION, &cfg);
#endif

#if SPT_SENSOR_VRV
	channel_get_cfg(SENSOR_HANDLE_ROTATION_VECTOR, &cfg);
	cfg.interval_min = CFG_DELAY_VRV_MIN;
	cfg.interval_max = CFG_DELAY_VRV_MAX;

	cfg.dep_hw = CFG_HW_DEP_VRV;
	channel_set_cfg(SENSOR_HANDLE_ROTATION_VECTOR, &cfg);
#endif
}


void sensor_cfg_init()
{
#ifdef CFG_SET_AXIS_FROM_FILE
	set_cfg_axis();
#endif
	set_cfg_misc();
}


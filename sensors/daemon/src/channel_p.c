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
 * @file         channel_p.c
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


#define LOG_TAG_MODULE "<channel_p>"
#include "sensord.h"

#if SPT_SENSOR_P
#define SYSFS_PATH_PRESSURE_VALUE "/sys/class/input/input3/pressure0_input"

static int g_enable_p = 0;

static int g_fd_value_p = -1;

static const char *g_bmp_names[] = {
	"bmp085",
	"bmpx85",
	"bmp18x",
	NULL
};

 /*
  * @Description:
  * sample code for bmpx85
 */
int get_data_p(void *pbuf, int n)
{
	struct exchange *pmsg = (struct exchange *)pbuf;
	int value = 0;
	int err;

	/* fill pmsg->data.pressure with real value */
	err = txt_file_read_int(g_fd_value_p, &value, 1);
	if (err) {
		PERR("error reading value of pressure");
		value = 0;
	}
	pmsg->data.pressure = value / 100.0f;
	PDEBUG("value_p: %d", value);

	return 1;
}


int channel_init_p(struct channel *ch)
{
	int err = 0;
	return err;
}


static int on_ch_enabled_p(struct channel * ch, int enable)
{
	g_enable_p = enable;
	return 0;
}


static int on_ch_interval_changed_p(struct channel * ch, int interval)
{
	ch->interval = interval;
	return 0;
}


static void get_curr_hw_dep_p(hw_dep_set_t * hw_dep)
{
	*hw_dep = 0;
	if (g_enable_p) {
		*hw_dep = (1 << SENSOR_HW_TYPE_P);
	}
}


static int sp_init_p(struct sensor_provider *sp)
{
	int err = 0;
	int num = -1;
	int i;
	const char *name;
	char path[128] = "";

	i = 0;
	while (NULL != (name = g_bmp_names[i++])) {
		num = sysfs_get_input_dev_num(name);
		if (-1 != num) {
			break;
		}
	}

	if (-1 != num) {
		sprintf(path, "/sys/class/input/input%d/pressure0_input", num);
		g_fd_value_p = open(path, O_RDONLY);
	}

	if (-1 == g_fd_value_p) {
		PERR("cannot find pressure sensor device");
		err = -ENODEV;
	}

	return err;
}


struct sensor_provider g_sp_pressure = {
	name:"SP_PRESSURE",
	sensors: (1 << SENSOR_TYPE_P),
	on_ch_enabled:on_ch_enabled_p,
	on_ch_interval_changed:on_ch_interval_changed_p,
	get_curr_hw_dep:get_curr_hw_dep_p,
	init:sp_init_p,
	exit:NULL,
	re:
	{
		op_blk:0,
		func:re_proc
	}
};
#endif

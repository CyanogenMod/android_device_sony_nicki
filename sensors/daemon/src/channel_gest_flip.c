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
 * @file         channel_gest_flip.c
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


#define LOG_TAG_MODULE "<channel_gest_flip>"
#include "sensord.h"

#if SPT_SENSOR_GEST_FLIP
static int data_filter_gest_flip(struct data_filter *df,
		const void *in, int len_in, void *out, int len_out)
{
	int ret = 0;
	const sensor_data_t *din = (const sensor_data_t *)in;
	sensor_data_t *dout = (sensor_data_t *)out;
	int gest_flip;
	int i;
	
	UNUSED_PARAM(df);
	len_out = MIN(len_in, len_out);
	ret = 0;
	for (i = 0; i < len_out; i++) {
		gest_flip = din[i].data[0];
		if ((gest_flip > SENSOR_GEST_FLIP_VAL_UNKNOWN) && 
			(gest_flip < SENSOR_GEST_FLIP_VAL_END)) {
			memcpy(dout + ret, din + i, sizeof(dout[0]));
			ret++;
		} else {
			PWARN("invalid gest value: %d filtered out",
					gest_flip);
		}
	}
	
	return ret;
}


static struct data_filter s_data_filter_gest_flip = {
	.filter         = data_filter_gest_flip,
};


int get_data_gest_flip(void *pbuf, int n)
{
	struct exchange *pmsg = (struct exchange *)pbuf;
	struct exchange msg_tmp;
	int ret = 0;

	UNUSED_PARAM(n);
	memcpy(&msg_tmp, pmsg, sizeof(msg_tmp));
	ret = algo_get_proc_data_gest_flip(&msg_tmp.data);
	
	if (ret > 0) {
		ret = s_data_filter_gest_flip.filter(&s_data_filter_gest_flip,
				&msg_tmp.data, 1, &pmsg->data, 1);
	}

	return ret;
}


int channel_init_gest_flip(struct channel *ch)
{
	ch->cfg.interval_min = CFG_DELAY_GEST_FLIP_MIN;
	ch->cfg.interval_max = CFG_DELAY_GEST_FLIP_MAX;
	ch->cfg.no_delay = 1;

	return 0;
}
#endif

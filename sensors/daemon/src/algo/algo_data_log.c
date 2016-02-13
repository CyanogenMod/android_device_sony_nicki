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
 * @file         algo_data_log.c
 * @date         "Tue Mar 12 17:11:32 2013 +0800"
 * @commit       "81910b2"
 *
 * @brief
 *
 * @detail
 *
 */



#define LOG_TAG_MODULE "<algo_data_log>"
#include "sensord.h"

#ifdef CFG_USE_DATA_LOG
static int g_fd_log_data_a = -1;
static int g_fd_log_data_m = -1;
static int g_fd_log_data_o = -1;

void algo_log_data_init()
{
	char filename_log_data[64];

	PINFO("function entry");

	sprintf(filename_log_data,
			PATH_DIR_SENSOR_STORAGE "/sensor_data_a.log");
	g_fd_log_data_a = open(filename_log_data, O_RDWR | O_CREAT | O_TRUNC,
			S_IRUSR | S_IWUSR |
			S_IRGRP | S_IWGRP |
			S_IROTH | S_IWOTH);
	if (-1 == g_fd_log_data_a) {
		PERR("cannot log data for acc");
	}

	sprintf(filename_log_data,
			PATH_DIR_SENSOR_STORAGE "/sensor_data_m.log");
	g_fd_log_data_m = open(filename_log_data, O_RDWR | O_CREAT | O_TRUNC,
			S_IRUSR | S_IWUSR |
			S_IRGRP | S_IWGRP |
			S_IROTH | S_IWOTH);
	if (-1 == g_fd_log_data_m) {
		PERR("cannot log data for mag");
	}

	sprintf(filename_log_data,
			PATH_DIR_SENSOR_STORAGE "/sensor_data_o.log");
	g_fd_log_data_o = open(filename_log_data, O_RDWR | O_CREAT | O_TRUNC,
			S_IRUSR | S_IWUSR |
			S_IRGRP | S_IWGRP |
			S_IROTH | S_IWOTH);
	if (-1 == g_fd_log_data_o) {
		PERR("cannot log data for ori");
	}
}


void algo_log_data_a(char magic, int time)
{
	int fd = g_fd_log_data_a;
	dataxyz_t data[3];
	BS_U8 status;
	char buf[128] = "";
	int ret = 0;

	if (-1 == fd) {
		return;
	}

	bsc_get_accrawdata_lsb(data + 0);
	bsc_get_acccordata_lsb(data + 1);
	bsc_get_accfiltdata_lsb(data + 2);
	bsc_get_accdatastatus(&status);

	ret = snprintf(buf, ARRAY_SIZE(buf) - 1,
			"%c,%8d, %4d,%4d,%4d, %4d,%4d,%4d, %4d,%4d,%4d, %4d\n",
			magic, time,
			data[0].x, data[0].y, data[0].z,
			data[1].x, data[1].y, data[1].z,
			data[2].x, data[2].y, data[2].z,
			status);

	if (ret > 0) {
		write(fd, buf, ret);
	}
}

#define SCALE_LSB2UT (1/4.0f)

void algo_log_data_m(char magic, int time)
{
	int fd = g_fd_log_data_m;
	dataxyz_t data[3];
	BS_U8 status;
	char buf[256] = "";
	int ret;

	if (-1 == fd) {
		return;
	}

	bsc_get_magrawdata_lsb(data + 0);
	bsc_get_magcordata_lsb(data + 1);
	bsc_get_magfiltdata_lsb(data + 2);
	bsc_get_magdatastatus(&status);

	ret = snprintf(buf, ARRAY_SIZE(buf) - 1,
			"%c,%8d, "
			"%10.6f,%10.6f,%10.6f, "
			"%10.6f,%10.6f,%10.6f, "
			"%10.6f,%10.6f,%10.6f, "
			"%2d\n",
			magic, time,
			data[0].x * SCALE_LSB2UT,
			data[0].y * SCALE_LSB2UT,
			data[0].z * SCALE_LSB2UT,
			data[1].x * SCALE_LSB2UT,
			data[1].y * SCALE_LSB2UT,
			data[1].z * SCALE_LSB2UT,
			data[2].x * SCALE_LSB2UT,
			data[2].y * SCALE_LSB2UT,
			data[2].z * SCALE_LSB2UT,
			status);

	if (ret > 0) {
		write(fd, buf, ret);
	}
}


void algo_log_data_o(char magic, int time)
{
	int fd = g_fd_log_data_o;
	ts_orientEuler data[1];
	BS_U8 status;
	char buf[128] = "";
	int ret;

	if (-1 == fd) {
		return;
	}

	bsc_get_orientdata_feuler(data + 0);
	bsc_get_orientdata_status(&status);

	ret = snprintf(buf, ARRAY_SIZE(buf) - 1,
			"%c,%8d, %10.6f,%10.6f,%10.6f, %2d\n",
			magic, time,
			data[0].h * RADIAN2DEGREE / AXIS_RESOLUTION_FACTOR,
			data[0].p * RADIAN2DEGREE / AXIS_RESOLUTION_FACTOR,
			data[0].r * RADIAN2DEGREE / AXIS_RESOLUTION_FACTOR,
			status);

	if (ret > 0) {
		write(fd, buf, ret);
	}
}


void algo_log_data_mgo(char magic, int time)
{
	int fd = g_fd_log_data_o;
	ts_orientQuat data[1];
	BS_U8 status;
	char buf[128] = "";
	int ret;

	if (-1 == fd) {
		return;
	}

	bsc_get_m4gdata_quat(data + 0);
	bsc_get_m4gdatastatus(&status);

	ret = snprintf(buf, ARRAY_SIZE(buf) - 1,
			"%c,%8d, %4d,%4d,%4d,%4d, %4d\n",
			magic, time,
			data[0].w, data[0].x, data[0].y, data[0].z, status);

	if (ret > 0) {
		write (fd, buf, ret);
	}
}


#endif

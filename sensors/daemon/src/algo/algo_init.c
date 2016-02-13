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
 * @file         algo_init.c
 * @date         "Mon Mar 18 11:02:35 2013 +0800"
 * @commit       "c68b71a"
 *
 * @brief
 *
 * @detail
 *
 */



#define LOG_TAG_MODULE "<algo_init_bst>"
#include "sensord.h"

static int g_acc_dyndistdect = -1;
static int g_filter_mode_o = ALGO_CUST_ORI_FILT_MODE;
int g_ori_thres_m = ALGO_CUST_ORI_NOI_THRES_M;

int g_accuracy_thres_m = ALGO_CUST_M_CALIB_ACCURACY_THRES;
int g_accuracy_thres_m_init = ALGO_CUST_M_CALIB_ACCURACY_THRES_INIT;


int g_gest_flip_dect_time = -1;

int g_fd_profile_calib_a = -1;
struct calib_profile g_profile_calib_a;
int g_fd_profile_calib_m = -1;
struct calib_profile g_profile_calib_m;


static void restore_sensor_profile(char magic, void *profile, int *fd)
{
	int err = 0;
	int size;
	unsigned char tmp;
	unsigned char ver = 0;
	char *filename;
	int fd_tmp = -1;

	struct calib_profile *cp = (struct calib_profile *)profile;

	err = 0;
	cp->status = 0;
	switch (magic) {
	case SENSOR_MAGIC_A:
		filename = SENSOR_CFG_FILE_SYS_PROFILE_CALIB_A;
		break;
	case SENSOR_MAGIC_M:
		filename = SENSOR_CFG_FILE_SYS_PROFILE_CALIB_M;
		break;
	case SENSOR_MAGIC_G:
		filename = SENSOR_CFG_FILE_SYS_PROFILE_CALIB_G;
		break;
	default:
		PWARN("unknown sensor");
		err = -EINVAL;
		return;
	}

	fd_tmp = open(filename, O_RDWR);
	if (-1 == fd_tmp) {
		PERR("file: %s does not exist, will be created", filename);
		fd_tmp = open(filename, O_RDWR | O_CREAT,
				S_IRUSR | S_IWUSR |
				S_IRGRP | S_IWGRP |
				S_IROTH | S_IWOTH);
		if (-1 == fd_tmp) {
			PERR("fail to create file: %s", filename);
			err = -EIO;
			*fd = -1;
			return;
		}
	}

	if (-1 != fd_tmp) {
		size = read(fd_tmp, &tmp, 1);
		if (!((1 == size) && (tmp == magic))) {
			err = -EIO;
			PWARN("invalid magic in file: %s", filename);
			lseek(fd_tmp, 0, SEEK_END);
			goto exit_invalid_content;
		}

		size = read(fd_tmp, &ver, 1);
		if (!((1 == size) && (ALGO_CALIB_PROFILE_VER == ver))) {
			err = -EIO;
			PWARN("invalid version in file: %s", filename);
			lseek(fd_tmp, 0, SEEK_END);
			goto exit_invalid_content;
		}

		size = read(fd_tmp, &tmp, 1);
		if (!((1 == size) && (sizeof(cp->profile) == tmp))) {
			err = -EIO;
			PWARN("invalid size in file: %s", filename);
			lseek(fd_tmp, 0, SEEK_END);
			goto exit_invalid_content;
		}

		size = read(fd_tmp, &cp->profile, sizeof(cp->profile));
		if ((int)sizeof(cp->profile) == size) {
			cp->status = 1;
		} else {
			PWARN("invalid content in file: %s",
					filename);
			err = -EIO;
			goto exit_invalid_content;
		}

	}

exit_invalid_content:
	if (err) {
		cp->status = 0;
	} else {
		PINFO("profile of %c applied", magic);
	}

	*fd = fd_tmp;
}


BS_U8 hc_acc_read_xyzdata_fr(BS_S16 *px, BS_S16 *py, BS_S16 *pz)
{
	UNUSED_PARAM(px);
	UNUSED_PARAM(py);
	UNUSED_PARAM(pz);
	return 0;
}


static void algo_load_cust_param_gest_flip()
{
#if SPT_SENSOR_GEST_FLIP && (defined ALGO_SPT_GEST_FLIP)
	int dect_time_ms = ALGO_CUST_GEST_FLIP_DECT_TIME;
	float dect_angle_up = ALGO_CUST_GEST_FLIP_ANGLE_RANGE_UP;
	float dect_angle_down = ALGO_CUST_GEST_FLIP_ANGLE_RANGE_DOWN;
	char *filename = SENSOR_CFG_FILE_ALGO_GEST_FLIP;
	int fd;
	char buf[64] = "";
	int ret = -1;

	fd = open(filename, O_RDONLY);
	if (-1 != fd) {
		ret = read(fd, buf, sizeof(buf) - 1);
		close(fd);
		if (ret >= 0) {
			PINFO("cfg of gest: %s", buf);
			ret = sscanf(buf, "%10f,%10f,%11d",
					&dect_angle_up,
					&dect_angle_down,
					&dect_time_ms);
			if (ret >= 3) {
				PINFO("cfg for gest: %f,%f,%d",
					dect_angle_up,
					dect_angle_down,
					dect_time_ms);
			} else {
				PWARN("invalid cfg for gest");
			}
		}
	} else {
		PERR("cfg file for gest sensor: %s not found", filename);
		return;
	}

	if ((dect_angle_up > 0) && (dect_angle_down > 0)) {
		bsc_set_flipgesture_angle((BS_U8)dect_angle_down,
				(BS_U8)dect_angle_up);
	}

	g_gest_flip_dect_time = dect_time_ms;
	if (dect_time_ms > 0) {
		bsc_set_flipgesture_detecttime(dect_time_ms);
	}
#endif
}


static void algo_load_cust_param()
{
	char *filename = SENSOR_CFG_FILE_ALGO;

	int fd;
	char buf[64] = "";
	int ret;

	int filt_mode;
	int p[4];
	float p4;

	fd = open(filename, O_RDONLY);
	if (-1 != fd) {
		ret = read(fd, buf, sizeof(buf) - 1);
		close(fd);
		if (ret >= 0) {
			ret = sscanf(buf, "%11d,%11d,%11d,%11d,%11d,%10f",
					&p[0],
					&p[1],
					&p[2],
					&p[3],
					&filt_mode,
					&p4);
			if (6 <= ret) {
				PINFO("config of param: %d %d %d %d %d %f",
						p[0],
						p[1],
						p[2],
						p[3],
						filt_mode,
						p4);

				g_acc_dyndistdect = p[0];
				g_filter_mode_o = filt_mode;
				g_ori_thres_m = p[2];
				g_accuracy_thres_m = p[3];
			} else {
				PWARN("invalid content: %s", buf);
			}
		} else {
			PERR("read error");
		}
	} else {
		PERR("no cfg file for algo");
		return;
	}
}

static void algo_apply_si_matrix()
{
#ifdef CFG_USE_PREDEFINED_SI_CORRECTION
	int err = 0;
	int fd;
	char buf[256] = "";
	ts_magSoftIronSensM matrix = {1, 0, 0, 0, 1, 0, 0, 0, 1};

	int matrix_available = 0;

	fd = open(SENSOR_CFG_FILE_SOFTIRON_MATRIX, O_RDONLY);

	if (-1 != fd) {
		err = read(fd, buf, sizeof(buf) - 1);
		close(fd);
		if (err >= 0) {
			memset(&matrix, 0, sizeof(matrix));
			err = sscanf(buf,
					"%10f,%10f,%10f,"
					"%10f,%10f,%10f,"
					"%10f,%10f,%10f",
					&matrix.xx, &matrix.xy, &matrix.xz,
					&matrix.yx, &matrix.yy, &matrix.yz,
					&matrix.zx, &matrix.zy, &matrix.zz);
			if (9 == err) {
				matrix_available = 1;
			} else {
				PWARN("invalid content of softiron matrix: %s",
						buf);
			}
		} else {
			PERR("read error");
		}
	} else {
		PERR("manual softiron matrix not provided");
	}

#if ALGO_CUST_USE_PREDEFINED_SIC_MATRIX
	if (!matrix_available) {
		matrix.xx = ALGO_CUST_SI_MATRIX_XX;
		matrix.xy = ALGO_CUST_SI_MATRIX_XY;
		matrix.xz = ALGO_CUST_SI_MATRIX_XZ;
		matrix.yx = ALGO_CUST_SI_MATRIX_YX;
		matrix.yy = ALGO_CUST_SI_MATRIX_YY;
		matrix.yz = ALGO_CUST_SI_MATRIX_YZ;
		matrix.zx = ALGO_CUST_SI_MATRIX_ZX;
		matrix.zy = ALGO_CUST_SI_MATRIX_ZY;
		matrix.zz = ALGO_CUST_SI_MATRIX_ZZ;
		matrix_available = 1;
	}
#endif

	if (matrix_available) {
		bsc_set_SoftIronCorrectionMode(1);
		bsc_set_SoftIronCorrectionMatrix(matrix);
		PINFO("softiron matrix applied:");
		PINFO("\n%f,%f,%f,\n%f,%f,%f,\n%f,%f,%f",
				matrix.xx, matrix.xy, matrix.xz,
				matrix.yx, matrix.yy, matrix.yz,
				matrix.zx, matrix.zy, matrix.zz);
	}
#endif
}


static int algo_init_cust()
{
	int err = 0;

	algo_load_cust_param();

	if (-1 != g_acc_dyndistdect) {
		bsc_set_accDyn4DistDetmode(!!g_acc_dyndistdect);
	}

	if (-1 != g_accuracy_thres_m) {
		bsc_set_magcalib_accuracy_threshold(g_accuracy_thres_m);
	}
	if (-1 != g_accuracy_thres_m_init) {
		bsc_set_magcalib_accuracy_threshold_initial(g_accuracy_thres_m_init);
	}

	if (-1 != g_filter_mode_o) {
		bsc_set_orientfiltermode(g_filter_mode_o);
	}

	if ((ALGO_CUST_ORI_FILT_COEF_A >= 0)
			&& (ALGO_CUST_ORI_FILT_DYNA_A >= 0)) {
		bsc_set_orientAccFilterParam(ALGO_CUST_ORI_FILT_COEF_A,
				ALGO_CUST_ORI_FILT_DYNA_A);
	}


	if ((ALGO_CUST_ORI_FILT_COEF_M >= 0)
			&& (ALGO_CUST_ORI_FILT_DYNA_M >= 0)) {
		bsc_set_orientMagFilterParam(ALGO_CUST_ORI_FILT_COEF_M,
				ALGO_CUST_ORI_FILT_DYNA_M);
	}

	algo_apply_si_matrix();

	algo_load_cust_param_gest_flip();
#ifdef CFG_ALGO_USE_ADV_PRE_FILTER
#if ALGO_SPT_ADV_PRE_FILTER
	bsc_accAdvPreFilterMode(1);
	bsc_set_accAdvPreFilterParam(ALGO_CUST_A_ADV_FILT_COEF,
			ALGO_CUST_A_ADV_FILT_NL);

	bsc_magAdvPreFilterMode(1);
	bsc_set_magAdvPreFilterParam(ALGO_CUST_M_ADV_FILT_COEF,
			ALGO_CUST_M_ADV_FILT_NL);
#endif
#endif

	bsc_set_orientopmode(BSC_ORIENTOPMODE_REGULAR);
	bsc_set_linaccopmode(BSC_LINACCOPMODE_SLEEP);
	bsc_set_m4gopmode(BSC_M4GOPMODE_SLEEP);

	return err;
}


int algo_init_bst()
{
	int err = 0;

	/* <algorithm_stack_initialization */
	/* </algorithm_stack_initialization */

	/* <algorithm_core_init> */
	err = algo_bst_set_hwid(HW_ID_A, HW_ID_M, 0);
	if (err) {
		PWARN("err setting hw id: %d", err);
		return err;
	}

	algo_bst_init_stk(NULL);
	/* </algorithm_core_init> */

	/* <axis_remap_config> */
	bsc_set_accremapparam(0, 0);
	bsc_set_magremapparam(0, 0);
	/* </axis_remap_config> */

	memset(&g_profile_calib_a, 0, sizeof(g_profile_calib_a));
	restore_sensor_profile(SENSOR_MAGIC_A,
			&g_profile_calib_a,
			&g_fd_profile_calib_a);
	if (g_profile_calib_a.status) {
		bsc_set_acccalibprofile(&g_profile_calib_a.profile);
	}

	memset(&g_profile_calib_m, 0, sizeof(g_profile_calib_m));
	restore_sensor_profile(SENSOR_MAGIC_M,
			&g_profile_calib_m,
			&g_fd_profile_calib_m);
	if (g_profile_calib_m.status) {
		bsc_set_magcalibprofile(&g_profile_calib_m.profile);
	}

	err = algo_init_cust();

	algo_adapter_init();

	return err;
}

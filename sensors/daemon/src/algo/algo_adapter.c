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
 * @file         algo_adapter.c
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

#define LOG_TAG_MODULE "<algo_adapter_bst>"
#include "sensord.h"


#define ALGO_MOD_ENABLE(id, enable)\
	do {\
		struct algo_module *mod;\
		mod = algo_get_mod(g_algo_modules, ARRAY_SIZE(g_algo_modules), id);\
		if (NULL != mod) {\
			algo_mod_ref_change(mod, enable);\
		}\
	} while (0)


#define ALGO_MOD_IS_ENABLED(id, mode)\
	do {\
		struct algo_module *mod;\
		mod = algo_get_mod(g_algo_modules, ARRAY_SIZE(g_algo_modules), id);\
		if (NULL != mod) {\
			(mode) = mod->op_mode;\
		} else {\
			(mode) = 0;\
		}\
	} while (0)


static BS_U16 g_tab_hz[ALGO_NUM_DR];

extern struct algo_product *fusion_get_product(uint32_t type);
extern void fusion_arbitrate_dr();


static const BS_U16 g_tab_intvl[ALGO_NUM_DR] = {1000, 200, 100, 50, 40, 20, 10, 5};
static const BS_U8 g_tab_ref_bw[ALGO_NUM_DR] = {0, 0, 0, 1, 1, 2, 3, 4};

static dataxyz_t g_data_a;
static dataxyz_t g_data_m;

static BS_S32 g_last_ts_a = -200;
static BS_S32 g_last_ts_m = -200;

static struct sensor_hw_a *g_p_hw_a = NULL;
static struct sensor_hw_m *g_p_hw_m = NULL;

static hw_dep_set_t g_active_hws = 0;

extern int g_ori_thres_m;

#define HW_IS_ACTIVE(hws, id) (hws & (1 << SENSOR_HW_TYPE_##id))

static int g_last_value_gest_flip = -1;
extern int g_gest_flip_dect_time;

static int g_ref_hw_a = 0;
static int g_ref_hw_m = 0;
static pthread_mutex_t g_lock_ref_hw;

static void algo_enable_a(struct algo_module *mod, int enable)
{
	if (enable) {
		bsc_set_accopmode(ALGO_A_OPMODE_REGULAR);
		bsc_set_acccalibmode(2);
		algo_load_calib_profile(SENSOR_MAGIC_A);
	} else {
		algo_save_calib_profile(SENSOR_MAGIC_A);
		bsc_set_accopmode(ALGO_A_OPMODE_SLEEP);
		bsc_set_acccalibmode(0);
	}

	mod->op_mode = enable;
}


static void algo_enable_m(struct algo_module *mod, int enable)
{
	if (enable) {
		bsc_set_magopmode(ALGO_M_OPMODE_REGULAR);
		bsc_set_magcalibmode(2);
		algo_load_calib_profile(SENSOR_MAGIC_M);
	} else {
		algo_save_calib_profile(SENSOR_MAGIC_M);
		bsc_set_magopmode(ALGO_M_OPMODE_SLEEP);
		bsc_set_magcalibmode(0);
	}

	mod->op_mode = enable;
}


static void algo_enable_o(struct algo_module *mod, int enable)
{
	if (!enable) {
		bsc_set_orientopmode(BSC_ORIENTOPMODE_SLEEP);
	}
	mod->op_mode = enable;
}


#if (SPT_SENSOR_VLA || SPT_SENSOR_VG)
static void algo_enable_vla(struct algo_module *mod, int enable)
{
	if (enable) {
		bsc_set_linaccopmode(BSC_LINACCOPMODE_REGULAR);
	} else {
		bsc_set_linaccopmode(BSC_LINACCOPMODE_SLEEP);
	}

	mod->op_mode = enable;
}
#endif


#if ((SPT_SENSOR_G && CFG_SENSOR_G_EMU) || SPT_SENSOR_VRV)
static void algo_enable_m4g(struct algo_module *mod, int enable)
{
	if (!enable) {
		bsc_set_m4gopmode(BSC_M4GOPMODE_SLEEP);
	}
	mod->op_mode = enable;
}
#endif


#if SPT_SENSOR_GEST_FLIP && (defined ALGO_SPT_GEST_FLIP)
static void algo_enable_gest_flip(struct algo_module *mod, int enable)
{
	if (enable) {
		bsc_set_flipgesture_opmode(BSC_FLIPGESTUREOPMODE_REGULAR);
	} else {
		bsc_set_flipgesture_opmode(BSC_FLIPGESTUREOPMODE_SLEEP);
	}
	mod->op_mode = enable;
}
#endif


static struct algo_module g_algo_modules[] = {
	{
		name: "ACC",
		id: ALGO_MODULE_ID_ACC,
		enable: algo_enable_a,
	},

	{
		name: "MAG",
		id: ALGO_MODULE_ID_MAG,
		enable: algo_enable_m,
	},

	{
		name: "CMP",
		id: ALGO_MODULE_ID_CMP,
		enable: algo_enable_o,
	},

#if (SPT_SENSOR_VG || SPT_SENSOR_VLA)
	{
		name: "VLA",
		id: ALGO_MODULE_ID_VLA,
		enable: algo_enable_vla,
	},
#endif

#if ((SPT_SENSOR_G && CFG_SENSOR_G_EMU) || (SPT_SENSOR_VRV))
	{
		name: "M4G",
		id: ALGO_MODULE_ID_M4G,
		enable: algo_enable_m4g,
	},
#endif

#if SPT_SENSOR_GEST_FLIP && (defined ALGO_SPT_GEST_FLIP)
	{
		name: "GEST_FLIP",
		id: ALGO_MODULE_ID_GEST_FLIP,
		enable: algo_enable_gest_flip,
	},
#endif
};


static void algo_products_init()
{
	/* min and max dr already pre-initilized in fusion_init() */
	ALGO_PRODUCT_SET_DR_MIN(SENSOR_TYPE_A, acc, ALGO_DR_5HZ);
	ALGO_PRODUCT_SET_DR_MAX(SENSOR_TYPE_A, acc, ALGO_DR_100HZ);

	ALGO_PRODUCT_SET_DR_MIN(SENSOR_TYPE_M, mag, ALGO_DR_10HZ);
	ALGO_PRODUCT_SET_DR_MAX(SENSOR_TYPE_M, mag, ALGO_DR_10HZ);

	ALGO_PRODUCT_SET_DR_MIN(SENSOR_TYPE_G, acc, ALGO_DR_50HZ);
	ALGO_PRODUCT_SET_DR_MAX(SENSOR_TYPE_G, acc, ALGO_DR_50HZ);
	ALGO_PRODUCT_SET_DR_MIN(SENSOR_TYPE_G, mag, ALGO_DR_50HZ);
	ALGO_PRODUCT_SET_DR_MAX(SENSOR_TYPE_G, mag, ALGO_DR_50HZ);

	ALGO_PRODUCT_SET_DR_MIN(SENSOR_TYPE_O, acc, ALGO_DR_10HZ);
	ALGO_PRODUCT_SET_DR_MAX(SENSOR_TYPE_O, acc, ALGO_DR_50HZ);
	ALGO_PRODUCT_SET_DR_MIN(SENSOR_TYPE_O, mag, ALGO_DR_10HZ);
	ALGO_PRODUCT_SET_DR_MAX(SENSOR_TYPE_O, mag, ALGO_DR_10HZ);

	ALGO_PRODUCT_SET_DR_MIN(SENSOR_TYPE_VG, acc, ALGO_DR_10HZ);
	ALGO_PRODUCT_SET_DR_MAX(SENSOR_TYPE_VG, acc, ALGO_DR_100HZ);

	ALGO_PRODUCT_SET_DR_MIN(SENSOR_TYPE_VLA, acc, ALGO_DR_10HZ);
	ALGO_PRODUCT_SET_DR_MAX(SENSOR_TYPE_VLA, acc, ALGO_DR_100HZ);

	ALGO_PRODUCT_SET_DR_MIN(SENSOR_TYPE_VRV, acc, ALGO_DR_50HZ);
	ALGO_PRODUCT_SET_DR_MAX(SENSOR_TYPE_VRV, acc, ALGO_DR_50HZ);
	ALGO_PRODUCT_SET_DR_MIN(SENSOR_TYPE_VRV, mag, ALGO_DR_50HZ);
	ALGO_PRODUCT_SET_DR_MAX(SENSOR_TYPE_VRV, mag, ALGO_DR_50HZ);

	ALGO_PRODUCT_SET_DR_MIN(SENSOR_TYPE_GEST_FLIP, acc, ALGO_DR_10HZ);
	ALGO_PRODUCT_SET_DR_MAX(SENSOR_TYPE_GEST_FLIP, acc, ALGO_DR_100HZ);
}

void algo_adapter_init()
{
	int i;
	struct algo_module *mod = g_algo_modules;
	struct sensor_hw *hw = NULL;

	for (i = 0; i < ALGO_NUM_DR; i++) {
		g_tab_hz[i] = 1000 / g_tab_intvl[i];
	}

	for (i = 0; i < ARRAY_SIZE(g_algo_modules); i++) {
		mod = g_algo_modules + i;
		PDEBUG("%s, %d, %d, %d",
				mod->name, mod->id, mod->op_mode, mod->ref);

		mod->ref = 0;
		mod->op_mode = ALGO_OPMODE_OFF;
		mod->enable(mod, 0);
	}

	algo_products_init();

	hw = hw_get_hw_by_id(SENSOR_HW_TYPE_A);

	if (NULL != hw) {
		g_p_hw_a = CONTAINER_OF(hw,
				struct sensor_hw_a, hw);
	}

	hw = hw_get_hw_by_id(SENSOR_HW_TYPE_M);
	if (NULL != hw) {
		g_p_hw_m = CONTAINER_OF(hw,
				struct sensor_hw_m, hw);
	}

	pthread_mutex_init(&g_lock_ref_hw, NULL);

#ifdef CFG_USE_DATA_LOG
	algo_log_data_init();
#endif
}


static struct algo_module * algo_get_mod(const struct algo_module *list,
		int len, uint32_t id)
{
	int i;
	struct algo_module *mod = NULL;

	for (i = 0; i < len; i++) {
		if (list[i].id == id) {
			mod = (struct algo_module *)list + i;
			break;
		}
	}

	if (NULL == mod) {
		PDEBUG("module: %d not found", id);
	}

	return mod;
}


static void algo_mod_ref_change(struct algo_module *mod, int updown)
{
	PDEBUG("%s, %d, ref: %d", mod->name, updown, mod->ref);
	if (updown) {
		mod->ref++;
		if (1 == mod->ref) {
			mod->enable(mod, 1);
		}
	} else {
		if (1 == mod->ref) {
			mod->enable(mod, 0);
		}

		if (mod->ref > 0) {
			mod->ref--;
		}
	}
}

static void algo_resolve_internal_state()
{
	int mode = 0;
	float a, b;

	ALGO_MOD_IS_ENABLED(ALGO_MODULE_ID_ACC, mode);
	if (mode) {
		bsc_set_accdatarate(g_dr_a);
	}

	ALGO_MOD_IS_ENABLED(ALGO_MODULE_ID_MAG, mode);
	if (mode) {
		bsc_set_magdatarate(g_dr_m);
	}

	/* this links the dr to the noise level */
	ALGO_MOD_IS_ENABLED(ALGO_MODULE_ID_CMP, mode);
	if (mode) {
		bsc_set_orientopmode(BSC_ORIENTOPMODE_REGULAR);
	}

	/* this links the dr to the noise level */
	ALGO_MOD_IS_ENABLED(ALGO_MODULE_ID_M4G, mode);
	if (mode) {
		bsc_set_m4gopmode(BSC_M4GOPMODE_REGULAR);
	}

	if (-1 != g_ori_thres_m) {
		bsc_set_orientMagNoiseThreshold(g_ori_thres_m);
	}

	a = b = 0;
	bsc_get_orientAccFilterParam(&a, &b);
	PDEBUG("ori acc filt: %f %f", a, b);
	a = b = 0;
	bsc_get_orientMagFilterParam(&a, &b);
	PDEBUG("ori mag filt: %f %f", a, b);
}


static void algo_update_data(BS_S32 ts)
{
	int err;
	int tmp;
	sensor_data_ival_t val;

	if (HW_IS_ACTIVE(g_active_hws, A)) {
		if (ts > g_last_ts_a) {
			tmp = ts - g_last_ts_a - g_tab_intvl[g_dr_a];
			if (tmp >= 0 || (tmp + CFG_TOLERANCE_TIME_PRECISION > 0)) {
#ifdef HW_A_USE_INPUT_EVENT
				if (hw_peek_data_status(1 << SENSOR_HW_TYPE_A)
				    & (1 << SENSOR_HW_TYPE_A)) {
					if (g_p_hw_a) {
						val.x = g_data_a.x;
						val.y = g_data_a.y;
						val.z = g_data_a.z;
						g_p_hw_a->hw.get_data(&val);
						g_data_a.x = (BS_S16)val.x;
						g_data_a.y = (BS_S16)val.y;
						g_data_a.z = (BS_S16)val.z;
					}

					PDEBUG("acc input event ready: %d %d %d",
					      g_data_a.x,
					      g_data_a.y,
					      g_data_a.z);
				}
#else
				if (g_p_hw_a) {
					err = g_p_hw_a->hw.get_data_nb(&val);
					if (!err) {
						g_data_a.x = (BS_S16)val.x;
						g_data_a.y = (BS_S16)val.y;
						g_data_a.z = (BS_S16)val.z;
					}
				}
#endif

				g_last_ts_a = ts;

				//PDEBUG("[acc]%d %d %d %d", ts, g_data_a.x, g_data_a.y, g_data_a.z);
			}
		} else {
			g_last_ts_a = ts;
		}
	}


	if (HW_IS_ACTIVE(g_active_hws, M)) {
		if (ts > g_last_ts_m) {
			tmp = ts - g_last_ts_m - g_tab_intvl[g_dr_m];
			if (tmp >= 0 || (tmp + CFG_TOLERANCE_TIME_PRECISION > 0)) {
				if (g_p_hw_m) {
					err = g_p_hw_m->hw.get_data_nb(&val);
					if (!err) {
						g_data_m.x = (BS_S16)val.x;
						g_data_m.y = (BS_S16)val.y;
						g_data_m.z = (BS_S16)val.z;
					}
				}

				g_last_ts_m = ts;
				//PDEBUG("[mag]%d %d %d %d", ts, g_data_m.x, g_data_m.y, g_data_m.z);
			}
		} else {
			g_last_ts_m = ts;
		}
	}
}


static int algo_hz2data_rate(int hz)
{
	int dr = 0;
	int i;

	for (i = 0; i < ALGO_NUM_DR; i++) {
		if (hz <= g_tab_hz[i]) {
			dr = i;
			break;
		}
	}

	if (i >= ALGO_NUM_DR) {
		dr = ALGO_NUM_DR - 1;
	}

	return dr;
}

static void algo_update_hw_ref(int type, int enable)
{
	pthread_mutex_lock(&g_lock_ref_hw);
	switch (type) {
		case SENSOR_HW_TYPE_A:
			if (enable) {
				g_ref_hw_a++;
			} else {
				if (g_ref_hw_a > 0) {
					g_ref_hw_a--;
				}
			}
			break;
		case SENSOR_HW_TYPE_M:
			if (enable) {
				g_ref_hw_m++;
			} else {
				if (g_ref_hw_m > 0) {
					g_ref_hw_m--;
				}
			}
			break;
		default:
			break;
	}
	pthread_mutex_unlock(&g_lock_ref_hw);
}

static void algo_update_mod_dep(struct algo_product *ap, int enable)
{
	if (ap->bypass_proc) {
		return;
	}

	switch (ap->type) {
		case SENSOR_TYPE_A:
			ALGO_MOD_ENABLE(ALGO_MODULE_ID_ACC, enable);
			break;
		case SENSOR_TYPE_M:
			ALGO_MOD_ENABLE(ALGO_MODULE_ID_MAG, enable);
			break;
		case SENSOR_TYPE_G:
			ALGO_MOD_ENABLE(ALGO_MODULE_ID_ACC, enable);
			ALGO_MOD_ENABLE(ALGO_MODULE_ID_MAG, enable);
			ALGO_MOD_ENABLE(ALGO_MODULE_ID_M4G, enable);
			break;
		case SENSOR_TYPE_O:
			ALGO_MOD_ENABLE(ALGO_MODULE_ID_ACC, enable);
			ALGO_MOD_ENABLE(ALGO_MODULE_ID_MAG, enable);
			ALGO_MOD_ENABLE(ALGO_MODULE_ID_CMP, enable);
			break;
		case SENSOR_TYPE_VG:
			ALGO_MOD_ENABLE(ALGO_MODULE_ID_ACC, enable);
			ALGO_MOD_ENABLE(ALGO_MODULE_ID_VLA, enable);
			break;
		case SENSOR_TYPE_VLA:
			ALGO_MOD_ENABLE(ALGO_MODULE_ID_ACC, enable);
			ALGO_MOD_ENABLE(ALGO_MODULE_ID_VLA, enable);
			break;
		case SENSOR_TYPE_VRV:
			ALGO_MOD_ENABLE(ALGO_MODULE_ID_ACC, enable);
			ALGO_MOD_ENABLE(ALGO_MODULE_ID_MAG, enable);
			ALGO_MOD_ENABLE(ALGO_MODULE_ID_M4G, enable);
			break;
		case SENSOR_TYPE_GEST_FLIP:
			ALGO_MOD_ENABLE(ALGO_MODULE_ID_ACC, enable);
			ALGO_MOD_ENABLE(ALGO_MODULE_ID_GEST_FLIP, enable);

			if (enable) {
				g_last_value_gest_flip = -1;
			}
			break;
		default:
			break;
	}
}

static void algo_update_hw_dep(struct algo_product *ap, int enable)
{
	switch (ap->type) {
		case SENSOR_TYPE_A:
			algo_update_hw_ref(SENSOR_HW_TYPE_A, enable);
			break;
		case SENSOR_TYPE_M:
			algo_update_hw_ref(SENSOR_HW_TYPE_M, enable);
			break;
		case SENSOR_TYPE_G:
			algo_update_hw_ref(SENSOR_HW_TYPE_A, enable);
			algo_update_hw_ref(SENSOR_HW_TYPE_M, enable);
			break;
		case SENSOR_TYPE_O:
			algo_update_hw_ref(SENSOR_HW_TYPE_A, enable);
			algo_update_hw_ref(SENSOR_HW_TYPE_M, enable);
			break;
		case SENSOR_TYPE_VG:
			algo_update_hw_ref(SENSOR_HW_TYPE_A, enable);
			break;
		case SENSOR_TYPE_VLA:
			algo_update_hw_ref(SENSOR_HW_TYPE_A, enable);
			break;
		case SENSOR_TYPE_VRV:
			algo_update_hw_ref(SENSOR_HW_TYPE_A, enable);
			algo_update_hw_ref(SENSOR_HW_TYPE_M, enable);
			break;
		case SENSOR_TYPE_GEST_FLIP:
			algo_update_hw_ref(SENSOR_HW_TYPE_A, enable);
			break;
		default:
			break;
	}
}

int algo_enable_product(struct algo_product *ap, int enable)
{
	int err = 0;

	algo_update_mod_dep(ap, enable);
	algo_update_hw_dep(ap, enable);

	ALGO_PRODUCT_REGULATE_DR(ap);
	fusion_arbitrate_dr();
	algo_resolve_internal_state();

	return err;
}


void algo_on_interval_changed(struct algo_product *ap, int *itvl)
{
	int interval = *itvl;
	int hz;
	int dr;

	if (interval <= 0) {
		return;
	}

	interval = get_nearest_divisible_int(1000, interval);
	*itvl = interval;

	hz = 1000 / interval;
	dr = algo_hz2data_rate(hz);

	PINFO("type: %d interval: %d new hz: %d dr: %d",
	      ap->type, interval, hz, dr);

	switch (ap->type) {
	case SENSOR_TYPE_A:
	case SENSOR_TYPE_VG:
	case SENSOR_TYPE_VLA:
		ap->dr_a = dr;
		break;
	case SENSOR_TYPE_M:
		ap->dr_m = dr;
		break;
	case SENSOR_TYPE_O:
		ap->dr_a = dr;
		ap->dr_m = dr;
		break;
	case SENSOR_TYPE_G:
	case SENSOR_TYPE_VRV:
		/* use default of M4G */
		ap->dr_a = dr;
		ap->dr_m = dr;
		break;
	case SENSOR_TYPE_GEST_FLIP:
		ap->dr_a = dr;
		break;
	default:
		break;
	}

	ALGO_PRODUCT_REGULATE_DR(ap);
	fusion_arbitrate_dr();
	algo_resolve_internal_state();

	if (HW_IS_ACTIVE(g_active_hws, A)) {
		if (g_p_hw_a && g_p_hw_a->set_bw) {
			g_p_hw_a->set_bw(g_p_hw_a, g_tab_ref_bw[g_dr_a]);
		}

		if (g_p_hw_a && g_p_hw_a->hw.set_delay) {
			g_p_hw_a->hw.set_delay(&g_p_hw_a->hw,
					       g_tab_intvl[g_dr_a]);
		}
	}
}


int algo_get_hint_interval()
{
	int ret;
	struct algo_module *mod;

	int intv_a = g_tab_intvl[g_dr_a];
	int intv_m = g_tab_intvl[g_dr_m];

	ret = 1000;

	mod = algo_get_mod(g_algo_modules, ARRAY_SIZE(g_algo_modules), ALGO_MODULE_ID_ACC);
	if (mod && mod->op_mode) {
		ret = get_max_comm_div(ret, intv_a);
	}

	mod = algo_get_mod(g_algo_modules, ARRAY_SIZE(g_algo_modules), ALGO_MODULE_ID_MAG);
	if (mod && mod->op_mode) {
		ret = get_max_comm_div(ret, intv_m);
	}

	return ret;
}


void algo_get_curr_hw_dep(hw_dep_set_t *dep)
{
	*dep = 0;

	pthread_mutex_lock(&g_lock_ref_hw);
	PDEBUG("algo_hw_ref: %d %d", g_ref_hw_a, g_ref_hw_m);
	if (g_ref_hw_a > 0) {
		*dep |= (1 << SENSOR_HW_TYPE_A);
	}

	if (g_ref_hw_m > 0) {
		*dep |= (1 << SENSOR_HW_TYPE_M);
	}
	pthread_mutex_unlock(&g_lock_ref_hw);
}


int algo_on_hw_dep_checked(const hw_dep_set_t *dep)
{
	int err = 0;
	g_active_hws = *dep;

	if (HW_IS_ACTIVE(g_active_hws, A)) {
		if (g_p_hw_a && g_p_hw_a->set_bw) {
			err = g_p_hw_a->set_bw(g_p_hw_a, g_tab_ref_bw[g_dr_a]);
		}

		if (g_p_hw_a && g_p_hw_a->hw.set_delay) {
			g_p_hw_a->hw.set_delay(&g_p_hw_a->hw,
					       g_tab_intvl[g_dr_a]);
		}
	}

	return err;
}


void algo_load_calib_profile(char magic)
{
	ts_calibProfile *profile = NULL;
	switch (magic) {
	case SENSOR_MAGIC_A:
		profile = &g_profile_calib_a.profile;
		if (profile->accuracy == SENSOR_ACCURACY_HIGH) {
			bsc_set_acccalibprofile(profile);
		}
		break;
	case SENSOR_MAGIC_M:
		profile = &g_profile_calib_m.profile;
		if (profile->accuracy == SENSOR_ACCURACY_HIGH) {
			bsc_set_magcalibprofile(profile);
		}
		break;
	default:
		PWARN("unknown sensor");
		return;
	}

	if (SENSOR_ACCURACY_HIGH == profile->accuracy) {
		PDEBUG("profile <%c> is loaded: %d %d %d %d %d",
		       magic,
		       (int)profile->offset.x,
		       (int)profile->offset.y,
		       (int)profile->offset.z,
		       (int)profile->radius,
		       (int)profile->accuracy
		      );

	} else {
		PDEBUG("profile <%c> is not loaded: %p", magic, profile);
	}
}


void algo_save_calib_profile(char magic)
{
	int fd = -1;
	ts_calibProfile *pprofile = NULL;
	ts_calibProfile profile;
	unsigned char tmp;

	switch (magic) {
	case SENSOR_MAGIC_A:
		bsc_get_acccalibprofile(&profile);
		pprofile = &g_profile_calib_a.profile;
		fd = g_fd_profile_calib_a;
		break;
	case SENSOR_MAGIC_M:
		bsc_get_magcalibprofile(&profile);
		pprofile = &g_profile_calib_m.profile;
		fd = g_fd_profile_calib_m;
		break;
	default:
		PWARN("unknown sensor");
		return;
	}

	if (SENSOR_ACCURACY_UNRELIABLE <= (int8_t)profile.accuracy) {
		memcpy(pprofile, &profile, sizeof(profile));
		PDEBUG("new profile <%c> is saved: %d %d %d %d %d",
				magic,
				(int)profile.offset.x,
				(int)profile.offset.y,
				(int)profile.offset.z,
				(int)profile.radius,
				(int)profile.accuracy
		      );

		if (-1 != fd) {
			lseek(fd, 0, SEEK_SET);
			write(fd, &magic, 1);
			tmp = ALGO_CALIB_PROFILE_VER;
			write(fd, &tmp, 1);
			tmp = (unsigned char)sizeof(*pprofile);
			write(fd, &tmp, 1);
			write(fd, pprofile, sizeof(*pprofile));
			fsync(fd);
		}
	} else {
		PDEBUG("status not good, profile disgarded");
	}
}


BS_S32 algo_proc_data(BS_S32 ts)
{
	int err = 0;

	algo_update_data(ts);
	bsc_run(ts, &g_data_a, &g_data_m, 0, 0);

#ifdef CFG_USE_DATA_LOG
	int mode = 0;

	ALGO_MOD_IS_ENABLED(ALGO_MODULE_ID_ACC, mode);
	if (mode) {
		algo_log_data_a(SENSOR_MAGIC_A, ts);
	}

	ALGO_MOD_IS_ENABLED(ALGO_MODULE_ID_MAG, mode);
	if (mode) {
		algo_log_data_m(SENSOR_MAGIC_M, ts);
	}

	ALGO_MOD_IS_ENABLED(ALGO_MODULE_ID_CMP, mode);
	if (mode) {
		algo_log_data_o(SENSOR_MAGIC_O, ts);
	}

	ALGO_MOD_IS_ENABLED(ALGO_MODULE_ID_M4G, mode);
	if (mode) {
		algo_log_data_mgo(SENSOR_MAGIC_G, ts);
	}
#endif
	return err;
}


#if SPT_SENSOR_A
int algo_get_proc_data_a(sensor_data_t *pdata)
{
	int err = 0;
	BS_U8 status = 0;
	dataxyzF32_t data;

	err = bsc_get_acccordata_ms2(&data);
	pdata->acceleration.x = data.x;
	pdata->acceleration.y = data.y;
	pdata->acceleration.z = data.z;

	bsc_get_accdatastatus(&status);
	pdata->status = status;

	return err;
}
#endif


#if SPT_SENSOR_M
int algo_get_proc_data_m(sensor_data_t *pdata)
{
	int err = 0;
	dataxyz_t data;
	BS_U8 status = 0;

	err = bsc_get_magfiltdata_lsb(&data);

	pdata->magnetic.x = (float) data.x / 4.0;
	pdata->magnetic.y = (float) data.y / 4.0;
	pdata->magnetic.z = (float) data.z / 4.0;

	bsc_get_magdatastatus(&status);
	pdata->status = status;

	return err;
}
#endif


#if SPT_SENSOR_O
int algo_get_proc_data_o(sensor_data_t *pdata)
{
	int err = 0;
	ts_orientEuler data;
	BS_U8 status = 0;

	err = bsc_get_orientdata_feuler(&data);

	pdata->orientation.azimuth = ((float)data.h *
			RADIAN2DEGREE / AXIS_RESOLUTION_FACTOR);

	pdata->orientation.pitch = ((float)data.p *
			RADIAN2DEGREE / AXIS_RESOLUTION_FACTOR);

	pdata->orientation.roll = ((float)data.r *
			RADIAN2DEGREE / AXIS_RESOLUTION_FACTOR);


	bsc_get_orientdata_status(&status);
	pdata->status = status;

	return err;
}
#endif


#if SPT_SENSOR_G && CFG_SENSOR_G_EMU
int algo_get_proc_data_g(sensor_data_t *pdata)
{
	int err = 0;
	dataxyz_t data;
	BS_U8 status = 0;

	err = bsc_get_m4gdata_angularrate(&data);

	pdata->gyro.x = (float) data.x / 938;
	pdata->gyro.y = (float) data.y / 938;
	pdata->gyro.z = (float) data.z / 938;

	bsc_get_m4gdatastatus(&status);
	pdata->status = status;
	return err;
}
#endif

#if SPT_SENSOR_VG
int algo_get_proc_data_vg(sensor_data_t *pdata)
{
	int err = 0;
	dataxyzF32_t data_a;
	dataxyzF32_t data_la;

	err = bsc_get_acccordata_ms2(&data_a);
	bsc_get_linaccdata_ms2(&data_la);

	pdata->data[0] = data_a.x - data_la.x;
	pdata->data[1] = data_a.y - data_la.y;
	pdata->data[2] = data_a.z - data_la.z;

	return err;
}
#endif


#if SPT_SENSOR_VLA
int algo_get_proc_data_vla(sensor_data_t *pdata)
{
	int err = 0;
	dataxyzF32_t data;

	bsc_get_linaccdata_ms2(&data);

	pdata->data[0] = data.x;
	pdata->data[1] = data.y;
	pdata->data[2] = data.z;

	return err;
}
#endif


#if SPT_SENSOR_VRV
int algo_get_proc_data_vrv(sensor_data_t *pdata)
{
	int err = 0;

	ts_orientQuat quat;

	err = bsc_get_m4gdata_quat(&quat);

#ifdef ALGO_FIX_QUAT_SIGN
	quat.x = 0 - quat.x;
	quat.y = 0 - quat.y;
	quat.z = 0 - quat.z;
#endif

	if (quat.w < 0) {
		quat.w = 0 - quat.w;
		quat.x = 0 - quat.x;
		quat.y = 0 - quat.y;
		quat.z = 0 - quat.z;
	}

	pdata->data[0] = (float) quat.x / 16384;
	pdata->data[1] = (float) quat.y / 16384;
	pdata->data[2] = (float) quat.z / 16384;

	return err;
}
#endif

#if SPT_SENSOR_GEST_FLIP
int algo_get_proc_data_gest_flip(sensor_data_t *pdata)
{
	BS_U8 gest_flip = -1;
	int ret;

#ifdef ALGO_SPT_GEST_FLIP
	bsc_get_flipgesture_status(&gest_flip);
#endif

	if (gest_flip != g_last_value_gest_flip) {
		g_last_value_gest_flip = gest_flip;
		pdata->data[0] = gest_flip;
		pdata->data[1] = 0;
		pdata->data[2] = 0;
		ret = 1;
	} else {
		ret = 0;
	}

	return ret;
}
#endif

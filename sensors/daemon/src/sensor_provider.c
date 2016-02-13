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
 * @file         sensor_provider.c
 * @date         "Tue Mar 12 17:11:32 2013 +0800"
 * @commit       "81910b2"
 *
 * @brief
 *
 * @detail
 *
 */


#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <pthread.h>
#include <time.h>

#include <linux/fs.h>

#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <sys/syscall.h>


#define LOG_TAG_MODULE "<sensor_provider>"
#include "sensord.h"
static pthread_mutex_t g_mutex_dat_fifo;
extern int g_fd_fifo_dat;

extern struct algo g_sp_algo_fusion;
extern struct sensor_provider g_sp_pressure;

static const struct sensor_provider *g_list_sp[] = {
	&g_sp_algo_fusion.sp,
#if SPT_SENSOR_P
	&g_sp_pressure,
#endif
	NULL	/* the terminator */
};


void sp_preinit()
{
	int i = 0;
	struct run_entity *re;
	struct sensor_provider *sp;
	int err = 0;

	i = 0;
	while (NULL != (sp = (struct sensor_provider *)g_list_sp[i++])) {
		sp->available = 0;
		sp->client_num = 0;
		sp->ref = 0;

		sp->curr_hw_dep = 0;
		sp->clients = NULL;
		sp->buf_out = NULL;
		sp->private_data = NULL;

		pthread_mutex_init(&sp->lock_ref, NULL);

		re = &sp->re;
		re->ptid = -1;
		re->tid = -1;

		re->started = 0;
		re->sleeping = 0;
		re->interval = 1000;
		re->private_data = NULL;

		pthread_cond_init(&re->cond, NULL);

		err = sp->init(sp);
		if (err) {
			PWARN("error init of sensor provider: %s", sp->name);
			continue;
		}

		sp->available = 1;
	}
}


static void sp_sync_re()
{
	int i = 0;
	struct sensor_provider *sp;

	i = 0;
	while (NULL != (sp = (struct sensor_provider *)g_list_sp[i++])) {
		if (!sp->available) {
			continue;
		}

		while (!sp->re.started) {
			eusleep(1000);
		}
	}

	PINFO("all available threads are ready now");
}


void sp_init()
{
	int err = 0;
	int i = 0;
	int tmp;
	struct exchange *data = NULL;
	struct sensor_provider *sp;
	pthread_attr_t thr_attr;
	size_t stk_size;

	pthread_mutex_init(&g_mutex_dat_fifo, NULL);

	pthread_attr_init(&thr_attr);
	pthread_attr_getstacksize(&thr_attr, &stk_size);
	PINFO("stack size: %d", stk_size);

	i = 0;
	while (NULL != (sp = (struct sensor_provider *)g_list_sp[i++])) {
		if (0 == sp->client_num) {
			sp->available = 0;
			continue;
		}

		data = (struct exchange *)sp->buf_out;
		if (NULL == data) {
			data = (struct exchange *)calloc(sp->client_num,
					sizeof(struct exchange));
			if (NULL == data) {
				PERR("no mem for %s", sp->name);
				/* wait for some time for system to release some resource for us */
				eusleep(100000);
				continue;
			}

			sp->buf_out = data;
		}

		for (tmp = 0; tmp < sp->client_num; tmp++) {
			data[tmp].magic = CHANNEL_PKT_MAGIC_DAT;
			data[tmp].data.version = sizeof(data[0]);
		}

		err = pthread_create(&sp->re.ptid,
				NULL,
				sp->re.func,
				(void*)sp);

		if (!err) {
			PINFO("thread created for provider: %s",
					sp->name);
		} else {
			PERR("error creating thread for provider: %s",
					sp->name);
		}
	}

	sp_sync_re();
}


struct sensor_provider *sp_scan_for_provider(struct channel *ch)
{
	struct sensor_provider *sp = NULL;
	int i;

	i = 0;
	while (NULL != (sp = (struct sensor_provider *)g_list_sp[i++])) {
		if ((1 << ch->type) & sp->sensors) {
			if (!strcmp(ch->cfg.sp_name, sp->name)) {
				break;
			}
		}
	}

	return sp;
}


void sp_register_ch(struct sensor_provider *sp, struct channel *ch)
{
	sp->client_num++;
	ch->sp = sp;
}


static int sp_re_check_dep_hw(struct sensor_provider *sp)
{
	int err = 0;
	hw_dep_set_t new_dep_hw = 0;
	hw_dep_set_t changed = 0;
	int i;
	int enable;

	PDEBUG("check dependency of %s",
			sp->name);

	sp->get_curr_hw_dep(&new_dep_hw);
	changed = new_dep_hw ^ sp->curr_hw_dep;

	for (i = 0; i < (int)SENSOR_HW_TYPE_MAX; i++) {
		if ((changed >> i) & 0x01) {
			enable = ((new_dep_hw >> i) & 0x01);
			if (enable) {
				err = hw_ref_up(i);
			} else {
				err = hw_ref_down(i);
			}

			if (err) {
				PWARN("<hw_dep> %s@%d %d -> %d err: %d",
						sp->name,
						i,
						(sp->curr_hw_dep >> i) & 0x01,
						(new_dep_hw >> i) & 0x01,
						err);

				new_dep_hw ^= (1 << i);
			}
		}
	}

	sp->curr_hw_dep = new_dep_hw;

	return err;
}


void sp_recalc_interval_re(struct sensor_provider *sp)
{
	struct list_node *cur;
	struct channel *ch;
	struct run_entity *re;
	int val = 1000;

	re = &sp->re;

	if (NULL != sp->get_hint_proc_interval) {
		re->interval = sp->get_hint_proc_interval();
	} else {
		cur = sp->clients;
		while (NULL != cur) {
			ch = CONTAINER_OF(cur, struct channel, client);
			if (CHANNEL_STATE_SLEEP != ch->state) {
				val = get_max_comm_div(val, ch->interval);
			}

			cur = cur->next;
		}

		re->interval = val;
	}

	if (re->interval < INTV_PROC_MIN) {
		re->interval = INTV_PROC_MIN;
	}

	PINFO("new interval for sp: %s is: %d",
			sp->name,
			re->interval);
}


void sp_enable_ch(struct sensor_provider *sp, struct channel *ch, int enable)
{
	struct list_node *head;
	int err;

	head = sp->clients;

	if (enable) {
		if (NULL == list_find_node(head, &ch->client)) {
			list_add_head(head, &ch->client);
		}

		sp->clients = &ch->client;
	} else {
		head = list_del_node(head, &ch->client);
		sp->clients = head;
	}


	/* notice provider that some channel will be switched on/off */
	/* provider should know that the h/w might not be switched on/off yet */
	err = sp->on_ch_enabled(ch, enable);
	if (err) {
		PWARN("on_ch_enabled: %d error for %s", enable, ch->name);
	}

	sp_re_check_dep_hw(sp);

	if (NULL != sp->on_hw_dep_checked) {
		sp->on_hw_dep_checked(&sp->curr_hw_dep);
	}

	sp_recalc_interval_re(sp);

	if (ch->cfg.bypass_proc) {
		/* no need to update the ref,
		 * thus return */
		PDEBUG("sp act as hw manager only for: %s",  ch->name);
		return;
	}

	if (enable) {
		sp->ref += 1;
		if ((1 == sp->ref) && !sp->re.op_blk) {
			/* CHECK: lock_cond is already locked */
			pthread_cond_signal(&sp->re.cond);
		}
	} else {
		if (sp->ref > 0) {
			sp->ref -= 1;
		}
	}
}


static int sp_report_data(struct sensor_provider *sp, void *buf, int n)
{
	struct exchange *data;
	int err = 0;

	UNUSED_PARAM(sp);
	data = (struct exchange *)buf;
	/* lock for single fifo write */
	if (n > 0) {
		pthread_mutex_lock(&g_mutex_dat_fifo);
		err = write(g_fd_fifo_dat, data, n * sizeof(*data));
		pthread_mutex_unlock(&g_mutex_dat_fifo);
	}

	return err;
}


void* re_proc(void* pparam)
{
	int sleep_time = 0;

	struct run_entity *re = NULL;
	struct sensor_provider *sp = NULL;
	struct channel *ch = NULL;
	struct list_node *cur = NULL;
	struct exchange *data = NULL;

	unsigned int time_start = 0;
	unsigned int time_now = 0;
	int elapse = 0;

	int i = 0;
	int n = 0;
	int tmp = 0;

	struct timespec ts;

	sp = (struct sensor_provider *)pparam;
	re = &sp->re;


	re->func_fp = (long *)&sleep_time;
	re->private_data = &pparam;
	re->tid = (int)syscall(__NR_gettid);
	PINFO("thread: %s tid: %d started pparam: %p @ %p",
			sp->name,
			re->tid,
			pparam,
			&pparam);

	re->started = 1;

	data = (struct exchange *)sp->buf_out;

	while (1) {
		//ch = (struct channel *)0xCCDDEEFF;

		if (!re->op_blk) {
			pthread_mutex_lock(&sp->lock_ref);

			if (0 == sp->ref) {
				re->sleeping = 1;
				/* wait for the sensor to be restarted */
				PINFO("%s is waiting for being signaled...",
						sp->name);
				if (pthread_cond_wait(&re->cond,
							&sp->lock_ref)) {
					re->sleeping = 0;
					PERR("%s waiting for being signaled error",
							sp->name);
					pthread_mutex_unlock(&sp->lock_ref);
					continue;
				}

				re->sleeping = 0;
				PINFO("%s is signaled", sp->name);
				//pthread_mutex_unlock(&re->lock_cond);
			}
		}

		/* start to proc sensor signal */
		time_start = get_time_tick();

		if (NULL != sp->proc_data) {
			sp->proc_data(time_start);
		}

		time_now = get_time_tick();
		clock_gettime(CLOCK_MONOTONIC, &ts);

		PDEBUG("proc time: %d for %s",
				time_now - time_start, sp->name);

		cur = sp->clients;
		n = 0;
		while (NULL != cur) {
			ch = CONTAINER_OF(cur, struct channel, client);
			tmp = 0;

			if ((CHANNEL_STATE_NORMAL == ch->state)
			    && !ch->cfg.bypass_proc) {
				elapse = (time_now - ch->ts_last_ev);
				if (elapse > 0) {
					elapse -= ch->interval;
				} else if (0 == elapse) {
					elapse = -1 - CFG_TOLERANCE_TIME_PRECISION;
				} else {
					elapse = 0;
				}

				if (ch->cfg.no_delay ||
						(elapse >= 0 ||
						 (elapse + CFG_TOLERANCE_TIME_PRECISION) > 0)) {
					tmp = ch->get_data(data + n, sp->client_num - n);
					ch->ts_last_ev = time_now;
				}
			}

			if (tmp > 0) {
				for (i = 0; i < tmp; i++) {
					data[n + i].data.sensor = ch->handle;
					data[n + i].data.type = ch->type;
				}
				n += tmp;
			}

			cur = cur->next;
		}

		if (!re->op_blk) {
			pthread_mutex_unlock(&sp->lock_ref);
		}

		for (i = 0; i < n; i++) {
			data[i].ts = ts.tv_sec * TIME_SCALE_S2NS + ts.tv_nsec;
		}

		PDEBUG("report %d events @%jd", n, data[0].ts);
		sp_report_data(sp, data, n);

		if (re->op_blk) {
			continue;
		}

		/* sleep */
		time_now = get_time_tick();

		if ((int)(time_now - time_start) < 0) {
			PWARN("elapse %d for %s is negative now",
					time_now - time_start, sp->name);
			sleep_time = -1;
		} else {
			sleep_time =
				(re->interval - (time_now - time_start));
		}

		if (sleep_time > SAMPLE_INTERVAL_MAX) {
			PWARN("sleep_time: %d too long for %s",
					sleep_time, sp->name);
		} else if (sleep_time <= 0) {
			continue;
		}

		eusleep(sleep_time * 1000);
	}


	re->started = -1;
	PINFO("thread %s terminated", sp->name);
	pthread_exit((void *)re->tid);
	return (pparam);
}


void sp_dump()
{
	struct sensor_provider *sp;
	struct run_entity *re;
	int i;

	PINFO("sensor provider dump...");
	i = 0;
	while (NULL != (sp = (struct sensor_provider *)g_list_sp[i++])) {
		re = &sp->re;
		PINFO("-----------------");
		PINFO("name: %s", sp->name);
		PINFO("addr: %p", sp);
		PINFO("ptid: %ld", re->ptid);
		PINFO("tid: %d", re->tid);
		PINFO("started: %d", re->started);
		PINFO("op_blk: %d", re->op_blk);
		PINFO("sleeping: %d", re->sleeping);
		PINFO("client_num: %d", sp->client_num);
		PINFO("ref: %d", sp->ref);
		PINFO("interval: %d", re->interval);
		PINFO("func_fp: %p", re->func_fp);
		PINFO("private_data: %p", re->private_data);
	}
}

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
* @file         cust.h
* @date         "Mon Mar 18 11:02:35 2013 +0800"
* @commit       "c68b71a"
*
* @brief
* customization file for fine-tuning performance factors of the algorithm
* @detail
*/


#ifndef __ALGO_CUST_H
#define __ALGO_CUST_H
struct algo_cust_param {
	int    version;

	int    p0:2;

	int    p1:16;
	int    p2:16;

	int    p3:8;

	float  p4;
};

#define ALGO_CUST_ORI_NOI_THRES_A -1
#define ALGO_CUST_ORI_NOI_THRES_M 4/*3*/

#define ALGO_CUST_ORI_FILT_MODE   3
#define ALGO_CUST_M_CALIB_ACCURACY_THRES 170
#define ALGO_CUST_M_CALIB_ACCURACY_THRES_INIT 100



#define ALGO_CUST_ORI_FILT_COEF_A 0.4f
#define ALGO_CUST_ORI_FILT_DYNA_A 0.1f

#define ALGO_CUST_ORI_FILT_COEF_M 0.6f
#define ALGO_CUST_ORI_FILT_DYNA_M 0.1f

#define ALGO_CUST_A_ADV_FILT_COEF 20
#define ALGO_CUST_A_ADV_FILT_NL 4

#define ALGO_CUST_M_ADV_FILT_COEF 20
#define ALGO_CUST_M_ADV_FILT_NL 5


#define ALGO_CUST_GEST_FLIP_ANGLE_RANGE_UP      -1
#define ALGO_CUST_GEST_FLIP_ANGLE_RANGE_DOWN    -1
#define ALGO_CUST_GEST_FLIP_DECT_TIME           -1

/* if ALGO_CUST_USE_PREDEFINED_SIC_MATRIX is defined as non-zero,
 * then the matrix (of float type) should be defined properly */
#define ALGO_CUST_USE_PREDEFINED_SIC_MATRIX 0
#define ALGO_CUST_SI_MATRIX_XX  1.0f
#define ALGO_CUST_SI_MATRIX_XY  0.0f
#define ALGO_CUST_SI_MATRIX_XZ  0.0f
#define ALGO_CUST_SI_MATRIX_YX  0.0f
#define ALGO_CUST_SI_MATRIX_YY  1.0f
#define ALGO_CUST_SI_MATRIX_YZ  0.0f
#define ALGO_CUST_SI_MATRIX_ZX  0.0f
#define ALGO_CUST_SI_MATRIX_ZY  0.0f
#define ALGO_CUST_SI_MATRIX_ZZ  1.0f

#endif

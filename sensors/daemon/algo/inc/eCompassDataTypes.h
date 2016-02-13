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
* @file         eCompassDataTypes.h
* @date         "Mon Mar 18 11:02:35 2013 +0800"
* @commit       "c68b71a"
*
* @brief
* @detail
*/


/* eCompassDataTypes.h */
#ifndef __ECOMPASSDATATYPES_H__
#define __ECOMPASSDATATYPES_H__


/*! \file eCompassDataTypes.h
    \brief Contains all the definitions & declarations used in the eCompass Software */

/* Standard includes */
#include <limits.h>

/* #Define Constants */
/* typedefs */
#if USHRT_MAX == 0xFFFF
    typedef unsigned short ECOMPASS_U16; // 16 bit achieved with short
    typedef signed short ECOMPASS_S16;
#elif UINT_MAX == 0xFFFF
        typedef unsigned int ECOMPASS_U16;  // 16 bit achieved with int
        typedef signed int ECOMPASS_S16;
#else
    #error U16 and S16 could not be defined automatically, please do so manually
#endif

// find correct data type for signed 32 bit variables
#if INT_MAX == 0x7FFFFFFF
        typedef signed int ECOMPASS_S32; // 32 bit achieved with int
        typedef unsigned int ECOMPASS_U32;
#elif LONG_MAX == 0x7FFFFFFF
    typedef signed long int ECOMPASS_S32;       // 32 bit achieved with long int
        typedef unsigned long int ECOMPASS_U32; // 32 bit achieved with long int
#else
    #error S32 could not be defined automatically, please do so manually
#endif

typedef signed char           ECOMPASS_S8;
typedef unsigned char         ECOMPASS_U8;
typedef signed long long      ECOMPASS_S64;
typedef unsigned long long    ECOMPASS_U64;
typedef unsigned char         ECOMPASS_BIT;
typedef unsigned int          ECOMPASS_BOOL;
typedef float                 ECOMPASS_F32;
typedef double                ECOMPASS_F64;

/*************************************************************************************************/
/*									CONSTANTS DEFINITION										 */
/*************************************************************************************************/

#define	C_ECOMPASS_Null_U8X             (ECOMPASS_U8)   0
#define C_ECOMPASS_Zero_U8X             (ECOMPASS_U8)   0
#define C_ECOMPASS_One_U8X              (ECOMPASS_U8)   1
#define C_ECOMPASS_Two_U8X              (ECOMPASS_U8)   2
#define C_ECOMPASS_Three_U8X            (ECOMPASS_U8)   3
#define C_ECOMPASS_Four_U8X				(ECOMPASS_U8)   4
#define C_ECOMPASS_Five_U8X             (ECOMPASS_U8)   5
#define C_ECOMPASS_Six_U8X              (ECOMPASS_U8)   6
#define C_ECOMPASS_Seven_U8X            (ECOMPASS_U8)   7
#define C_ECOMPASS_Eight_U8X            (ECOMPASS_U8)   8
#define C_ECOMPASS_Nine_U8X             (ECOMPASS_U8)   9
#define C_ECOMPASS_Ten_U8X              (ECOMPASS_U8)  10
#define C_ECOMPASS_Eleven_U8X           (ECOMPASS_U8)  11
#define C_ECOMPASS_Twelve_U8X           (ECOMPASS_U8)  12
#define C_ECOMPASS_Sixteen_U8X          (ECOMPASS_U8)  16
#define C_ECOMPASS_TwentyFour_U8X       (ECOMPASS_U8)  24
#define C_ECOMPASS_ThirtyTwo_U8X        (ECOMPASS_U8)  32
#define C_ECOMPASS_Hundred_U8X          (ECOMPASS_U8) 100
#define C_ECOMPASS_OneTwentySeven_U8X	(ECOMPASS_U8) 127
#define C_ECOMPASS_TwoFiftyFive_U8X     (ECOMPASS_U8) 255
#define C_ECOMPASS_TwoFiftySix_U16X     (ECOMPASS_U16)256

/** \def Conversion Factors */
#define C_MILLI_F32X					(ECOMPASS_F32)1e3
#define C_MICRO_F32X					(ECOMPASS_F32)1e6   
#define C_NANO_F32X						(ECOMPASS_F32)1e9

#define C_MG2MSEC2_F32X					(ECOMPASS_F32)0.00981    /** \def mg -> m/s2 */ 
#define C_LSB2uT_F32X					(ECOMPASS_F32)0.25
#define C_uT2LSB_F32X					(ECOMPASS_F32)4 

/* Constants */
#define C_PI_F32X						(ECOMPASS_F32) 3.1416
#define C_RAD2DEG_FACTOR_F32X			(ECOMPASS_F32)57.295647  /**< radiant to degree conversion factor i.e.,(180/3.1416)*/
#define C_DEG2RAD_FACTOR_F32X			(ECOMPASS_F32)0.0175

/* Status */
#define C_SCALEUP_U8R					(ECOMPASS_U8)0
#define C_SCALEDOWN_U8R					(ECOMPASS_U8)1

#define C_DEACTIVATE_U8R				(ECOMPASS_U8)0
#define C_ACTIVATE_U8R					(ECOMPASS_U8)1

#define C_FAILURE_U8R					(ECOMPASS_U8)0
#define C_SUCCESS_U8R					(ECOMPASS_U8)1

#define C_DISABLE_U8R					(ECOMPASS_U8)0
#define C_ENABLE_U8R					(ECOMPASS_U8)1

#define C_FALSE_U8X						(ECOMPASS_U8)0
#define C_TRUE_U8X						(ECOMPASS_U8)1

#define C_NOERROR_U8R					(ECOMPASS_U8)0 	
#define C_ERROR_U8R						(ECOMPASS_U8)1

#define C_ECOMPASS_RESET_U8X			(ECOMPASS_U8)0
#define C_ECOMPASS_SET_U8X				(ECOMPASS_U8)1

#define C_POSITIVE_U8R					(ECOMPASS_U8)0
#define C_NEGATIVE_U8R					(ECOMPASS_U8)1

/*************************************************************************************************/
/*									STRUCTURES DEFINITION										 */
/*************************************************************************************************/

typedef struct
{
	ECOMPASS_S16 x;
	ECOMPASS_S16 y;
	ECOMPASS_S16 z;
}dataxyz_t;



typedef struct
{
	ECOMPASS_U8 x;
	ECOMPASS_U8 y;
	ECOMPASS_U8 z;
}dataxyzU8_t;

typedef struct{
	ECOMPASS_F32 x;
	ECOMPASS_F32 y;
	ECOMPASS_F32 z;
}dataxyzF32_t ;

/** \struct ts_orientEuler
        \brief Euler angles
*/
typedef struct
{
     ECOMPASS_S16 h;  
     ECOMPASS_S16 p;        
     ECOMPASS_S16 r;          
}ts_orientEuler;

/** \struct ts_orientQuat
        \brief Quaternion Data
*/
typedef struct
{
	ECOMPASS_S16  w;
	ECOMPASS_S16  x;
	ECOMPASS_S16  y;
	ECOMPASS_S16  z;
}ts_orientQuat;

typedef struct
{
	ECOMPASS_F32 xx,xy,xz;
	ECOMPASS_F32 yx,yy,yz;
	ECOMPASS_F32 zx,zy,zz;
}ts_magSoftIronSensM;
#endif


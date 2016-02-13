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
* @file         BSC_Library.h
* @date         "Mon Mar 18 11:02:35 2013 +0800"
* @commit       "c68b71a"
*
* @brief
* @detail
*/


#ifndef __BSCLIBRARY_H__
#define __BSCLIBRARY_H__

/** includes
*/
#include "eCompassDataTypes.h"
#include "eCompassDefine.h"

/** \def operation modes accelerometer */
#define BSC_ACCOPMODE_SLEEP     (ECOMPASS_U8)0
#define BSC_ACCOPMODE_LOWPOWER  (ECOMPASS_U8)1
#define BSC_ACCOPMODE_REGULAR   (ECOMPASS_U8)2
        
/** \def operation modes magnetometer */
#define BSC_MAGOPMODE_SLEEP        (ECOMPASS_U8)0
#define BSC_MAGOPMODE_LOWPOWER     (ECOMPASS_U8)1
#define BSC_MAGOPMODE_REGULAR      (ECOMPASS_U8)2
#define BSC_MAGOPMODE_HIGHACCURACY (ECOMPASS_U8)3
#define BSC_MAGOPMODE_ALWAYSON     (ECOMPASS_U8)4
        
/** \def operation modes orientation */
#define BSC_ORIENTOPMODE_SLEEP    (ECOMPASS_U8)0
#define BSC_ORIENTOPMODE_REGULAR  (ECOMPASS_U8)1
        
/** \def operation modes: linear acceleration sensor */
#define BSC_LINACCOPMODE_SLEEP     (ECOMPASS_U8)0
#define BSC_LINACCOPMODE_REGULAR   (ECOMPASS_U8)1
        
/** \def operation modes: magnetic gyroscope */
#define BSC_M4GOPMODE_SLEEP    (ECOMPASS_U8)0
#define BSC_M4GOPMODE_REGULAR  (ECOMPASS_U8)1
        
/** \def Data Output Rate */
#define BSC_DATARATE_1HZ      (ECOMPASS_U8)0
#define BSC_DATARATE_5HZ      (ECOMPASS_U8)1
#define BSC_DATARATE_10HZ     (ECOMPASS_U8)2
#define BSC_DATARATE_20HZ     (ECOMPASS_U8)3
#define BSC_DATARATE_25HZ     (ECOMPASS_U8)4
#define BSC_DATARATE_50HZ     (ECOMPASS_U8)5
#define BSC_DATARATE_100HZ    (ECOMPASS_U8)6
#define BSC_DATARATE_200HZ    (ECOMPASS_U8)7
        
/** \def Accelerometer G-Range */
#define BSC_ACCGRANGE_2G     (ECOMPASS_U8)0
#define BSC_ACCGRANGE_4G     (ECOMPASS_U8)1
#define BSC_ACCGRANGE_8G     (ECOMPASS_U8)2
#define BSC_ACCGRANGE_16G    (ECOMPASS_U8)3
                        
/** \def Sensor Accuracy Information */
#define BSC_SENSOR_STATUS_UNRELIABLE       (ECOMPASS_U8)0
#define BSC_SENSOR_STATUS_ACCURACY_LOW     (ECOMPASS_U8)1
#define BSC_SENSOR_STATUS_ACCURACY_MEDIUM  (ECOMPASS_U8)2
#define BSC_SENSOR_STATUS_ACCURACY_HIGH    (ECOMPASS_U8)3
        
/** \def Default Axis Configuration */
#define BSC_ACCAXIS_CONFIG    (ECOMPASS_U8)0
#define BSC_ACCAXIS_SIGN      (ECOMPASS_U8)0
#define BSC_MAGAXIS_CONFIG    (ECOMPASS_U8)0
#define BSC_MAGAXIS_SIGN      (ECOMPASS_U8)0

/** \def Correction Method for Calibration */
#define BSC_CORMETHOD_NONE       (ECOMPASS_U8)0
#define BSC_CORMETHOD_OFFSET     (ECOMPASS_U8)1
#define BSC_CORMETHOD_OFFSENS    (ECOMPASS_U8)2

/** \def Orientation Adaptive Filter Operation Modes */
#define BSC_ORIENTFILTERMODE_BYPASS	(ECOMPASS_U8)0
#define BSC_ORIENTFILTERMODE_LOW	(ECOMPASS_U8)1
#define BSC_ORIENTFILTERMODE_MEDIUM	(ECOMPASS_U8)2
#define BSC_ORIENTFILTERMODE_HIGH	(ECOMPASS_U8)3

#define BSC_SAMPLESTOSKIPAFTERPROFILEUPDATE (ECOMPASS_U8)30

/** \def operation modes: linear acceleration sensor */
#define BSC_FLIPGESTUREOPMODE_SLEEP     (ECOMPASS_U8)0
#define BSC_FLIPGESTUREOPMODE_REGULAR   (ECOMPASS_U8)1

/** \def defined status for flip detection */
#define BSC_FLIPGESTURE_FACING_UNKNOWN            (ECOMPASS_U8)0		
#define BSC_FLIPGESTURE_FACING_UP                 (ECOMPASS_U8)1		
#define BSC_FLIPGESTURE_FACING_DOWN               (ECOMPASS_U8)2		
#define BSC_FLIPGESTURE_FACING_NEUTRAL            (ECOMPASS_U8)3		

/** \struct ts_bsclibobject
        \brief BSC_Library configuration variables.
*/
typedef struct
{
	ECOMPASS_U8		acc_hw_id;		/**< 1 = bma250; 2 = bma222; 3 = bma255; 4 = bma280; 5=bmca022e; 6=bmca050e */
    ECOMPASS_U8		mag_hw_id;      /**< 1 = bmm050; 2 = bmm150; */
      
    /**< Accelerometer Parameter / Objects */
    ECOMPASS_U8		accOpmode;				/**< operational mode of accelerometer */
    ECOMPASS_U8		accRange;				/**< accelerometer range */
    ECOMPASS_U8		accDatarate;			/**< data rate configuration */
    ECOMPASS_U8		accAxisConfig;			/**< axis */
    ECOMPASS_U8		accAxisSign;			/**< axis sign configuration */
	ECOMPASS_U8		accCorMethod;			/**< Raw accel data correction method */
    ECOMPASS_U8     accAdvPreFiltOpMode;	/**< Accelerometer advance pre-filter mode Modes: 0-bypass 1-Active*/
    ECOMPASS_U8		accDyn4DistDetmode;		/**< mode to enable/disable acc dynamics for distortion detection */

    ECOMPASS_F32	lsb2mg;					/**< conversion factor from lsb -> mg */
    ECOMPASS_F32	mg2lsb;					/**< conversion factor from mg -> lsb */
              
    ECOMPASS_U8		accProcTick;            /**< accelerometer data processing timer tick */
    ECOMPASS_U8		accCalTick;             /**< calibration processing timer tick */
    ECOMPASS_S32	accTrigProcTimerVal;    /**< calibration timer value */
    ECOMPASS_S32	accTrigCalTimerVal;     /**< calibration timer value */
      
    /**< Magnetometer Parameter / Objects */
    ECOMPASS_U8		magOpmode;				/**<  magnetometer operational mode */
    ECOMPASS_U8		magDatarate;			/**<  magnetometer data output rate */
    ECOMPASS_U8		magAxisConfig;			/**<  mag axis configuration byte */
    ECOMPASS_U8		magAxisSign;			/**<  magnetometer axis sign configuration */
	ECOMPASS_U8		magCorMethod;			/**< Raw mag data correction method */
    ECOMPASS_U8		magAdvPreFiltOpMode;	    /**< Magenetometer advance pre-filter mode Modes: 0-bypass 1-Active*/

    ECOMPASS_F32	lsb2uT;					/**< conversion factor lsb -> uT */
    ECOMPASS_F32	uT2lsb;					/**< convesrion factor uT -> lsb */
              
    ECOMPASS_U8		magProcTick;            /**< magnetometer data processing timer tick */
    ECOMPASS_U8		magCalTick;             /**< magnetometer calibration processing timer tick */
    ECOMPASS_S32	magTrigProcTimerVal;    /**< magnetometer processing timer value */
    ECOMPASS_S32	magTrigCalTimerVal;     /**< magnetometer calibration timer value */
             
    /**< Orientation Sensor Parameter */
    ECOMPASS_U8		orientOpmode;			/**< operational mode */
    ECOMPASS_U8		orientFilterMode;		/**< filter mode configuration (by-pass, low, medium, high) */
    ECOMPASS_U8		orientProcTick;			/**< orientation sensor processing flag */
    ECOMPASS_U8		osDistFreeCnt;

    /**< M4G Parameter */  
    ECOMPASS_U8		m4gOpmode;
    ECOMPASS_U8		m4gFilterMode;			/**< filter mode configuration (by-pass, low, medium, high) */
    ECOMPASS_U8		m4gProcTick;
              
    /**< LinAcc Parameter */
	ECOMPASS_U8		linaccOpmode;
    ECOMPASS_U8		linaccProcTick;
	  
    /**< Soft Iron Correction Parameter */
	ECOMPASS_U8		magSoftIronMode;
    ts_magSoftIronSensM  magSoftIronSensMat;    /**< Soft Iron correction matrix */
	
	/**< Flip Gesture Parameter */
	ECOMPASS_U8		flipGestureOpmode;
	
	/**< Function Pointers */
	ECOMPASS_U8		(*acc_get_opmode_func)(ECOMPASS_U8 *opmode);	/**< function pointer to accelerometer read operation mode */
	ECOMPASS_U8		(*acc_set_opmode_func)(ECOMPASS_U8 opmode); 	/**< function pointer to accelerometer set operation mode function */
	ECOMPASS_U8		(*acc_get_grange_func)(ECOMPASS_U8 *range);		/**< function pointer to accelerometer read operation mode */
	ECOMPASS_U8		(*acc_set_grange_func)(ECOMPASS_U8 range);  	/**< function pointer to accelerometer set operation mode function */
	ECOMPASS_U8		(*acc_get_bandwidth_func)(ECOMPASS_U8 *bw); 	/**< function pointer to accelerometer read bandwidth settigns */
	ECOMPASS_U8		(*acc_set_bandwidth_func)(ECOMPASS_U8 bw);  	/**< function pointer to accelerometer set bandwidth */
	ECOMPASS_U8		(*acc_get_register_func)(ECOMPASS_U8 *data, ECOMPASS_U8 address, ECOMPASS_U8 count);  	/**< function pointer to accelerometer get register data */
	ECOMPASS_U8		(*acc_set_register_func)(ECOMPASS_U8 *data, ECOMPASS_U8 address, ECOMPASS_U8 count);  	/**< function pointer to accelerometer set register data */
	  
	ECOMPASS_U8		(*mag_get_opmode_func)(ECOMPASS_U8 *opmode);    /**< function pointer to magnetometer read operation mode */
	ECOMPASS_U8		(*mag_set_opmode_func)(ECOMPASS_U8 opmode); 	/**< function pointer to magnetometer set operation mode function */
}ts_bsclibobject;

/** \struct ts_accdata
        \brief Accel data.
*/
typedef struct	
{
    /**< Accelerometer Data Stack (External) */
    dataxyz_t raxyz;      /**< raw accelerometer data */
    dataxyz_t caxyz;      /**< corrected accelerometer data */
    dataxyz_t faxyz;      /**< pre-filtered accelerometer data */
} ts_accdata;

/** \struct ts_magdata
        \brief Magnetic data.
*/
typedef struct	
{
    /**< Magnetometer Data Stack (External) */
    dataxyz_t rmxyz;	/**< raw magnetometer data */
    dataxyz_t cmxyz;    /**< corrected magnetometer data */
    dataxyz_t fmxyz;    /**< pre-filtered magnetometer data */
	dataxyz_t sicmxyz;	/**< soft iron corrected magnetometer data */
} ts_magdata;

/** \struct ts_orientdata
        \brief Orientation Sensor data.
*/
typedef struct	
{
    /**< Orientation sensor Data Stack (External) */
	dataxyz_t		osdfacc;	 /**< distortion free filtered accel data */
	dataxyz_t		osdfmagc;	 /**< distortion free & tilt compensated mag data */
	dataxyz_t		osfacc;		 /**< filtered accelerometer data for compass orientation recognition */
    dataxyz_t		osfmag;      /**< filtered magnetometer data for compass orientation recognition */
    dataxyz_t		ostacc;      /**< temp accelerometer data for compass orientation recognition */
    ts_orientQuat	osquat;      /**< orientation as quaternion */
    ts_orientEuler	oseuler;     /**< orientation as euler angles */
} ts_orientdata;
	
/** \struct ts_m4gdata
        \brief M4G data.
*/
typedef struct	
{
    /**< M4G Data Stack (External) */
	dataxyz_t		m4gacc;		/**< filtered accelerometer data for compass orientation recognition */
    dataxyz_t		m4gmag;     /**< filtered magnetometer data for compass orientation recognition */
    dataxyz_t		m4gtacc;    /**< temp accelerometer data for compass orientation recognition */
    ts_orientQuat	m4gquat;	/**< orientation as quaternion */
    ts_orientEuler	m4geuler;   /**< orientation as euler angles */
} ts_m4gdata;

/** \struct ts_calibProfile
        \brief Calibration output
*/
typedef struct
{
	dataxyz_t    offset;
	ECOMPASS_S16 radius;
	ECOMPASS_U8  accuracy;
}ts_calibProfile;

/** \struct ts_Version
        \brief version format
*/
typedef struct
{
	ECOMPASS_S16 major;
	ECOMPASS_S16 minor;
	ECOMPASS_S16 bugFix;
}ts_version;

/*************************************************************************/ 
/*					ECOMPASS LIBRARY API CALLS			 				 */
/*************************************************************************/

/** \fn bsc_getVersion
        \brief Gets revision id of the Compass Library
        \param *version - library version
        \return error code
*/
ECOMPASS_S8 bsc_getVersion(ts_version *);

/** \fn bsc_get_acc_hwid(ECOMPASS_U8 *)
        \brief Returns hardware_id  of the Accelerometer
        \param *hardware_id  hardware id for accelerometer
        \return error code
*/
ECOMPASS_S8 bsc_get_acc_hwid(ECOMPASS_U8 *);

/** \fn bsc_get_mag_hwid(ECOMPASS_U8 *)
        \brief Returns hardware_id  of the Magnetometer
        \param *hardware_id  hardware id for magnetometer
        \return error code
*/
ECOMPASS_S8 bsc_get_mag_hwid(ECOMPASS_U8 *);

/** \fn bsc_set_acc_hwid(ECOMPASS_U8 *)
        \brief Sets hardware_id  of the Accelerometer
        \param hardware_id  hardware for accelerometer
        \return error code
*/
ECOMPASS_S8 bsc_set_acc_hwid(ECOMPASS_U8 );

/** \fn bsc_set_mag_hwid(ECOMPASS_U8 *)
        \brief Sets hardware_id  for Magnetometer
        \param hardware_id  hardware id for magnetometer
        \return error code
*/
ECOMPASS_S8 bsc_set_mag_hwid(ECOMPASS_U8 );

/** \fn bsc_init(ts_bsclibobject *, ECOMPASS_U8 , ECOMPASS_U8 )
        \brief eCompass Lib: Initialization of Library
		\param	p_bsclibobj	-> library object created externally
				acc_hw_id	-> hardware id for accelerometer
				mag_hw_id	-> hardware id for magnetometer
		\return status variable.
*/
ECOMPASS_S8 bsc_init(ts_bsclibobject *p_bsclibobj, ECOMPASS_U8 acc_hw_id, ECOMPASS_U8 mag_hw_id);

/** \fn bsc_run(ECOMPASS_S32 ,dataxyz_t *,dataxyz_t *,ECOMPASS_U8 ,ECOMPASS_U8 )
        \brief Main Library Process 
        \param timerValueInMSec -> timer value in microseconds
               acceldata        -> accelerometer data
               magdata          -> magnetometer data     
               extMagDistFlag1  -> Magnetic Distortion Flag1               
               extMagDistFlag2  -> Magnetic Distortion Flag2                     
        \return error code
 */
ECOMPASS_S8 bsc_run(ECOMPASS_S32 ,dataxyz_t *,dataxyz_t *,ECOMPASS_U8 ,ECOMPASS_U8 );

/** \fn bsc_accDataPreProc(ECOMPASS_S32 ,dataxyz_t *)
        \brief Accelerometer data processing routine
        \param timerValueInMSec -> timer value in microseconds
               acceldata		-> accelerometer data
        \return error code
 */
ECOMPASS_S8 bsc_accDataPreProc(ECOMPASS_S32 ,dataxyz_t *);

/** \fn bsc_accDataPreProc(ECOMPASS_S32 ,dataxyz_t *)
        \brief Magnetometer data processing routine
        \param timerValueInMSec -> timer value in microseconds
               magdata    		-> Magnetometer data
        \return error code
 */
ECOMPASS_S8 bsc_magDataPreProc(ECOMPASS_S32 ,dataxyz_t *);

/** \fn ECOMPASS_S8 bsc_accCalibProc(dataxyz_t *,ECOMPASS_U8 ,ECOMPASS_U8 ,ECOMPASS_U8 )
        \brief Accelerometer Calibration Process
        \param acceldata        -> accelerometer data
               doCalibStepTick  -> Calibration tick
               extDistFalg1     -> Distortion Flag 1
               extDistFalg1     -> Distortion Flag 2                     
        \return error code
 */
ECOMPASS_S8 bsc_accCalibProc(dataxyz_t *,ECOMPASS_U8 ,ECOMPASS_U8 ,ECOMPASS_U8 );

/** \fn ECOMPASS_S8 bsc_magCalibProc(dataxyz_t *,ECOMPASS_U8 ,ECOMPASS_U8 ,ECOMPASS_U8 )
        \brief Magnetometer Calibration Process
        \param magdata          -> Magnetometer data
               doCalibStepTick  -> Calibration tick
               extDistFalg1     -> Distortion Flag 1
               extDistFalg1     -> Distortion Flag 2                     
        \return error code
 */
ECOMPASS_S8 bsc_magCalibProc(dataxyz_t *,ECOMPASS_U8 ,ECOMPASS_U8 ,ECOMPASS_U8 );

/** \fn ECOMPASS_S8 bsc_orientDataPreProc(dataxyz_t *,dataxyz_t *,ECOMPASS_U8 ,ECOMPASS_U8 )
        \brief Orientation Sensor Pre Preprocessing
        \param acceldata -> Accelerometer data
               magdata   -> Magnetometer data
               accTick   -> Acclerometer tick
               magTick   -> Magnetometer Flag                  
        \return error code
 */
ECOMPASS_S8 bsc_orientDataPreProc(dataxyz_t *,dataxyz_t *,ECOMPASS_U8 ,ECOMPASS_U8 );

/** \fn ECOMPASS_S8 bsc_m4gDataPreProc(dataxyz_t *,dataxyz_t *,ECOMPASS_U8 ,ECOMPASS_U8 )
        \brief M4G Sensor Pre Preprocessing
        \param acceldata -> Accelerometer data
               magdata   -> Magnetometer data
               accTick   -> Acclerometer tick
               magTick   -> Magnetometer Flag                   
        \return error code
 */
ECOMPASS_S8 bsc_m4gDataPreProc(dataxyz_t *,dataxyz_t *,ECOMPASS_U8 ,ECOMPASS_U8 );

/** \fn ECOMPASS_S8 bsc_linaccDataPreProc(dataxyz_t *, ECOMPASS_U8 )
        \brief M4G Sensor Pre Preprocessing
        \param acceldata -> Accelerometer data
               accTick   -> Acclerometer tick                 
        \return error code
 */
ECOMPASS_S8 bsc_linaccDataPreProc(dataxyz_t *, ECOMPASS_U8 );

/** \fn ECOMPASS_S8 bsc_orientDataProc(dataxyz_t *,dataxyz_t *,ECOMPASS_S16 ,ECOMPASS_U8 ,ECOMPASS_U8 )
        \brief Orientation Sensor Use Case Processing
        \param acceldata        -> Accelerometer data
               magdata          -> Magnetometer data
               accDyn           -> Accleration Dynamics
               magDist          -> Magnetic Distortion
               doOrientProcFlag -> Orientation Flag
        \return error code
 */
ECOMPASS_S8 bsc_orientDataProc(dataxyz_t *,dataxyz_t *,ECOMPASS_S16 ,ECOMPASS_U8 ,ECOMPASS_U8 );

/** \fn ECOMPASS_S8 bsc_m4gDataProc(dataxyz_t *,dataxyz_t *,ECOMPASS_S16 ,ECOMPASS_U8 ,ECOMPASS_U8 )
        \brief M4G Sensor Use Case Processing
        \param acceldata      -> Accelerometer data
               magdata        -> Magnetometer data
               accDyn         -> Accleration Dynamics
               magDist        -> Magnetic Distortion
               doM4GProcFlag  -> M4G Flag
        \return error code
 */
ECOMPASS_S8 bsc_m4gDataProc(dataxyz_t *,dataxyz_t *,ECOMPASS_S16 ,ECOMPASS_U8 ,ECOMPASS_U8);

/** \fn ECOMPASS_S8 bsc_linaccDataProc(dataxyz_t *,dataxyz_t *,ECOMPASS_U8)
        \brief linear Acceleration Use Case Processing
        \param acceldata        -> Accelerometer data
               gyrodata         -> M4G data
               doLinaccProcFlag -> Linear Processing Flag
        \return error code
 */
ECOMPASS_S8 bsc_linaccDataProc(dataxyz_t *,dataxyz_t *,ECOMPASS_U8);

/** \fn ECOMPASS_S8 bsc_flipGestureDataProc(dataxyz_t *, ECOMPASS_U8 , ECOMPASS_U8)
        \brief Flip Gesture Use Case Processing
        \param acceldata             -> Accelerometer data
        \param onegflag              -> one g status
        \param doFlipGestureProcFlag -> Flip Gesture Processing Flag
        \return error code
 */
ECOMPASS_S8 bsc_flipGestureDataProc(dataxyz_t *, ECOMPASS_U8 , ECOMPASS_U8);

/*************************************************************************/ 
/*			EXTERNAL ACCELEROMETER CONFIGURATION INTERFACE 				 */
/*************************************************************************/

/** \fn ECOMPASS_S8 bsc_get_accopmode(ECOMPASS_U8 *)
        \brief Get Accelerometer Operation Mode
        \param *opmode operation mode of accelerometer
        \return error code
*/
ECOMPASS_S8 bsc_get_accopmode(ECOMPASS_U8 *);

/** \fn ECOMPASS_S8 bsc_set_accopmode(ECOMPASS_U8 )
        \brief Set Accelerometer Operation Mode
        \param opmode operation mode of accelerometer
*/
ECOMPASS_S8 bsc_set_accopmode(ECOMPASS_U8 );

/** \fn ECOMPASS_S8 bsc_get_accrange(ECOMPASS_U8 *);
        \brief Get Accelerometer Range
        \param *range of accelerometer
        \return error code
*/
ECOMPASS_S8 bsc_get_accrange(ECOMPASS_U8 *);

/** \fn ECOMPASS_S8 bsc_set_accrange(ECOMPASS_U8 )
        \brief Set Accelerometer Range
        \param range measurement g-range of accelerometer
        \return error code
*/
ECOMPASS_S8 bsc_set_accrange(ECOMPASS_U8 );

/*! \fn ECOMPASS_S8 bsc_get_accdatarate(ECOMPASS_U8 *)
        \brief Returns Current Data Output Rate of Accelerometer
        \param *rate data output rate of accelerometer
        \return error code
*/
ECOMPASS_S8 bsc_get_accdatarate(ECOMPASS_U8 *);

/*! \fn ECOMPASS_S8 bsc_set_accdatarate(ECOMPASS_U8 )
        \brief Set Accelerometer Data Output Rate
        \param rate data output rate of accelerometer
        \return error code
*/
ECOMPASS_S8 bsc_set_accdatarate(ECOMPASS_U8 );

/*! \fn ECOMPASS_S8 bsc_acc_reset()
    \brief Reset Accelerometer Sensor & Configuration Parameter
*/
ECOMPASS_S8 bsc_acc_reset(void);

/* Accelerometer remapping parameter configuration */

/*! \fn ECOMPASS_S8 bsc_compass_get_accremapparam(ECOMPASS_U8 *,ECOMPASS_U8 *);
        \brief Returns Axis Configuration & sign of Accelerometer Data
        \param *axisConfig -> axis configuration parameter for accelerometer data
               *axisSign   -> sign configuration parameter for accelerometer data
        \return error code
*/
ECOMPASS_S8 bsc_get_accremapparam(ECOMPASS_U8 *,ECOMPASS_U8 *);

/*! \fn ECOMPASS_S8 bsc_compass_set_accremapparam(ECOMPASS_U8 ,ECOMPASS_U8 );
        \brief Set axis Configuration & sign of Accelerometer Data
        \param axisConfig -> axis configuration parameter for accelerometer data
                   axisSign   -> sign configuration parameter for accelerometer data
        \return error code
*/
ECOMPASS_S8 bsc_set_accremapparam(ECOMPASS_U8 ,ECOMPASS_U8 );

/*! \fn ECOMPASS_S8 bsc_get_acccalibprofile(ts_calibProfile *)
    \brief Returns Current Calibration Profile of Accelerometer
    \param *configProfile pointer to configuration profile
        \see sensorProfile_t
*/
ECOMPASS_S8 bsc_get_acccalibprofile(ts_calibProfile *);

/*! \fn ECOMPASS_S8 bsc_set_acccalibprofile(ts_calibProfile *)
    \brief Set Current Calibration Profile of Accelerometer
    \param *configProfile pointer to configuration profile
        \see sensorProfile_t
*/
ECOMPASS_S8 bsc_set_acccalibprofile(ts_calibProfile *);

/*! \fn ECOMPASS_S8 bsc_get_acccalibparam(dataxyz_t *,ECOMPASS_S16 *)
        \brief get the estimated offset and sensitivity parameters of the accelerometer
        \param dataxyz_t *sens  -> returns the estimated offset of the accelerometer
			   ECOMPASS_S16 *p_radius_s16r -> returns the radius
        \return error code
*/
ECOMPASS_S8 bsc_get_acccalibparam(dataxyz_t *,ECOMPASS_S16 *);

/*! \fn ECOMPASS_S8 bsc_set_acccalibmode(ECOMPASS_U8 )
        \brief set the conrols active for observer, calib and the method according to the mode
        \param mode -> the set mode to be used for calibration activation for accelerometer
        \return error code
*/
ECOMPASS_S8 bsc_set_acccalibmode(ECOMPASS_U8 );

/*! \fn ECOMPASS_S8 bsc_set_acccalib_accuracy_threshold(ECOMPASS_U8 )
        \brief set the calibration accuracy threshold
        \param accurThres -> accuracy threshold
        \return error code
*/
ECOMPASS_S8 bsc_set_acccalib_accuracy_threshold(ECOMPASS_U8 );

/*! \fn ECOMPASS_U8 bsc_acccalib_reset()
        \brief reset the accelerometer calibration module including calibration parameter
           observation objects, calibration objects, internal states
        \param none
        \return error code
*/
ECOMPASS_U8 bsc_acccalib_reset(void);

/*************************************************************************/ 
/*					  ACCELEROMETER DATA INTERFACE		   				 */
/*************************************************************************/

/*! \fn ECOMPASS_S8 bsc_get_accrawdata_lsb(dataxyz_t *)
        \brief get the raw accelerometer data and convert to LSB from mg
        \param dataxyz_t *outdata -> accel data in LSB
        \return error code
*/
ECOMPASS_S8 bsc_get_accrawdata_lsb(dataxyz_t *);

/*! \fn ECOMPASS_S8 bsc_get_accrawdata_ms2(dataxyzF32_t *)
        \brief get the raw accelerometer data and convert to ms2 from mg
        \param dataxyz_t *outdata -> accel data in ms2
        \return error code
*/
ECOMPASS_S8 bsc_get_accrawdata_ms2(dataxyzF32_t *);

/*! \fn ECOMPASS_S8 bsc_get_acccordata_lsb(dataxyz_t *)
        \brief get the corrected accelerometer data and convert to LSB from mg
        \param dataxyz_t *outdata -> accel data in LSB
        \return error code
*/
ECOMPASS_S8 bsc_get_acccordata_lsb(dataxyz_t *);

/*! \fn ECOMPASS_S8 bsc_get_acccordata_ms2(dataxyzF32_t *)
        \brief get the corrected accelerometer data and convert to ms2 from mg
        \param dataxyz_t *outdata -> accel data in ms2
        \return error code
*/
ECOMPASS_S8 bsc_get_acccordata_ms2(dataxyzF32_t *);

/*! \fn ECOMPASS_S8 bsc_get_accfiltdata_lsb(dataxyz_t *)
        \brief get the filtered accelerometer data and convert to LSB from mg
        \param dataxyz_t *outdata -> accel data in LSB
        \return error code
*/
ECOMPASS_S8 bsc_get_accfiltdata_lsb(dataxyz_t *);

/*! \fn ECOMPASS_S8 bsc_get_accfiltdata_ms2(dataxyzF32_t *)
        \brief get the filtered accelerometer data and convert to ms2 from mg
        \param dataxyz_t *outdata -> accel data in ms2
        \return error code
*/
ECOMPASS_S8 bsc_get_accfiltdata_ms2(dataxyzF32_t *);

/*! \fn ECOMPASS_S8 bsc_get_accdatastatus(ECOMPASS_U8 *)
        \brief Returns Calibration Accuracy Status of Accelerometer Data
        \param *status calibration accuracy of accelerometer
        \see sensor_calib_accur_status
*/
ECOMPASS_S8 bsc_get_accdatastatus(ECOMPASS_U8 *);

/*************************************************************************/ 
/*			   EXTERNAL MAGNETOMETER CONFIGURATION INTERFACE			 */
/*************************************************************************/ 

/*! \fn bsc_get_magopmode
        \brief returns operation mode of magnetometer.
        \param [out] -> pointer to hold magnetometer opmode of type ECOMPASS_U8
        \return status variable
*/
ECOMPASS_S8 bsc_get_magopmode(ECOMPASS_U8 *);

/*! \fn bsc_set_magopmode
        \brief Sets the operation mode of magnetometer.
        \param [in] -> mode of operation of magnetometer of type ECOMPASS_U8
        \return Status variable.
*/
ECOMPASS_S8 bsc_set_magopmode(ECOMPASS_U8);

/*! \fn bsc_get_magdatarate
        \brief Returns the datarate of the magnetometer.
        \param [out] -> pointer to hold magnetometer datarate of type ECOMPASS_U8
        \return status variable.
*/
ECOMPASS_S8 bsc_get_magdatarate(ECOMPASS_U8 *);

/*! \fn bsc_set_magdatarate
        \brief sets the datarate of the magnetometer.
        \param [in] -> datarate of magnetometer of type ECOMPASS_U8
        \return status variable
*/
ECOMPASS_S8 bsc_set_magdatarate(ECOMPASS_U8);

/*! \fn bsc_mag_reset
        \brief resets the magnetometer configuration to default settings.
        \param none
        \return status variable
*/
ECOMPASS_S8 bsc_mag_reset(void);

/*! \fn bsc_get_magremapparam
        \brief returns the magnetometer data remapping configuration details
        \param [out] -> pointer to hold the value indicating axis configuration of type ECOMPASS_U8
		\param [out] -> pointer to hold the sign of axis of type ECOMPASS_U8
        \return status variable
*/
ECOMPASS_S8 bsc_get_magremapparam(ECOMPASS_U8 *, ECOMPASS_U8 *);

/*! \fn bsc_set_magremapparam
        \brief configures settings for magnetometer data remapping
        \param [out] -> variable to hold the value indicating axis configuration of type ECOMPASS_U8
		\param [out] -> variable to hold the sign of axis of type ECOMPASS_U8
        \return status variable
*/
ECOMPASS_S8 bsc_set_magremapparam(ECOMPASS_U8, ECOMPASS_U8);

/*! \fn ECOMPASS_S8 bsc_get_magcalibprofile(ts_calibProfile *)
        \brief Access to mag calibration data (offsets and data accuracy)
        \param [out] -> pointer to structure containing calibration profile of type ts_calibProfile
		\return status variable
*/
ECOMPASS_S8 bsc_get_magcalibprofile(ts_calibProfile *);

/*! \fn ECOMPASS_S8 bsc_set_magcalibprofile(ts_calibProfile *)
        \brief API to set magnetic data calibration profile 
        \param [in] -> pointer to structure containing calibration profile of type ts_calibProfile
		\return status variable
*/
ECOMPASS_S8 bsc_set_magcalibprofile(ts_calibProfile *);

/*! \fn bsc_set_magcalibmode
        \brief API sets the operation mode for calibration of magnetometer data.
        \param [in] -> mode of magnetometer data calibration of type ECOMPASS_U8
		\return status variable
*/
ECOMPASS_S8 bsc_set_magcalibmode(ECOMPASS_U8);

/*! \fn bsc_get_magcalibparam
        \brief gives the estimated offsets and radius derived from the calibration of magnetometer data.
        \param [out] -> pointer to hold estimated offsets(x,y,z) of type ECOMPASS_S16.
		\param [out] -> pointer to hold estimated radius of type ECOMPASS_S16
		\return status variable
*/
ECOMPASS_S8 bsc_get_magcalibparam(dataxyz_t *, ECOMPASS_S16 *);

/*! \fn bsc_set_magcalib_accuracy_threshold_initial
        \brief To set the threshold value for initial calibration accuracy for magnetometer data.
        \param [in] -> Accuracy threshold of type ECOMPASS_U8.
					   (value = 40 .. 100; / default 60)
                \return status variable
*/
ECOMPASS_S8 bsc_set_magcalib_accuracy_threshold_initial(ECOMPASS_U8);



/*! \fn bsc_set_magcalib_accuracy_threshold
        \brief To set the threshold value for calibration accuracy for magnetometer data.
        \param [in] -> Accuracy threshold of type ECOMPASS_U8.
		\return status variable
*/
ECOMPASS_S8 bsc_set_magcalib_accuracy_threshold(ECOMPASS_U8);

/*! \fn bsc_magcalib_reset
        \brief API resets the calibration configuration for magnetometer data to the default settings.
        \param none
		\return status variable
*/
ECOMPASS_S8 bsc_magcalib_reset(void);

/*! \fn bsc_set_magcalib_process_noise
 *      \brief API sets the mag calibration process noise parameter with the values passed
 *      \param [in] -> processNoiseDiag (diagonal elements of process noise matrix) of type ECOMPASS_F32
 *     			 \ return status variable
 */

ECOMPASS_S8 bsc_set_magcalib_process_noise(ECOMPASS_F32 *);

/*! \fn bsc_get_magcalib_process_noise
 *      \brief API used to get the mag calibration process noise value set
 *      \param [out] -> processNoiseDiag - to hold the diagonal elements of process noise matrix
 *      			\ return status variable
 */

ECOMPASS_S8 bsc_get_magcalib_process_noise(ECOMPASS_F32 *);

/*! \fn bsc_set_magcalib_accurDistResetFlag
 *      \brief API used to enable or disable the mag calibration accuracy Distortion Reset flag according to distortion
 *      \param [in]-> flag of type ECOMPASS_U8
 *      			\ return status variable
 */

ECOMPASS_S8 bsc_set_magcalib_accurDistResetFlag(ECOMPASS_U8 );

/*! \fn bsc_get_magcalib_accurDistResetFlag
 *      \brief API used to get the mag calibration accuracy Distortion Reset flag value
 *      \param [out]-> flag to hold the accuracy status of type ECOMPASS_U8
 *      			\ return status variable
 */

ECOMPASS_S8 bsc_get_magcalib_accurDistResetFlag(ECOMPASS_U8 *);

/*************************************************************************/ 
/*					  MAGNETOMETER DATA INTERFACE		   				 */
/*************************************************************************/

/*! \fn bsc_get_magrawdata_lsb
        \brief API to access raw magnetometer data(in LSB units)
        \param [out] -> pointer variable to hold the raw magnetometer data(x,y,z) of type ECOMPASS_S16
		\return status variable
*/
ECOMPASS_S8 bsc_get_magrawdata_lsb(dataxyz_t *);

/*! \fn bsc_get_magrawdata_microtesla
        \brief API to access raw magnetometer data(in uT units)
        \param [out] -> pointer variable to hold the raw magnetometer data(x,y,z) of type ECOMPASS_S16
		\return status variable
*/
ECOMPASS_S8 bsc_get_magrawdata_microtesla(dataxyzF32_t *);

/*! \fn bsc_get_magcordata_lsb
        \brief API to access corrected magnetometer data(in LSB units)
        \param [out] -> pointer variable to hold the corrected magnetometer data(x,y,z) of type ECOMPASS_S16
		\return status variable
*/
ECOMPASS_S8 bsc_get_magcordata_lsb(dataxyz_t *);

/*! \fn bsc_get_magcordata_microtesla
        \brief API to access corrected magnetometer data(in uT units)
        \param [out] -> pointer variable to hold the corrected magnetometer data(x,y,z) of type ECOMPASS_S16
		\return status variable
*/
ECOMPASS_S8 bsc_get_magcordata_microtesla(dataxyzF32_t *);

/*! \fn bsc_get_magfiltdata_lsb
        \brief API to access filtered magnetometer data(in LSB units)
        \param [out] -> pointer variable to hold the filtered magnetometer data(x,y,z) of type ECOMPASS_S16
		\return status variable
*/
ECOMPASS_S8 bsc_get_magfiltdata_lsb(dataxyz_t *);

/*! \fn bsc_get_magfiltdata_microtesla
        \brief API to access filtered magnetometer data(in uT units)
        \param [out] -> pointer variable to hold the filtered magnetometer data(x,y,z) of type ECOMPASS_S16
		\return status variable
*/
ECOMPASS_S8 bsc_get_magfiltdata_microtesla(dataxyzF32_t *);

/*! \fn bsc_get_magdatastatus
        \brief Returns the accuracy status of the magnetometer data.
        \param [out] -> pointer to hold the accuracy status of type ECOMPASS_S8
		\return status variable
*/
ECOMPASS_S8 bsc_get_magdatastatus(ECOMPASS_U8 *);

/*************************************************************************/ 
/*		 EXTERNAL ORIENTATION SENSOR CONFIGURATION INTERFACE			 */
/*************************************************************************/

/*! \fn bsc_get_orientopmode
        \brief Returns the operation mode of orientation sensor module.
        \param [out] -> pointer variable to hold value of orientation sensor operation mode of type ECOMPASS_U8
		\return status variable.
*/
ECOMPASS_S8 bsc_get_orientopmode(ECOMPASS_U8 *);

/*! \fn bsc_set_orientopmode
        \brief Sets the operation mode of orientation sensor module.
        \param [in] -> orientation sensor operation mode of type ECOMPASS_U8
		\return status variable.
*/
ECOMPASS_S8 bsc_set_orientopmode(ECOMPASS_U8);

/*! \fn bsc_set_orientfiltermode
        \brief Sets the mode of filtering for the orientation sensor module.
        \param [in] -> orientation sensor filter operation mode of type ECOMPASS_U8
		\return status variable.
*/
ECOMPASS_S8 bsc_set_orientfiltermode(ECOMPASS_U8);

/*! \fn bsc_set_orientAccNoiseThreshold
        \brief Sets the noise threshold value for the orientation sensor module for accel data.
        \param [in] -> orientation sensor noise threshold value of type ECOMPASS_S16
		\return status variable.
*/
ECOMPASS_S8 bsc_set_orientAccNoiseThreshold(ECOMPASS_S16);

/*! \fn bsc_set_orientMagNoiseThreshold
        \brief Sets the noise threshold value for the orientation sensor module for magnetic data.
        \param [in] -> orientation sensor noise threshold value of type ECOMPASS_S16
		\return status variable.
*/
ECOMPASS_S8 bsc_set_orientMagNoiseThreshold(ECOMPASS_S16);

/*! \fn bsc_get_orientAccNoiseThreshold
        \brief Gets the orient accel noise threshold
        \param [in] -> orientation sensor noise threshold value of type ECOMPASS_S16
		\return status variable.
*/
ECOMPASS_S8 bsc_get_orientAccNoiseThreshold(ECOMPASS_S16 *);

/*! \fn bsc_get_orientMagNoiseThreshold
        \brief Gets the orient mag noise threshold
        \param [in] -> orientation sensor noise threshold value of type ECOMPASS_S16
		\return status variable.
*/
ECOMPASS_S8 bsc_get_orientMagNoiseThreshold(ECOMPASS_S16 *);

/*! \fn bsc_set_orientAccFilterParam
        \brief Sets the noise threshold value for the orientation sensor module for magnetic data.
        \param [in] -> orientation sensor noise threshold value of type ECOMPASS_S16
		\return status variable.
*/
ECOMPASS_S8 bsc_set_orientAccFilterParam(ECOMPASS_F32 , ECOMPASS_F32 );

/*! \fn bsc_set_orientMagFilterParam
        \brief Sets the filter param value for the orientation sensor module for magnetic data.
        \param [in] -> orientation sensor noise threshold value of type ECOMPASS_F32
		\return status variable.
*/
ECOMPASS_S8 bsc_set_orientMagFilterParam(ECOMPASS_F32 , ECOMPASS_F32 );

/*! \fn bsc_get_orientAccFilterParam
        \brief Gets the noise threshold value for the orientation sensor module for Accel data.
        \param [in] -> orientation sensor noise threshold value of type ECOMPASS_F32
		\return status variable.
*/
ECOMPASS_S8 bsc_get_orientAccFilterParam(ECOMPASS_F32 *, ECOMPASS_F32 *);

/*! \fn bsc_get_orientMagFilterParam
        \brief Gets the orient filter param.
        \param [in] -> orientation sensor noise threshold value of type ECOMPASS_F32
		\return status variable.
*/
ECOMPASS_S8 bsc_get_orientMagFilterParam(ECOMPASS_F32 *, ECOMPASS_F32 *);
/*************************************************************************/ 
/*					ORIENTATION SENSOR DATA INTERFACE					 */
/*************************************************************************/

/*! \fn bsc_get_orientdata_fquat
        \brief API to access filtered quaternion data from Orientation Sensor module
        \param [out] -> pointer variable to hold filtered quaternion data(w,x,y,z) of type ts_orientQuat
		\return status variable.
*/
ECOMPASS_S8 bsc_get_orientdata_fquat(ts_orientQuat *);

/*! \fn bsc_get_orientdata_feuler
        \brief API to access filtered euler data(heading, pitch, roll) from Orientation Sensor module
        \param [out] -> pointer variable to hold filtered heading value of type ECOMPASS_S16
		\param [out] -> pointer variable to hold filtered pitch value of type ECOMPASS_S16
		\param [out] -> pointer variable to hold filtered roll value of type ECOMPASS_S16
		\return status variable.
*/
ECOMPASS_S8 bsc_get_orientdata_feuler(ts_orientEuler *);

/*! \fn bsc_get_orientdata_rquat
        \brief API to access raw quaternion data from Orientation Sensor module
        \param [out] -> pointer variable to hold raw quaternion data(w,x,y,z) of type ts_orientQuat
		\return status variable.
*/
ECOMPASS_S8 bsc_get_orientdata_rquat(ts_orientQuat *);

/*! \fn bsc_get_orientdata_reuler
        \brief API to access raw euler data(heading, pitch, roll) from Orientation Sensor module
        \param [out] -> pointer variable to hold raw heading value of type ECOMPASS_S16
		\param [out] -> pointer variable to hold raw pitch value of type ECOMPASS_S16
		\param [out] -> pointer variable to hold raw roll value of type ECOMPASS_S16
		\return status variable.
*/
ECOMPASS_S8 bsc_get_orientdata_reuler(ts_orientEuler *);

/*! \fn bsc_get_orientdata_status
        \brief tbd
        \param tbd
		\return status variable.
*/
ECOMPASS_S8 bsc_get_orientdata_status(ECOMPASS_U8 *);

/*************************************************************************/ 
/*					EXTERNAL M4G SENSOR INTERFACE						 */
/*************************************************************************/

/** \fn ECOMPASS_S8 bsc_get_m4gopmode(ECOMPASS_U8 *)
        \brief Get M4G Operation Mode
        \param *opmode operation mode of M4G
        \return error code
*/
ECOMPASS_S8 bsc_get_m4gopmode(ECOMPASS_U8 *);

/** \fn ECOMPASS_S8 bsc_set_m4gopmode(ECOMPASS_U8 )
        \brief Set M4G Operation Mode
        \param opmode operation mode of M4G
		\return error code
*/
ECOMPASS_S8 bsc_set_m4gopmode(ECOMPASS_U8 );

/** \fn ECOMPASS_S8 bsc_get_m4gdata_angularrate(dataxyz_t *)
        \brief Reads M4G Data
        \param dataxyz_t -> M4G angular data
        \return error code
*/
ECOMPASS_S8 bsc_get_m4gdata_angularrate(dataxyz_t *);

/** \fn ECOMPASS_S8 bsc_get_m4gdatastatus(ECOMPASS_U8 *)
        \brief Reads M4G Status
        \param *status -> Status for M4G Data
        \return error code
*/
ECOMPASS_S8 bsc_get_m4gdatastatus(ECOMPASS_U8 *);

/** \fn ECOMPASS_S8 bsc_get_m4gdata_quat(ts_orientQuat *)
        \brief Reads M4G Data
        \param 
        \return error code
*/
ECOMPASS_S8 bsc_get_m4gdata_quat(ts_orientQuat *);

/** \fn ECOMPASS_S8 bsc_get_m4gdata_euler(ts_orientEuler *)
        \brief Reads M4G Data
        \param ts_orientEuler *-> orientation structure containing Euler's data
        \return error code
*/
ECOMPASS_S8 bsc_get_m4gdata_euler(ts_orientEuler *);

/** \fn ECOMPASS_S8 bsc_set_m4gAccNoiseThreshold(ECOMPASS_U8 )
        \brief set acclerometer noise threshold 
        \param Vaslue of threshold
        \return error code
*/
ECOMPASS_S8 bsc_set_m4gAccNoiseThreshold(ECOMPASS_S16);

/** \fn ECOMPASS_S8 bsc_set_m4gMagNoiseThreshold(ECOMPASS_S16 )
        \brief set magnetometer noise threshold 
        \param Vaslue of threshold
        \return error code
*/
ECOMPASS_S8 bsc_set_m4gMagNoiseThreshold(ECOMPASS_S16);

/*************************************************************************/ 
/*					EXTERNAL LINACC SENSOR INTERFACE					 */
/*************************************************************************/

/** \fn ECOMPASS_S8 bsc_get_linaccopmode(ECOMPASS_U8 *)
        \brief Get linear accelerometer Operation Mode
        \param *opmode operation mode of linera accelerometer
        \return error code
*/
ECOMPASS_S8 bsc_get_linaccopmode(ECOMPASS_U8 *);

/** \fn ECOMPASS_S8 bsc_set_linaccopmode(ECOMPASS_U8 )
        \brief Set linear accelerometer Operation Mode
        \param opmode operation mode of linera accelerometer
		\return error code
*/
ECOMPASS_S8 bsc_set_linaccopmode(ECOMPASS_U8 );

/** \fn ECOMPASS_S8 bsc_get_linaccdata_lsb(dataxyz_t *)
        \brief Reads linear acceleration Data in LSB
        \param dataxyz_t * -> Output of linear acceleration data
        \return error code
*/
ECOMPASS_S8 bsc_get_linaccdata_lsb(dataxyz_t *);

/** \fn ECOMPASS_S8 bsc_get_linaccdata_ms2(dataxyzF32_t *)
        \brief Reads linear acceleration Data in ms2
        \param dataxyz_t * -> Output of linear acceleration data
        \return error code
*/
ECOMPASS_S8 bsc_get_linaccdata_ms2(dataxyzF32_t *);

/****** EXTENDED LIBRARY FUNCTION FOR ADVANCED FILTERING OF THE RAW SENSOR DATA *********/

/** \fn ECOMPASS_U8 bsc_accAdvPreFilterMode(ECOMPASS_U8 mode);
        \brief operation mode of the accelerometer pre-filter
        \param ECOMPASS_U8 mode is the operation mode of the filter: 0 - deactivated; 1 - active
        \return error code
*/
ECOMPASS_U8 bsc_accAdvPreFilterMode(ECOMPASS_U8 mode);

/** \fn ECOMPASS_U8 bsc_magAdvPreFilterMode(ECOMPASS_U8 mode);
        \brief operation mode of the magnetometer pre-filter
        \param ECOMPASS_U8 mode is the operation mode of the filter: 0 - deactivated; 1 - active
        \return error code
*/
ECOMPASS_U8 bsc_magAdvPreFilterMode(ECOMPASS_U8 mode);

/** \fn ECOMPASS_U8 bsc_set_accAdvPreFilterParam(ECOMPASS_U8 coef, ECOMPASS_U8 noiLevel);
        \brief configuration of the accelerometer filtering parameter
        \param ECOMPASS_U8 coef - filtering coefficient : 0 .. 99 (default: 60)
		\param ECOMPASS_U8 noiLevel - noise level to suppress the output: 0 .. 50 (lsb)
        \return error code
*/
ECOMPASS_U8 bsc_set_accAdvPreFilterParam(ECOMPASS_U8 coef, ECOMPASS_U8 noiLevel);

/** \fn ECOMPASS_U8 bsc_set_magAdvPreFilterParam(ECOMPASS_U8 coef, ECOMPASS_U8 noiLevel);
        \brief configuration of the magnetometer filtering parameter
        \param ECOMPASS_U8 coef - filtering coefficient : 0 .. 99 (default: 60)
		\param ECOMPASS_U8 noiLevel - noise level to suppress the output: 0 .. 99 (lsb)
        \return error code
*/
ECOMPASS_U8 bsc_set_magAdvPreFilterParam(ECOMPASS_U8 coef, ECOMPASS_U8 noiLevel);

/*************************************************************************/ 
/*					EXTERNAL SOFT IRON CORRECTION INTERFACE				 */
/*************************************************************************/

/** \fn ECOMPASS_U8 bsc_set_softIronCorrectionMode(ECOMPASS_U8 mode)
        \brief set the soft iron correction mode
        \param ECOMPASS_U8 mode - soft iron correction mode
        \return error code
*/
ECOMPASS_U8 bsc_set_SoftIronCorrectionMode(ECOMPASS_U8 mode);

/** \fn ECOMPASS_U8 bsc_set_softIronCorrectionMatrix(ts_magSoftIronSensM sensMat)
        \brief set the soft iron correction matrix
        \param ts_magSoftIronSensM sensMat - soft iron correction matrix
        \return error code
*/
ECOMPASS_U8 bsc_set_SoftIronCorrectionMatrix(ts_magSoftIronSensM sensMat);

/** \fn ECOMPASS_U8 bsc_get_softIronCorrectionMatrix(ts_magSoftIronSensM *sensMat)
        \brief get the soft iron correction matrix
        \param ts_magSoftIronSensM *sensMat - soft iron correction matrix
        \return error code
*/
ECOMPASS_U8 bsc_get_SoftIronCorrectionMatrix(ts_magSoftIronSensM *sensMat);

/*************************************************************************/ 
/*			ACCEL DYNAMIC FOR DISTORTION DETECTION INTERFACE			 */
/*************************************************************************/

/* fn ECOMPASS_S8 bsc_get_accDyn4DistDetmode(ECOMPASS_U8 *) 
		\brief get accelerometer dynamic check mode
		\param *mode
		\return error code
*/
ECOMPASS_S8 bsc_get_accDyn4DistDetmode(ECOMPASS_U8 *);

/* fn ECOMPASS_S8 bsc_set_accDyn4DistDetmode(ECOMPASS_U8) 
		\brief set accelerometer dynamic check mode
		\param mode
		\return error code
*/
ECOMPASS_S8 bsc_set_accDyn4DistDetmode(ECOMPASS_U8);

/*************************************************************************/ 
/*							FLIP GESTURE INTERFACE						 */
/*************************************************************************/

/* fn ECOMPASS_S8 bsc_get_flipgesture_opmode(ECOMPASS_U8 *) 
		\brief get flip gesture detection operational mode 
		\param *mode (sleep[0]/regular[1])
		\return error code
*/
ECOMPASS_S8 bsc_get_flipgesture_opmode(ECOMPASS_U8 *);

/* fn ECOMPASS_S8 bsc_set_flipgesture_opmode(ECOMPASS_U8) 
		\brief set flip gesture detection operational mode
		\param mode (sleep[0]/regular[1])
		\return error code
*/
ECOMPASS_S8 bsc_set_flipgesture_opmode(ECOMPASS_U8);

/* fn ECOMPASS_S8 bsc_get_flipgesture_angle(ECOMPASS_U8 *, ECOMPASS_U8 *) 
		\brief get flip gesture detection angle in degrees
		\param *angle_facedown (range[10 to 80], default[15], unit[degrees])
		\param *angle_faceup (range[100 to 170], default[105], unit[degrees])		
		\return error code
*/
ECOMPASS_S8 bsc_get_flipgesture_angle(ECOMPASS_U8 *, ECOMPASS_U8 *);

/* fn ECOMPASS_S8 bsc_set_flipgesture_angle(ECOMPASS_U8, ECOMPASS_U8) 
		\brief set flip gesture detection angle in degrees
		\param *angle_facedown (range[10 to 80], default[15], unit[degrees])
		\param *angle_faceup (range[100 to 170], default[105], unit[degrees])		
		\return error code
*/
ECOMPASS_S8 bsc_set_flipgesture_angle(ECOMPASS_U8, ECOMPASS_U8);

/* fn ECOMPASS_S8 bsc_get_flipgesture_detecttime(ECOMPASS_U16 *) 
		\brief get flip gesture detection time in milli seconds 
		\param *detecttime (range[100 to 5000], default[500], unit[milliseconds])
		\return error code
*/
ECOMPASS_S8 bsc_get_flipgesture_detecttime(ECOMPASS_U16 *);

/* fn ECOMPASS_S8 bsc_set_flipgesture_detecttime(ECOMPASS_U16) 
		\brief set flip gesture detection time in milli seconds 
		\param *detecttime (range[100 to 5000], default[500], unit[milliseconds])
		\return error code
*/
ECOMPASS_S8 bsc_set_flipgesture_detecttime(ECOMPASS_U16);

/* fn ECOMPASS_S8 bsc_get_flipgesture_status(ECOMPASS_U8 *) 
		\brief get flip gesture status
		\param *status (facedown[0]/faceup[1])
		\return error code
*/
ECOMPASS_S8 bsc_get_flipgesture_status(ECOMPASS_U8 *);

#endif

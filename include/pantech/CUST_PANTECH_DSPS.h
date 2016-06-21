/*                                                                                                                                
 * =================================================================
 *
 *       Filename:  CUCST_PANTECH_DSPS.c
 *
 *    Description:  
 *
 *        Version:  1.1
 *        Created:  09/18/12 13:25:26
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  LS2 SENSOR, 
 *        Company:  
 *
 * =================================================================
 */

/*
 * =================================================================
 * EDIT HISTORY FOR MODULE

 * This section contains comments describing changes made to the module.
 * Notice that changes are listed in reverse chronological order. Please use ISO format for dates.

 *   $DateTime: 2011/11/09 16:58:38 $

 * when       who    what, where, wh
  ---------- --- ---------------------------------------------------
  2012-09-18 sgh Global feature be imported for JB
  2012-09-12 sgh Initial revision
  2012-10-17 shp Feature seperation by sensor type

 * =================================================================
 */

#ifndef _CUST_PANTECH_DSPS_H_
#define _CUST_PANTECH_DSPS_H_

#include "CUST_PANTECH_SENSORLIST.h"

#ifdef CONFIG_PANTECH_DSPS_ENABLE

/*
 * =================================================================
 * 1. COMMON
 * =================================================================
 */

/* -----------------------------------------------------------------
 * PANTECH_DSPS_PREVENT_DEADLOCK_ANR
 * -----------------------------------------------------------------
 *   .Brif          : prevent DEADLOCK and ANR
 *   .Applied Block : libqctdspstest & test app
 *   .Applied Files : 
 *                    LINUX/android/pantech/frameworks/dspstest/jni/src/sensor_test.c
 *                    LINUX/android/pantech/apps/SkyMenu/src/com/pantech/app/test_menu/apps/SensorTest4648.java
 *                    LINUX/android/pantech/apps/SkyMenu/src/com/pantech/app/test_menu/apps/SensorTest8378522.java
 * ---------------------------------------------------------------*/
#define PANTECH_DSPS_PREVENT_DEADLOCK_ANR

 /* -----------------------------------------------------------------
 * PANTECH_DSPS_TIMER_ROLLOVER_BUG_FIX
 * -----------------------------------------------------------------
 *   .Brif          : rollover bug fix in hal_timestamp_calc function of HAL 
 *   .Applied Block : sensordaemon & HAL
 *   .Applied Files : 
 *                    LINUX/android/vendor/qcom/proprietary/sensors/dsps/libhalsensors/src/sensors_qcom_hal.c
 *                    LINUX/android/vendor/qcom/proprietary/sensors/dsps/sensordaemon/time/src/sns_time.c
 * ---------------------------------------------------------------*/
#define PANTECH_DSPS_TIMER_ROLLOVER_BUG_FIX

 /* -----------------------------------------------------------------
 * PANTECH_DSPS_AVOID_DAEMON_ASSERT_BY_LOW_MEMORY
 * -----------------------------------------------------------------
 *   .Brif          : avoid daemon assert by error which could not allocate heap memory (QCT : testSBA_F8064AAAAANLYD1233.3 _Pantech_12132012)
 *   .Applied Block : sensordaemon
 *   .Applied Files : 
 *                    LINUX/android/vendor/qcom/proprietary/sensors/dsps/sensordaemon/apps/common/sns_debug/inc/sns_string_db.h
 *                    LINUX/android/vendor/qcom/proprietary/sensors/dsps/sensordaemon/common/inc/sns_debug_api.h
 *                    LINUX/android/vendor/qcom/proprietary/sensors/dsps/sensordaemon/common/smr/src/sns_smr.c
 *                    LINUX/android/vendor/qcom/proprietary/sensors/dsps/sensordaemon/common/smr/src/sns_smr_priv.h
 *                    LINUX/android/vendor/qcom/proprietary/sensors/dsps/sensordaemon/common/util/memmgr/inc/oi_support_init.h
 *                    LINUX/android/vendor/qcom/proprietary/sensors/dsps/sensordaemon/common/util/memmgr/inc/sns_memmgr.h
 *                    LINUX/android/vendor/qcom/proprietary/sensors/dsps/sensordaemon/common/util/memmgr/src/oi_memmgr.c
 *                    LINUX/android/vendor/qcom/proprietary/sensors/dsps/sensordaemon/common/util/memmgr/src/sns_memmgr.c
 * ---------------------------------------------------------------*/
#define PANTECH_DSPS_AVOID_DAEMON_ASSERT_BY_LOW_MEMORY

 /* -----------------------------------------------------------------
 * PANTECH_DSPS_FIRST_PDL_ERROR_FIX
 * -----------------------------------------------------------------
 *   .Brif          : fix first pdl error
 *   .Applied Block : init process & sensordaemon
 *   .Applied Files : 
 *                    LINUX/android/vendor/qcom/proprietary/sensors/dsps/sensordaemon/main/src/sns_main.c
 *                    LINUX/android/device/qcom/common/rootdir/etc/init.qcom.rc
 * ---------------------------------------------------------------*/
#define PANTECH_DSPS_FIRST_PDL_ERROR_FIX

/* -----------------------------------------------------------------
 * PANTECH_DSPS_CHECK_DEVICE_VERSION
 * -----------------------------------------------------------------
 *   .Brif          : check device version is over 1 (because of CTS test)
 *   .Applied Block : HAL
 *   .Applied Files : 
 *                    LINUX/android/vendor/qcom/proprietary/sensors/dsps/libhalsensors/src/sensors_qcom_hal.c
 * ---------------------------------------------------------------*/
#define PANTECH_DSPS_CHECK_DEVICE_VERSION

 /* -----------------------------------------------------------------
 * PANTECH_DSPS_LOGGING
 * -----------------------------------------------------------------
 *   .Brif          : 불필요한 Qualcomm 로그 삭제 및 필요한 로그 추가
 *   .Applied Block : HAL & sensordaemon
 *   .Applied Files : 
 *                    LINUX/android/vendor/qcom/proprietary/sensors/dsps/libhalsensors/src/sensors_qcom_hal.c
 *                    LINUX/android/vendor/qcom/proprietary/sensors/dsps/sensordaemon/main/src/sns_main.c
  *                   LINUX/android/vendor/qcom/proprietary/sensors/QSensorTest/src/com/qualcomm/sensors/qsensortest/SensorStreamEventListener.java
 * ---------------------------------------------------------------*/
#define PANTECH_DSPS_LOGGING

/* -----------------------------------------------------------------
 * PANTECH_DSPS_USE_NOT_OEM_SHARED_LIBRARY
 * -----------------------------------------------------------------
 *   .Brif          : 사용하지 않는 OEM LIB 관련 불필요한 처리 방지
 *   .Applied Block : HAL
 *   .Applied Files : 
 *                    LINUX/android/vendor/qcom/proprietary/sensors/dsps/libhalsensors/src/sensors_qcom_hal.c
 * ---------------------------------------------------------------*/
#define PANTECH_DSPS_USE_NOT_OEM_SHARED_LIBRARY

 /* -----------------------------------------------------------------
 * PANTECH_DSPS_ENCRYPTION
 * -----------------------------------------------------------------
 *   .Brif          : Encryption Mode 에서도 센서가 정상 동작 할 수 있도록 처리
 *   .Applied Block : HAL & sensordaemon & SensorService & init process
 *   .Applied Files :
 *                    LINUX/android/device/qcom/common/rootdir/etc/init.qcom.rc
 *                    LINUX/android/system/core/rootdir/init.rc
 *                    LINUX/android/vendor/qcom/proprietary/sensors/dsps/libsensor1/inc/libsensor1.h
 *                    LINUX/android/frameworks/base/services/sensorservice/SensorDevice.cpp
 *                    LINUX/android/vendor/qcom/proprietary/sensors/dsps/sensordaemon/main/src/sns_main.c
 *                    LINUX/android/vendor/qcom/proprietary/sensors/dsps/sensordaemon/apps/common/reg/src/sns_reg.c
 * ---------------------------------------------------------------*/
#define PANTECH_DSPS_ENCRYPTION

 /* -----------------------------------------------------------------
 * PANTECH_DSPS_PROCESS_CMD
 * -----------------------------------------------------------------
 *   .Brif          : Encryption Mode 에서도 센서가 정상 동작 할 수 있도록 처리
 *   .Applied Block : pantech_server
 *   .Applied Files :
 *                    LINUX/android/pantech/frameworks/testmenu_server/server/sky_process_cmd_thread.c
 * ---------------------------------------------------------------*/
#define PANTECH_DSPS_PROCESS_CMD

 /* -----------------------------------------------------------------
 * PANTECH_DSPS_UTILS
 * -----------------------------------------------------------------
 *   .Brif          : 팬택 API set
 *   .Applied Block : HAL & DSPS & pantech_server & test app 
 *   .Applied Files :
 *                    LINUX/android/vendor/qcom/proprietary/sensors/dsps/libhalsensors/src/sensors_qcom_hal.c
 *                    LINUX/android/pantech/frameworks/testmenu_server/server/sky_process_cmd_thread.c
 *                    LINUX/android/pantech/frameworks/dspstest/jni/src/sensor_test.c
 *                    LINUX/android/pantech/frameworks/dspstest/api/com/pantech/test/SensorTest.java
 *                    LINUX/android/pantech/apps/SkyMenu/src/com/pantech/app/test_menu/apps/SensorTest4648.java
 *                    LINUX/android/pantech/apps/SkyMenu/src/com/pantech/app/test_menu/apps/SensorTest8378522.java
 *                    LINUX/android/pantech/apps/SkyMenu/src/com/pantech/app/test_menu/apps/IRGesture4648.java
 *                    LINUX/android/pantech/apps/SkyMenu/src/com/pantech/app/test_menu/apps/IRGesture8378522.java
 *                    LINUX/android/pantech/apps/SkyMenu/src/com/pantech/app/test_menu/apps/jig_FuncTest/jig_FuncTest_SensorTest.java
 *                    LINUX/android/pantech/apps/SkyMenu/src/com/pantech/app/test_menu/apps/jig_FuncTest/jig_FuncTest_IRFpcbTest.java
 *                    LINUX/android/pantech/apps/SkyMenu/src/com/pantech/app/test_menu/apps/jig_FuncTest/jig_FuncTest_IRFrontTest.java
 *                    dsps_proc/core/sensors/dd/src/sns_dd_alsprx_max88260m.c
 *                    dsps_proc/core/sensors/smgr/src/common/sns_smgr_task.c
 *                    dsps_proc/core/sensors/smgr/src/common\sns_smgr_sensor.c
 * ---------------------------------------------------------------*/
#define PANTECH_DSPS_UTILS
#ifdef PANTECH_DSPS_UTILS
#define PANTECH_DSPS_SUPPORTED_PROPERTY "sys.sns.supported"
#define PANTECH_DSPS_ACCEL_NAME_PROPERTY "sys.sns.accel"
#endif // PANTECH_DSPS_UTILS

 /* -----------------------------------------------------------------
 * PANTECH_DSPS_SYS_PROPERTY_ACCESS_UID
 * -----------------------------------------------------------------
 *   .Brif          : JB에서 4648의 SDCARD 테스트 오류 문제로 com.pantech.app.test_menu.apk 의 uid 가 system 에서 phone으로 바뀌면서 system property 의 write 권한을 상실함, 센서가 사용하는 system property 의 owner를 radio로 변경함
 *   .Applied Block : pantech_server
 *   .Applied Files :
 *                    LINUX/android/system/core/init/property_service.c 
 * ---------------------------------------------------------------*/
#define PANTECH_DSPS_SYS_PROPERTY_ACCESS_UID 1001 // AID_RADIO

/*
 * =================================================================
 * 2. ALSPRX 
 * =================================================================
 */

#if ( ! ( defined(CONFIG_PANTECH_DSPS_PRX_NONE) && defined(CONFIG_PANTECH_DSPS_LIG_NONE) && defined(CONFIG_PANTECH_DSPS_IRM_NONE) ) )

/* -----------------------------------------------------------------
 * PANTECH_DSPS_ALSPRX_UPDATE_CONDITION_CHECK
 * -----------------------------------------------------------------
 *   .Brif          : 근접,조도,IR Event 를 Framework 으로 전달 할 때 update 조건 체크
 *   .Applied Block : HAL
 *   .Applied Files : sensors_qcom_hal.c
 * ---------------------------------------------------------------*/
#define PANTECH_DSPS_ALSPRX_UPDATE_CONDITION_CHECK

/* -----------------------------------------------------------------
 * PANTECH_DSPS_ALSPRX_EACH_SENSOR_NAMING
 * -----------------------------------------------------------------
 *   .Brif          : SensorList의 Info 에서 근접,조도,IR 센서의 이름을 각 센서별로 구체화
 *   .Applied Block : HAL
 *   .Applied Files : sensors_qcom_hal.c
 * ---------------------------------------------------------------*/
#define PANTECH_DSPS_ALSPRX_EACH_SENSOR_NAMING

/* -----------------------------------------------------------------
 * PANTECH_DSPS_ALSPRX_SENSOR_REPORT_TYPE_3AXES
 * -----------------------------------------------------------------
 *   .Brif          : 근접,조도,IR 센서의 데이터를 디버그 목적으로 기존 1개 데이터를 3개의 데이터로 확장
 *   .Applied Block : HAL and DSPS
 *   .Applied Files : sensors_qcom_hal.c sns_dd_alsprx_apds9900.c sns_dd_alsprx_max88260m.c
 * ---------------------------------------------------------------*/
#define PANTECH_DSPS_ALSPRX_SENSOR_REPORT_TYPE_3AXES
#ifdef  PANTECH_DSPS_ALSPRX_SENSOR_REPORT_TYPE_3AXES
#define PANTECH_DSPS_ALSPRX_SENSOR_PROPERTY "sys.sns.debug"
#endif // end of PANTECH_DSPS_ALSPRX_SENSOR_REPORT_TYPE_3AXES

/*
 * =================================================================
 * 2-1. ALS
 * =================================================================
 */
#ifndef CONFIG_PANTECH_DSPS_LIG_NONE

/* -----------------------------------------------------------------
 * PANTECH_DSPS_LIGHT_REPRESENT
 * -----------------------------------------------------------------
 *   .Brif          : 조도센서 데이터를 레벨 구분하여 대표값을 Framework 으로 전달
 *   .Applied Block : HAL
 *   .Applied Files : sensors_qcom_hal.c
 * ---------------------------------------------------------------*/
/* Hong seul-ki 2013-02-19
#define PANTECH_DSPS_LIGHT_REPRESENT */


#endif // end of CONFIG_PANTECH_DSPS_LIG_NONE

/*
 * =================================================================
 * 2-2. PRX
 * =================================================================
 */
#ifndef CONFIG_PANTECH_DSPS_PRX_NONE

/* -----------------------------------------------------------------
 * PANTECH_DSPS_PROXIMITY_SENSOR_RATE_5HZ_FIX
 * -----------------------------------------------------------------
 *   .Brif          : 근접센서 freq는 무조건 5Hz로 설정함으로써 HAL의 set_delay 에 영향을 받지 않도록 함
 *   .Applied Block : DSPS
 *   .Applied Files :
 *                    dsps_proc/core/sensors/dd/src/sns_dd_alsprx_apds9900.c
 *                    dsps_proc/core/sensors/dd/src/sns_dd_alsprx_max88260.c
 * ---------------------------------------------------------------*/
#define PANTECH_DSPS_PROXIMITY_SENSOR_RATE_5HZ_FIX

/* -----------------------------------------------------------------
 * PANTECH_DSPS_PROXIMITY_MAX_DISTANCE_METER
 * -----------------------------------------------------------------
 *   .Brif          : 근접센서 range의 distance는 무조건 0.05m 로 고정
 *   .Applied Block : DSPS & HAL
 *   .Applied Files :
 *                    dsps_proc/core/sensors/dd/src/sns_dd_alsprx_apds9900.c
 *                    dsps_proc/core/sensors/dd/src/sns_dd_alsprx_max88260.c
 *                    LINUX/android/vendor/qcom/proprietary/sensors/dsps/libhalsensors/src/sensors_qcom_hal.c
 * ---------------------------------------------------------------*/
#define PANTECH_DSPS_PROXIMITY_MAX_DISTANCE_METER (0.05)

//hong
//#if defined(CONFIG_PANTECH_DSPS_PRX_APDS9900) && defined(CONFIG_PANTECH_DSPS_ALS_APDS9900)
#if defined(CONFIG_PANTECH_DSPS_PRX_APDS9900) && defined(CONFIG_PANTECH_DSPS_LIG_APDS9900)
/* -----------------------------------------------------------------
 * PANTECH_APDS9900_SUNLIGHT_CANCELATION
 * -----------------------------------------------------------------
 *   .Brif          : 태양광에서의 근접효과를 가시광선 데이터를 비교하여 근접효과를 무시하도록 함
 *   .Applied Block : DSPS
 *   .Applied Files :
 *                    dsps_proc/core/sensors/dd/src/sns_dd_alsprx_apds9900.c
 * ---------------------------------------------------------------*/
#define PANTECH_APDS9900_SUNLIGHT_CANCELATION
#endif // CONFIG_PANTECH_DSPS_PRX_APDS9900 && CONFIG_PANTECH_DSPS_PRX_APDS9900

#endif // end of CONFIG_PANTECH_DSPS_PRX_NONE

/*
 * =================================================================
 * 2-3. IRM
 * =================================================================
 */
#ifndef CONFIG_PANTECH_DSPS_IRM_NONE

/* -----------------------------------------------------------------
 * PANTECH_DSPS_IR_INTEGRATED_ON_LIGHT_PATH
 * -----------------------------------------------------------------
 *   .Brif          : IR Gesture 를 사용하는 경우, DSPS에서 path 를 추가하는 게 불가능하여 기존 LIGHT path 를 대신 사용함
 *   .Applied Block : HAL and DSPS
 *   .Applied Files :
 *                    LINUX/android/vendor/qcom/proprietary/sensors/dsps/libhalsensors/src/sensors_qcom_hal.c
 *                    dsps_proc/core/sensors/smgr/src/common/sns_smgr_sensor.c
 *                    dsps_proc/core/sensors/smgr/src/common/sns_smgr_task.c
 *                    dsps_proc/core/sensors/dd/src/sns_dd_alsprx_max88260m.c
 *                    dsps_proc/core/sensors/smgr/src/8960/sns_smgr_sensor_config.h
 * ---------------------------------------------------------------*/
#define PANTECH_DSPS_IR_INTEGRATED_ON_LIGHT_PATH

/* -----------------------------------------------------------------
 * PANTECH_DSPS_IR_CALIBRATION
 * -----------------------------------------------------------------
 *   .Brif          : IR 센서 calibration path
 *   .Applied Block : HAL and DSPS
 *   .Applied Files :
 *                    dsps_proc/core/sensors/smgr/src/common/sns_smgr_task.c
 *                    dsps_proc/core/sensors/dd/src/sns_dd_alsprx_max88260m.c
 * ---------------------------------------------------------------*/
#define PANTECH_DSPS_IR_CALIBRATION
#ifdef PANTECH_DSPS_IR_CALIBRATION
#define PANTECH_DSPS_IR_CALIBRATION_MAGICNUM              88260
#define PANTECH_DSPS_IR_CALIBRATION_GESTURE_PROPERTY      "sys.sns.ircalges"
#define PANTECH_DSPS_IR_CALIBRATION_PROXIMITY_PROPERTY    "sys.sns.ircalprx"
#define PANTECH_DSPS_IR_CALIBRATION_FLAG_PROPERTY         "sys.sns.ircalflag"
#endif // PANTECH_DSPS_IR_CALIBRATION

/* -----------------------------------------------------------------
 * PANTECH_DSPS_IR_LEDCONTROL
 * -----------------------------------------------------------------
 *   .Brif          : IR 센서 LED Control path
 *   .Applied Block : HAL and DSPS
 *   .Applied Files :
 *                    dsps_proc/core/sensors/smgr/src/common/sns_smgr_task.c
 *                    dsps_proc/core/sensors/dd/src/sns_dd_alsprx_max88260m.c
 * ---------------------------------------------------------------*/
#define PANTECH_DSPS_IR_LEDCONTROL

#endif // end of CONFIG_PANTECH_DSPS_IRM_NONE


#endif  // end of PANTECH_DSPS_ALSPRX_


/*
 * =================================================================
 * 3. ACCELEROMETER
 * =================================================================
 */
#ifndef CONFIG_PANTECH_DSPS_ACC_NONE

#ifdef CONFIG_PANTECH_DSPS_ACC_BMA250
/* -----------------------------------------------------------------
 * PANTECH_BMA250_USE_NOT_INTERRUPT
 * -----------------------------------------------------------------
 *   .Brif          : BMA250 의 interrupt handler 를 사용하지 않음
 *   .Applied Block : DSPS
 *   .Applied Files :
 *                    dsps_proc/core/sensors/dd/src/sns_dd_bma250.c
 * ---------------------------------------------------------------*/
#define PANTECH_BMA250_USE_NOT_INTERRUPT
#endif // end of CONFIG_PANTECH_DSPS_ACC_BMA250

#endif // end of CONFIG_PANTECH_DSPS_ACC_NONE


/*
 * =================================================================
 * 4. MAGNETOMETER
 * =================================================================
 */
#ifndef CONFIG_PANTECH_DSPS_MAG_NONE

/* -----------------------------------------------------------------
 * PANTECH_DSPS_COMPASS_FAST_REACH_TRACK
 * -----------------------------------------------------------------
 *   .Brif          : 나침반 어플에서 방향 궤도 진입이 느려 디스플레이가 흐르는 문제 해결
 *   .Applied Block : sensordaemon
 *   .Applied Files :
 *                    LINUX/android/vendor/qcom/proprietary/sensors/dsps/sensordaemon/common/inc/sns_reg_common.h
  * ---------------------------------------------------------------*/
#define PANTECH_DSPS_COMPASS_FAST_REACH_TRACK

#ifdef CONFIG_PANTECH_DSPS_MAG_YAS530
/* -----------------------------------------------------------------
 * PANTECH_DSPS_YAS_USE_NOT_ELLIPSOID_MATRIX_FILE
 * -----------------------------------------------------------------
 *   .Brif          : 야마하 칩셋의 소프트아이언 보정
 *   .Applied Block : sensordaemon
 *   .Applied Files :
 *                    LINUX/android/vendor/qcom/proprietary/sensors/dsps/libhalsensors/src/YAS530/algo_mag_yas_calib.c
  * ---------------------------------------------------------------*/
#define PANTECH_DSPS_YAS_USE_NOT_ELLIPSOID_MATRIX_FILE
#endif // CONFIG_PANTECH_DSPS_MAG_YAS530

#endif // end of CONFIG_PANTECH_DSPS_MAG_NONE


/*
 * =================================================================
 * 5. GYROSCOPE
 * =================================================================
 */
#ifndef CONFIG_PANTECH_DSPS_GYR_NONE

/* -----------------------------------------------------------------
 * PANTECH_DSPS_GYRO_MAX_SAMPLE_RATE_FOR_CAMERA
 * -----------------------------------------------------------------
 *   .Brif          : 카메라쪽에서 자이로스코프 쓸때 너무 빠른 sampling rate로 인해 DSPS crash 발생할 때 있어서 이를 회피 하고자 함
 *   .Applied Block : camera
 *   .Applied Files :
 *                    LINUX/android/vendor/qcom/proprietary/mm-camera/server/hardware/dsps/dsps_hw.h
 * ---------------------------------------------------------------*/
#define PANTECH_DSPS_GYRO_MAX_SAMPLE_RATE_FOR_CAMERA (100) // Hz

#ifdef CONFIG_PANTECH_DSPS_GYR_MPU3050

/* -----------------------------------------------------------------
 * PANTECH_MPU3050_USE_NOT_AXES_MAP
 * -----------------------------------------------------------------
 *   .Brif          : MPU3050 실장에 따른 축 변환을 퀄컴에서는 sns_ddf_map_axes() 을 사용하는데, 모델별로 수정하기 번거로움이 있어 사용 안하기로 함
 *   .Applied Block : DSPS
 *   .Applied Files :
 *                    dsps_proc/core/sensors/dd/src/sns_dd_gyro.c
 * ---------------------------------------------------------------*/
#define PANTECH_MPU3050_USE_NOT_AXES_MAP

/* -----------------------------------------------------------------
 * PANTECH_MPU3050_SELFTEST
 * -----------------------------------------------------------------
 *   .Brif          : 퀄컴의 selftest 는 표준편차를 구하는 방식으로 변별력이 떨어져 INVENSENS에서 제안하는 RMS를 체크하는 방식을 사용함
 *   .Applied Block : DSPS
 *   .Applied Files :
 *                    dsps_proc/core/sensors/dd/src/sns_dd_gyro.c
 *                    dsps_proc/core/sensors/dd/src/sns_dd_inertial_test.h
 *                    dsps_proc/core/sensors/dd/src/sns_dd_inertial_test.c
 * ---------------------------------------------------------------*/
#define PANTECH_MPU3050_SELFTEST

#endif // CONFIG_PANTECH_DSPS_GYR_MPU3050


#ifdef CONFIG_PANTECH_DSPS_GYR_MPU6050
/* -----------------------------------------------------------------
 * PANTECH_MPU6050_USE_NOT_AXES_MAP
 * -----------------------------------------------------------------
 *   .Brif          : MPU6050 실장에 따른 축 변환을 퀄컴에서는 sns_ddf_map_axes() 을 사용하는데, 모델별로 수정하기 번거로움이 있어 사용 안하기로 함
 *   .Applied Block : HAL and DSPS
 *   .Applied Files :
 *                    dsps_proc/core/sensors/dd/src/sns_dd_mpu6050.c
 * ---------------------------------------------------------------*/
#define PANTECH_MPU6050_USE_NOT_AXES_MAP

/* -----------------------------------------------------------------
 * PANTECH_MPU6050_SELFTEST
 * -----------------------------------------------------------------
 *   .Brif          : 퀄컴의 selftest 는 표준편차를 구하는 방식으로 변별력이 떨어져 INVENSENS에서 제안하는 RMS를 체크하는 방식을 사용함
 *   .Applied Block : DSPS
 *   .Applied Files :
 *                    dsps_proc/core/sensors/dd/src/sns_dd_mpu6050_selftest.c
 *                    dsps_proc/core/sensors/dd/src/sns_dd_inertial_test.h
 *                    dsps_proc/core/sensors/dd/src/sns_dd_inertial_test.c
 * ---------------------------------------------------------------*/
#define PANTECH_MPU6050_SELFTEST

#endif // CONFIG_PANTECH_DSPS_GYR_MPU6050


#endif // end of CONFIG_PANTECH_DSPS_GYR_NONE



#endif // end of CONFIG_PANTECH_DSPS_ENABLE




#endif // _CUST_PANTECH_DSPS_H_




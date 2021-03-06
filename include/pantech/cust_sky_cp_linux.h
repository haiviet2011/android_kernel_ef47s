#ifndef __CUST_SKY_CP_H__
#define __CUST_SKY_CP_H__


/*****************************************************
    SKY Android 모델 공통 적용사항
    Feature Name : T_SKY_MODEL_TARGET_COMMON
******************************************************/

/*------------------------------------------------------------
**  LINUX와 MODEM 간의 인터페이스가 RPC에서 QMI로 변경되어 
**  RPC 구조는 8960 이후부터 사용하지 않아 삭제 함.
**----------------------------------------------------------*/
#if 0
/* QCRIL RPC 초기화 추가하함. 
   System VOB에서의 지원을 위해서 target feature를 qcril_qmi.mk 에도 선언해둠 */
#ifndef FEATURE_SKY_CP_RPC_FUSION_SUPPORT
#define FEATURE_SKY_CP_RPC_FUSION_SUPPORT
#endif/* FEATURE_SKY_CP_RPC_FUSION_SUPPORT */

/* OEM RAPI 에서 CM RPC를 등록하여 사용함.
   CM PH, SS Event 와 CM Call Event 를 oem_rapi 를 통해서 linux로 전달받기 위함 */
#define FEATURE_SKY_CP_OEM_RAPI_CM_EVENT_SUPPORT

/* OEM RAPI 에서 mmgsdi RPC 등록.
   linux에서 mmgsdi API 호출 위해서 필요함 */
#define FEATURE_SKY_CP_OEM_RAPI_MMGSDI_RPC_SUPPORT

/* OEM RAPI 에서 gsdi_exp RPC 등록.
   linux에서 gsdi API 호출 위해서 필요함 */
#define FEATURE_SKY_CP_OEM_RAPI_GSDI_EXP_RPC_SUPPORT

/* RPC를 통해서 공정커맨드 처리 ( 프로토콜 담당 커맨드 처리 ) */
#define FEATURE_SKY_CP_PROCESS_CMD_WITH_RPC // FEATURE_TODO [RPC 관련 공정커맨드 처리로 적용 보류]

/* OEM RAPI 를 이용하기 위한 Protocol Feature */
#define FEATURE_SKY_RPC_OEM_RAPI_NEW_INTERFACE

#define FEATURE_SKY_CP_ADDITIONAL_NV_ITEMS
#define FEATURE_SKY_CP_RPC_XDR_NV_ACCESS

/* qualcomm OEM RAPI이용을 위한 구성 ( FEATURE_SKY_RPC_OEM_RAPI_NEW_INTERFACE 와 동기화)
   !!! kernel/arch/arm/mach-msm/oem_rapi_client.c 에도 반드시 Feature 적용해주어야 함. 
   vendor는 vendor\qcom\proprietary\modem-apis\msm7627_surf\api\libs\remote_apis\oem_rapi\inc\oem_rapi.h, buffer length 수정 
   vendor\qcom\proprietary\modem-apis\msm7627_surf\api\libs\remote_apis\oem_rapi\src\oem_rapi_clnt.c, out length 전달 수정 */
#define FEATURE_SKY_CP_OEM_RAPI_USING

/* FEATURE_SKY_CP_RPC_XDR_NV_ACCESS feature와 동기화를 위함.
   XDR에 빠져있는 아이템 추가 */
#define FEATURE_SKY_CP_NV_ACCESS_RPC

/* [EF40K] - FEATURE_SKY_CP_SUP_SVC_FOR_ANDROID에 필요한 sups_info(CM_SUPS_EVENT)를 CM RPC로 전달받도록 함*/
#ifdef FEATURE_SKY_CP_OEM_RAPI_CM_EVENT_SUPPORT
#define FEATURE_KT_CP_SUPS_EVENT_RPC
#endif

#endif
/*------------------------------------------------------------
**  RPC 삭제 END
**----------------------------------------------------------*/

#ifdef T_SKY_MODEL_TARGET_COMMON

/* Qualcomm OEM Hook 기능을 이용한 확장.  ( NV access, SIM access etc..) */
#define FEATURE_SKY_CP_QCRILHOOK_INTERFACE // FEATURE_TODO [Qcril_sky_rapi.c 추가 여부 검토 필요]


/* Qualcomm Feature [FEATURE_QCRIL_UIM_QMI] 사용 */
#define FEATURE_SKY_CP_SUPPORT_FEATURE_QCRIL_UIM_QMI
#ifdef FEATURE_SKY_CP_SUPPORT_FEATURE_QCRIL_UIM_QMI
/* qcril 에서 mmgsdi 및 gsdi function 사용시 RPC callback 이 필요함. */
#define FEATURE_SKY_CP_GSDI_RPC_CALLBACK_SUPPORT
#endif/* FEATURE_SKY_CP_SUPPORT_FEATURE_QCRIL_UIM_QMI */

/* MODEM과 LINUX간의 CM 에 대해 QMI로 변경함.*/
#define FEATURE_SKY_CP_CM_QMI_SUPPORT


#ifdef FEATURE_SKY_CP_QCRILHOOK_INTERFACE
/* oemhook및 qcril에서 error exception처리를 위한 선언. */
// [EF40K] uca-ril에서 uca-ril-qmi로 구조 변경되면서 FEATURE 미사용.
#define FEATURE_SKY_CP_EXCEPTION_DEFINITION

#define FEATURE_SKY_QCRILHOOK_EVENT_PROCESSED_BY_SUB_THREAD

/* need to notify Qcrilhook Unsol Event to application */
#define FEATURE_SKY_CP_EVENT_NOTIFIER


/**
    [EF45K] SkyUsim.java 에서 호출하는 USIM I/F를 지원하지 않음. 
    ( qcril_other_usim.c 지원하지 않음. )
*/
/* OEM Hook 기반으로 SIM access를 GSDI를 이용할때 sync방식으로 access하기 위한 I/F */
//#define FEATURE_SKY_CP_GSDI_SYNC_ACCESS_BY_REMOTE_PROCESSOR

#ifdef FEATURE_SKY_CP_GSDI_SYNC_ACCESS_BY_REMOTE_PROCESSOR
#ifdef FEATURE_SKY_CP_OEM_RAPI_GSDI_EXP_RPC_SUPPORT
//#define FEATURE_SKY_CP_USING_GSDI_RPC_CLIENT
#endif/* FEATURE_SKY_CP_OEM_RAPI_GSDI_EXP_RPC_SUPPORT */
#endif/* FEATURE_SKY_CP_GSDI_SYNC_ACCESS_BY_REMOTE_PROCESSOR */

#endif/* FEATURE_SKY_CP_QCRILHOOK_INTERFACE */


/* 
   SkyTelephonyInterfaceManager.java, Service_Manager.c, ISkyTelephony.aidl 
*/
#define FEATURE_SKY_CP_TELEPHONYMANAGER
#ifdef FEATURE_SKY_CP_TELEPHONYMANAGER
/* Java에서 Modem API 호출을 위한 Daemon ( NV access, 자동응답, VE 기능, etc.. ) 
** init.rc에 추가해야 함(init_모델명.rc)
** init.rc는 \LINUX\android\system\core\rootdir 에 위치함 */
#define FEATURE_SKY_CP_MANAGER_DAEMON_INTERFACE
#ifdef FEATURE_SKY_CP_MANAGER_DAEMON_INTERFACE
/* Voice Call connection sound event */
#define FEATURE_SKT_CP_VOICE_CALL_CONNECT_SOUND
#endif/* FEATURE_SKY_CP_MANAGER_DAEMON_INTERFACE */
#endif/* FEATURE_SKY_CP_TELEPHONYMANAGER */

/* UMTS PS/CS Domain setting menu support */
//#define FEATURE_SKY_CP_SERVICE_DOMAIN_CHANGE_CMD
/* [EF40K] QMI로 변경하면서 FEATURE_SKY_CP_SERVICE_DOMAIN_CHANGE_CMD를 대체함.
           setPreferredSystem 함수를 통해 재부팅없이 pref domain 변경가능 함.
*/
#define FEATURE_SKY_CP_CM_SYS_SELECTION_PREF


/* UMTS SMS MO PS/CS Domain setting menu support */
#define FEATURE_SKY_CP_SMS_CFG_SET_GW_DOMAIN

/* Phone Operation Mode setting (lpm, offline, online .. ) */
#define FEATURE_SKY_CP_PHONE_OPERATION_MODE


/* [EF40K] [EF45K] - 적용하지 않음 */
/* RIL state 에 상관없이 항상 ril socket open상태에서는 RIL_REQUEST_XXX 가 동작하도록 함. */
/* RIL state가 radio unavailable상태일 경우 RIL request/response가 되지 않도록 되어있어 일부 테스트 모드에서 오동작을 유발하는 경우가 있음.
     RIL radio state와 상관없이 무조건 request를 처리하도록 함. */
#define FEATURE_SKY_CP_FORCE_ALLOW_RIL_REQUEST

/* [EF40K] [EF45K] 미적용 */
/* Airplane mode 진입시 network mode menu 진입이 순간적으로 진입이 가능해지는 문제 발생
  이전 EF30S의 이전 버전의 경우 service state를 보고서 airplane mode check box를 disable 시키도록 하는 부분이 
  존재..하지만 현재 버전에는 해당 부분 없음...EF30S 소스기반으로 해당 함수 수정 이후 6140도 해당 부분이
  존재 하지 않음 */
#define FEATURE_SKY_CP_AIRPLANE_MODE_CHECK_BOX_CONTROL


/* DDMS Log에 radio log 를 볼수있도록 함. 
   Test 편의를 위해 사용하는 것이기 때문에 envsetup.mk 의 TARGET_BUILD_VARIANT 가 user ( user mode compile )
   일때 만 FEATURE_AARM_RELEASE_MODE 가 define됨.
   (PS1팀 작업 필수: cust_sky.h 에 사용여부 확인.)
   android/system/core/liblog/logd_write.c */
#ifndef FEATURE_AARM_RELEASE_MODE
//#define FEATURE_SKY_CP_RADIO_LOG_DDMS
#endif/* FEATURE_AARM_RELEASE_MODE */


/* [EF40K] [EF45K] - 미적용 */
/* QMI 사용 모델의 경우 모뎀의 QMI에서 NASI_DEFAULT_RSSI_DELTA 값을 변경하여 적용 */ 
/* RSSI Delta Threshold Value를 Modem과 동일하게 1dB로 변경함. Modem을 변경해도 qcril_cm_init시 
   CM_PH_CMD_SIGNAL_STRENGTH_DELTA처리에 의해 ph_ptr의 rssi_delta vaule가 update되어 RSSI Report시에 
   5dB 차이가 나야 report되므로 Linux단도 변경함 */
#define FEATURE_SKY_CP_RSSI_REPORT_VARIATION_FIX


/* 음성호 발신을 위해서 CSFB동작 시 또는 음성호 종료 후 LTE로 이동할때 
   급격한 Ant. bar의 변화가 없게 하기 위한 처리 */
// EF45K에서 재현여부 확인 후 적용여부 판단할 것, 관련하여 함수 변경되어 미적용해도 될 것 같음.   
//#define FEATURE_SKY_CP_RSSI_REPORT_TIMING_GAP_FIX


/* [EF45K] - ICS에서 적용, LTE를 먼저 획득한 후 음성 착발신시 3G RSSI 값이 없어 ANT Bar가 표시되지 않는 현상 보완 */
#define FEATURE_SKY_CP_RSSI_REPORT_FOR_ICS


/* [EF40K] [EF45K] - 향후 검토, 일단 미적용 - FEATURE_TODO */
/* LCD OFF 상태에서 SRV_CHANGED_EVENT가 Dereg 되어 LINUX단에서 해당 event를 수신할 수 없다.
   부팅시 GMM Info 수신 전에 LCD OFF하면 시간정보가 Update되지 않아 RTC에 문제가 발생한 경우
   잘못된 시간표시를 할 수 있다. 
   network 등록이 완료된 후 30초후에 property를 설정하여 lcd on/off 에 대해서 cm event reg/dereg가 
   가능하도록 한다.
   수동 시간 설정 후 부팅시 GMM Info 수신전에 LCD OFF 하고 이후 자동으로 변경하면 시간정보가 
   이상해 지는 문제는 같이 해결됨. */
#define FEATURE_SKY_CP_TIME_UPDATE_ABSOLUTELY_ON_BOOT


/* Airplane mode 적용/해제를 위한 공정 커맨드 처리 */
// [EF45K] [필요하지 않을 것으로 판단됨]
#define FEATURE_SKY_CP_FACTORY_AIRPLANE_MODE_I


/* QMI 를 통해서 CM PH event info. 처리 */
#define FEATURE_SKY_CP_OEM_PH_EVENT_WITH_QMI


/* SIM Invalid의 Reject을 수신시에 gsm.sim.operator.numeric 이 초기화 되는 문제 fix */
// [EF45K] 구조 변경으로 setSubscriptionInfo 호출하는 부분이 없어 사용하지 않음.
//#define FEATURE_SKY_USIM_ICC_OPERATOR_PROPERTY_NOT_RESET


/* qcril_data_init() 과정에서 5초 delay를 3초로 변경하고 이에 대한 추가 보완코드 적용 
   5초 delay발생으로 부팅 초기에 PIN lock 화면이 늦게 발생하고 노서비스 상태가 오래 지속됨 */
#define FEATURE_SKY_CP_QCRIL_DATA_INIT_DELAY_REMOVE


/* Not support USIM Voice Mail EF */
#define FEATURE_SKY_USIM_VOICE_MAIL_EF_MWIS_NOT_SUPPORT


/* Network Name을 수신했음에도 불구하고, "nas_cached_info.current_plmn" 값이 Invalid로 처리되어 
** 해당 Network Name이 아닌 Table의 name을 표시하는 문제를 위해 Qcril에서 관리하는 system info를 
** state 변화시마다 update하도록 함.
** QCT는 이 system info를 LCD enable시에만 update 하도록 하고 있음 */
#define FEATURE_SKY_CP_QMI_SYS_INFO_ALWAYS_UPDATE

/*
 * @TODO
 */
#define FEATURE_SKY_CP_FIX_OPERATOR_NAME_DISPLAY


/* SKT 망연동 문제 - getSimOperatorName()을 호출하는 경우 Null return되는 문제로 
** EF_SPN read시 "gsm.sim.operator.alpha" property에 set되도록 함 */
#define FEATURE_SKY_USIM_PROPERTY_ICC_OPERATOR_ALPHA_UPDATE

/* 괌에서 시간표시 오류 수정 
** 1. 기본적으로 Android 구조는 시간 정보가 내려와도 그 시간을 저장하는 것이 아니라 GMT 시간만 사용하고 
**    Time Zone은 사용 않는 구조임. 따라서, Time Zone 값은 시간 정보(NITZ)의 것을 사용하지 않고 자체 
**    관리하는 Time Zone Table에서 가져와 GMT에 더해서 사용하는 방식임
** 2. GMT시간에 timeoffset이 +40 으로 정확한 시간정보가 망으로 부터 내려오지만 timezone을 New York으로
**    인식하여 GMT -5시간으로 표시하는 문제
** 3. mcc정보가 310(미국) 인 괌은 timezone에 대한 timeoffset정보를 가지고 있지 않아 정확한 timezone을
**    얻어오지 못하고 default인 NewYork시간으로 표시하는 문제가 있음.
** 4. mcc가 310 이고 timeoffset이 +40 일경우는 timezone name을 Pacific/Guam  으로 설정하여 
**    timezone 이 fix되도록 수정함.
** 5. 4번의 동작이 이루어지면 time설정메뉴에 timezone이 "Chamrro" ( 차모로우 ) 로표시됨. */
#define FEATURE_SKY_CP_TIMEZONE_FIX 

/* [EF45K] 占쏙옙占쏙옙 占쏙옙占쏙옙 占쏙옙占쏙옙.
   
*/
// dm logging 占쏙옙占쏙옙
#define FEATURE_SKY_ADB_LOG_FOR_VITAMIN
#define FEATURE_SKY_CP_DMLOGGING

//...not used
//#define FEATURE_SKY_CP_DATA_LOG_QMI_LOG_ADB_ON
//#define FEATURE_DM_LOG_STORE_TEMP_MEMORY
//#define FEATURE_DMMON_F3TRACE

#define FEATURE_SKY_CP_SYSLOG

/* 
   SD 카드를 통한 DM Logging
*/
#define FEATURE_SKY_CP_DM_LOG_STORE_TEMP_MEMORY

/*
   20120423 Lee Jonghwan
   30145 patch후 qcril.c의 android_request_id가 QMI_RIL_FW_ANDROID_REQUEST_HNDL_MAX_EVT_ID (127)로 제한됨.
   Ril.h에 추가된 event id값을 추가하여 132 값보다 큰 값으로 설정함.
*/
#define FEATURE_SKY_CP_RIL_FW_ANDROID_REQUEST_HNDL_MAX_EVT_ID_FIX

/*
     sky_rawdata 占쏙옙占쏙옙占쏙옙 opening day backup 
*/    
#define FEATURE_SKY_CP_NEW_OPENING_DAY

/*
  [EF49K] Fast_Return_To_LTE 기능을 On/Off 하는 Hidden Menu 추가.
*/
#define FEATURE_SKY_CP_FAST_RETURN_TO_LTE_ONOFF

#define FEATURE_SKY_CP_LTE_BAND_PREFER_SETTING

// 부재중 전화(Missed Call)이 7건 이상일 때 이후 수신되지 않는 현상
#define FEATURE_SKY_CP_MISSED_CALL_BUG_FIX

// EF48S에서 2'nd Call 종료될 경우 소리 나는 경우에 대한 수정사항이지만,
// 근본적인 원인은 통화중 2'nd Call 발신 직후 PHONE_DISCONNECT가 한번 더 올라오는 문제점.
// 이에 대해 수정사항 반영함.
#define FEATURE_SKY_CP_DISCONNECT_SND_BUG_FIX

/*
   전화걸자마자 종료 시 종료되지 않고 발신되는 현상 수정
*/
#define FEATURE_SKY_CP_1X_CSFB_RETRY_BUG_FIX

/*   Android Factory reset, NV should be initialized default value.*/
#define FEATURE_SKY_CP_FACTORY_RESET_NV_INIT

#endif/* T_SKY_MODEL_TARGET_COMMON */


/* ######################################################################### */



/*****************************************************
    SKT/KT 공통 적용사항
    Feature Name : T_SKY_MODEL_TARGET_WCDMA
******************************************************/
#ifdef T_SKY_MODEL_TARGET_WCDMA

#define FEATURE_SKY_CP_LOCAL_DB     // qcril_qmi_security.c 에 ME Perso. 작업이후에 추가할 것.
#define FEATURE_SKY_CP_LOCAL_DB_LTE
#define FEATURE_SKY_CP_LOCAL_DB_WITH_QMI

/* OEM QMI commands set */
#define FEATURE_SKY_CP_OEM_COMMANDS_WITH_QMI

#define FEATURE_SKT_CP_SUBSCRIPTION_MODE
#define FEATURE_SKY_CP_OTA_KT_SUBSCRIPTION
/* [EF40K] */
#define FEATURE_SKY_CP_OTA_KT_SUBSCRIPTION_WITH_QMI

#define FEATURE_SKY_USIM_CARD_TYPE    //FEATURE_TODO : keyguardstatusviewmanager.java 에 추가해야함.

#define FEATURE_SKY_USIM_GET_CARD_MODE_AS_APP_TYPE

#define FEATURE_SKY_CP_ACQ_DB_DELETE

// [20120215] [EF45K] Not Used Any more...
//#define FEATURE_SKY_CP_END_DUN_INTERFACE

#ifdef FEATURE_SKY_CP_QCRILHOOK_INTERFACE
/* OEM Hook 기반으로 NV access */
#define FEATURE_SKY_CP_NV_ACCESS_OEMHOOK

#ifdef FEATURE_SKY_CP_LOCAL_DB
/* OEM Hook 기반으로 Local DB access */
#define FEATURE_SKY_CP_LOCAL_DB_ACCESS_OEMHOOK
#endif/* FEATURE_SKY_CP_LOCAL_DB */
#endif/* FEATURE_SKY_CP_QCRILHOOK_INTERFACE */

#ifdef FEATURE_SKY_CP_MANAGER_DAEMON_INTERFACE
/* cpmgrif.c daemon을 통한 NV Access */

#define FEATURE_SKY_CP_NV_ACCESS_CPMGRIF

#ifdef FEATURE_SKY_CP_LOCAL_DB
/* cpmgrif.c daemon을 통한 Local DB Access */
#define FEATURE_SKY_CP_LOCAL_DB_ACCESS_CPMGRIF
#endif/* FEATURE_SKY_CP_LOCAL_DB */
#endif/* FEATURE_SKY_CP_MANAGER_DAEMON_INTERFACE */

/* SKT/KT 공통 Me Personalization ( With QMI interface ) */
#define FEATURE_SKY_USIM_ME_PERSONALIZATION


/* EF40K - 적용 불필요 */
/*--------------------------------------------------------------------------------------------------------------
** 1. qcril 에서 default voice tech.를 3GPP2가 이닌 3GPP로 설정.
**   --> 부팅 초기에 3GPP2로 radio technology가 천이되었다가 3GPP로 바뀌어서 3GPP2인 CDMA SIM 에서 SIM ready가 
**       발생하여 PUK및 PIN 설정이 제대로 안되거나 SIM Record함수들이 CDMA용으로 동작하는 경우가 발생함.
** 2. java class에서 Phone type이 GSMPhone으로 create 되도록 설정함
**--------------------------------------------------------------------------------------------------------------*/
#define FEATURE_SKY_CP_DEFAULT_NETWORK_UMTS_IN_RIL

/*--------------------------------------------------------------------------------------------
** Manual PLMN Selection시 FPLMN에 있는 망을 선택해서 Reject 수신한 후 
** 단말 재부팅시 RPLMN 망에 등록한 후 바로 이전에 Reject 받았던 망으로 재등록을 시도하는 
** 현상을 막기 위해.
** frameworks\base\core\res\res\values\config.xml 에서 skip_restoring_network_selection을 
** TRUE로 변경해도 됨
**-------------------------------------------------------------------------------------------*/
#define FEATURE_SKY_CP_BLOCK_RESTORING_NETWORK_SELECTION 

/* FEATURE_TODO - 검토 후 적용 필요 */
/* [EF39S/EF40K]
   부팅 초기 socket open fail되고 4초간격으로 재시도하는 것을 1초 간격으로 8회 반복하도록 수정.
   PIN lock 화면에 조금더 빨리 진입되도록 하기 위함. */
// [EF45K] 미적용

//#define FEATURE_SKY_CP_RIL_SOCKET_OPEN_RETRY_MILLIS

/* FEATURE_TODO - 검토 후 적용 필요 */
/* RIL_REQUEST_GET_NEIGHBORING_CELL_IDS 커맨드가 호출 되었을때 
   Neighbor Cell정보가 실제로 있는 경우 system halt를 유발함.
   불필요한 커맨드로 처리하지 않도록 수정 */
// [EF45K] 미적용   
//#define FEATURE_SKY_CP_GET_NEIGHBORING_CELL_IDS_NOT_SUPPORT

/*
   20120424 Lee Jonghwan
   30145 patch후 qcril.c 추가된 RIL관련 ITEM 처리 구조의 변화로 간헐적으로 이밴트 처리에 문제가 됨.
   Voice & Data REG STATE, Auto & Malual Network Selection 관련 RIL event는 30145 patch 이전과 같이 처리되도록 
   qmi_ril_fw_dedicated_thrd_exec_android_requests_set 테이블에서 제외함.
*/
#define FEATURE_SKY_CP_FW_DEDICATED_ANDROID_REQ_BUG_FIX

/* centralized_eons_supported  기능 동작에 따라 network name 및 manual search list 표시 오류가 발생함 */
#define FEATURE_SKY_CP_CENTRALIZED_EONS_NOT_SUPPORTED

/* 20120314 ithong
   isim application 지원을 위해 feature.
   모뎀단에서는 isim app init 을 진행하지 않기에 isim app detected 이후 usim ready되면,
   isim app 역시 ready 로 처리하여 안드로이드단으로 전달하도록 함.
*/
#define FEATURE_SKY_CP_OEM_SUPPORT_FOR_ISIM_APP_IN_QCRIL

/* 
LTE 3GFB call시  system time이 역전되는 현상에 대해 900ms 이전의 system time setting은 skip하도록 하여 역전현상을 줄임
*/
#define FEATURE_SKY_CP_DECREASE_TIME_ROLLBACK

#endif/* T_SKY_MODEL_TARGET_WCDMA */


/* ######################################################################### */


/*****************************************************
    SKT 모델 적용사항
    Feature Name : T_SKY_MODEL_TARGET_SKT
******************************************************/
#ifdef T_SKY_MODEL_TARGET_SKT

#ifdef T_SKY_MODEL_TARGET_KT
#error occurred !!  This section is SKT only !!
#endif

#ifdef FEATURE_SKY_CP_MANAGER_DAEMON_INTERFACE

/* USIM card removed event */
#define FEATURE_SKY_CP_USIM_CARD_REMOVED_EVENT

#endif/* FEATURE_SKY_CP_MANAGER_DAEMON_INTERFACE */

#endif/* T_SKY_MODEL_TARGET_SKT */


/* ######################################################################### */


/*****************************************************
    KT 모델 적용사항
    Feature Name : T_SKY_MODEL_TARGET_KT
******************************************************/

#ifdef T_SKY_MODEL_TARGET_KT

#ifdef T_SKY_MODEL_TARGET_SKT
#error occurred !!  This section is KT only !!
#endif

#define FEATURE_KT_CP_SMART_DM
#define FEATURE_KT_CP_SMART_DM_WIFI
#define FEATURE_SKY_CP_PST_DEBUGSCREEN_SUPPORT


/* -----------------------------------------------------------------------------
** SKT 기존 Original Feature 
** 확인하면서 삭제함. 
** 소스에 남아 있는 Feature 
** ----------------------------------------------------------------------------*/

/* 소스에 남아 있는 Feature임
   Android 상태를 Roaming상태로 전환하도록 설정한다.
   Roaming상태를 강제로 설정되도록 하여 RAD app. 나 해외에서만 동작하는 기능 테스트를 위함.
   #47566# 코드로 진입함. */
#define ds1_cp_roaming_fake_setting

/* ETC(상대방연결) 서비스 수행시 망에서의 call end 되는 순서가 active call이 holding call보다 먼저인 수행되는 경우 
   [Unable to switch calls.]이란 팝업이 표시됨. 팝업 표시 되지 않도록 문제 수정 */
//#define ds1_cp_etc_bug_fix2

/* ETC(상대방연결) 서비스 수행시 call end에 의해서 CM_EVENT_CALL_MNG_CALLS_CONF 가 처리되지 못하고
   pending되어 있는경우 call end화면 처리를 하지 못하고 연결 실패 팝업이 발생하는 문제 수정 */
//#define ds1_cp_etc_bug_fix


/*==============================================================================
**------------------------------------------------------------------------------
**      SKY  Call Processing ( DS1 Features for WCDMA KTF on LINUX Module)
**------------------------------------------------------------------------------
**============================================================================*/

/* From EF10, ds1_cp_sim_card_retry_num_support
   pin verify 등에서의 retry num 값이 전달되어 처리될 수 있도록 구성함
   EF18K에는 qualcomm제공 api 사용으로 미적용 */
#define FEATURE_SKY_CP_SIM_CARD_RETRY_NUM_SUPPORT


/* [ds1_cp_time_info_bug_fix]의 수정코드 제거함, 향후에도 적용하지 말 것
   20100611 : 최초 수정자로부터 제거 요청 받아 제거함.
   data동작 중지 상태에서 시간정보 갱신 오류 수정.
   LCD on시 망으로 부터 수신된 시간정보로 무조건 변경되는 오류수정. */
#define FEATURE_SKY_CP_TIME_INFO_BUG_FIX


/* From EF10, ds1_cp_factory_diag_protocol
   /android/kernel/drivers/char/diag/diagfwd.c 에 위치 
   공정 Command 중 protocol파트에서 관리하는 부분 추가. (구현부분은 별도 파일로 분리하여 관리)
   nv.h [ds1_cp_nv_access_rpc]부분에 nv_net_sel_mode_pref_type 추가 하였음. */
#define FEATURE_SKY_CP_FACTORY_DIAG_PROTOCOL


/* From EF10, ds1_cp_skt_send_dtmf_in_alerting_state
   SKT부가서비스 중 비밀번호 통화 등은 call state가 Alerting state(CC/Progress 상태) 일때 
   비밀번호 입력이 필요하기 때문에 origination이 진행 중인 Alerting state에서 DTMF 입력이 가능하도록 함.
   3200 patch버전에서 컬컴 구현사항과 동일하여 feature삭제!!! */
#define FEATURE_SKT_CP_SEND_DTMF_IN_ALERTING_STATE


/* [EF40K]는 해당 코드가 없어 미적용 */
/* From EF10, ds1_cp_cdma_app_remove
   cdma용 app. 삭제.
   NAM setting app. */
#define FEATURE_SKY_CP_CDMA_APPP_REMOVE

// WCDMA 모델의 경우 CTS 테스트를 위해 CDMA 내용 android.hardware.telephony.cdma 항목 삭제.
// android\device\qcom\common\common.mk 파일.
// frameworks/base/data/etc/android.hardware.telephony.cdma.xml:system/etc/permissions/android.hardware.telephony.cdma.xml
#define FEATURE_SKY_CP_CTS_CDMA_DELETE

/* From EF10, ds1_cp_auto_answer_bug_fix
   Qualcomm NV intem 연동 하지 않게함
   Android 기본 setting으로 동작함 */
#define FEATURE_SKY_CP_AUTO_ANSWER_BUG_FIX


/* From EF10, ds1_cp_usermode_off_debug_message
   SP33K에 이 기능이 적용되어 있지 않음. EF12K 모델부터 적용
   user mode 버전에서 불필요한 메세지 막음
   EF18K 미적용 */
#define FEATURE_SKY_CP_USERMODE_OFF_DEBUG_MESSAGE


/* From [ds1_cp_service_domain_changed_bug_fix] of EF10
   부팅 초기에 qcril 에서 service domain을 CS_PS 로 무조건 변경하는 문제 수정
   EF18K에는 이미 수정되어 미적용 */
#define FEATURE_SKY_CP_SERVICE_DOMAIN_CHANGED_BUG_FIX


/* 20100714 hbwoo
   3가지 아쉬운 점 수정
   1.ANR 로그는 기존의 로그를 지우고 새로 남깁니다. 기존 History가 지워져 버립니다.
   2.VM의 Exception 로그는 기존 /data/anr/traces.txt 파일이 없을 남지 않습니다.
   3.2번에서 남기는 Exception 로그도 android runtime에서 출력하는 call stack을 표시해주지 않아 어느 위치에서 exception이 발생했는지를 알 수 없습니다.
   EF18K에는 미적용 */
#define FEATURE_SKY_CP_CONTROL_ERROR_LOG_FOR_ANDROID


/* 20100814 이상욱
   Froyo 패치 후 SIM READY가 오지 않아 폰북 로딩안됨 수정 (수정내역서 86번)
   발신 측은 분명 SIM READY를 전달했으나 수신측은 오지 않음.Froyo 패치되면서 FLAG_RECEIVER_REPLACE_PENDING라는 flag가 추가되었는데
   broadcast하도 나서 아직 도착하기 전 새로운 broadcast를 보내면 이전 내용이 최신 broadcast로 대치되도록 하는 flag임. 
   이에 따라 수신측에서 받지 못한 것임. broadcast 전달 시 이 flag를 막음.
   [feature_sky_usim_block_flag_receiver_replace_pending] */
#define FEATURE_SKY_USIM_BLOCK_FLAG_RECEIVER_REPLACE_PENDING


/* T_SKY_MODEL_TARGET_WCDMA 부분에 define되어 있지만, KT 요구사항을 만족시키기 위한 구현사항 추가.
   SKT 개통모드   
   To synchronize with modem on FEATURE_SKT_CP_SUBSCRIPTION_MODE */  
#define FEATURE_SKT_CP_SUBSCRIPTION_MODE


/* T_SKY_MODEL_TARGET_WCDMA 부분에 define되어 있지만, KT 요구사항을 만족시키기 위한 구현사항 추가.
   ME Personalization 동작 구성.
   관련 AMSS feature는 FEATURE_SKY_USIM_ME_PERSONALIZATION */
#define FEATURE_SKY_USIM_ME_PERSONALIZATION


/* android 부팅 시 device_provisioned 라는 secure setting값을 체크하여 설정되어있지 않다면 
   콜착신을 거부하거나 keyguard lock screen이 설정되지 않게 하는등 단말 사용을 제한함. 
   불필요한 기능으로 disable 시킴 */
#define FEATURE_SKY_CP_DISABLE_CHECK_DEVICE_PROVISIONED


/* SIM card type을 확인할 수 있는 I/F 구성. ( 사업자 요구사항 반영을 위함. ) */
#define FEATURE_SKY_CP_SIM_CARD_TYPE_CHECK


/* SKY 단말용으로 사용할 intent Action 정의 */
#define FEATURE_SKY_CP_TELEPHONY_INTENT_ACTION


/* T_SKY_MODEL_TARGET_WCDMA 부분에 define되어 있지만, KT 요구사항을 만족시키기 위한 구현사항 추가.
   To synchronize with modem on FEATURE_KTF_CP_SUBSCRIPTION_MODE */
#define FEATURE_SKY_CP_OTA_KT_SUBSCRIPTION


/* STATE_IN_SERVICE, STATE_OUT_OF_SERVICE 두개로 관리되는 framework service state를 세분화 하기 위해 sub state를 추가함.
   OUT_OF_SERVICE를 NO Service와 Limited Service로 구분하기 위함. */
#define FEATURE_SKY_CP_SERVICE_STATUS_DETAIL_SUBSTATE


/* WCDMA, GSM 의 RSSI level 기준 변경... 
   H/W 요청에 의한 변경... */
#define FEATURE_SKY_CP_GW_RSSI_LEVEL


/* service상태 에서만 MCC/MNC 가 update 되던 부분을 Limited service상태에서도 update가 가능하도록 수정함. */
#define FEATURE_SKY_CP_GET_MCCMNC_UPDATE_IN_LIMITED_SRV


/* Data 접속 상태로 인해 Plmn 수동검색이 되지 않는 현상 수정.
   리스트 검색 전에 data 접속 상태를 체크하여 disconnect상태가 아니라면 Data connectivity 를 disable시키고 나서 
   리스트 검색에 진입하도록 함. */
#define FEATURE_SKY_CP_MANUAL_SEL_PLMN_AFTER_DATA_DISCONNECT


/* 비행중 모드 설정 후 재부팅시 비행중 모드가 재설정되지 않도록 함. */
#define FEATURE_SKY_CP_AIRPLANE_MODE_RELEASE_AFTER_BOOT


/* android original 소스에서 제공되는 CDMA 선택사항 삭제 및 문구 수정
   메뉴 진입시 roaming 경고 문구 표시 
   국내에서는 network 설정 메뉴 진입하지 못하도록 수정.
   Hidden 메뉴에서 band 설정 변경후 Android 셋팅 메뉴에서 network preferred band 설정이 안되는 문제 수정. */
#define FEATURE_SKY_CP_PREFERRED_NETWORK_MODE_SELECTION


/* [EF40K] - 적용 불필요 - onServiceStateChanged() 안에 updateCdmaRoamingIcon()이 없음 */
/* GSM/WCDMA mode에서 signal strength status bar 표시가 되지 않는 문제 수정.
   3108 버전에서 cdma관련 icon만 표시되도록 하는 오류가 있음.
   3200 버전에서 수정이 되어 roaming icon을 제외한 수정사항 삭제 */
#define FEATURE_SKY_CP_SIGNAL_STRENGTH_STATUSBAR_UMTS


/* PUK 10회 실패 카드 status 추가
   PUK 10회 실패 카드 사용시 INTENT_VALUE_ICC_PERM_BLOCKED 를 발생시킴. */
#define FEATURE_SKY_CP_ADD_PERM_BLOCKED_CARD_STATUS


/* 20110622 - [EF40K]부터는 FEATURE_SKY_CP_USSD_CNAP_8BIT_CHAR_SUPPORT로 처리되면서 Qcril단 
** 적용은 불필요. GsmConnection.java만 적용하면 됨 */
/* CNAP 지원을 위한 RIL 및 framework 수정. */
#define FEATURE_SKY_CP_CNAP_SUPPORT


/* Android에서 IMEI 확인 기능 선택시 ******** 형태로 보이도록 수정
   3GPP 규격이지만 국내 모델에서는 유저가 확인 할 수 없어야 함. */
/* [EF45K] 방통위 정책 BlackList 제도 시행함으로 해서 IMEI 표시 함. */      
//#define FEATURE_SKY_CP_IMEI_NO_DISPLAY


/* [EF40K] - status.java에 처리한 코드는, 모듈이 변경되어 msimstatus.java에서 처리함 */
/* 20100514 seobest
   IMEI 표시 요구사항 최종 정리안 반영
   *#06# 시에 IMEI는 *************** 로 표시
   휴대폰 전화 정보 상태의 IMEI도 *************** 로 표시
   IMEI를 읽는 Method는 정상적으로 제공되어야 함 */
/* [EF45K] 방통위 정책 BlackList 제도 시행함으로 해서 IMEI 표시 함. */   
//#define FEATURE_SKY_CP_HIDE_IMEI


/* Emergency Call 관련 구현 사항 추가. 
   Emergency Call 판단여부를 위한 구조를 안드로이드 원본을 이용하는 구조로 변경 */
#define FEATURE_SKY_CP_EMERGENCY_CALL


/* 통화연결음 설정을 위한 이벤트 전달 */
#define FEATURE_SKY_CP_CS_CALL_CONNECTION_SND_START


/* USSD 메세지 및 CNAP 에서 KSC5601 지원하기 위해서 수정함.
   data coding scheme에 따라 문자가 정상적으로 표현되는지 확인 필요! */
#define FEATURE_SKY_CP_USSD_CNAP_8BIT_CHAR_SUPPORT


/* 통화설정 메뉴 삭제
   CDMA, WCDMA관련 메뉴 불필요.... */
#define FEATURE_SKY_CP_REMOVE_ANDROID_CALL_FEATURE_SETTING_MENU


/* card power down 커맨드 처리하지 않도록 함. < 미 수정시 발생하는 주요 문제점 >
   1. 비행중 모드 진입시 USIM card access되지 않는 문제
   2. 비행중 모드 진입시 SIM card가 인식되지 않는다는 문구 표시됨.
   3. on chip sim mode로 동작중 비행중 모드 들어가면 card가 없는 상태에서 
   UIM으로 card power down커맨드가 전달되어 page fault 에러가 발생됨.... */
#define FEATURE_SKY_CP_CARD_POWER_DOWN_NOT_SUPPORT


/* 히든 메뉴 항목에 대해서 class단위로 개별 실행을 막음...
   Market 의 system application중 Startup Manager와 같은 프로그램에서의 실행. */
#define FEATURE_SKY_CP_CLASS_DEPENDENCY_CHECK


/* [EF40K] - Gsmcalltracker.java의 hangup()에서 다른 팀에서 BRCM[Excelt], BTL-A로 해서 처리해 놓아 일단 적용하지 않음 */
/* Bluetooth 인증 절차중 통화중에 호 수신시 active call 연결을 해제 했을때 수신된 호는 Alerting상태를 유지 해야함.
   안드로이드 기본 동작은 active call해제시 수신된 호가 자동 연결됨. */
#define FEATURE_SKY_CP_BLUEBOOTH_CERTIFICATION


/* To synchronize with modem on FEATURE_SKY_CP_PLMN_SELECTION */
#define FEATURE_SKY_CP_PLMN_SELECTION


/* To synchronize with modem on FEATURE_SKY_CP_DISP_NETWORK_NAME */
#define FEATURE_SKY_CP_DISP_NETWORK_NAME


/* 20100316 hbwoo Phone process 내에서도 Qcrilhook을 호출하도록 함.
   Phone process/main thread에서 qcrilhook을 호출하면 sync operation을 정상적으로 수행할 수 없음. 
   때문에 sub thread를 생성하여 이를 처리하도록 함. */
#define FEATURE_SKY_CP_CALL_QCRILHOOK_IN_PHONE_PROCESS


/* Qcril에서 발생하는 Event를 Application으로 전달하기 위한 Event Notifier */
#define FEATURE_SKY_CP_EVENT_NOTIFIER


/* [EF40K] - 기존에는 stauts.java에서 처리했던 것을 모듈 변경으로 인해 msimstatus.java에서 처리함 */
/* 20100503 hbwoo
   KT의 경우 Settings > System > About phone > Status > My phone number의 표시가 +821 029 219302 로 표시됨.
   PhoneNumberUtils에서 수정할 수 있으나 Phone number utils의 경우 MSISDN 외의 다른 번호도 Handling 하므로 
   표시하는 쪽에서만 수정하기로 함.
   향후, 아래단 에서 수정할 경우, AdnRecord.java/parseRecord()/PhoneNumberUtils.calledPartyBCDToString()를 참조하면 됨. */
#define FEATURE_SKY_CP_DISPLAY_PHONE_NUMBER_WITH_TOA


/* [EF40K] - QMI 적용으로 인해 일단 이 기능은 적용하지 않음 */
/* 망에서 release를 수신받지 못하는 상황에서 Call END 시도시 call 화면이 계속해서 in call상태를 유지하는 현상 수정.
   기존 피쳐폰에서도 적용된 사항으로 호종료시 call end를 기다리지 않고 call_end_req 커맨드 이벤트 발생시 call 화면을 정리할 수 있도록 함.
   A + B ( active ) , B + C ( hold ) 상태에서 A가 호종료 하는 시점에서 B가 호를 종료하면 android 쪽 call state와 ril쪽 call state가 꼬이는 경우가 발생함.
   Disconnect 이후 release procedure가 LG망과 삼성망에 차이가 있어서 KT의 경우 추풍령, 익산 등 삼성망에서 시험해야 됨. */
#define FEATURE_SKY_CP_CALL_END_REQ_FOR_UI_CLEAN


/* 20100514 hbwoo
   IDLE 모드중 30초마다 Status command를 UICC로 보내는지 확인하고, UICC가 없는 것으로 판단되면
   "USIM 카드를 재 장착한 후 재 부팅하십시오" 문구표시 후 긴급호 UI로 전환
   Event를 전달하기 위한 작업 */
#define FEATURE_SKY_CP_CARD_REMOVED


/* [EF40K] - QMI로 변경되어 미적용 */
/* phone process 에러 발생 이후, lpm에 지속적으로 빠지는 문제
   Android Phone process 가 excpetion발생에 의해서 재시작될때 phone state가 LPM 에서 online으로 진입하지 못하는 현상으로 비행중모드 진입을 하거나 폰을 껐다 켜기 전까지 현상이 유지됨
   subscription available을 수행하지 못하고 lpm 진입에 의한 subscription disable 상태가 유지되어 문제가 발생       
   GW subscription available/disable 커맨드 및 이벤트를 처리하는 데 있어 예외상황발생에 대해서도 해당 이벤트및 커맨드가 처리될 수 있도록 함 */
#define FEATURE_SKY_CP_SERIVCE_RECOVERY_FROM_ERROR


/* [EF40K] - QMI로 변경되어 미적용 */
/* modem 쪽과 Android쪽 service status가 서로 다른 경우 방지
   Modem( in service ), android ( out-of-service )   
   Service status가 In serivce상태로 변경될때 RIL_UNSOL_RESPONSE_NETWORK_STATE_CHANGED 를 Android로 전달하여 
   service state가 변경될 수 있도록 함.  LCD on상태에서만 동작하도록 하여 불필요한 wakeup 동작을 유발하지 않도록 함
   SVCMGR_SS_SRV_CHANGED_EVENT에 대해 changed_fields 값을 기반으로 처리를 하는데, SVCMGR_SS_SRV_CHANGED_EVENT를 받았으나 
   changed_fields 값이 없는 경우 변경된 Service Status를 업데이트하지 못하는 현상을 방지하기 위함. */
#define FEATURE_SKY_CP_MODEM_VS_ANDROID_SRV_STATE_MISMATCH


/* 20120327 SHPark
   부팅후 첫 MT call 수신상태에서 통화추가하여 hold reject을 받을 경우 last_call_failure_cause가 linux단으로 전달되지 않아
   통화 화면이 첫 MO call 이 아닌 Managed call로 보이는 현상을 방지하기 위함. */
#define FEATURE_SKY_CP_LAST_CALL_FAILURE_FORCED_INIT


/***********************************************   KT GPS FEATURE *************************************************************/

/* GPS Test  menu default  ##759477#  */
#define FEATURE_SKY_CP_GPS_TEST_SUPPORT
/****************************************************************************/
/****       FEATURE_SKY_CP_GPS_TEST_SUPPORT 에 일괄 작업. *************/
/****          KT 사업자용 GPS Test menu 작업 (##759477#)           *************/
/****             #define FEATURE_KTF_CP_GPS_TESTMENU            **************/
/****             KT GPS - H/W Cno Test menu 작업                        **************/
/****               Timeout, CNo 미측정시 문제 수정                       **************/
/****               #define FEATURE_SKY_CP_GPS_CNO                   **************/
/****************************************************************************/


/*[EF45K] KT LBS EXTENSION */
#define FEATURE_KT_CP_LBS_TEST

/* KT GPS 관련 NV Item RW 기능 추가 작업 */
#define FEATURE_SKY_CP_GPS_NV

/*gps configuration*/
#define FEATURE_SKY_CP_GPS_CONFIGURATION


/*********************************************************************************************************************************/



/* [EF40K] - qcril_other.c의 qcril_other_read_imei_from_nv()에 적용된 코드는 QMI 변경으로 미적용 */
/* EF18K - CTS TEST (testGetDeviceId)시 IMEI를 null로 리턴하여 Fail되는 Bug Fix
   Fix the CTS Test bug */
#define FEATURE_SKY_CP_CTS_TEST_FIX


/* 해당 루틴은 skyusimreceiver.c로 6팀에서 관리하고 UICC GCF를 F/U 하므로 적용하지 않음 */
/* GCF Test 중 로밍중 자동설정 메뉴로 인해 테스트에 방해가 되거나 USIM phonebook 
   read로 인해서 동작 오류가 발생하여 fail되는 현상이 나타남.
   KT의 경우 해외카드일경우 phonebook 읽을 수 없으므로 조건 삭제, On chip SIM 등을 고려하여.. 
   gcf mode이거나 cardmode, cardtype이 unavailable할 경우에는 pb access block. */
#define FEATURE_SKY_CP_PHONEBOOK_ACCESS_BLOCK_CONDITION


/* 20100605 hbwoo
   Phone process 를 ArrayIndexOutOfBoundsException 이 발생하게 하여 process를 죽이는 code
   ril.java의 if(false)를 if(true)로 변경하고 
   new SkyQcRilHook().sendQcRilHookMsg("phone.crash");를 보내면 exception이 발생함 */
#define FEATURE_SKY_CP_SIMULATION_PHONE_CRASH


/* [EF40K] - Qcril.c의 persist.radio.onchipsim는 적용할 필요 없음 */
/* Modified [ds1_cp_ftm_exit_rf_calibration] of EF10
   RF조정 이후 부팅 시 online으로 변경되지 못하고 ftm mode를 유지하는 현상 제거
   FTM 설정 후 재부팅시 online으로 진입하지 못하는 현상 수정.
   20100610 hbwoo, Onchip sim mode 인 경우 FTM으로 정상적으로 진입하지 않는 문제 발생 
   FTM mode 설정과 Onchip sim에 없는 EF를 읽는 동작이 서로 충돌한 것으로 보임. 
   Onchip sim 인 경우 fetchSimRecords() 하지 않도록 함. */
#define FEATURE_SKY_CP_FTM_EXIT_RF_CALIBRATION

/* 20110413 - EF34K부터 적용하지 않음 */
/* Problem description 
   When SIM_REFRESH with SIM_INIT is received, the Android framework updates all saved SIM data. 
   This causes a large amount of SIM_IO. In the meantime, when SIM_READY is received, 
   the framework again starts updating SIM_READY. This results in excessive SIM_IO. */
#define FEATURE_SKY_CP_BUG_FIX_CR228975_FOR_5320


/* 시간 표시 관련 검증을 위해 Log를 남기도록 함
   AMSS단과 LINUX단 모두에서 Log를 남김 */
#define FEATURE_SKY_CP_TIME_VERIFY


/* [ds1_cp_sky_utils] 이름 변경 */
#define FEATURE_SKY_CP_UTILS


/* 해외카드 + 해외망, 해외카드 + 국내타사망에 대한 Lock 해제 
   To synchronize with modem on FEATURE_SKY_USIM_ALLOW_OTHER_MCC */
#define FEATURE_SKY_USIM_ALLOW_OTHER_MCC


/* [EF18K] only, MSM8255 only
   Qualcomm bug로 추정됨. PhoneManager의 GetSimState시 항상 Unknown으로 return 되는 오류 */
#define FEATURE_SKY_USIM_GET_SIM_STATE


/* EF40K 적용 불필요 */
/* 단말 PS ONLY 모드로 설정시 android단에서 Reg state를 No Service로 처리되는 오류를 수정함 */
#define FEATURE_SKY_CP_SUPPORT_PS_ONLY_MODE


/* 불필요하게 Linux단이 wakeup되어 간헐적인 CM Dog Error Fatal 현상이 발생하는 것을 막기 위함
   DFEATURE_QCRIL_NCELL 을 Block함 */
#define FEATURE_SKY_CP_BLOCK_QCRIL_NCELL


/* 20101006 hbwoo
   EF18K Froyo 패치 후 Dual Card지원으로 인한 구조변경으로 Absent로 처리되지 않는 문제점 수정
   No SIM, 카드 제거시, 불량 카드 인입시 Absent로 State변경되지 않아 알림 팝업 발생안함 
   카드가 없는경우에도 UiccCard를 구성하고, event 처리하도록 수정 */
#define FEATURE_SKY_CP_CARD_FUSION


/* frameworks\base\core\res\res\values - config.xml */
/* Network Provider 생성이 되지 않아 문제 발생. 
   Location manager service에서 Network Provider를 생성할 수 있도록 ID 설정 함. */
#define FEATURE_SKY_CP_NETWORK_LOCATION_PROVIDER_SETTING


/* 개통된 해외 USIM(일본 사업자의 Softbank) 인입 후 phone 프로세스가 중지되는 현상 수정(StkService.java, NullPointer Exception)
   EF18K는 현상 발생되지 않아 미적용 */
#define FEATURE_SKY_CP_GOOGLE_BUG_FIX


/* SKT카드 + SKT망 수동검색시 SKT망 활성화되도록 수정 */
#define FEATURE_SKY_USIM_ALLOW_OTHER_MNC


/* 특정카드(폰북 2000개, 3개의 Application이 존재하는 카드)의 경우 상용망에서 KT 개통이 정상적으로 되지 않는 현상
   AppType이 Unknown인 경우 RuimRecords를 생성하여 REFRESH Event가 SIMRecords에 등록되지 못해서 나타나는 문제로 
   AppType이 Unknown인 경우도 SIMRecords를 생성하도록 수정 */
#define FEATURE_SKY_USIM_CHANGE_RUIM_TO_SIM_FOR_APPTYPE_UNKNOWN


/* EF34K부터 QCT 코드 변경으로 인해 적용할 필요 없음 */
/* RILD crash 발생시 Detach후 단말기는 계속해서 LPM state에만 머물러 있는 현상
   QCRIL의 LPM 천이 전에 RIL단에서 RADIO_POWER request가 먼저 온 경우 
   QCRIL은 Operate mode가 change되지 않았다고 판단하고 바로 complete를 보내버리고 
   pending event를 처리하지 않기 때문에 RADIO_POWER request 발생시점에 따라 해당 현상이 발생할 수 있어 
   이런 경우 pending event 처리할때까지 기다린 후 RADIO_POWER request에 대한 complete를 처리하도록 함. */
#define FEATURE_SKY_CP_KEEP_LPM_FIX_DUE_TO_RILD_CRASH


/* event 전달을 위한 jni interface
   from EF13S 
   FEATURE_SKY_CP_TELEPHONYMANAGER 로 변경된 것 같음.
   추후 동작 확인 필요함.*/
#define FEATURE_SKY_CP_JNI_INTERFACE

/* 자동응답 이벤트 전달을 위한 interface
   from EF13S */
#define FEATURE_SKY_CP_AUTOANSWER_INTERFACE

/* EF34K 부터 미적용 */
/* 20101123 PDM 문제점 
   No SIM 상태로 부팅시 no_sim icon 표시 되지 않는 현상 
   SP33K코드를 참조하여 임시로 수정하고, 추후 보완하도록 함. */
#define FEATURE_SKY_CP_NOSIM_ICON


/* FEATURE_TODO - 검토 후 적용 필요 */
/* 단말의 service status가 SYS_SRV_STATUS_PWR_SAVE 일때 QCRIL_CM_SCREEN_STATE_ON 상태가 될때 
   즉 Key interrup 발생으로 LCD가 on될때 단말이 power save상태라면 modem을 wakeup시키도록 되나, 
   qualcomm bug로 동작 안되는 현상 수정 */
#define FEATURE_SKY_CP_MODEM_WAKEUP_IN_STATUS_PWR_SAVE_BUGFIX


/* SkyNv Interface를 사용하도록 수정함.
   EVENT_GET_GCF_MODE_DONE 은 필요가 없어 주석 처리함 */
#define FEATURE_KT_CP_CHECK_GCF_MODE


/* test menu 진입을 위한 dial 히든 코드 */
#define FEATURE_KT_CP_HIDDEN_CODE


/* SKT 히든메뉴 및 테스트 메뉴 구성 */
#define FEATURE_KT_CP_HIDDEN_MENU


/* WCDMA/GSM debugscreen
   Radio Condition debugscreen (CS Debug Screen) */
#define FEATURE_KT_CP_DEBUG_SCREEN


/* From EF10, ds1_cp_cs_debugscreen
   CS 센터 Debug Screen */
#define FEATURE_SKY_CP_CS_DEBUGSCREEN


/* [EF40K] - This feature doesn't need */
/* debugscreen에 표시되는 local_db 값을 RIL을 통해서 가져올수 있도록 하는 기능 추가 */
#define FEATURE_KT_CP_MODEM_LD_ACCESS


/* SKT UA field 생성을 위해서 cdma용 EF file인 IMSI_M, IRM 을 읽을수 있도록 telephonyManager구성
   GSMPhone.java에서 부팅 초기 EVENT_SIM_RECORDS_LOADED event발생 했을때 read */
#define FEATURE_SKT_CP_CDMA_MIN_EF_ACCESS


/* SKT 국내망에서는 Supplementary Service MMI Code 가 적용되지 않도록 한다.
   CDMA의 feature code와 공용화를 위한 SKT요구 사항으로 mcc+mnc가 45005 인 경우에 한해서 처리함. */
#define FEATURE_SKT_CP_SUPS_SERVICE_REQUEST


/* 20100421 hbwoo, hksong
   히든메뉴에서 OTA LOG를 표시하기 위한 작업 */
#define FEATURE_KTF_CP_WOTA


/* 네트워크 접속모드를 KT 요구사항에 맞게 작업
   네트워크 접속모드 선택 후 재부팅 팝업에서 확인을 선택하는 순간 저장되도록 수정 */
#define FEATURE_KT_CP_NETWORK_ACCESS_MODE


/* To synchronize with modem on FEATURE_KTF_USIM_MF, FEATURE_KTF_USIM_ADF, and FEATURE_KTF_USIM_TELECOM  */
#define FEATURE_SKY_CP_KTF_USIM_EF_FILE


/* To synchronize with modem on FEATURE_KTF_CP_REG_REJECT_CONTROL
   [ds1_cp_sky_reg_reject_display] for SKT, which is deleted
   [ds1_cp_cs_call_reject_display] is only used for SKY and the codes are not performed */
#define FEATURE_KTF_CP_REG_REJECT_CONTROL


/* To synchronize with modem on FEATURE_KTF_CP_PLMN_PROC_BY_UICC_TYPE */
#define FEATURE_KTF_CP_PLMN_PROC_BY_UICC_TYPE


/* To synchronize with modem on FEATURE_KTF_CP_FREE_ZONE */
//#define FEATURE_KTF_CP_FREE_ZONE


/* To synchronize with modem on FEATURE_KTF_CP_MULTI_SMS
   Basically, KTF multi-sms has included the functionality of "[ds1_cp_multisms_requirement]"
   WMS Link control을 사용하며 MMS app.로 부터 발신 총 개수를 넘겨받아 WMS에서 처리하도록 RIL I/F 수정 */
#define FEATURE_KTF_CP_MULTI_SMS


/* 20110705 - SMS에 대해 국내 Prefer domain과 해외 Prefer domain이 분리되어 적용 됨
** 국내는 PS domain, 해외는 CS domain으로 SMS 발신이 자동으로 이루어 지도록 처리하기 위해 */
#define FEATURE_KT_CP_SMS_MO_DOMAIN_SET_BY_MCC	


/* 20100325 JongYeob
   To synchronize with modem on FEATURE_KTF_CP_PLMN_SELECTION
   Automatic/Manual PLMN Selection functionality for KT
   This functionality included "[ds1_cp_skt_network_plmn_manual_selection]" */
#define FEATURE_KTF_CP_PLMN_SELECTION


/* KT UICC 인입 상태에서 국내 타사망에 Camping시 RSSI Bar 개수를 표시하지 않도록 함 */
#define FEATURE_KT_CP_RSSI_BAR_ZERO_DISPLAY


/* 네트워크 접속모드를 KT 요구사항에 맞게 작업
   네트워크 접속모드 선택 후 재부팅 팝업에서 확인을 선택하는 순간 저장되도록 수정 */
#define FEATURE_KT_CP_NETWORK_ACCESS_MODE


/* REFRESH(UICC Reset)인 OTA msg를 받은 경우 Status Bar에 
   "카드 정보 변경으로 카드가 리셋되었습니다. " Noti하도록 수정 */
#define FEATURE_KT_CP_OTA_UICC_RESET


/* [ds1_cp_display_network_name] for SKT, which is deleted
   Notification 영역에 표시되는 PNN, SPN, PLMN 에 대한 표현 방법 변경
   Network Name만을 표시하도록 수정하기 위해서 PNN, SPN 표시 않하도록 수정함
   Network Name은 KT 요구에 따라  Long Name 우선 표시 되도록 하고 Long Name이 없는 경우 Short Name을 표시하도록 변경 
   Andorid는 Full name을 표시하는 것으로 처리되고 있어 만약 full name이 망으로 부터 수신되지 않는 경우 공백으로 처리되기 때문에 
   short name으로 처리될 수 있도록 예외 처리함 */
#define FEATURE_KT_CP_DISPALY_NETWORK_NAME


/* KT에서 요구하는 부가서비스 중 CNAP, CD, ECT, COLP, COLR, CLIP 등은 안드로이드에서 지원하지 않아 이를 구현함
   RIL은 Call 파트에서 구현하고 Phone은 Call UI에서 구현함.
   call UI 구현은 FEATURE_GSM_MMI_CODE_KTF_REQUIREMENT 로 구현되었으며 김종만 선임이 구현하였음. */
#define FEATURE_KT_CP_GSM_MMI_CODE_FOR_KTF_REQUIREMENT


/* A-B가 통화 중에 C가 A에 전화를 할 경우 A는 CC/Setup을 받음. 
  이 때 signal_incl 이 포함되어 있지 않은 경우, Network은 vocoder data로 signal tone을 내려줌. 
  문제는 android는 second call을 수신하는 경우 default로 signal tone을 재생하기 때문에 
  장비에서 내려준 signal tone과 겹치게 됨. 때문에 call notifier 쪽에서 signal value를 수신할 필요가 있음.
  signal value 값을 broadcast하도록 함. */
#define FEATURE_KTF_CP_CALL_MANAGER_NOTIFY_SIGNAL_VALUE


/* SKT 향의 [ds1_cp_event_for_time_and_rad] 에서 시간체크 부분만을 차용함
   TIME_VALIDITY_CHECK Intent를 Broadcast하여 수동시간설정 유도 여부를 결정함
   시간이 Invalid하면 Notication 영역에 수동시간설정을 유도하도록 함 */
#define FEATURE_KT_CP_TIME_VALIDITY_CHECK


/* 로밍듀얼시간 표시 기능에 gsm.operator.sky_numeric Property에 값 읽어올 수 있도록 설정. 
**/
#define FEATURE_SKY_CP_VALID_OPERATOR_NUMERIC


/* 해외 로밍 중 GSM 모드로 설정 후, Power On 위치등록 시도시 네트워크 검색 결과 GSM 네트워크가 존재하지 않을 경우, 
   “네트워크 접속 모드가 GSM 모드입니다.  자동모드로 변경하시겠습니까?”의 팝업 UI 표시하고 
   사용자 선택에 의해서 네트워크 접속 모드가 변경되어야 한다는 SBSM 추가 요구사항 구현 */
#define FEATURE_KT_CP_NETWORK_ACCESS_MODE_GSM_ONLY


/* 안드로이드에 구현되어 있지 않은 KT 부가 서비스 규격에 대응하기 위한 모듈 */
#define FEATURE_KT_CP_SUP_SVC_FOR_ANDROID
/* KT 부가서비스 CFD 자동연결관련 QMI 수정사항 반영 */
/* all Conditional CF 004에 대해 query시에 009로 보내며 이를 지원해야함 -KT 망문제*/
#define FEATURE_KT_CP_SUP_SVC_FOR_ANDROID_CFD
#define FEATURE_KT_CP_SUP_SVC_FOR_ANDROID_WITH_QMI


/* EF40K - 적용 불필요 */
/* EF18K Froyo(2020) Update시 SVLTE(simultaneous Voice and LTE)로 인해 적용된 수정 사항
   안정화 후 삭제할 FEATURE : EF18K에서 qcril_sms_api_map.c/h에는 추가 구현한 사항으로 남겨둠 */
#define FEATURE_KT_CP_SVLTE


/* To synchronize with modem on FEATURE_KTF_USSD_VER_1_1_0 */
#define FEATURE_KTF_USSD_VER_1_1_0


/* EF18K Froyo(2020) Update 이후 Data Call을 suspend/resume하는 Interface 변경되어 적용 */
#define FEATURE_KT_CP_SUSPEND_RESUME_DATA_CALL_CHANGED


/* 20100523 hbwoo
   호 연결 중에 MMGSDI_REFRESH_EVENT가 발생하면 이는 MMGSDI_REFRESH_STAGE_END_FAILED이므로 
   android로 RIL_UNSOL_SIM_REFRESH를 올리지 않음.
   이후 정상적으로 UICC Reset이 되면 MMGSDI_REFRESH_STAGE_START stage 가 되므로 Event를 올리게 됨. 
   그러므로 아래 코드가 오류를 발생하시키지 않을 것으로 예상됨.
   하지만 이후 Refresh와 관련된 오류 발생시 이 Feature를 눈여겨 보아야 함 */
#define FEATURE_KT_CP_OTA_WARM_RESET_HANDLING


/* EF40K - QMI 사용으로 인해 적용 불필요 - Modem의 pbm.c 만 적용하면 됨 */
/* for only EF18K
   FEATURE_QCRIL_UIM_QMI를 막으면서 긴급호 List Update가 제대로 안되는 현상을 위해 수정한 사항
   향후 FEATURE_QCRIL_UIM_QMI 적용시 검토 필요 */
#define FEATURE_KT_CP_FIX_FOR_UNDEF_FEATURE_QCRIL_UIM_QMI


/* EF40K - 적용 불필요 */
/* [EF18K]
   CISS에 가입된 번호로부터 호착신시 call state오류로 off hook처리되어 벨 울리지 않는 문제로 수정
   CLIST_STATE_SETUP에 대한 RIL_call_state mismatch발생 
   call setup state일 경우는 unsol_call_state_changed 를 보내지 않게 함. */
#define FEATURE_SKY_CP_SETUP_CISS


/* Romaing 아이콘 업데이트 되지 않는 현상 수정. */
#define FEATURE_SKY_CP_UPDATING_ROAMING_INDICATOR


/* [EF40K] - 적용 불필요 */
/* ds1_cp_updating_roaming_indicator 와 적용 목적이 동일함
   qcril 단에서 ui 로 올라가는 reg_status에 오류가 있어 이를 수정함
   EF18K는 검토 후 적용 여부 결정 */
#define FEATURE_SKY_CP_REG_STATUS_UPDATE_CORRECTION


/* 언어 설정을 변경후 이전 언어가 LockScreen에 남아있어 Locale Sync가 맞지 않아 수정함. */
#define FEATURE_CP_KT_LANGUAGE_SYNC


/* [EF40K] - QMI 사용으로 인해 미적용 */
/* EF18K 
   Network Mode가 정상적이지 않은 문제 
   내전화번호 보기에서 번호정보 없음으로 표시되는 문제 : mSIMRecords가 Null이 되는 현상 */
#define FEATURE_KTF_CP_NET_PREF


/* EF34K부터 USIM QMI 사용으로 미적용 */
/* EF18K, UIM_QMI block */
#define FEATURE_KTF_CP_BLOCK_UIM_QMI


/* 망연동 문제점 수정 
   ss-code 코드를 생략하고 New Password 등록 시 register Password가 0x90으로 전송되는 현상. 
   *03**Old_PWD*New_PWD*New_PWD# or **03**Old_PWD*New_PWD*New_PWD# + SEND 시 0x00으로 전송되도록 수정함 */
#define FEATURE_KT_CP_SS_REG_PASSWD


/* 망연동 문제점 수정 
   발신번호표시제한(*23#)으로 음성호 발신 시 SETUP의 BCD NUMBER에 Feature code(*23#)를 포함하여 전송하도록 수정 */
#define FEATURE_KT_CP_SUPS_CLIR_CDMA


/* 2010110 EF18K 망연동 문제점, EF18K Froyo Version부터 적용 필요(SP33K Froyo는 적용할 필요 없음)
   SIM state가 CS_PS_Invalid인 illegal SIM 상태일 때 Subscription Not Available로 전환되도록 변경되어 
   Linux단 SIM state가 Ready 상태가 되지 못해 SMS를 카드로 복사/이동 및 USIM 설정 메뉴 진입이 안되는 문제 fix.
   이 코드는 Subscription Not Available이  처리되어 모뎀의 SIM State가 Not Available로 되지만 
   Linux단은 SIM Ready를 유지하도록 하기 위한 것임.
   Modem단에서 MMGSDI_SESSION_ILLEGAL_SUBSCRIPTION_EVT가 새롭게 추가되고 구조가 많이 변경되어 
   Qcril에서만 MMGSDI_ILLEGAL_CARD_EVT에 대한 처리를 하지 않도록 한 것임. */
#define FEATURE_KT_CP_MAINTAIN_SIM_READY_ILLEGAL_SIM


/* [EF40K] - FEATURE_KT_CP_GSM_MMI_CODE_FOR_KTF_REQUIREMENT를 QMI 구조로 변경함에 따라 적용 불필요 */
/* 20101119 EF18K 망연동 문제점
   EF18K Froyo Update 이후 qcril_reqlist_new() 구조 자체의 변경으로 sub_id를 처리하지 않는 문제
   qcril_reqlist_update_sub_id()를 이용하여 정상적인 sub_id를 설정하도록 처리
   향후 Porting시에 FEATURE_KT_CP_GSM_MMI_CODE_FOR_KTF_REQUIREMENT를 그대로 적용하지 말고 qcril_reqlist_new()에서 
   sub_id를 처리하는지 확인 후 FEATURE_KT_CP_SUPSVC_UPDATE_SUB_ID 부분을 적용해야 함 SP33K의 경우 qcril_reqlist_new()에서
   sub_id를 처리하므로 해당 코드를 적용할 필요 없음 */
#define FEATURE_KT_CP_SUPSVC_UPDATE_SUB_ID


/* FEATURE_KT_CP_USIM_WAIT_SYNC 사용으로 인해 qcril_sleep()은 삭제함 */
/* 20101217 add by yjheo.
   KT_UCM의 CPU 점유율의 높은 차지로 인해 단말리셋되는 현상에 대해 수정함. */
#define FEATURE_KT_USIM_SLEEP_TIME


/* 20100819 kblee | [EF18K] SBSM3.4.0 */
#define FEATURE_KTF_CP_ACC_BARRED_DISPLAY 


/* Limited, SIM Missing 상태에서 LockScreen에 긴급통화 버튼 표시 및 "긴급통화만" 문구 표시 삭제*/
#define FEATURE_KT_CP_EMERGENCY_LOCKSCREEN_DISPLAY


/* 20110223 - KT는 자동응답 기능을 제외한 나머지 기능에 대해서는 cpmgrif 를 사용하지 않도록 한다 
   unsol event들은 기존대로 Qcril을 이용한다 */
#define FEATURE_KT_CPMGRIF_NOT_USED


/* 20110314 - 기존에 사용해 왔던 feature인데 define 안되어 있어 정의함 - PPK Blocked를 처리함 */
#define FEATURE_SKY_CP_USIM_ACCESS



// FEATURE_TODO
/* 20110502 JongYeob - Power Off시 setDataConnectionAsDesired(mDesiredPowerState, powerOffMsg)에 의해 
** PDP Deactivation 처리한 다음 Detach Request에 대한 처리가 바로 이어지는 경우가 발생하여 
** PS Domain release된 상태에서 Detach가 전송되므로 Network에서 이를 인식하지 못해 "전원 OFF" 멘트가 
** 나오지 않는 문제를 보완하기 위해 Radio Off시 RRC State가 Diconnected 상태가 아니면 delay를 주어 
** Detach를 위한 RRC를 다시 열어서 처리되도록 함.  
** GB 버전에서 setRilPowerOff()가 추가되어 이 delay가 필요없지만, KT Network이 CELL_FACH, URA_PCH 등을 
** 운용하면서 문제가 되어 자체 delay를 적용함. */
#define FEATURE_SKY_CP_DELAYED_POWER_OFF


/* 20110503 - 망연동 문제 : A망 GMM INFO 수신 후 전원 OFF/ON시 A망에서 GMM INFO 미수신하게 되면 
** MCC/MNC 정보가 동일하므로 기존 GMM INFO의 Network Name을 보여주게 됨. 이런 경우 KT에서는 
** Table에 있는 정보를 보여 주도록 수정요청하여 qcril init시에 NITZ Property를 clear해 줌 */
#define FEATURE_SKY_CP_INIT_NITZ_INFO_PROPERTY

/* 20110503 kblee : EF32K 수정사항 반영
   gsdi read/ write시에 wait_signal 보다 cb가 먼저 올 경우에 대한 문제 수정
   sleep 대신 사용 */
#define FEATURE_KT_CP_USIM_WAIT_SYNC

/*
20131015 USIM 에 applet 설치 (install for install) 과정 중 5초 초과 되었을 경우, QMI_TIMEOUT_ERR 발생 
QMI_SYNC_MSG_DEFAULT_TIMEOUT을 5초에서 10초로 수정
*/
#define FEATURE_KT_FIX_QMI_SYNC_MSG_DEFAULT_TIMEOUT

/* [EF40K] - QMI로 인해 FEATURE_SKY_CP_CALL_END_REQ_FOR_UI_CLEAN 을 적용하지 않으므로 아래 기능은 적용할 필요 없음
             GsmCallTracker, GSMPhone.java */
/* [EF34K] 망연동 문제점 - 부가서비스 관련 
   두명을 다자간통화(Conference Call)로 묶고 held로 만든 상태에서 통화중화면의 “종료" 버튼을 선택시(or 0 send) 
   held로 설정되어 있는 Conference Call내 두명이 모두 종료되지 않고, 한사람만 종료되는 현상 
   Qcril_cm에서 hangup_waiting_or_background 수행시 held call 일 경우 FEATURE_SKY_CP_CALL_END_REQ_FOR_UI_CLEAN에
   의해 call_id 하나에 대해서만 call_end하도록 처리됨, process 호출 하는곳에서 allcallRelease하도록 수정함 
   FEATURE_SKY_CP_CALL_END_REQ_FOR_UI_CLEAN이 없다면 수정 할 필요없음*/    
#define FEATURE_KT_CP_MULTI_HELD_CALL_END

/* [EF40K] 20110816 Kim Youngchan :   
   CM PH Event에 대해 SKT는 FEATURE_SKY_CP_OEM_PH_EVENT_WITH_QMI를 사용하여 CPMGR로 전달하고,
   KT는 FEATURE_KT_CP_CMPH_EVENT_QMI를 사용하여 QCRILHOOK으로 전달함.
*/
#ifdef FEATURE_SKY_CP_CM_QMI_SUPPORT
#define FEATURE_KT_CP_CMPH_EVENT_QMI
#endif
#ifdef FEATURE_KT_CP_CMPH_EVENT_QMI
#define FEATURE_KTF_CP_REG_REJECT_CONTROL_QMI
#define FEATURE_KTF_CP_PLMN_PROC_BY_UICC_TYPE_QMI
#define FEATURE_SKY_CP_DISP_NETWORK_NAME_QMI
#define FEATURE_KTF_CP_ACC_BARRED_DISPLAY_QMI
#endif



#define FEATURE_KTF_CP_CALL_MANAGER_NOTIFY_SIGNAL_VALUE_QMI

/* [EF40K] 망연동 OTA 문제점, ISIM 추가된 EF read가능하도록 수정
     USIM_ADF 내에 ISIM_ACCESS DF 아래 path를 사용함. ISIM_ADF가 아니라 !!
     현재 LinearFixed item(EF_IMPU/EF_PCSCF) 의 경우 아직은 첫번째 record에 대해서만 값을 가져오도록 구현됨.
     수정필요함. - EF_IMPU/ EF_PCSCF
*/
#define FEATURE_KT_CP_ISIM_EF_ACCESS_BY_PATH

#endif/* T_SKY_MODEL_TARGET_KT */

// Google Hidden Code인 *#*#4636#*#* 에서 "휴대폰 정보" 삭제.
// packages\apps\Settings\res\xml\testing_settings.xml 막음.
#define FEATURE_SKY_CP_GOOGLE_HIDDEN_MENU_BLOCK



// 추후 Feature 정리하자. [
#define FEATURE_SKY_CP_OEM_QMI_ACCESS
#define FEATURE_SKY_CP_NV_ACCESS_WITH_QMI
// ]

/***********************************************************
   JAVA code에만 적용된 Feature 및 code 확인용...
   실제로 C/C++ 코드에는 적용되지 않는 사항으로 
   코드 검색및 확인용도로 사용하기 위함.
************************************************************/

/* import 문이나 여러 기능에 공통으로 들어가는 코드 표시 */
#define FEATURE_SKY_CP_COMMON_JAVA_DECLARATION

/* EF File 접근을 Path 를 이용하기 위해서 사용된 코드 */
#define FEATURE_SKY_USIM_EF_FILE_ACCESS_BY_PATH

/* DS3 P15574 Lee.Myengjun 2012-02-24 15:35 */
/* SIM State Change */
#define FEATURE_SKY_USIM_PIN_RETRY_INIT

/* 20120228 ithong.
   Refresh 발생 시 usim app 가 inactive 상태가 gw prov index 가 invalid(0xffff)로 설정됨.
   이미 정상 ready 된 상태에서 발생한 경우 card io error 를 유발하고, 이에 invalid card 팝업이 발생함.
   이에 refresh 발생 시 usim app가 다시 설정되기 전에는, sim status 가 변경되더라도 card io error 를 발생하지 않게 함.
*/
#define FEATURE_SKY_CP_CHECK_REFRESH_STATE

/* 20120228 ithong.
   sim inserted 에 의한 sim status indication 정보내에 실제 할당된 slot 이 없음에도. gw provision index가 설정되어 linux 에 수신됨
   해당 정보가 그대로 안드로이드 단으로 전달되어 초기 card 객체와 app 객체 생성에 영향을 미칠 우려가 되어 방지 코드 적용함.
   즉 할당된 slot이 없는 상태에서의 sim status indication은 안드로이드 단으로 전달하지 않도록 함.
*/
#define FEATURE_SKY_CP_SKIP_SIM_STAT_INT_FOR_NON_SLOT_STATE


#define FEATURE_SKY_CP_DEBUGGING_LOG_FOR_TIME_SETTING

/*
** [E49K_JB이후 JB 모델]
   망으로부터 GSM-7bit Scheme으로 정상적으로 받았는데, qmi_voice_cm_if.c 에서 gsm7 bit를 utf16으로 변환하여 
   qmi_voice.c 에서 VOICEI_ORIG_USSD_DATA, VOICEI_ORIG_USSD_DATA_UTF16 2개 모두 LINUX로 전달함.
   LINUX쪽 qcril_qmi_voice.c 에서 VOICEI_ORIG_USSD_DATA_UTF16 에 대해서는 처리하지 않도록 막음.
*/
#define FEATURE_SKY_CP_USSD_RESPONSE_MSG_DECODING_BUG_FIX

/*
** [EF49K_JB 이후 모델]
** Fusion_3 1234 패치에서 redirecting party bcd number에 대해 수신 번호뒤에 *와 같이 붙여주는 코드가 추가되어 [발신번호*262032584] 표시됨.
** 간혹 KT 망으로부터 MT의 SETUP 메시지에 redirecting party bcd number IE가 채워져서 내려오긴 하지만, 
** 사용하지 않는 IE이므로 수신화면에 표시되지 않도록 막음.
*/
#define FEATURE_KT_CP_SKIP_REDIRECTING_PARTY_BCD_NUMBER_FIELD

/* LTE-A indicator enable/disable
** When device is camped on CA and 20M BW region, 
** LTE-A Indicator display and other regions do not. 
*/
#define FEATURE_KT_CP_LTE_A_INDICATOR

#endif/* __CUST_SKY_CP_H__ */

#ifndef __CUST_SKY_CP_H__
#define __CUST_SKY_CP_H__


/*****************************************************
    SKY Android �� ���� �������
    Feature Name : T_SKY_MODEL_TARGET_COMMON
******************************************************/

/*------------------------------------------------------------
**  LINUX�� MODEM ���� �������̽��� RPC���� QMI�� ����Ǿ� 
**  RPC ������ 8960 ���ĺ��� ������� �ʾ� ���� ��.
**----------------------------------------------------------*/
#if 0
/* QCRIL RPC �ʱ�ȭ �߰�����. 
   System VOB������ ������ ���ؼ� target feature�� qcril_qmi.mk ���� �����ص� */
#ifndef FEATURE_SKY_CP_RPC_FUSION_SUPPORT
#define FEATURE_SKY_CP_RPC_FUSION_SUPPORT
#endif/* FEATURE_SKY_CP_RPC_FUSION_SUPPORT */

/* OEM RAPI ���� CM RPC�� ����Ͽ� �����.
   CM PH, SS Event �� CM Call Event �� oem_rapi �� ���ؼ� linux�� ���޹ޱ� ���� */
#define FEATURE_SKY_CP_OEM_RAPI_CM_EVENT_SUPPORT

/* OEM RAPI ���� mmgsdi RPC ���.
   linux���� mmgsdi API ȣ�� ���ؼ� �ʿ��� */
#define FEATURE_SKY_CP_OEM_RAPI_MMGSDI_RPC_SUPPORT

/* OEM RAPI ���� gsdi_exp RPC ���.
   linux���� gsdi API ȣ�� ���ؼ� �ʿ��� */
#define FEATURE_SKY_CP_OEM_RAPI_GSDI_EXP_RPC_SUPPORT

/* RPC�� ���ؼ� ����Ŀ�ǵ� ó�� ( �������� ��� Ŀ�ǵ� ó�� ) */
#define FEATURE_SKY_CP_PROCESS_CMD_WITH_RPC // FEATURE_TODO [RPC ���� ����Ŀ�ǵ� ó���� ���� ����]

/* OEM RAPI �� �̿��ϱ� ���� Protocol Feature */
#define FEATURE_SKY_RPC_OEM_RAPI_NEW_INTERFACE

#define FEATURE_SKY_CP_ADDITIONAL_NV_ITEMS
#define FEATURE_SKY_CP_RPC_XDR_NV_ACCESS

/* qualcomm OEM RAPI�̿��� ���� ���� ( FEATURE_SKY_RPC_OEM_RAPI_NEW_INTERFACE �� ����ȭ)
   !!! kernel/arch/arm/mach-msm/oem_rapi_client.c ���� �ݵ�� Feature �������־�� ��. 
   vendor�� vendor\qcom\proprietary\modem-apis\msm7627_surf\api\libs\remote_apis\oem_rapi\inc\oem_rapi.h, buffer length ���� 
   vendor\qcom\proprietary\modem-apis\msm7627_surf\api\libs\remote_apis\oem_rapi\src\oem_rapi_clnt.c, out length ���� ���� */
#define FEATURE_SKY_CP_OEM_RAPI_USING

/* FEATURE_SKY_CP_RPC_XDR_NV_ACCESS feature�� ����ȭ�� ����.
   XDR�� �����ִ� ������ �߰� */
#define FEATURE_SKY_CP_NV_ACCESS_RPC

/* [EF40K] - FEATURE_SKY_CP_SUP_SVC_FOR_ANDROID�� �ʿ��� sups_info(CM_SUPS_EVENT)�� CM RPC�� ���޹޵��� ��*/
#ifdef FEATURE_SKY_CP_OEM_RAPI_CM_EVENT_SUPPORT
#define FEATURE_KT_CP_SUPS_EVENT_RPC
#endif

#endif
/*------------------------------------------------------------
**  RPC ���� END
**----------------------------------------------------------*/

#ifdef T_SKY_MODEL_TARGET_COMMON

/* Qualcomm OEM Hook ����� �̿��� Ȯ��.  ( NV access, SIM access etc..) */
#define FEATURE_SKY_CP_QCRILHOOK_INTERFACE // FEATURE_TODO [Qcril_sky_rapi.c �߰� ���� ���� �ʿ�]


/* Qualcomm Feature [FEATURE_QCRIL_UIM_QMI] ��� */
#define FEATURE_SKY_CP_SUPPORT_FEATURE_QCRIL_UIM_QMI
#ifdef FEATURE_SKY_CP_SUPPORT_FEATURE_QCRIL_UIM_QMI
/* qcril ���� mmgsdi �� gsdi function ���� RPC callback �� �ʿ���. */
#define FEATURE_SKY_CP_GSDI_RPC_CALLBACK_SUPPORT
#endif/* FEATURE_SKY_CP_SUPPORT_FEATURE_QCRIL_UIM_QMI */

/* MODEM�� LINUX���� CM �� ���� QMI�� ������.*/
#define FEATURE_SKY_CP_CM_QMI_SUPPORT


#ifdef FEATURE_SKY_CP_QCRILHOOK_INTERFACE
/* oemhook�� qcril���� error exceptionó���� ���� ����. */
// [EF40K] uca-ril���� uca-ril-qmi�� ���� ����Ǹ鼭 FEATURE �̻��.
#define FEATURE_SKY_CP_EXCEPTION_DEFINITION

#define FEATURE_SKY_QCRILHOOK_EVENT_PROCESSED_BY_SUB_THREAD

/* need to notify Qcrilhook Unsol Event to application */
#define FEATURE_SKY_CP_EVENT_NOTIFIER


/**
    [EF45K] SkyUsim.java ���� ȣ���ϴ� USIM I/F�� �������� ����. 
    ( qcril_other_usim.c �������� ����. )
*/
/* OEM Hook ������� SIM access�� GSDI�� �̿��Ҷ� sync������� access�ϱ� ���� I/F */
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
/* Java���� Modem API ȣ���� ���� Daemon ( NV access, �ڵ�����, VE ���, etc.. ) 
** init.rc�� �߰��ؾ� ��(init_�𵨸�.rc)
** init.rc�� \LINUX\android\system\core\rootdir �� ��ġ�� */
#define FEATURE_SKY_CP_MANAGER_DAEMON_INTERFACE
#ifdef FEATURE_SKY_CP_MANAGER_DAEMON_INTERFACE
/* Voice Call connection sound event */
#define FEATURE_SKT_CP_VOICE_CALL_CONNECT_SOUND
#endif/* FEATURE_SKY_CP_MANAGER_DAEMON_INTERFACE */
#endif/* FEATURE_SKY_CP_TELEPHONYMANAGER */

/* UMTS PS/CS Domain setting menu support */
//#define FEATURE_SKY_CP_SERVICE_DOMAIN_CHANGE_CMD
/* [EF40K] QMI�� �����ϸ鼭 FEATURE_SKY_CP_SERVICE_DOMAIN_CHANGE_CMD�� ��ü��.
           setPreferredSystem �Լ��� ���� ����þ��� pref domain ���氡�� ��.
*/
#define FEATURE_SKY_CP_CM_SYS_SELECTION_PREF


/* UMTS SMS MO PS/CS Domain setting menu support */
#define FEATURE_SKY_CP_SMS_CFG_SET_GW_DOMAIN

/* Phone Operation Mode setting (lpm, offline, online .. ) */
#define FEATURE_SKY_CP_PHONE_OPERATION_MODE


/* [EF40K] [EF45K] - �������� ���� */
/* RIL state �� ������� �׻� ril socket open���¿����� RIL_REQUEST_XXX �� �����ϵ��� ��. */
/* RIL state�� radio unavailable������ ��� RIL request/response�� ���� �ʵ��� �Ǿ��־� �Ϻ� �׽�Ʈ ��忡�� �������� �����ϴ� ��찡 ����.
     RIL radio state�� ������� ������ request�� ó���ϵ��� ��. */
#define FEATURE_SKY_CP_FORCE_ALLOW_RIL_REQUEST

/* [EF40K] [EF45K] ������ */
/* Airplane mode ���Խ� network mode menu ������ ���������� ������ ���������� ���� �߻�
  ���� EF30S�� ���� ������ ��� service state�� ���� airplane mode check box�� disable ��Ű���� �ϴ� �κ��� 
  ����..������ ���� �������� �ش� �κ� ����...EF30S �ҽ�������� �ش� �Լ� ���� ���� 6140�� �ش� �κ���
  ���� ���� ���� */
#define FEATURE_SKY_CP_AIRPLANE_MODE_CHECK_BOX_CONTROL


/* DDMS Log�� radio log �� �����ֵ��� ��. 
   Test ���Ǹ� ���� ����ϴ� ���̱� ������ envsetup.mk �� TARGET_BUILD_VARIANT �� user ( user mode compile )
   �϶� �� FEATURE_AARM_RELEASE_MODE �� define��.
   (PS1�� �۾� �ʼ�: cust_sky.h �� ��뿩�� Ȯ��.)
   android/system/core/liblog/logd_write.c */
#ifndef FEATURE_AARM_RELEASE_MODE
//#define FEATURE_SKY_CP_RADIO_LOG_DDMS
#endif/* FEATURE_AARM_RELEASE_MODE */


/* [EF40K] [EF45K] - ������ */
/* QMI ��� ���� ��� ���� QMI���� NASI_DEFAULT_RSSI_DELTA ���� �����Ͽ� ���� */ 
/* RSSI Delta Threshold Value�� Modem�� �����ϰ� 1dB�� ������. Modem�� �����ص� qcril_cm_init�� 
   CM_PH_CMD_SIGNAL_STRENGTH_DELTAó���� ���� ph_ptr�� rssi_delta vaule�� update�Ǿ� RSSI Report�ÿ� 
   5dB ���̰� ���� report�ǹǷ� Linux�ܵ� ������ */
#define FEATURE_SKY_CP_RSSI_REPORT_VARIATION_FIX


/* ����ȣ �߽��� ���ؼ� CSFB���� �� �Ǵ� ����ȣ ���� �� LTE�� �̵��Ҷ� 
   �ް��� Ant. bar�� ��ȭ�� ���� �ϱ� ���� ó�� */
// EF45K���� �������� Ȯ�� �� ���뿩�� �Ǵ��� ��, �����Ͽ� �Լ� ����Ǿ� �������ص� �� �� ����.   
//#define FEATURE_SKY_CP_RSSI_REPORT_TIMING_GAP_FIX


/* [EF45K] - ICS���� ����, LTE�� ���� ȹ���� �� ���� ���߽Ž� 3G RSSI ���� ���� ANT Bar�� ǥ�õ��� �ʴ� ���� ���� */
#define FEATURE_SKY_CP_RSSI_REPORT_FOR_ICS


/* [EF40K] [EF45K] - ���� ����, �ϴ� ������ - FEATURE_TODO */
/* LCD OFF ���¿��� SRV_CHANGED_EVENT�� Dereg �Ǿ� LINUX�ܿ��� �ش� event�� ������ �� ����.
   ���ý� GMM Info ���� ���� LCD OFF�ϸ� �ð������� Update���� �ʾ� RTC�� ������ �߻��� ���
   �߸��� �ð�ǥ�ø� �� �� �ִ�. 
   network ����� �Ϸ�� �� 30���Ŀ� property�� �����Ͽ� lcd on/off �� ���ؼ� cm event reg/dereg�� 
   �����ϵ��� �Ѵ�.
   ���� �ð� ���� �� ���ý� GMM Info �������� LCD OFF �ϰ� ���� �ڵ����� �����ϸ� �ð������� 
   �̻��� ���� ������ ���� �ذ��. */
#define FEATURE_SKY_CP_TIME_UPDATE_ABSOLUTELY_ON_BOOT


/* Airplane mode ����/������ ���� ���� Ŀ�ǵ� ó�� */
// [EF45K] [�ʿ����� ���� ������ �Ǵܵ�]
#define FEATURE_SKY_CP_FACTORY_AIRPLANE_MODE_I


/* QMI �� ���ؼ� CM PH event info. ó�� */
#define FEATURE_SKY_CP_OEM_PH_EVENT_WITH_QMI


/* SIM Invalid�� Reject�� ���Žÿ� gsm.sim.operator.numeric �� �ʱ�ȭ �Ǵ� ���� fix */
// [EF45K] ���� �������� setSubscriptionInfo ȣ���ϴ� �κ��� ���� ������� ����.
//#define FEATURE_SKY_USIM_ICC_OPERATOR_PROPERTY_NOT_RESET


/* qcril_data_init() �������� 5�� delay�� 3�ʷ� �����ϰ� �̿� ���� �߰� �����ڵ� ���� 
   5�� delay�߻����� ���� �ʱ⿡ PIN lock ȭ���� �ʰ� �߻��ϰ� �뼭�� ���°� ���� ���ӵ� */
#define FEATURE_SKY_CP_QCRIL_DATA_INIT_DELAY_REMOVE


/* Not support USIM Voice Mail EF */
#define FEATURE_SKY_USIM_VOICE_MAIL_EF_MWIS_NOT_SUPPORT


/* Network Name�� ������������ �ұ��ϰ�, "nas_cached_info.current_plmn" ���� Invalid�� ó���Ǿ� 
** �ش� Network Name�� �ƴ� Table�� name�� ǥ���ϴ� ������ ���� Qcril���� �����ϴ� system info�� 
** state ��ȭ�ø��� update�ϵ��� ��.
** QCT�� �� system info�� LCD enable�ÿ��� update �ϵ��� �ϰ� ���� */
#define FEATURE_SKY_CP_QMI_SYS_INFO_ALWAYS_UPDATE

/*
 * @TODO
 */
#define FEATURE_SKY_CP_FIX_OPERATOR_NAME_DISPLAY


/* SKT ������ ���� - getSimOperatorName()�� ȣ���ϴ� ��� Null return�Ǵ� ������ 
** EF_SPN read�� "gsm.sim.operator.alpha" property�� set�ǵ��� �� */
#define FEATURE_SKY_USIM_PROPERTY_ICC_OPERATOR_ALPHA_UPDATE

/* ������ �ð�ǥ�� ���� ���� 
** 1. �⺻������ Android ������ �ð� ������ �����͵� �� �ð��� �����ϴ� ���� �ƴ϶� GMT �ð��� ����ϰ� 
**    Time Zone�� ��� �ʴ� ������. ����, Time Zone ���� �ð� ����(NITZ)�� ���� ������� �ʰ� ��ü 
**    �����ϴ� Time Zone Table���� ������ GMT�� ���ؼ� ����ϴ� �����
** 2. GMT�ð��� timeoffset�� +40 ���� ��Ȯ�� �ð������� ������ ���� ���������� timezone�� New York����
**    �ν��Ͽ� GMT -5�ð����� ǥ���ϴ� ����
** 3. mcc������ 310(�̱�) �� ���� timezone�� ���� timeoffset������ ������ ���� �ʾ� ��Ȯ�� timezone��
**    ������ ���ϰ� default�� NewYork�ð����� ǥ���ϴ� ������ ����.
** 4. mcc�� 310 �̰� timeoffset�� +40 �ϰ��� timezone name�� Pacific/Guam  ���� �����Ͽ� 
**    timezone �� fix�ǵ��� ������.
** 5. 4���� ������ �̷������ time�����޴��� timezone�� "Chamrro" ( ����ο� ) ��ǥ�õ�. */
#define FEATURE_SKY_CP_TIMEZONE_FIX 

/* [EF45K] ���� ���� ����.
   
*/
// dm logging ����
#define FEATURE_SKY_ADB_LOG_FOR_VITAMIN
#define FEATURE_SKY_CP_DMLOGGING

//...not used
//#define FEATURE_SKY_CP_DATA_LOG_QMI_LOG_ADB_ON
//#define FEATURE_DM_LOG_STORE_TEMP_MEMORY
//#define FEATURE_DMMON_F3TRACE

#define FEATURE_SKY_CP_SYSLOG

/* 
   SD ī�带 ���� DM Logging
*/
#define FEATURE_SKY_CP_DM_LOG_STORE_TEMP_MEMORY

/*
   20120423 Lee Jonghwan
   30145 patch�� qcril.c�� android_request_id�� QMI_RIL_FW_ANDROID_REQUEST_HNDL_MAX_EVT_ID (127)�� ���ѵ�.
   Ril.h�� �߰��� event id���� �߰��Ͽ� 132 ������ ū ������ ������.
*/
#define FEATURE_SKY_CP_RIL_FW_ANDROID_REQUEST_HNDL_MAX_EVT_ID_FIX

/*
     sky_rawdata ������ opening day backup 
*/    
#define FEATURE_SKY_CP_NEW_OPENING_DAY

/*
  [EF49K] Fast_Return_To_LTE ����� On/Off �ϴ� Hidden Menu �߰�.
*/
#define FEATURE_SKY_CP_FAST_RETURN_TO_LTE_ONOFF

#define FEATURE_SKY_CP_LTE_BAND_PREFER_SETTING

// ������ ��ȭ(Missed Call)�� 7�� �̻��� �� ���� ���ŵ��� �ʴ� ����
#define FEATURE_SKY_CP_MISSED_CALL_BUG_FIX

// EF48S���� 2'nd Call ����� ��� �Ҹ� ���� ��쿡 ���� ��������������,
// �ٺ����� ������ ��ȭ�� 2'nd Call �߽� ���� PHONE_DISCONNECT�� �ѹ� �� �ö���� ������.
// �̿� ���� �������� �ݿ���.
#define FEATURE_SKY_CP_DISCONNECT_SND_BUG_FIX

/*
   ��ȭ���ڸ��� ���� �� ������� �ʰ� �߽ŵǴ� ���� ����
*/
#define FEATURE_SKY_CP_1X_CSFB_RETRY_BUG_FIX

/*   Android Factory reset, NV should be initialized default value.*/
#define FEATURE_SKY_CP_FACTORY_RESET_NV_INIT

#endif/* T_SKY_MODEL_TARGET_COMMON */


/* ######################################################################### */



/*****************************************************
    SKT/KT ���� �������
    Feature Name : T_SKY_MODEL_TARGET_WCDMA
******************************************************/
#ifdef T_SKY_MODEL_TARGET_WCDMA

#define FEATURE_SKY_CP_LOCAL_DB     // qcril_qmi_security.c �� ME Perso. �۾����Ŀ� �߰��� ��.
#define FEATURE_SKY_CP_LOCAL_DB_LTE
#define FEATURE_SKY_CP_LOCAL_DB_WITH_QMI

/* OEM QMI commands set */
#define FEATURE_SKY_CP_OEM_COMMANDS_WITH_QMI

#define FEATURE_SKT_CP_SUBSCRIPTION_MODE
#define FEATURE_SKY_CP_OTA_KT_SUBSCRIPTION
/* [EF40K] */
#define FEATURE_SKY_CP_OTA_KT_SUBSCRIPTION_WITH_QMI

#define FEATURE_SKY_USIM_CARD_TYPE    //FEATURE_TODO : keyguardstatusviewmanager.java �� �߰��ؾ���.

#define FEATURE_SKY_USIM_GET_CARD_MODE_AS_APP_TYPE

#define FEATURE_SKY_CP_ACQ_DB_DELETE

// [20120215] [EF45K] Not Used Any more...
//#define FEATURE_SKY_CP_END_DUN_INTERFACE

#ifdef FEATURE_SKY_CP_QCRILHOOK_INTERFACE
/* OEM Hook ������� NV access */
#define FEATURE_SKY_CP_NV_ACCESS_OEMHOOK

#ifdef FEATURE_SKY_CP_LOCAL_DB
/* OEM Hook ������� Local DB access */
#define FEATURE_SKY_CP_LOCAL_DB_ACCESS_OEMHOOK
#endif/* FEATURE_SKY_CP_LOCAL_DB */
#endif/* FEATURE_SKY_CP_QCRILHOOK_INTERFACE */

#ifdef FEATURE_SKY_CP_MANAGER_DAEMON_INTERFACE
/* cpmgrif.c daemon�� ���� NV Access */

#define FEATURE_SKY_CP_NV_ACCESS_CPMGRIF

#ifdef FEATURE_SKY_CP_LOCAL_DB
/* cpmgrif.c daemon�� ���� Local DB Access */
#define FEATURE_SKY_CP_LOCAL_DB_ACCESS_CPMGRIF
#endif/* FEATURE_SKY_CP_LOCAL_DB */
#endif/* FEATURE_SKY_CP_MANAGER_DAEMON_INTERFACE */

/* SKT/KT ���� Me Personalization ( With QMI interface ) */
#define FEATURE_SKY_USIM_ME_PERSONALIZATION


/* EF40K - ���� ���ʿ� */
/*--------------------------------------------------------------------------------------------------------------
** 1. qcril ���� default voice tech.�� 3GPP2�� �̴� 3GPP�� ����.
**   --> ���� �ʱ⿡ 3GPP2�� radio technology�� õ�̵Ǿ��ٰ� 3GPP�� �ٲ� 3GPP2�� CDMA SIM ���� SIM ready�� 
**       �߻��Ͽ� PUK�� PIN ������ ����� �ȵǰų� SIM Record�Լ����� CDMA������ �����ϴ� ��찡 �߻���.
** 2. java class���� Phone type�� GSMPhone���� create �ǵ��� ������
**--------------------------------------------------------------------------------------------------------------*/
#define FEATURE_SKY_CP_DEFAULT_NETWORK_UMTS_IN_RIL

/*--------------------------------------------------------------------------------------------
** Manual PLMN Selection�� FPLMN�� �ִ� ���� �����ؼ� Reject ������ �� 
** �ܸ� ����ý� RPLMN ���� ����� �� �ٷ� ������ Reject �޾Ҵ� ������ ������ �õ��ϴ� 
** ������ ���� ����.
** frameworks\base\core\res\res\values\config.xml ���� skip_restoring_network_selection�� 
** TRUE�� �����ص� ��
**-------------------------------------------------------------------------------------------*/
#define FEATURE_SKY_CP_BLOCK_RESTORING_NETWORK_SELECTION 

/* FEATURE_TODO - ���� �� ���� �ʿ� */
/* [EF39S/EF40K]
   ���� �ʱ� socket open fail�ǰ� 4�ʰ������� ��õ��ϴ� ���� 1�� �������� 8ȸ �ݺ��ϵ��� ����.
   PIN lock ȭ�鿡 ���ݴ� ���� ���Եǵ��� �ϱ� ����. */
// [EF45K] ������

//#define FEATURE_SKY_CP_RIL_SOCKET_OPEN_RETRY_MILLIS

/* FEATURE_TODO - ���� �� ���� �ʿ� */
/* RIL_REQUEST_GET_NEIGHBORING_CELL_IDS Ŀ�ǵ尡 ȣ�� �Ǿ����� 
   Neighbor Cell������ ������ �ִ� ��� system halt�� ������.
   ���ʿ��� Ŀ�ǵ�� ó������ �ʵ��� ���� */
// [EF45K] ������   
//#define FEATURE_SKY_CP_GET_NEIGHBORING_CELL_IDS_NOT_SUPPORT

/*
   20120424 Lee Jonghwan
   30145 patch�� qcril.c �߰��� RIL���� ITEM ó�� ������ ��ȭ�� ���������� �̹�Ʈ ó���� ������ ��.
   Voice & Data REG STATE, Auto & Malual Network Selection ���� RIL event�� 30145 patch ������ ���� ó���ǵ��� 
   qmi_ril_fw_dedicated_thrd_exec_android_requests_set ���̺��� ������.
*/
#define FEATURE_SKY_CP_FW_DEDICATED_ANDROID_REQ_BUG_FIX

/* centralized_eons_supported  ��� ���ۿ� ���� network name �� manual search list ǥ�� ������ �߻��� */
#define FEATURE_SKY_CP_CENTRALIZED_EONS_NOT_SUPPORTED

/* 20120314 ithong
   isim application ������ ���� feature.
   �𵩴ܿ����� isim app init �� �������� �ʱ⿡ isim app detected ���� usim ready�Ǹ�,
   isim app ���� ready �� ó���Ͽ� �ȵ���̵������ �����ϵ��� ��.
*/
#define FEATURE_SKY_CP_OEM_SUPPORT_FOR_ISIM_APP_IN_QCRIL

/* 
LTE 3GFB call��  system time�� �����Ǵ� ���� ���� 900ms ������ system time setting�� skip�ϵ��� �Ͽ� ���������� ����
*/
#define FEATURE_SKY_CP_DECREASE_TIME_ROLLBACK

#endif/* T_SKY_MODEL_TARGET_WCDMA */


/* ######################################################################### */


/*****************************************************
    SKT �� �������
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
    KT �� �������
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
** SKT ���� Original Feature 
** Ȯ���ϸ鼭 ������. 
** �ҽ��� ���� �ִ� Feature 
** ----------------------------------------------------------------------------*/

/* �ҽ��� ���� �ִ� Feature��
   Android ���¸� Roaming���·� ��ȯ�ϵ��� �����Ѵ�.
   Roaming���¸� ������ �����ǵ��� �Ͽ� RAD app. �� �ؿܿ����� �����ϴ� ��� �׽�Ʈ�� ����.
   #47566# �ڵ�� ������. */
#define ds1_cp_roaming_fake_setting

/* ETC(���濬��) ���� ����� �������� call end �Ǵ� ������ active call�� holding call���� ������ ����Ǵ� ��� 
   [Unable to switch calls.]�̶� �˾��� ǥ�õ�. �˾� ǥ�� ���� �ʵ��� ���� ���� */
//#define ds1_cp_etc_bug_fix2

/* ETC(���濬��) ���� ����� call end�� ���ؼ� CM_EVENT_CALL_MNG_CALLS_CONF �� ó������ ���ϰ�
   pending�Ǿ� �ִ°�� call endȭ�� ó���� ���� ���ϰ� ���� ���� �˾��� �߻��ϴ� ���� ���� */
//#define ds1_cp_etc_bug_fix


/*==============================================================================
**------------------------------------------------------------------------------
**      SKY  Call Processing ( DS1 Features for WCDMA KTF on LINUX Module)
**------------------------------------------------------------------------------
**============================================================================*/

/* From EF10, ds1_cp_sim_card_retry_num_support
   pin verify ����� retry num ���� ���޵Ǿ� ó���� �� �ֵ��� ������
   EF18K���� qualcomm���� api ������� ������ */
#define FEATURE_SKY_CP_SIM_CARD_RETRY_NUM_SUPPORT


/* [ds1_cp_time_info_bug_fix]�� �����ڵ� ������, ���Ŀ��� �������� �� ��
   20100611 : ���� �����ڷκ��� ���� ��û �޾� ������.
   data���� ���� ���¿��� �ð����� ���� ���� ����.
   LCD on�� ������ ���� ���ŵ� �ð������� ������ ����Ǵ� ��������. */
#define FEATURE_SKY_CP_TIME_INFO_BUG_FIX


/* From EF10, ds1_cp_factory_diag_protocol
   /android/kernel/drivers/char/diag/diagfwd.c �� ��ġ 
   ���� Command �� protocol��Ʈ���� �����ϴ� �κ� �߰�. (�����κ��� ���� ���Ϸ� �и��Ͽ� ����)
   nv.h [ds1_cp_nv_access_rpc]�κп� nv_net_sel_mode_pref_type �߰� �Ͽ���. */
#define FEATURE_SKY_CP_FACTORY_DIAG_PROTOCOL


/* From EF10, ds1_cp_skt_send_dtmf_in_alerting_state
   SKT�ΰ����� �� ��й�ȣ ��ȭ ���� call state�� Alerting state(CC/Progress ����) �϶� 
   ��й�ȣ �Է��� �ʿ��ϱ� ������ origination�� ���� ���� Alerting state���� DTMF �Է��� �����ϵ��� ��.
   3200 patch�������� ���� �������װ� �����Ͽ� feature����!!! */
#define FEATURE_SKT_CP_SEND_DTMF_IN_ALERTING_STATE


/* [EF40K]�� �ش� �ڵ尡 ���� ������ */
/* From EF10, ds1_cp_cdma_app_remove
   cdma�� app. ����.
   NAM setting app. */
#define FEATURE_SKY_CP_CDMA_APPP_REMOVE

// WCDMA ���� ��� CTS �׽�Ʈ�� ���� CDMA ���� android.hardware.telephony.cdma �׸� ����.
// android\device\qcom\common\common.mk ����.
// frameworks/base/data/etc/android.hardware.telephony.cdma.xml:system/etc/permissions/android.hardware.telephony.cdma.xml
#define FEATURE_SKY_CP_CTS_CDMA_DELETE

/* From EF10, ds1_cp_auto_answer_bug_fix
   Qualcomm NV intem ���� ���� �ʰ���
   Android �⺻ setting���� ������ */
#define FEATURE_SKY_CP_AUTO_ANSWER_BUG_FIX


/* From EF10, ds1_cp_usermode_off_debug_message
   SP33K�� �� ����� ����Ǿ� ���� ����. EF12K �𵨺��� ����
   user mode �������� ���ʿ��� �޼��� ����
   EF18K ������ */
#define FEATURE_SKY_CP_USERMODE_OFF_DEBUG_MESSAGE


/* From [ds1_cp_service_domain_changed_bug_fix] of EF10
   ���� �ʱ⿡ qcril ���� service domain�� CS_PS �� ������ �����ϴ� ���� ����
   EF18K���� �̹� �����Ǿ� ������ */
#define FEATURE_SKY_CP_SERVICE_DOMAIN_CHANGED_BUG_FIX


/* 20100714 hbwoo
   3���� �ƽ��� �� ����
   1.ANR �α״� ������ �α׸� ����� ���� ����ϴ�. ���� History�� ������ �����ϴ�.
   2.VM�� Exception �α״� ���� /data/anr/traces.txt ������ ���� ���� �ʽ��ϴ�.
   3.2������ ����� Exception �α׵� android runtime���� ����ϴ� call stack�� ǥ�������� �ʾ� ��� ��ġ���� exception�� �߻��ߴ����� �� �� �����ϴ�.
   EF18K���� ������ */
#define FEATURE_SKY_CP_CONTROL_ERROR_LOG_FOR_ANDROID


/* 20100814 �̻��
   Froyo ��ġ �� SIM READY�� ���� �ʾ� ���� �ε��ȵ� ���� (���������� 86��)
   �߽� ���� �и� SIM READY�� ���������� �������� ���� ����.Froyo ��ġ�Ǹ鼭 FLAG_RECEIVER_REPLACE_PENDING��� flag�� �߰��Ǿ��µ�
   broadcast�ϵ� ���� ���� �����ϱ� �� ���ο� broadcast�� ������ ���� ������ �ֽ� broadcast�� ��ġ�ǵ��� �ϴ� flag��. 
   �̿� ���� ���������� ���� ���� ����. broadcast ���� �� �� flag�� ����.
   [feature_sky_usim_block_flag_receiver_replace_pending] */
#define FEATURE_SKY_USIM_BLOCK_FLAG_RECEIVER_REPLACE_PENDING


/* T_SKY_MODEL_TARGET_WCDMA �κп� define�Ǿ� ������, KT �䱸������ ������Ű�� ���� �������� �߰�.
   SKT ������   
   To synchronize with modem on FEATURE_SKT_CP_SUBSCRIPTION_MODE */  
#define FEATURE_SKT_CP_SUBSCRIPTION_MODE


/* T_SKY_MODEL_TARGET_WCDMA �κп� define�Ǿ� ������, KT �䱸������ ������Ű�� ���� �������� �߰�.
   ME Personalization ���� ����.
   ���� AMSS feature�� FEATURE_SKY_USIM_ME_PERSONALIZATION */
#define FEATURE_SKY_USIM_ME_PERSONALIZATION


/* android ���� �� device_provisioned ��� secure setting���� üũ�Ͽ� �����Ǿ����� �ʴٸ� 
   �������� �ź��ϰų� keyguard lock screen�� �������� �ʰ� �ϴµ� �ܸ� ����� ������. 
   ���ʿ��� ������� disable ��Ŵ */
#define FEATURE_SKY_CP_DISABLE_CHECK_DEVICE_PROVISIONED


/* SIM card type�� Ȯ���� �� �ִ� I/F ����. ( ����� �䱸���� �ݿ��� ����. ) */
#define FEATURE_SKY_CP_SIM_CARD_TYPE_CHECK


/* SKY �ܸ������� ����� intent Action ���� */
#define FEATURE_SKY_CP_TELEPHONY_INTENT_ACTION


/* T_SKY_MODEL_TARGET_WCDMA �κп� define�Ǿ� ������, KT �䱸������ ������Ű�� ���� �������� �߰�.
   To synchronize with modem on FEATURE_KTF_CP_SUBSCRIPTION_MODE */
#define FEATURE_SKY_CP_OTA_KT_SUBSCRIPTION


/* STATE_IN_SERVICE, STATE_OUT_OF_SERVICE �ΰ��� �����Ǵ� framework service state�� ����ȭ �ϱ� ���� sub state�� �߰���.
   OUT_OF_SERVICE�� NO Service�� Limited Service�� �����ϱ� ����. */
#define FEATURE_SKY_CP_SERVICE_STATUS_DETAIL_SUBSTATE


/* WCDMA, GSM �� RSSI level ���� ����... 
   H/W ��û�� ���� ����... */
#define FEATURE_SKY_CP_GW_RSSI_LEVEL


/* service���� ������ MCC/MNC �� update �Ǵ� �κ��� Limited service���¿����� update�� �����ϵ��� ������. */
#define FEATURE_SKY_CP_GET_MCCMNC_UPDATE_IN_LIMITED_SRV


/* Data ���� ���·� ���� Plmn �����˻��� ���� �ʴ� ���� ����.
   ����Ʈ �˻� ���� data ���� ���¸� üũ�Ͽ� disconnect���°� �ƴ϶�� Data connectivity �� disable��Ű�� ���� 
   ����Ʈ �˻��� �����ϵ��� ��. */
#define FEATURE_SKY_CP_MANUAL_SEL_PLMN_AFTER_DATA_DISCONNECT


/* ������ ��� ���� �� ����ý� ������ ��尡 �缳������ �ʵ��� ��. */
#define FEATURE_SKY_CP_AIRPLANE_MODE_RELEASE_AFTER_BOOT


/* android original �ҽ����� �����Ǵ� CDMA ���û��� ���� �� ���� ����
   �޴� ���Խ� roaming ��� ���� ǥ�� 
   ���������� network ���� �޴� �������� ���ϵ��� ����.
   Hidden �޴����� band ���� ������ Android ���� �޴����� network preferred band ������ �ȵǴ� ���� ����. */
#define FEATURE_SKY_CP_PREFERRED_NETWORK_MODE_SELECTION


/* [EF40K] - ���� ���ʿ� - onServiceStateChanged() �ȿ� updateCdmaRoamingIcon()�� ���� */
/* GSM/WCDMA mode���� signal strength status bar ǥ�ð� ���� �ʴ� ���� ����.
   3108 �������� cdma���� icon�� ǥ�õǵ��� �ϴ� ������ ����.
   3200 �������� ������ �Ǿ� roaming icon�� ������ �������� ���� */
#define FEATURE_SKY_CP_SIGNAL_STRENGTH_STATUSBAR_UMTS


/* PUK 10ȸ ���� ī�� status �߰�
   PUK 10ȸ ���� ī�� ���� INTENT_VALUE_ICC_PERM_BLOCKED �� �߻���Ŵ. */
#define FEATURE_SKY_CP_ADD_PERM_BLOCKED_CARD_STATUS


/* 20110622 - [EF40K]���ʹ� FEATURE_SKY_CP_USSD_CNAP_8BIT_CHAR_SUPPORT�� ó���Ǹ鼭 Qcril�� 
** ������ ���ʿ�. GsmConnection.java�� �����ϸ� �� */
/* CNAP ������ ���� RIL �� framework ����. */
#define FEATURE_SKY_CP_CNAP_SUPPORT


/* Android���� IMEI Ȯ�� ��� ���ý� ******** ���·� ���̵��� ����
   3GPP �԰������� ���� �𵨿����� ������ Ȯ�� �� �� ����� ��. */
/* [EF45K] ������ ��å BlackList ���� ���������� �ؼ� IMEI ǥ�� ��. */      
//#define FEATURE_SKY_CP_IMEI_NO_DISPLAY


/* [EF40K] - status.java�� ó���� �ڵ��, ����� ����Ǿ� msimstatus.java���� ó���� */
/* 20100514 seobest
   IMEI ǥ�� �䱸���� ���� ������ �ݿ�
   *#06# �ÿ� IMEI�� *************** �� ǥ��
   �޴��� ��ȭ ���� ������ IMEI�� *************** �� ǥ��
   IMEI�� �д� Method�� ���������� �����Ǿ�� �� */
/* [EF45K] ������ ��å BlackList ���� ���������� �ؼ� IMEI ǥ�� ��. */   
//#define FEATURE_SKY_CP_HIDE_IMEI


/* Emergency Call ���� ���� ���� �߰�. 
   Emergency Call �Ǵܿ��θ� ���� ������ �ȵ���̵� ������ �̿��ϴ� ������ ���� */
#define FEATURE_SKY_CP_EMERGENCY_CALL


/* ��ȭ������ ������ ���� �̺�Ʈ ���� */
#define FEATURE_SKY_CP_CS_CALL_CONNECTION_SND_START


/* USSD �޼��� �� CNAP ���� KSC5601 �����ϱ� ���ؼ� ������.
   data coding scheme�� ���� ���ڰ� ���������� ǥ���Ǵ��� Ȯ�� �ʿ�! */
#define FEATURE_SKY_CP_USSD_CNAP_8BIT_CHAR_SUPPORT


/* ��ȭ���� �޴� ����
   CDMA, WCDMA���� �޴� ���ʿ�.... */
#define FEATURE_SKY_CP_REMOVE_ANDROID_CALL_FEATURE_SETTING_MENU


/* card power down Ŀ�ǵ� ó������ �ʵ��� ��. < �� ������ �߻��ϴ� �ֿ� ������ >
   1. ������ ��� ���Խ� USIM card access���� �ʴ� ����
   2. ������ ��� ���Խ� SIM card�� �νĵ��� �ʴ´ٴ� ���� ǥ�õ�.
   3. on chip sim mode�� ������ ������ ��� ���� card�� ���� ���¿��� 
   UIM���� card power downĿ�ǵ尡 ���޵Ǿ� page fault ������ �߻���.... */
#define FEATURE_SKY_CP_CARD_POWER_DOWN_NOT_SUPPORT


/* ���� �޴� �׸� ���ؼ� class������ ���� ������ ����...
   Market �� system application�� Startup Manager�� ���� ���α׷������� ����. */
#define FEATURE_SKY_CP_CLASS_DEPENDENCY_CHECK


/* [EF40K] - Gsmcalltracker.java�� hangup()���� �ٸ� ������ BRCM[Excelt], BTL-A�� �ؼ� ó���� ���� �ϴ� �������� ���� */
/* Bluetooth ���� ������ ��ȭ�߿� ȣ ���Ž� active call ������ ���� ������ ���ŵ� ȣ�� Alerting���¸� ���� �ؾ���.
   �ȵ���̵� �⺻ ������ active call������ ���ŵ� ȣ�� �ڵ� �����. */
#define FEATURE_SKY_CP_BLUEBOOTH_CERTIFICATION


/* To synchronize with modem on FEATURE_SKY_CP_PLMN_SELECTION */
#define FEATURE_SKY_CP_PLMN_SELECTION


/* To synchronize with modem on FEATURE_SKY_CP_DISP_NETWORK_NAME */
#define FEATURE_SKY_CP_DISP_NETWORK_NAME


/* 20100316 hbwoo Phone process �������� Qcrilhook�� ȣ���ϵ��� ��.
   Phone process/main thread���� qcrilhook�� ȣ���ϸ� sync operation�� ���������� ������ �� ����. 
   ������ sub thread�� �����Ͽ� �̸� ó���ϵ��� ��. */
#define FEATURE_SKY_CP_CALL_QCRILHOOK_IN_PHONE_PROCESS


/* Qcril���� �߻��ϴ� Event�� Application���� �����ϱ� ���� Event Notifier */
#define FEATURE_SKY_CP_EVENT_NOTIFIER


/* [EF40K] - �������� stauts.java���� ó���ߴ� ���� ��� �������� ���� msimstatus.java���� ó���� */
/* 20100503 hbwoo
   KT�� ��� Settings > System > About phone > Status > My phone number�� ǥ�ð� +821 029 219302 �� ǥ�õ�.
   PhoneNumberUtils���� ������ �� ������ Phone number utils�� ��� MSISDN ���� �ٸ� ��ȣ�� Handling �ϹǷ� 
   ǥ���ϴ� �ʿ����� �����ϱ�� ��.
   ����, �Ʒ��� ���� ������ ���, AdnRecord.java/parseRecord()/PhoneNumberUtils.calledPartyBCDToString()�� �����ϸ� ��. */
#define FEATURE_SKY_CP_DISPLAY_PHONE_NUMBER_WITH_TOA


/* [EF40K] - QMI �������� ���� �ϴ� �� ����� �������� ���� */
/* ������ release�� ���Ź��� ���ϴ� ��Ȳ���� Call END �õ��� call ȭ���� ����ؼ� in call���¸� �����ϴ� ���� ����.
   ���� ������������ ����� �������� ȣ����� call end�� ��ٸ��� �ʰ� call_end_req Ŀ�ǵ� �̺�Ʈ �߻��� call ȭ���� ������ �� �ֵ��� ��.
   A + B ( active ) , B + C ( hold ) ���¿��� A�� ȣ���� �ϴ� �������� B�� ȣ�� �����ϸ� android �� call state�� ril�� call state�� ���̴� ��찡 �߻���.
   Disconnect ���� release procedure�� LG���� �Ｚ���� ���̰� �־ KT�� ��� ��ǳ��, �ͻ� �� �Ｚ������ �����ؾ� ��. */
#define FEATURE_SKY_CP_CALL_END_REQ_FOR_UI_CLEAN


/* 20100514 hbwoo
   IDLE ����� 30�ʸ��� Status command�� UICC�� �������� Ȯ���ϰ�, UICC�� ���� ������ �ǴܵǸ�
   "USIM ī�带 �� ������ �� �� �����Ͻʽÿ�" ����ǥ�� �� ���ȣ UI�� ��ȯ
   Event�� �����ϱ� ���� �۾� */
#define FEATURE_SKY_CP_CARD_REMOVED


/* [EF40K] - QMI�� ����Ǿ� ������ */
/* phone process ���� �߻� ����, lpm�� ���������� ������ ����
   Android Phone process �� excpetion�߻��� ���ؼ� ����۵ɶ� phone state�� LPM ���� online���� �������� ���ϴ� �������� �����߸�� ������ �ϰų� ���� ���� �ѱ� ������ ������ ������
   subscription available�� �������� ���ϰ� lpm ���Կ� ���� subscription disable ���°� �����Ǿ� ������ �߻�       
   GW subscription available/disable Ŀ�ǵ� �� �̺�Ʈ�� ó���ϴ� �� �־� ���ܻ�Ȳ�߻��� ���ؼ��� �ش� �̺�Ʈ�� Ŀ�ǵ尡 ó���� �� �ֵ��� �� */
#define FEATURE_SKY_CP_SERIVCE_RECOVERY_FROM_ERROR


/* [EF40K] - QMI�� ����Ǿ� ������ */
/* modem �ʰ� Android�� service status�� ���� �ٸ� ��� ����
   Modem( in service ), android ( out-of-service )   
   Service status�� In serivce���·� ����ɶ� RIL_UNSOL_RESPONSE_NETWORK_STATE_CHANGED �� Android�� �����Ͽ� 
   service state�� ����� �� �ֵ��� ��.  LCD on���¿����� �����ϵ��� �Ͽ� ���ʿ��� wakeup ������ �������� �ʵ��� ��
   SVCMGR_SS_SRV_CHANGED_EVENT�� ���� changed_fields ���� ������� ó���� �ϴµ�, SVCMGR_SS_SRV_CHANGED_EVENT�� �޾����� 
   changed_fields ���� ���� ��� ����� Service Status�� ������Ʈ���� ���ϴ� ������ �����ϱ� ����. */
#define FEATURE_SKY_CP_MODEM_VS_ANDROID_SRV_STATE_MISMATCH


/* 20120327 SHPark
   ������ ù MT call ���Ż��¿��� ��ȭ�߰��Ͽ� hold reject�� ���� ��� last_call_failure_cause�� linux������ ���޵��� �ʾ�
   ��ȭ ȭ���� ù MO call �� �ƴ� Managed call�� ���̴� ������ �����ϱ� ����. */
#define FEATURE_SKY_CP_LAST_CALL_FAILURE_FORCED_INIT


/***********************************************   KT GPS FEATURE *************************************************************/

/* GPS Test  menu default  ##759477#  */
#define FEATURE_SKY_CP_GPS_TEST_SUPPORT
/****************************************************************************/
/****       FEATURE_SKY_CP_GPS_TEST_SUPPORT �� �ϰ� �۾�. *************/
/****          KT ����ڿ� GPS Test menu �۾� (##759477#)           *************/
/****             #define FEATURE_KTF_CP_GPS_TESTMENU            **************/
/****             KT GPS - H/W Cno Test menu �۾�                        **************/
/****               Timeout, CNo �������� ���� ����                       **************/
/****               #define FEATURE_SKY_CP_GPS_CNO                   **************/
/****************************************************************************/


/*[EF45K] KT LBS EXTENSION */
#define FEATURE_KT_CP_LBS_TEST

/* KT GPS ���� NV Item RW ��� �߰� �۾� */
#define FEATURE_SKY_CP_GPS_NV

/*gps configuration*/
#define FEATURE_SKY_CP_GPS_CONFIGURATION


/*********************************************************************************************************************************/



/* [EF40K] - qcril_other.c�� qcril_other_read_imei_from_nv()�� ����� �ڵ�� QMI �������� ������ */
/* EF18K - CTS TEST (testGetDeviceId)�� IMEI�� null�� �����Ͽ� Fail�Ǵ� Bug Fix
   Fix the CTS Test bug */
#define FEATURE_SKY_CP_CTS_TEST_FIX


/* �ش� ��ƾ�� skyusimreceiver.c�� 6������ �����ϰ� UICC GCF�� F/U �ϹǷ� �������� ���� */
/* GCF Test �� �ι��� �ڵ����� �޴��� ���� �׽�Ʈ�� ���ذ� �ǰų� USIM phonebook 
   read�� ���ؼ� ���� ������ �߻��Ͽ� fail�Ǵ� ������ ��Ÿ��.
   KT�� ��� �ؿ�ī���ϰ�� phonebook ���� �� �����Ƿ� ���� ����, On chip SIM ���� ����Ͽ�.. 
   gcf mode�̰ų� cardmode, cardtype�� unavailable�� ��쿡�� pb access block. */
#define FEATURE_SKY_CP_PHONEBOOK_ACCESS_BLOCK_CONDITION


/* 20100605 hbwoo
   Phone process �� ArrayIndexOutOfBoundsException �� �߻��ϰ� �Ͽ� process�� ���̴� code
   ril.java�� if(false)�� if(true)�� �����ϰ� 
   new SkyQcRilHook().sendQcRilHookMsg("phone.crash");�� ������ exception�� �߻��� */
#define FEATURE_SKY_CP_SIMULATION_PHONE_CRASH


/* [EF40K] - Qcril.c�� persist.radio.onchipsim�� ������ �ʿ� ���� */
/* Modified [ds1_cp_ftm_exit_rf_calibration] of EF10
   RF���� ���� ���� �� online���� ������� ���ϰ� ftm mode�� �����ϴ� ���� ����
   FTM ���� �� ����ý� online���� �������� ���ϴ� ���� ����.
   20100610 hbwoo, Onchip sim mode �� ��� FTM���� ���������� �������� �ʴ� ���� �߻� 
   FTM mode ������ Onchip sim�� ���� EF�� �д� ������ ���� �浹�� ������ ����. 
   Onchip sim �� ��� fetchSimRecords() ���� �ʵ��� ��. */
#define FEATURE_SKY_CP_FTM_EXIT_RF_CALIBRATION

/* 20110413 - EF34K���� �������� ���� */
/* Problem description 
   When SIM_REFRESH with SIM_INIT is received, the Android framework updates all saved SIM data. 
   This causes a large amount of SIM_IO. In the meantime, when SIM_READY is received, 
   the framework again starts updating SIM_READY. This results in excessive SIM_IO. */
#define FEATURE_SKY_CP_BUG_FIX_CR228975_FOR_5320


/* �ð� ǥ�� ���� ������ ���� Log�� ���⵵�� ��
   AMSS�ܰ� LINUX�� ��ο��� Log�� ���� */
#define FEATURE_SKY_CP_TIME_VERIFY


/* [ds1_cp_sky_utils] �̸� ���� */
#define FEATURE_SKY_CP_UTILS


/* �ؿ�ī�� + �ؿܸ�, �ؿ�ī�� + ����Ÿ����� ���� Lock ���� 
   To synchronize with modem on FEATURE_SKY_USIM_ALLOW_OTHER_MCC */
#define FEATURE_SKY_USIM_ALLOW_OTHER_MCC


/* [EF18K] only, MSM8255 only
   Qualcomm bug�� ������. PhoneManager�� GetSimState�� �׻� Unknown���� return �Ǵ� ���� */
#define FEATURE_SKY_USIM_GET_SIM_STATE


/* EF40K ���� ���ʿ� */
/* �ܸ� PS ONLY ���� ������ android�ܿ��� Reg state�� No Service�� ó���Ǵ� ������ ������ */
#define FEATURE_SKY_CP_SUPPORT_PS_ONLY_MODE


/* ���ʿ��ϰ� Linux���� wakeup�Ǿ� �������� CM Dog Error Fatal ������ �߻��ϴ� ���� ���� ����
   DFEATURE_QCRIL_NCELL �� Block�� */
#define FEATURE_SKY_CP_BLOCK_QCRIL_NCELL


/* 20101006 hbwoo
   EF18K Froyo ��ġ �� Dual Card�������� ���� ������������ Absent�� ó������ �ʴ� ������ ����
   No SIM, ī�� ���Ž�, �ҷ� ī�� ���Խ� Absent�� State������� �ʾ� �˸� �˾� �߻����� 
   ī�尡 ���°�쿡�� UiccCard�� �����ϰ�, event ó���ϵ��� ���� */
#define FEATURE_SKY_CP_CARD_FUSION


/* frameworks\base\core\res\res\values - config.xml */
/* Network Provider ������ ���� �ʾ� ���� �߻�. 
   Location manager service���� Network Provider�� ������ �� �ֵ��� ID ���� ��. */
#define FEATURE_SKY_CP_NETWORK_LOCATION_PROVIDER_SETTING


/* ����� �ؿ� USIM(�Ϻ� ������� Softbank) ���� �� phone ���μ����� �����Ǵ� ���� ����(StkService.java, NullPointer Exception)
   EF18K�� ���� �߻����� �ʾ� ������ */
#define FEATURE_SKY_CP_GOOGLE_BUG_FIX


/* SKTī�� + SKT�� �����˻��� SKT�� Ȱ��ȭ�ǵ��� ���� */
#define FEATURE_SKY_USIM_ALLOW_OTHER_MNC


/* Ư��ī��(���� 2000��, 3���� Application�� �����ϴ� ī��)�� ��� �������� KT ������ ���������� ���� �ʴ� ����
   AppType�� Unknown�� ��� RuimRecords�� �����Ͽ� REFRESH Event�� SIMRecords�� ��ϵ��� ���ؼ� ��Ÿ���� ������ 
   AppType�� Unknown�� ��쵵 SIMRecords�� �����ϵ��� ���� */
#define FEATURE_SKY_USIM_CHANGE_RUIM_TO_SIM_FOR_APPTYPE_UNKNOWN


/* EF34K���� QCT �ڵ� �������� ���� ������ �ʿ� ���� */
/* RILD crash �߻��� Detach�� �ܸ���� ����ؼ� LPM state���� �ӹ��� �ִ� ����
   QCRIL�� LPM õ�� ���� RIL�ܿ��� RADIO_POWER request�� ���� �� ��� 
   QCRIL�� Operate mode�� change���� �ʾҴٰ� �Ǵ��ϰ� �ٷ� complete�� ���������� 
   pending event�� ó������ �ʱ� ������ RADIO_POWER request �߻������� ���� �ش� ������ �߻��� �� �־� 
   �̷� ��� pending event ó���Ҷ����� ��ٸ� �� RADIO_POWER request�� ���� complete�� ó���ϵ��� ��. */
#define FEATURE_SKY_CP_KEEP_LPM_FIX_DUE_TO_RILD_CRASH


/* event ������ ���� jni interface
   from EF13S 
   FEATURE_SKY_CP_TELEPHONYMANAGER �� ����� �� ����.
   ���� ���� Ȯ�� �ʿ���.*/
#define FEATURE_SKY_CP_JNI_INTERFACE

/* �ڵ����� �̺�Ʈ ������ ���� interface
   from EF13S */
#define FEATURE_SKY_CP_AUTOANSWER_INTERFACE

/* EF34K ���� ������ */
/* 20101123 PDM ������ 
   No SIM ���·� ���ý� no_sim icon ǥ�� ���� �ʴ� ���� 
   SP33K�ڵ带 �����Ͽ� �ӽ÷� �����ϰ�, ���� �����ϵ��� ��. */
#define FEATURE_SKY_CP_NOSIM_ICON


/* FEATURE_TODO - ���� �� ���� �ʿ� */
/* �ܸ��� service status�� SYS_SRV_STATUS_PWR_SAVE �϶� QCRIL_CM_SCREEN_STATE_ON ���°� �ɶ� 
   �� Key interrup �߻����� LCD�� on�ɶ� �ܸ��� power save���¶�� modem�� wakeup��Ű���� �ǳ�, 
   qualcomm bug�� ���� �ȵǴ� ���� ���� */
#define FEATURE_SKY_CP_MODEM_WAKEUP_IN_STATUS_PWR_SAVE_BUGFIX


/* SkyNv Interface�� ����ϵ��� ������.
   EVENT_GET_GCF_MODE_DONE �� �ʿ䰡 ���� �ּ� ó���� */
#define FEATURE_KT_CP_CHECK_GCF_MODE


/* test menu ������ ���� dial ���� �ڵ� */
#define FEATURE_KT_CP_HIDDEN_CODE


/* SKT ����޴� �� �׽�Ʈ �޴� ���� */
#define FEATURE_KT_CP_HIDDEN_MENU


/* WCDMA/GSM debugscreen
   Radio Condition debugscreen (CS Debug Screen) */
#define FEATURE_KT_CP_DEBUG_SCREEN


/* From EF10, ds1_cp_cs_debugscreen
   CS ���� Debug Screen */
#define FEATURE_SKY_CP_CS_DEBUGSCREEN


/* [EF40K] - This feature doesn't need */
/* debugscreen�� ǥ�õǴ� local_db ���� RIL�� ���ؼ� �����ü� �ֵ��� �ϴ� ��� �߰� */
#define FEATURE_KT_CP_MODEM_LD_ACCESS


/* SKT UA field ������ ���ؼ� cdma�� EF file�� IMSI_M, IRM �� ������ �ֵ��� telephonyManager����
   GSMPhone.java���� ���� �ʱ� EVENT_SIM_RECORDS_LOADED event�߻� ������ read */
#define FEATURE_SKT_CP_CDMA_MIN_EF_ACCESS


/* SKT ������������ Supplementary Service MMI Code �� ������� �ʵ��� �Ѵ�.
   CDMA�� feature code�� ����ȭ�� ���� SKT�䱸 �������� mcc+mnc�� 45005 �� ��쿡 ���ؼ� ó����. */
#define FEATURE_SKT_CP_SUPS_SERVICE_REQUEST


/* 20100421 hbwoo, hksong
   ����޴����� OTA LOG�� ǥ���ϱ� ���� �۾� */
#define FEATURE_KTF_CP_WOTA


/* ��Ʈ��ũ ���Ӹ�带 KT �䱸���׿� �°� �۾�
   ��Ʈ��ũ ���Ӹ�� ���� �� ����� �˾����� Ȯ���� �����ϴ� ���� ����ǵ��� ���� */
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
   WMS Link control�� ����ϸ� MMS app.�� ���� �߽� �� ������ �Ѱܹ޾� WMS���� ó���ϵ��� RIL I/F ���� */
#define FEATURE_KTF_CP_MULTI_SMS


/* 20110705 - SMS�� ���� ���� Prefer domain�� �ؿ� Prefer domain�� �и��Ǿ� ���� ��
** ������ PS domain, �ؿܴ� CS domain���� SMS �߽��� �ڵ����� �̷�� ������ ó���ϱ� ���� */
#define FEATURE_KT_CP_SMS_MO_DOMAIN_SET_BY_MCC	


/* 20100325 JongYeob
   To synchronize with modem on FEATURE_KTF_CP_PLMN_SELECTION
   Automatic/Manual PLMN Selection functionality for KT
   This functionality included "[ds1_cp_skt_network_plmn_manual_selection]" */
#define FEATURE_KTF_CP_PLMN_SELECTION


/* KT UICC ���� ���¿��� ���� Ÿ����� Camping�� RSSI Bar ������ ǥ������ �ʵ��� �� */
#define FEATURE_KT_CP_RSSI_BAR_ZERO_DISPLAY


/* ��Ʈ��ũ ���Ӹ�带 KT �䱸���׿� �°� �۾�
   ��Ʈ��ũ ���Ӹ�� ���� �� ����� �˾����� Ȯ���� �����ϴ� ���� ����ǵ��� ���� */
#define FEATURE_KT_CP_NETWORK_ACCESS_MODE


/* REFRESH(UICC Reset)�� OTA msg�� ���� ��� Status Bar�� 
   "ī�� ���� �������� ī�尡 ���µǾ����ϴ�. " Noti�ϵ��� ���� */
#define FEATURE_KT_CP_OTA_UICC_RESET


/* [ds1_cp_display_network_name] for SKT, which is deleted
   Notification ������ ǥ�õǴ� PNN, SPN, PLMN �� ���� ǥ�� ��� ����
   Network Name���� ǥ���ϵ��� �����ϱ� ���ؼ� PNN, SPN ǥ�� ���ϵ��� ������
   Network Name�� KT �䱸�� ����  Long Name �켱 ǥ�� �ǵ��� �ϰ� Long Name�� ���� ��� Short Name�� ǥ���ϵ��� ���� 
   Andorid�� Full name�� ǥ���ϴ� ������ ó���ǰ� �־� ���� full name�� ������ ���� ���ŵ��� �ʴ� ��� �������� ó���Ǳ� ������ 
   short name���� ó���� �� �ֵ��� ���� ó���� */
#define FEATURE_KT_CP_DISPALY_NETWORK_NAME


/* KT���� �䱸�ϴ� �ΰ����� �� CNAP, CD, ECT, COLP, COLR, CLIP ���� �ȵ���̵忡�� �������� �ʾ� �̸� ������
   RIL�� Call ��Ʈ���� �����ϰ� Phone�� Call UI���� ������.
   call UI ������ FEATURE_GSM_MMI_CODE_KTF_REQUIREMENT �� �����Ǿ����� ������ ������ �����Ͽ���. */
#define FEATURE_KT_CP_GSM_MMI_CODE_FOR_KTF_REQUIREMENT


/* A-B�� ��ȭ �߿� C�� A�� ��ȭ�� �� ��� A�� CC/Setup�� ����. 
  �� �� signal_incl �� ���ԵǾ� ���� ���� ���, Network�� vocoder data�� signal tone�� ������. 
  ������ android�� second call�� �����ϴ� ��� default�� signal tone�� ����ϱ� ������ 
  ��񿡼� ������ signal tone�� ��ġ�� ��. ������ call notifier �ʿ��� signal value�� ������ �ʿ䰡 ����.
  signal value ���� broadcast�ϵ��� ��. */
#define FEATURE_KTF_CP_CALL_MANAGER_NOTIFY_SIGNAL_VALUE


/* SKT ���� [ds1_cp_event_for_time_and_rad] ���� �ð�üũ �κи��� ������
   TIME_VALIDITY_CHECK Intent�� Broadcast�Ͽ� �����ð����� ���� ���θ� ������
   �ð��� Invalid�ϸ� Notication ������ �����ð������� �����ϵ��� �� */
#define FEATURE_KT_CP_TIME_VALIDITY_CHECK


/* �ιֵ��ð� ǥ�� ��ɿ� gsm.operator.sky_numeric Property�� �� �о�� �� �ֵ��� ����. 
**/
#define FEATURE_SKY_CP_VALID_OPERATOR_NUMERIC


/* �ؿ� �ι� �� GSM ���� ���� ��, Power On ��ġ��� �õ��� ��Ʈ��ũ �˻� ��� GSM ��Ʈ��ũ�� �������� ���� ���, 
   ����Ʈ��ũ ���� ��尡 GSM ����Դϴ�.  �ڵ����� �����Ͻðڽ��ϱ�?���� �˾� UI ǥ���ϰ� 
   ����� ���ÿ� ���ؼ� ��Ʈ��ũ ���� ��尡 ����Ǿ�� �Ѵٴ� SBSM �߰� �䱸���� ���� */
#define FEATURE_KT_CP_NETWORK_ACCESS_MODE_GSM_ONLY


/* �ȵ���̵忡 �����Ǿ� ���� ���� KT �ΰ� ���� �԰ݿ� �����ϱ� ���� ��� */
#define FEATURE_KT_CP_SUP_SVC_FOR_ANDROID
/* KT �ΰ����� CFD �ڵ�������� QMI �������� �ݿ� */
/* all Conditional CF 004�� ���� query�ÿ� 009�� ������ �̸� �����ؾ��� -KT ������*/
#define FEATURE_KT_CP_SUP_SVC_FOR_ANDROID_CFD
#define FEATURE_KT_CP_SUP_SVC_FOR_ANDROID_WITH_QMI


/* EF40K - ���� ���ʿ� */
/* EF18K Froyo(2020) Update�� SVLTE(simultaneous Voice and LTE)�� ���� ����� ���� ����
   ����ȭ �� ������ FEATURE : EF18K���� qcril_sms_api_map.c/h���� �߰� ������ �������� ���ܵ� */
#define FEATURE_KT_CP_SVLTE


/* To synchronize with modem on FEATURE_KTF_USSD_VER_1_1_0 */
#define FEATURE_KTF_USSD_VER_1_1_0


/* EF18K Froyo(2020) Update ���� Data Call�� suspend/resume�ϴ� Interface ����Ǿ� ���� */
#define FEATURE_KT_CP_SUSPEND_RESUME_DATA_CALL_CHANGED


/* 20100523 hbwoo
   ȣ ���� �߿� MMGSDI_REFRESH_EVENT�� �߻��ϸ� �̴� MMGSDI_REFRESH_STAGE_END_FAILED�̹Ƿ� 
   android�� RIL_UNSOL_SIM_REFRESH�� �ø��� ����.
   ���� ���������� UICC Reset�� �Ǹ� MMGSDI_REFRESH_STAGE_START stage �� �ǹǷ� Event�� �ø��� ��. 
   �׷��Ƿ� �Ʒ� �ڵ尡 ������ �߻��Ͻ�Ű�� ���� ������ �����.
   ������ ���� Refresh�� ���õ� ���� �߻��� �� Feature�� ������ ���ƾ� �� */
#define FEATURE_KT_CP_OTA_WARM_RESET_HANDLING


/* EF40K - QMI ������� ���� ���� ���ʿ� - Modem�� pbm.c �� �����ϸ� �� */
/* for only EF18K
   FEATURE_QCRIL_UIM_QMI�� �����鼭 ���ȣ List Update�� ����� �ȵǴ� ������ ���� ������ ����
   ���� FEATURE_QCRIL_UIM_QMI ����� ���� �ʿ� */
#define FEATURE_KT_CP_FIX_FOR_UNDEF_FEATURE_QCRIL_UIM_QMI


/* EF40K - ���� ���ʿ� */
/* [EF18K]
   CISS�� ���Ե� ��ȣ�κ��� ȣ���Ž� call state������ off hookó���Ǿ� �� �︮�� �ʴ� ������ ����
   CLIST_STATE_SETUP�� ���� RIL_call_state mismatch�߻� 
   call setup state�� ���� unsol_call_state_changed �� ������ �ʰ� ��. */
#define FEATURE_SKY_CP_SETUP_CISS


/* Romaing ������ ������Ʈ ���� �ʴ� ���� ����. */
#define FEATURE_SKY_CP_UPDATING_ROAMING_INDICATOR


/* [EF40K] - ���� ���ʿ� */
/* ds1_cp_updating_roaming_indicator �� ���� ������ ������
   qcril �ܿ��� ui �� �ö󰡴� reg_status�� ������ �־� �̸� ������
   EF18K�� ���� �� ���� ���� ���� */
#define FEATURE_SKY_CP_REG_STATUS_UPDATE_CORRECTION


/* ��� ������ ������ ���� �� LockScreen�� �����־� Locale Sync�� ���� �ʾ� ������. */
#define FEATURE_CP_KT_LANGUAGE_SYNC


/* [EF40K] - QMI ������� ���� ������ */
/* EF18K 
   Network Mode�� ���������� ���� ���� 
   ����ȭ��ȣ ���⿡�� ��ȣ���� �������� ǥ�õǴ� ���� : mSIMRecords�� Null�� �Ǵ� ���� */
#define FEATURE_KTF_CP_NET_PREF


/* EF34K���� USIM QMI ������� ������ */
/* EF18K, UIM_QMI block */
#define FEATURE_KTF_CP_BLOCK_UIM_QMI


/* ������ ������ ���� 
   ss-code �ڵ带 �����ϰ� New Password ��� �� register Password�� 0x90���� ���۵Ǵ� ����. 
   *03**Old_PWD*New_PWD*New_PWD# or **03**Old_PWD*New_PWD*New_PWD# + SEND �� 0x00���� ���۵ǵ��� ������ */
#define FEATURE_KT_CP_SS_REG_PASSWD


/* ������ ������ ���� 
   �߽Ź�ȣǥ������(*23#)���� ����ȣ �߽� �� SETUP�� BCD NUMBER�� Feature code(*23#)�� �����Ͽ� �����ϵ��� ���� */
#define FEATURE_KT_CP_SUPS_CLIR_CDMA


/* 2010110 EF18K ������ ������, EF18K Froyo Version���� ���� �ʿ�(SP33K Froyo�� ������ �ʿ� ����)
   SIM state�� CS_PS_Invalid�� illegal SIM ������ �� Subscription Not Available�� ��ȯ�ǵ��� ����Ǿ� 
   Linux�� SIM state�� Ready ���°� ���� ���� SMS�� ī��� ����/�̵� �� USIM ���� �޴� ������ �ȵǴ� ���� fix.
   �� �ڵ�� Subscription Not Available��  ó���Ǿ� ���� SIM State�� Not Available�� ������ 
   Linux���� SIM Ready�� �����ϵ��� �ϱ� ���� ����.
   Modem�ܿ��� MMGSDI_SESSION_ILLEGAL_SUBSCRIPTION_EVT�� ���Ӱ� �߰��ǰ� ������ ���� ����Ǿ� 
   Qcril������ MMGSDI_ILLEGAL_CARD_EVT�� ���� ó���� ���� �ʵ��� �� ����. */
#define FEATURE_KT_CP_MAINTAIN_SIM_READY_ILLEGAL_SIM


/* [EF40K] - FEATURE_KT_CP_GSM_MMI_CODE_FOR_KTF_REQUIREMENT�� QMI ������ �����Կ� ���� ���� ���ʿ� */
/* 20101119 EF18K ������ ������
   EF18K Froyo Update ���� qcril_reqlist_new() ���� ��ü�� �������� sub_id�� ó������ �ʴ� ����
   qcril_reqlist_update_sub_id()�� �̿��Ͽ� �������� sub_id�� �����ϵ��� ó��
   ���� Porting�ÿ� FEATURE_KT_CP_GSM_MMI_CODE_FOR_KTF_REQUIREMENT�� �״�� �������� ���� qcril_reqlist_new()���� 
   sub_id�� ó���ϴ��� Ȯ�� �� FEATURE_KT_CP_SUPSVC_UPDATE_SUB_ID �κ��� �����ؾ� �� SP33K�� ��� qcril_reqlist_new()����
   sub_id�� ó���ϹǷ� �ش� �ڵ带 ������ �ʿ� ���� */
#define FEATURE_KT_CP_SUPSVC_UPDATE_SUB_ID


/* FEATURE_KT_CP_USIM_WAIT_SYNC ������� ���� qcril_sleep()�� ������ */
/* 20101217 add by yjheo.
   KT_UCM�� CPU �������� ���� ������ ���� �ܸ����µǴ� ���� ���� ������. */
#define FEATURE_KT_USIM_SLEEP_TIME


/* 20100819 kblee | [EF18K] SBSM3.4.0 */
#define FEATURE_KTF_CP_ACC_BARRED_DISPLAY 


/* Limited, SIM Missing ���¿��� LockScreen�� �����ȭ ��ư ǥ�� �� "�����ȭ��" ���� ǥ�� ����*/
#define FEATURE_KT_CP_EMERGENCY_LOCKSCREEN_DISPLAY


/* 20110223 - KT�� �ڵ����� ����� ������ ������ ��ɿ� ���ؼ��� cpmgrif �� ������� �ʵ��� �Ѵ� 
   unsol event���� ������� Qcril�� �̿��Ѵ� */
#define FEATURE_KT_CPMGRIF_NOT_USED


/* 20110314 - ������ ����� �Դ� feature�ε� define �ȵǾ� �־� ������ - PPK Blocked�� ó���� */
#define FEATURE_SKY_CP_USIM_ACCESS



// FEATURE_TODO
/* 20110502 JongYeob - Power Off�� setDataConnectionAsDesired(mDesiredPowerState, powerOffMsg)�� ���� 
** PDP Deactivation ó���� ���� Detach Request�� ���� ó���� �ٷ� �̾����� ��찡 �߻��Ͽ� 
** PS Domain release�� ���¿��� Detach�� ���۵ǹǷ� Network���� �̸� �ν����� ���� "���� OFF" ��Ʈ�� 
** ������ �ʴ� ������ �����ϱ� ���� Radio Off�� RRC State�� Diconnected ���°� �ƴϸ� delay�� �־� 
** Detach�� ���� RRC�� �ٽ� ��� ó���ǵ��� ��.  
** GB �������� setRilPowerOff()�� �߰��Ǿ� �� delay�� �ʿ������, KT Network�� CELL_FACH, URA_PCH ���� 
** ����ϸ鼭 ������ �Ǿ� ��ü delay�� ������. */
#define FEATURE_SKY_CP_DELAYED_POWER_OFF


/* 20110503 - ������ ���� : A�� GMM INFO ���� �� ���� OFF/ON�� A������ GMM INFO �̼����ϰ� �Ǹ� 
** MCC/MNC ������ �����ϹǷ� ���� GMM INFO�� Network Name�� �����ְ� ��. �̷� ��� KT������ 
** Table�� �ִ� ������ ���� �ֵ��� ������û�Ͽ� qcril init�ÿ� NITZ Property�� clear�� �� */
#define FEATURE_SKY_CP_INIT_NITZ_INFO_PROPERTY

/* 20110503 kblee : EF32K �������� �ݿ�
   gsdi read/ write�ÿ� wait_signal ���� cb�� ���� �� ��쿡 ���� ���� ����
   sleep ��� ��� */
#define FEATURE_KT_CP_USIM_WAIT_SYNC

/*
20131015 USIM �� applet ��ġ (install for install) ���� �� 5�� �ʰ� �Ǿ��� ���, QMI_TIMEOUT_ERR �߻� 
QMI_SYNC_MSG_DEFAULT_TIMEOUT�� 5�ʿ��� 10�ʷ� ����
*/
#define FEATURE_KT_FIX_QMI_SYNC_MSG_DEFAULT_TIMEOUT

/* [EF40K] - QMI�� ���� FEATURE_SKY_CP_CALL_END_REQ_FOR_UI_CLEAN �� �������� �����Ƿ� �Ʒ� ����� ������ �ʿ� ����
             GsmCallTracker, GSMPhone.java */
/* [EF34K] ������ ������ - �ΰ����� ���� 
   �θ��� ���ڰ���ȭ(Conference Call)�� ���� held�� ���� ���¿��� ��ȭ��ȭ���� ������" ��ư�� ���ý�(or 0 send) 
   held�� �����Ǿ� �ִ� Conference Call�� �θ��� ��� ������� �ʰ�, �ѻ���� ����Ǵ� ���� 
   Qcril_cm���� hangup_waiting_or_background ����� held call �� ��� FEATURE_SKY_CP_CALL_END_REQ_FOR_UI_CLEAN��
   ���� call_id �ϳ��� ���ؼ��� call_end�ϵ��� ó����, process ȣ�� �ϴ°����� allcallRelease�ϵ��� ������ 
   FEATURE_SKY_CP_CALL_END_REQ_FOR_UI_CLEAN�� ���ٸ� ���� �� �ʿ����*/    
#define FEATURE_KT_CP_MULTI_HELD_CALL_END

/* [EF40K] 20110816 Kim Youngchan :   
   CM PH Event�� ���� SKT�� FEATURE_SKY_CP_OEM_PH_EVENT_WITH_QMI�� ����Ͽ� CPMGR�� �����ϰ�,
   KT�� FEATURE_KT_CP_CMPH_EVENT_QMI�� ����Ͽ� QCRILHOOK���� ������.
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

/* [EF40K] ������ OTA ������, ISIM �߰��� EF read�����ϵ��� ����
     USIM_ADF ���� ISIM_ACCESS DF �Ʒ� path�� �����. ISIM_ADF�� �ƴ϶� !!
     ���� LinearFixed item(EF_IMPU/EF_PCSCF) �� ��� ������ ù��° record�� ���ؼ��� ���� ���������� ������.
     �����ʿ���. - EF_IMPU/ EF_PCSCF
*/
#define FEATURE_KT_CP_ISIM_EF_ACCESS_BY_PATH

#endif/* T_SKY_MODEL_TARGET_KT */

// Google Hidden Code�� *#*#4636#*#* ���� "�޴��� ����" ����.
// packages\apps\Settings\res\xml\testing_settings.xml ����.
#define FEATURE_SKY_CP_GOOGLE_HIDDEN_MENU_BLOCK



// ���� Feature ��������. [
#define FEATURE_SKY_CP_OEM_QMI_ACCESS
#define FEATURE_SKY_CP_NV_ACCESS_WITH_QMI
// ]

/***********************************************************
   JAVA code���� ����� Feature �� code Ȯ�ο�...
   ������ C/C++ �ڵ忡�� ������� �ʴ� �������� 
   �ڵ� �˻��� Ȯ�ο뵵�� ����ϱ� ����.
************************************************************/

/* import ���̳� ���� ��ɿ� �������� ���� �ڵ� ǥ�� */
#define FEATURE_SKY_CP_COMMON_JAVA_DECLARATION

/* EF File ������ Path �� �̿��ϱ� ���ؼ� ���� �ڵ� */
#define FEATURE_SKY_USIM_EF_FILE_ACCESS_BY_PATH

/* DS3 P15574 Lee.Myengjun 2012-02-24 15:35 */
/* SIM State Change */
#define FEATURE_SKY_USIM_PIN_RETRY_INIT

/* 20120228 ithong.
   Refresh �߻� �� usim app �� inactive ���°� gw prov index �� invalid(0xffff)�� ������.
   �̹� ���� ready �� ���¿��� �߻��� ��� card io error �� �����ϰ�, �̿� invalid card �˾��� �߻���.
   �̿� refresh �߻� �� usim app�� �ٽ� �����Ǳ� ������, sim status �� ����Ǵ��� card io error �� �߻����� �ʰ� ��.
*/
#define FEATURE_SKY_CP_CHECK_REFRESH_STATE

/* 20120228 ithong.
   sim inserted �� ���� sim status indication �������� ���� �Ҵ�� slot �� ��������. gw provision index�� �����Ǿ� linux �� ���ŵ�
   �ش� ������ �״�� �ȵ���̵� ������ ���޵Ǿ� �ʱ� card ��ü�� app ��ü ������ ������ ��ĥ ����� �Ǿ� ���� �ڵ� ������.
   �� �Ҵ�� slot�� ���� ���¿����� sim status indication�� �ȵ���̵� ������ �������� �ʵ��� ��.
*/
#define FEATURE_SKY_CP_SKIP_SIM_STAT_INT_FOR_NON_SLOT_STATE


#define FEATURE_SKY_CP_DEBUGGING_LOG_FOR_TIME_SETTING

/*
** [E49K_JB���� JB ��]
   �����κ��� GSM-7bit Scheme���� ���������� �޾Ҵµ�, qmi_voice_cm_if.c ���� gsm7 bit�� utf16���� ��ȯ�Ͽ� 
   qmi_voice.c ���� VOICEI_ORIG_USSD_DATA, VOICEI_ORIG_USSD_DATA_UTF16 2�� ��� LINUX�� ������.
   LINUX�� qcril_qmi_voice.c ���� VOICEI_ORIG_USSD_DATA_UTF16 �� ���ؼ��� ó������ �ʵ��� ����.
*/
#define FEATURE_SKY_CP_USSD_RESPONSE_MSG_DECODING_BUG_FIX

/*
** [EF49K_JB ���� ��]
** Fusion_3 1234 ��ġ���� redirecting party bcd number�� ���� ���� ��ȣ�ڿ� *�� ���� �ٿ��ִ� �ڵ尡 �߰��Ǿ� [�߽Ź�ȣ*262032584] ǥ�õ�.
** ��Ȥ KT �����κ��� MT�� SETUP �޽����� redirecting party bcd number IE�� ä������ �������� ������, 
** ������� �ʴ� IE�̹Ƿ� ����ȭ�鿡 ǥ�õ��� �ʵ��� ����.
*/
#define FEATURE_KT_CP_SKIP_REDIRECTING_PARTY_BCD_NUMBER_FIELD

/* LTE-A indicator enable/disable
** When device is camped on CA and 20M BW region, 
** LTE-A Indicator display and other regions do not. 
*/
#define FEATURE_KT_CP_LTE_A_INDICATOR

#endif/* __CUST_SKY_CP_H__ */

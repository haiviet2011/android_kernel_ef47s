#ifndef CUST_PANTECH_H
#define CUST_PANTECH_H

#include "BOARD_REV.h"

#if defined(T_CHEETAH)
    #define CONFIG_PANTECH_CHEETAH_BOARD
#endif

/* Emergency Dload USB */
/* define after merging dload module #define FEATURE_PANTECH_DLOAD_USB*/

/*******************************************************************************
  **  PDL (LK(emergency), bootimage(phoneinfo), KERNEL(idle download))
  *******************************************************************************/
#define FEATURE_PANTECH_PDL_DLOADINFO
#define FEATURE_PANTECH_PDL_DLOAD
#define FEATURE_PANTECH_FLASH_ACCESS
#define FEATURE_PANTECH_DLOAD_USB
#define FEATURE_PANTECH_REBOOT_FOR_IDLE_DL
#define FEATURE_PANTECH_GPT_RECOVERY     //chjeon20120412@LS1 add

/*************************************************************************/
/*                            PANTECH STABILITY		                     */
/*************************************************************************/
#define F_PANTECH_VZW_PS_STABILITY_AT_CMD

#ifdef __BOOTBUILD__
/*
    ONLY BOOT BUILD FEATURE
*/

/*
      !!!!!!!!!!!!!!!!!! MUST BE DEFINED AS FOLLOWS (ONLY MODEM)!!!!!!!!!!!!!!!!!!
      FEATURE_{COMPANY_NAME}_{FUNCTION_NAME}_{ACTION_NAME}
      ex) PMIC function.

      #define FEATURE_PANTECH_PMIC
*/
// TO DO ..

#define FEATURE_PANTECH_BOOT_PMIC

#if defined(FEATURE_PANTECH_BOOT_PMIC)
#define FEATURE_PANTECH_BOOT_PMIC_POWER_ON_PROCESS
#define FEATURE_PANTECH_BOOT_PMIC_POWER_ON_MPP
#endif

#define FEATURE_PANTECH_BOOT_CHARGER
#if defined(FEATURE_PANTECH_BOOT_CHARGER)
#define FEATURE_PANTECH_BOOT_CHARGER_NO_WAIT
#endif

#define FEATURE_PANTECH_ERR_CRASH_LOGGING

/*
 * Caution!!! Enable before FEATURE_PANTECH_ERR_CRASH_LOGGING must enable under feature
 * by tarial 20120111
 */
#ifdef FEATURE_PANTECH_ERR_CRASH_LOGGING
//#define FEATURE_QHSUSB_HDLC_CDCACM   // tarial 20120111 add for USB DUMP for Modem port 
#endif

#define FEATURE_PANTECH_DDR_TINIT3_MODIFY  // 20120131 jylee , Tinit3 

#endif /* __BOOTBUILD__ */

#ifdef __MODEMBUILD__
/* 
    ONLY MODEM BUILD FEATURE
*/

/*
      !!!!!!!!!!!!!!!!!! MUST BE DEFINED AS FOLLOWS (ONLY MODEM)!!!!!!!!!!!!!!!!!!
      FEATURE_{COMPANY_NAME}_{FUNCTION_NAME}_{ACTION_NAME}
      ex) PMIC function.

      #define FEATURE_PANTECH_PMIC
*/

// TO DO ..

#define FEATURE_PANTECH_MODEL                       //chjeon20111031@LS1 add CS tool.

#endif /* __MODEMBUILD__ */


#if !defined(__KERNELBUILD__) && !defined(__MODEMBUILD__)
/*
    ONLY ANROID BUILD FEATURE
*/

/*
      !!!!!!!!!!!!!!!!!! MUST BE DEFINED AS FOLLOWS (ANDROID)!!!!!!!!!!!!!!!!!!
      CONFIG_{COMPANY_NAME}_{FUNCTION_NAME}_{ACTION_NAME}
      ex) PMIC function.
      #define CONFIG_PANTECH_PMIC

      for using BOTH (android & kernel) definition, please read engineer note about chapter 5 Arm Linux Kernel.

      IF YOU ADD FEATURE IN KERNEL , YOU CHECK THE RELEASE ENGINNER NOTE

      __KERNELBUILD__ :  for avoid redefined , this is predefined name in kernel makefile.

*/

/* TO DO define */
#define FEATURE_PANTECH_BMS_TEST   // equals 'CONFIG_PANTECH_BMS_TEST' at \LINUX\android\kernel\arch\arm\mach-msm\cust\Kconfig
/* [LS2_SYS_KIM.DONGSU 20110927] Enable AT command for OEM stability test */
#define FEATURE_PANTECH_STABILITY_AT_COMMAND
#define CONFIG_PANTECH_ERR_CRASH_LOGGING
/* [LS2_USB 20130213 Warfs] Enable factory command for PST download(domestic only) */
#if defined(T_EF46L) ||  defined(T_EF47S) || defined(T_EF45K)
    #define FEATURE_PANTECH_PST_USB_MODE_CHANGE
#endif
#endif /* !defined(__KERNELBUILD__) && !defined(__MODEMBUILD__) */


#if !defined(__KERNELBUILD__)
/*
  MODEM and ANDROID Feature 
*/



#endif /* !defined(__KERNELBUILD__) */

#if !defined(__KERNELBUILD__) && !defined(__MODEMBUILD__) && !defined(__BOOTBUILD__)
/* TO DO define */

#define CONFIG_PANTECH

#include "CUST_PANTECH_CAMERA.h"

/*******************************************************************************
**  Display
*******************************************************************************/
#include "CUST_PANTECH_DISPLAY.h"

/*******************************************************************************
**  TDMB
*******************************************************************************/
/*#include "CUST_PANTECH_TDMB.h"*/

/*******************************************************************************
**  USER DATA REBUILDING VERSION
*******************************************************************************/
#define FEATURE_SKY_USER_DATA_VER
#define FEATURE_SKY_FAT16_FOR_SBL3
//20111220 jwheo Data Encryption
#define FEATURE_SKY_DATA_ENCRYPTION
//20120117 jwheo SD Card Block Encryption
#if defined(T_OSCAR)
#define FEATURE_SKY_SD_BLOCK_ENCRYPTION
#define F_PANTECH_COPY_PRELOAD_DATA	// p13783 : add for copy preload data
#endif

// 20120516 - App CRC CHECK For Factory Command(LS1)
#define F_PANTECH_APP_CRC_CHECK

#include "CUST_PANTECH_MMP.h"

/****************************************************
** SOUND
****************************************************/
#include "CUST_PANTECH_SOUND.h"

/****************************************************
** MMC(eMMC, MicroSD)
****************************************************/
#if defined(PANTECH_STORAGE_INTERNAL_FAT)
#define FEATURE_SKY_MMC
#endif

/*******************************************************************************
**  EXT4 (repair /data partition)  manual, auto repair
*******************************************************************************/
#define FEATURE_RECOVERY_HIDDEN_MENU
#define FEATURE_PANTECH_AUTO_REPAIR
#define FEATURE_PANTECH_MANUAL_REPAIR
#if defined(T_EF45K) || defined(T_EF46L) || defined(T_EF47S)
#define FEATURE_CS_USERDATA_BACKUP
#endif
/*************************************************************************/
/****************************  PANTECH UIM ********************************/
/*************************************************************************/
#define F_PANTECH_UIM_TESTMENU


/*******************************************************************************
**  FACTORY_COMMAND
*******************************************************************************/
#define FEATURE_PANTECH_FACTORY_COMMAND
#define FEATURE_PANTECH_BT_FC           //20121004 kim yonghwan BT
#ifdef FEATURE_PANTECH_FACTORY_COMMAND
#define FEATURE_PANTECH_CS_AUTO_TAKEOVER
#define FEATURE_PANTECH_MEDIA_FILE_CHECK	// p13783 : add for FACTORY_INIT_SYS_CHECK_I	
#define FEATURE_PANTECH_WLAN_FC
#define F_PANTECH_FACTORY_INIT_ALL_CMD	// p13783 : add for FACTORY_INIT_ALL_I
#define F_SKYLCD_FACTORY_PROCESS_CMD

#if defined (T_STARQ)
#define F_PANTECH_FACTORY_INIT_MODEM	// p13783 : add for init NV item for Verizon Model
#endif
#endif

/*******************************************************************************
**  RAWDATA PARTITION ACCESS, FOR BACKUP
*******************************************************************************/
#define FEATURE_SKY_RAWDATA_ACCESS

#define PANTECH_DIAG_MSECTOR

/*******************************************************************************
**  GOTA
*******************************************************************************/
#include "CUST_PANTECH_GOTA.h"

/*******************************************************************************
**  PMIC
*******************************************************************************/
#define CONFIG_A_PANTECH_PMIC
#if defined(CONFIG_A_PANTECH_PMIC)
#define CONFIG_A_PANTECH_PMIC_SHARED_DATA
#define CONFIG_A_PANTECH_PMIC_HW_REVISION
#define CONFIG_A_PANTECH_PMIC_SILENT_BOOT
#define CONFIG_A_PANTECH_PMIC_RESET_REASON
#define CONFIG_A_PANTECH_PMIC_THERM
#if defined(T_EF44S)
#if(BOARD_VER >= WS20)
#define CONFIG_A_PANTECH_MAX17058
#endif
#elif defined(T_STARQ)
#define CONFIG_A_PANTECH_MAX17058
#elif defined(T_OSCAR)
#define CONFIG_A_PANTECH_MAX17058
#endif
#endif

#define FEATURE_PANTECH_CHARGER
#if defined(FEATURE_PANTECH_CHARGER)
#define FEATURE_PANTECH_CHARGER_OFFLINE
#endif /* FEATURE_PANTECH_CHARGER */

/****************************************************
** POWER ON/OFF REASON COUNT
****************************************************/
#define FEATURE_PANTECH_PWR_ONOFF_REASON_CNT
#define FEATURE_PANTECH_ANDROID_RESETCNT // p13783 add : for Framework reset count

#if defined(T_STARQ) || defined(T_OSCAR) || defined(T_VEGAPVW) || defined(T_EF45K) || defined(T_EF46L) || defined(T_EF47S)  //chjeon20120224@LS1 add
/*******************************************************************************
 **  WIDEVINE DRM
*******************************************************************************/
#define FEATURE_PANTECH_WIDEVINE_DRM

/*******************************************************************************
 **  PANTECH CERTIFICATION FOR Image_verify
*******************************************************************************/
#define FEATURE_PANTECH_KEY_CERTIFICATION



#endif

/* 120421 LS1-JHM modified : user data backup */
#if defined(T_EF45K) || defined(T_EF46L) || defined(T_EF47S)
#define FEATURE_CS_USERDATA_BACKUP
#endif

#endif /*!defined(__KERNELBUILD__) && !defined(__MODEMBUILD__) && !defined(__BOOTBUILD__)*/


/*******************************************************************************
**  WLAN
*******************************************************************************/
/* WLAN Common Feature */
#define FEATURE_PANTECH_WLAN // used in wlan_hdd_main.c
#define FEATURE_PANTECH_WLAN_PROCESS_CMD
#define FEATURE_PANTECH_WLAN_TESTMENU
#define FEATURE_PANTECH_WLAN_RAWDATA_ACCESS
#define FEATURE_PANTECH_WLAN_FOUR_MAC_ADDRESS // for pantech_wifi_mac_backup.h
#define FEATURE_PANTECH_WLAN_MAC_ADDR_BACKUP // used in skytest_thread.c
#define FEATURE_PANTECH_WLAN_TRP_TIS // 2012-04-09, Pantech only, ymlee_p11019, to config & test TRP TIS
#define FEATURE_PANTECH_WLAN_QCOM_PATCH
#define FEATURE_PANTECH_5G_DPD_ENABLE_AUTO_TEST // 2012-04-02, Pantech only, ymlee_p11019, On Auto test mode 5G DPD enabled

/* WLAN Model Feature */
#if defined(T_EF45K) || defined(T_EF46L) || defined(T_EF47S)
#define FEATURE_PANTECH_WLAN_SCAN
#endif 


/*******************************************************************************
**  SENSOR
*******************************************************************************/
#include "CUST_PANTECH_DSPS.h" 

/*******************************************************************************
 **  PANTECH ROOTING CHECK		//lsi@ls1
*******************************************************************************/
#define F_PANTECH_OEM_ROOTING

/*******************************************************************************
 **  PANTECH SECURE BOOT		//lsi@ls1
*******************************************************************************/
#if defined(T_STARQ)
#define F_PANTECH_SECBOOT
#endif

/*******************************************************************************
**  PM
*******************************************************************************/
#define PANTECH_CHARGER_MONITOR_TEST //20120229_khlee_pm : for chargerMonitor test(#8378522#)
#define FEATURE_PANTECH_BATTERY_DUMMY
/*******************************************************************************
** USB 
*******************************************************************************/
#if defined(T_STARQ) || defined(T_VEGAPVW)
#define FEATURE_ANDROID_PANTECH_USB_CDFREE
#endif

#define FEATURE_ANDROID_PANTECH_USB_PROPERTY_SETTING
#define FEATURE_ANDROID_PANTECH_USB_TESTMENU
#define FEATURE_HSUSB_SET_SIGNALING_PARAM
#define FEATURE_PANTECH_USB_CABLE_CONNECT
/*T_EF47S, T_EF46L, T_EF45K, T_CHEETAH, T_VEGAVZW    */
#if defined(T_EF46L) ||  defined(T_EF47S) || defined(T_EF45K)
#if(BOARD_VER >= TP10)
    #define FEATURE_ANDROID_PANTECH_USB_OTG_MODE
#endif
#endif
#define FEATURE_PANTECH_MSG_ONOFF // QXDM MSG ONOFF
/****************************************************
** TOUCH & HS
****************************************************/
#if defined(T_OSCAR) || defined(T_EF45K) || defined(T_EF46L) || defined(T_EF47S)
// This feature is not used in STARQ & PREMIA_V because VRZ requirement.
// EventHub.cpp / EventHub.h / WindowManagerService.java
#define FEATURE_PANTECH_VOLUME_CTL
#endif
// MTC
#if defined(T_EF45K) || defined(T_EF46L) || defined(T_EF47S)
//#define CONFIG_FEATURE_PANTECH_MDS_MTC   /* MTC */
//#define CONFIG_FEATURE_PANTECH_MAT      /* MAT */
//#define CONFIG_FEATURE_DIAG_LARGE_PACKET
#endif

/****************************************************
** RF
****************************************************/
#if defined(T_EF46L) || defined(T_EF47S) || defined(T_EF45K)
#define FEATURE_RF_TUNABLE_ANT_TEST //EF46L tunable ant test bin
#endif

/****************************************************
** PS1 Team Feature [FEATURE_SKY_CP_COMMON_INTERFACE]
****************************************************/
/*  2011-05-16 octopusy added  [PS1 Team Feature] */
#ifdef T_SKY_MODEL_TARGET_COMMON
#include "cust_sky_cp_linux.h"
#include "cust_sky_ds_linux.h"
#endif/* T_SKY_MODEL_TARGET_COMMON */

/****************************************************
** CPRM
****************************************************/
#if defined(T_VEGAPKDDI)
#define FEATURE_CPRM_INTERFACE //Vega Premia KDDI
#endif
/*******************************************************************************
** Release/Debug User/Eng mode 
*******************************************************************************/
#if defined(FEATURE_AARM_RELEASE_MODE)
#define FEATURE_SW_RESET_RELEASE_MODE // use in release mode
#endif

/*******************************************************************************
** Android Patternlock Reset
*******************************************************************************/
#define FEATURE_PANTECH_PATTERN_UNLOCK
#if defined(T_STARQ) || defined(T_OSCAR) || defined(T_VEGAPVW) || defined(T_VEGAPKDDI)
	#define FEATURE_PANTECH_PATTERN_MIN
#endif
/*************************************************************************/
/*                            PANTECH UTS(220 ~ 239(                     */
/*************************************************************************/
#define F_PANTECH_UTS_POWER_UP // p13783 add : power on in offline charging mode


/* 201207-11 jylee for power on/off test */
//#define FEATURE_POWER_ON_OFF_TEST

/****************************************************
** MMC(eMMC, MicroSD)
****************************************************/
/* 20121221 LS1-JHM modified : enabling BKOPS for eMMC performance */
#define FEATURE_PANTECH_SAMSUNG_EMMC_BUG_FIX

//+US1-CF1
//Feature : FW_VENDOR_FOR_AOT_VIDEO_APP
//API support for AOT 
#define FEATURE_PANTECH_MMP_SUPPORT_AOT
//-US1-CF1

#endif/* CUST_PANTECH_H */

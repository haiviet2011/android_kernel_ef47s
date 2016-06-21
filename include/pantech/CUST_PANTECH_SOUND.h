#ifndef __CUST_PANTECH_SOUND_H__
#define __CUST_PANTECH_SOUND_H__

/* 
  2012/05/15
  All sound related debug messages enable
*/
#define FEATURE_PANTECH_SND_DEBUG

#if defined(FEATURE_PANTECH_SND_DEBUG)
#define VERY_VERBOSE_LOGGING // ALOGVV message enable of AudioFliger.cpp, AuddioPolicyManagerBase.cpp and AuddioPolicyManagerALSA.cpp
#endif

/* 
  2012/02/20 
  QualComm CR Patch feature
*/
#define FEATURE_PANTECH_SND_QCOM_CR

/* 
  2012/12/07 
  QualComm Test Patch feature - shuld be checked before market release version
*/
#define FEATURE_PANTECH_SND_TEST_PATCH

/* 
  2012/03/12
  Feature must be applied to all models
*/
#define FEATURE_PANTECH_SND
#define FEATURE_PANTECH_SND_ENFORCED_HEADSET // for ear protection analog gain down of headset in enforced audible

/*
 2011/10/24
  내수와 해외모델을 구분하기 위해 FEATURE를 적용
*/
#if defined(T_EF45K) || defined(T_EF46L) || defined(T_EF47S)
#define FEATURE_PANTECH_SND_DOMESTIC
#define FEATURE_PANTECH_SND_QSOUND // for QSound Effect solution(QFX, QVSS, QXV)
#define FEATURE_PANTECH_SND_LPA  // for QSound LPA
#define FEATURE_PANTECH_SND_AUTOANSWER_RX_MUTE  // for autoanswer rx mute on/off
#define FEATURE_PANTECH_SND_VR_PATH // for voice recognition ACDB separation
#if defined(T_EF47S)
#define FEATURE_PANTECH_SND_SKT
#elif defined(T_EF45K)
#define FEATURE_PANTECH_SND_KT
#elif defined(T_EF46L)
#define FEATURE_PANTECH_SND_LGT
#endif

#elif defined(T_STARQ)
#define FEATURE_PANTECH_SND_ABROAD
#define FEATURE_PANTECH_SND_VZW
#define FEATURE_PANTECH_SND_STARQ
#define FEATURE_PANTECH_SND_ELECTOVOX
#define FEATURE_PANTECH_SND_NR_DEV
#define FEATURE_PANTECH_SND_BT_ECNR
#define FEATURE_PANTECH_SND_BT_GROUPING

#elif defined(T_OSCAR)
#define FEATURE_PANTECH_SND_ABROAD
#define FEATURE_PANTECH_SND_ATT
#define FEATURE_DOLBY_AUDIOEFFECT_DM
#define DOLBY_AUDIOEFFECT_DM
#define FEATURE_OSCAR_POWER_SAVE_SND /* For Power Save TF */
#define FEATURE_PANTECH_SND_BT_GROUPING /* For NAC certification */
#define FEATURE_OSCAR_MIC_LOOPBACK /* For Test Mode, 1, 2st loopback*/
#define FEATURE_PANTECH_SND_VOC_LOOPBACK //For submic loop back

#else
    #error "FEATURE_PANTECH_SND ? DOMESTIC or ABROAD"
#endif

/* 
  2012/09/19
  Feature regarding the boot sound(SKT/VZW/ATT carrier only)
*/
#if defined(FEATURE_PANTECH_SND_SKT) || defined(FEATURE_PANTECH_SND_VZW) || defined(FEATURE_PANTECH_SND_ATT) 
#define FEATURE_PANTECH_SND_BOOT_SOUND
#endif

/* 
  2012/12/21
  Feature regarding the shutdown sound(SKT/VZW carrier only)
*/
#if defined(FEATURE_PANTECH_SND_SKT) || defined(FEATURE_PANTECH_SND_VZW)
#define FEATURE_PANTECH_SND_SHUTDOWN_SOUND
#endif

#endif /* __CUST_PANTECH_SOUND_H__ */
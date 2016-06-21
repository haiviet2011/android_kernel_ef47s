/*
 lived 2009.11.05
 FEATURE define
*/

#ifndef F_SKYDISP_FRAMEWORK_FEATURE
#define F_SKYDISP_FRAMEWORK_FEATURE

/* Debug Msg */
//#if defined(FEATURE_AARM_RELEASE_MODE)
//#define SKYDISP_MSG(...)
//#else
//#define SKYDISP_MSG(...)   ((void)LOG(LOG_WARN, LOG_TAG, __VA_ARGS__))
//#endif

/* PMEM ���� ����ȭ
 * MSM_FB_SIZE �� MSM_PMEM_SF_SIZE ũ�� ����
#define F_SKYDISP_PMEM_OPTIMIZE
 */

/* 
 *32bpp ������ ������ �����Ǿ����� �κе� 
 * KERNEL : used     
 * USER   : used
#define CONFIG_FB_MSM_DEFAULT_DEPTH_RGBA8888 
���� ������ ���� FEATURE�� ���� 
 */
 #undef CONFIG_FB_MSM_DEFAULT_DEPTH_RGBA8888
 #define CONFIG_FB_MSM_DEFAULT_DEPTH_RGBA8888

/* 
 * init ���μ������� �Ѹ��� �� Cursor ���ֱ� 
 * KERNEL : used     
 * USER   : not used
 */
#undef CONFIG_F_SKYDISP_NO_CURSOR_IN_BOOT
#define CONFIG_F_SKYDISP_NO_CURSOR_IN_BOOT

/* Android Boot Animation �߿� ���Ⱑ 6���� User Set Value��
 * ���� �Ǵ� ������ ���� -> ������ Feature 
#define F_SKYDISP_SET_BACKLIGHT_BEFORE_BOOTANIM
 */

/* 
 *gralloc ���⿡ refresh rate ���� �߸��� �κ� ���� 
#define F_SKYDISP_FIX_REFRESH_RATE
 */

/* 
 * Backlight ���� ���� ���� 
 * KERNEL : used     
 * USER   : not used
 */
#undef CONFIG_F_SKYDISP_QBUG_FIX_BACKLIGHT 
#define CONFIG_F_SKYDISP_QBUG_FIX_BACKLIGHT

/* Qualcomm�� �۾��� HDMI ���� DUAL Display�� �۾� ����
 * ����, HDMI�� �����ϴ� ������ �Ʒ� Feature�� undefine�ϰ�
 * Qualcomm�� HDMI_DUAL_DISPLAY �� define�ؾ� �Ѵ�.
 * android/device/qcom/msm8660_surf/ ���� 
 * BoardConfig.mk -> TARGET_HAVE_HDMI_OUT := false
 * system.prop -> ro.hdmi.enable=false
 * �� �� ������ ���� Config/Feature �̴�. ���� �� ��
#define F_SKYDISP_REMOVE_HDMI
 */

/*
 * SHARP MIPI ���� ���� ���� ���� Feature
 * KERNEL : used     
 * USER   : not used
#define CONFIG_F_SKYDISP_QBUG_FIX_MIPI_ERROR
 */
 

/*
 * SHARP LCD Veil View ���� Feature
#define F_SKYDISP_VEIL_VIEW
 */

/*
 * SKY Boot Logo in Kernel Feature
 * KERNEL : used     
 * USER   : not used
 */
#undef CONFIG_F_SKYDISP_BOOT_LOGO_IN_KERNEL  
#define CONFIG_F_SKYDISP_BOOT_LOGO_IN_KERNEL

/*
 * for TARGET_USES_OVERLAY feature fix
#define F_SKYDISP_OVERLAY_FIX
 */

/*
 * for Mirror Flip Effect for Camera
 * KERNEL : not used     
 * USER   : used
#define F_SKYDISP_GBUG_OVERLAY_FLIP
 */

/*
 * Overlay�� ���� SurfaceView���� Landscape<->Portrait ��ȯ ��
 * ȭ���� �ϱ׷����� ������ ����
 * 1080 ���Ŀ��� �ʿ��Ѱ�?
#define F_SKYDISP_GBUG_FIX_OVERLAY_ORIENTATION
 */

/*
 * LCD Module Reset ##1199 Test Menu
 * KERNEL : used     
 * USER   : used
#define CONFIG_F_SKYDISP_LCD_RESET
 */
#define CONFIG_F_SKYDISP_LCD_RESET /*temp*/

/*
 * LCD ���� on/off ����, sleep������ �Դ´�
 * �ʿ��� �� ���� �ǰڴ�.
 * EF33/34/35���� Battery Charging�ÿ� �־���
 * KERNEL : used     
 * USER   : used
#define CONFIG_F_SKYDISP_LCD_FORCE_ONOFF
 */
#define CONFIG_F_SKYDISP_LCD_FORCE_ONOFF/*temp*/

/*
 * Overlay 2�� ���� �����ϵ��� �Ѵ�.
 * 35L�� GIPS �������� GLSurfaceView�� ���� ������ ���ʿ�
 * 40K������ �ʿ��ϴ�
 * Kang Seong-Goo, 2011.08.22, Qualcomm ���� �������� ����
#if defined(T_EF40K)
#define F_SKYDISP_DUAL_OVERLAY
#endif
 */
 
 /*
 * Qualcomm Triple buffer 기�? ?? Double buffer ??? ??? Application ??? �?��.
 * ?????? Application(double buffering) : Sling Player , Colorix ( Market App )
 * KERNEL: None.
 * USER: used.
 * Shin Jae-gon, 2012.04.13 */
#define CONFIG_F_SKYDISP_DOUBLE_BUFFER_FORCE_APP

/* 20120503 Google Display List Patch */

#define CONFIG_BUG_FIX_QUALCOMM_GOOGLE_PATCH_FOR_DISPLAYLIST

 /*
 * ?��? apps ?��? back key�?�?���??????? 겹�?보�??????
 * StarQ�????.
 * KERNEL: None.
 * USER: used.
 * Shin Jae-gon, 2012.06.18 */
 //#define CONFIG_F_SKYDISP_LCD_FACTORY_REQUEST
 
#if defined(T_STARQ)
#define FEATURE_QUALCOMM_BUG_FIX_LCD_BYPASS_BUG_FIX
#endif
/*
 * Surface Information �߸��� ���� ����
#define F_SKYDISP_FIX_INVALID_SURFACE
 */
 
/*
 * Overlay ���� ��, MDP_OV_PLAY_NOWAIT�� ���� ó�� �߰�
 */
/*#define F_SKYDISP_OV_PLAY_NOWAIT*/

/*
 * LCD Gamma Table Test
#define F_SKYDISP_LCD_GAMMA_TEST
 */

/*
 * 8660 MIPI Video mode LCD display
 * by Qualcomm SR fix
#define F_SKYDISP_MIPI_VIDEO_LK_DISPLAY
 */

/*
 * MHL-HDMI ���� ��, Feature �ڸ�/�ػ��� ���� API ����
 * KERNEL : used     
 * USER   : used
#define CONFIG_F_SKYDISP_HDMI_OPTION
 */

/*
 * 2011.08.19
 * GPU composition ���� ��, ASHMEM ������ ���� Feature
 * BoardConfig.mk�� TARGET_GRALLOC_USES_ASHMEM := true �⺻ ������ �� �ϸ�,
 * Kernel config�� /dev/pmem ���� ��ü�� ���� ���� Feature��
 * android/system/core/rootdir/ueventd.rc ���� /dev/pmem permission ������ ����
 * KERNEL : used     
 * USER   : not used
#define CONFIG_F_SKYDISP_USE_ASHMEM
 */

/*
 * Beam On Bug Fix, because the screen does not display at Beam on  
 * KERNEL : used     
 * USER   : used
 * Author : LS4 p13156 LKS
#define CONFIG_F_SKYDISP_BEAM_ON_BUG_FIX
 */

/*
 * HDMI Blocking Feature
 */
#define PANTECH_LCD_QCBUGFIX_AOT_SCREEN_COMPRESSION_ISSUE
#if defined(T_EF46L) ||  defined(T_EF47S) || defined(T_EF45K) || defined(T_VEGAPKDDI) || defined(T_VEGAPVW)
#define CONFIG_F_SKYDISP_HDMI_BLOCK
#define CONFIG_F_SKYDISP_RETRY_ENCRYPTION		/// p16008 @ 20120425 : prevent surfaceflinger's error when encryption mode 
//#define PANTECH_LCD_LIBGUI_FIX_FOR_OLLEH_TV  /* kangsg 130117 */
#endif
/* hdmi on �� uevent�� daemon���� ���޵ǰ� hdmi enable��Ŵ, 
app������ broadcast �� hdmi power on �����Ѵ�.
#define CONFIG_F_HDMI_NOTIFY_POWER_ON
 */
#define	CONFIG_PANTECH_F_HDMI_NOTIFY_POWER_ON
	/* MHL SII9244�� PIXEL CLK, refresh rate�� �Ѱ谡 ����, 75Mhz, 30Hz �̱� ������ hdmi output format�� ������ �д�
	1080P�� ���� pixel clk 60Hz�� 30Hz�� ����. 
	#define CONFIG_PANTECH_FORMAT_FOR_MHL_LIMIT */
#define CONFIG_PANTECH_FORMAT_FOR_MHL_LIMIT

#define PANTECH_LCD_FORCE_FB_FALLBACK_WHEN_LCD_OFF
//#define CONFIG_FEATURE_QUALCOMM_BUG_FIX_MHL_FIX_DELAY  // 1042 tmp block 
#if defined(T_OSCAR)
#undef CONFIG_F_SKYDISP_ACL_FOR_AMOLED
#define CONFIG_F_SKYDISP_ACL_FOR_AMOLED

#undef CONFIG_F_SKYDISP_SMART_DIMMING
#define CONFIG_F_SKYDISP_SMART_DIMMING
#define JNI_CALLSTACK_DEBUG
#define CONFIG_F_SKYDISP_TWITTER_FIX
#endif
#if defined(T_EF46L) ||  defined(T_EF47S) || defined(T_EF45K)
#undef 	CONFIG_F_SKYDISP_CABC_FIX
#define CONFIG_F_SKYDISP_CABC_FIX
#define QUALCOMM_CONFIG_HDMI_PREVENT_ROTATE_BUG // 20120423 
#define CONFIG_PANTECH_JB_SKIP_COMPOSITION
#define CONFIG_F_SKYDISP_VEIL_VIEW
#endif

//#define CONFIG_QUALCOMM_SUPPORT_4LAYER_BYPASS
#undef CONFIG_F_SKYDISP_FORCE_ENCRYPTION_OFF
#define CONFIG_F_SKYDISP_FORCE_ENCRYPTION_OFF
//#define QUALCOMM_CONFIG_HDMI_PREVENT_ROTATE_BUG

#define PANTECH_LCD_LOCKUP_ISSUE_FIX
#endif  /* SKY_FRAMEWORK_FEATURE */

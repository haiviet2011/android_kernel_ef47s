#ifndef __CUST_PANTECH_CAMERA_H__
#define __CUST_PANTECH_CAMERA_H__


/*------------------------------------------------------------------------------

(1)  �ϵ����� ����

EF39S   : APQ8060, CE1612(8M ISP), S5K6AAFX13(1.3M)
EF40K   : APQ8060, CE1612(8M ISP), S5K6AAFX13(1.3M)
PRESTO  : MSM7x27, MT9P111(5M SOC), MT9V113(VGA)


(2)  ī�޶� ���� ���� kernel/userspace/android �α׸� ����

kernel/arch/arm/config/msm8660-perf-(�𵨸�)_(��������)_defconfig �� �����Ѵ�.

	# CONFIG_MSM_CAMERA_DEBUG is not set (default)

CUST_PANTECH_CAMERA.h ���� F_PANTECH_CAMERA_LOG_PRINTK �� #undef �Ѵ�.

	#define F_PANTECH_CAMERA_LOG_PRINTK (default)

���� �ҽ� ���Ͽ��� F_PANTECH_CAMERA_LOG_OEM �� ã�� �ּ� ó���Ѵ�.
	���� �� ����, �ش� ���Ͽ� ������ SKYCDBG/SKYCERR ��ũ�θ� �̿���
	�޽������� Ȱ��ȭ ��Ų��. (user-space only)

���� �ҽ� ���Ͽ��� F_PANTECH_CAMERA_LOG_CDBG �� ã�� �ּ� ó���Ѵ�.
	���� �� ����, �ش� ���Ͽ� ������ CDBG ��ũ�θ� �̿��� �޽�������
	Ȱ��ȭ ��Ų��. (user-space only)

���� �ҽ� ���Ͽ��� F_PANTECH_CAMERA_LOG_VERBOSE �� ã�� �ּ� ó���Ѵ�.
	���� �� ����, �ش� ���Ͽ� ������ LOGV/LOGD/LOGI ��ũ�θ� �̿���
	�޽������� Ȱ��ȭ ��Ų��. (user-space only)


(4)  �ȸ��ν� ���� ���� ���� ȯ��

vendor/qcom/android-open/libcamera2/Android.mk �� �����Ѵ�.
	3rd PARTY �ַ��� ���� ���θ� �����Ѵ�.

	PANTECH_CAMERA_FD_ENGINE := 0		������
	PANTECH_CAMERA_FD_ENGINE := 1		�ö����� �ַ��� ����
	PANTECH_CAMERA_FD_ENGINE := 2		��Ÿ �ַ��� ����

CUST_PANTECH_CAMERA.h ���� F_PANTECH_CAMERA_ADD_CFG_FACE_FILTER �� #undef �Ѵ�.
	�ȸ��ν� ���� ���� �������̽� ���� ���θ� �����Ѵ�.

libOlaEngine.so �� ���� libcamera.so �� ��ũ�ϹǷ� ���� ���� libcamera.so ��
ũ�Ⱑ �����Ͽ� ��ũ ������ �߻� �����ϸ�, �� ���� �Ʒ� ���ϵ鿡��
liboemcamera.so �� ������ �ٿ� libcamera.so �� ������ Ȯ���� �� �ִ�.

build/core/prelink-linux-arm-2G.map (for 2G/2G)
build/core/prelink-linux-arm.map (for 1G/3G)

------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
/*  MODEL-SPECIFIC                                                            */
/*  �ش� �𵨿��� �����Ǵ� �Ǵ� �ش� �𵨿����� ������ FEATURE ����           */
/*----------------------------------------------------------------------------*/
#if defined(CONFIG_SKY_EF39S_BOARD)
#define F_PANTECH_CAMERA
#define F_PANTECH_CAMERA_TARGET_EF39S
#define F_PANTECH_CAMERA_EF39S_40K
#elif defined(CONFIG_SKY_EF40K_BOARD)
#define F_PANTECH_CAMERA
#define F_PANTECH_CAMERA_TARGET_EF40K
#define F_PANTECH_CAMERA_EF39S_40K
#elif defined(CONFIG_PANTECH_PRESTO_BOARD)
#define F_PANTECH_CAMERA
#define F_PANTECH_CAMERA_TARGET_PRESTO
#define F_PANTECH_CAMERA_PRESTO
/* AT&T������ ���� �߰��Ǿ��� �ϴ� Featrue */
#define F_PANTECH_CAMERA_ATT
#elif defined(T_EF45K) && !defined(T_EF45KV)
#define F_PANTECH_CAMERA
#define F_PANTECH_CAMERA_TARGET_EF45K
#define F_PANTECH_CAMERA_EF47S_45K_46L
#elif defined(T_EF45K) && defined(T_EF45KV)
#define F_PANTECH_CAMERA
#define F_PANTECH_CAMERA_TARGET_EF45KV
#define F_PANTECH_CAMERA_EF47S_45K_46L
#elif defined(T_EF46L)
#define F_PANTECH_CAMERA
#define F_PANTECH_CAMERA_TARGET_EF46L
#define F_PANTECH_CAMERA_EF47S_45K_46L
#elif defined(T_EF47S)
#define F_PANTECH_CAMERA
#define F_PANTECH_CAMERA_TARGET_EF47S
#define F_PANTECH_CAMERA_EF47S_45K_46L
/* #define F_PANTECH_CAMERA_SKT */
#elif defined(T_SVLTE)
#define F_PANTECH_CAMERA
#define F_PANTECH_CAMERA_TARGET_SVLTE
/*#define F_PANTECH_CAMERA_EF47S_45K_46L*/
#elif defined(T_CSFB)
#define F_PANTECH_CAMERA
#define F_PANTECH_CAMERA_TARGET_CSFB
/*#define F_PANTECH_CAMERA_EF47S_45K_46L*/
#elif defined(T_CHEETAH)
#define F_PANTECH_CAMERA
#define F_PANTECH_CAMERA_TARGET_CHEETAH
/*#define F_PANTECH_CAMERA_EF47S_45K_46L*/
#elif defined(T_STARQ)
#define F_PANTECH_CAMERA
#define F_PANTECH_CAMERA_TARGET_STARQ
#define F_PANTECH_CAMERA_ATT
/*#define F_PANTECH_CAMERA_EF47S_45K_46L*/
#elif defined(T_OSCAR)
#define F_PANTECH_CAMERA
#define F_PANTECH_CAMERA_TARGET_OSCAR
#define F_PANTECH_CAMERA_ATT
/*#define F_PANTECH_CAMERA_EF47S_45K_46L*/
#elif defined(T_VEGAPVW)
#define F_PANTECH_CAMERA
#define F_PANTECH_CAMERA_TARGET_VEGAPVW
/*#define F_PANTECH_CAMERA_EF47S_45K_46L*/
#elif defined(T_ZEPPLIN)
#define F_PANTECH_CAMERA
#define F_PANTECH_CAMERA_TARGET_ZEPPLIN
/*#define F_PANTECH_CAMERA_EF47S_45K_46L*/
#elif defined(T_RACERJ)
#define F_PANTECH_CAMERA
#define F_PANTECH_CAMERA_TARGET_RACERJ
/*#define F_PANTECH_CAMERA_EF47S_45K_46L*/
#elif defined(T_VEGAPKDDI)
#define F_PANTECH_CAMERA
#define F_PANTECH_CAMERA_TARGET_VEGAPKDDI
/*#define F_PANTECH_CAMERA_EF47S_45K_46L*/
#endif

#ifdef F_PANTECH_CAMERA

#ifndef CONFIG_PANTECH_CAMERA
#define CONFIG_PANTECH_CAMERA
/* #define CONFIG_PANTECH_CAMERA_TUNER */
#endif

/* QC FD ������ �������� �ʰ�, �ش� callback ������ �����Ͽ� ó���Ѵ�.
 * ���� FD ������ OlaWorks �� �����ϰ�, QC FD ����ȭ �������� �ִ���
 * �����ϰ� �������̽��� �����Ѵ�.
 * QC FD ���� �Ŀ��� (���� YUV ���� ���� �����ϴٸ�...) ���� �ڵ� ������
 * �ʿ��ϹǷ� ������ feature �� �и��Ѵ�. */
#define F_PANTECH_CAMERA_FD

/* MSM7230 is used VFE31
   QSD8250 is used VFE41
   Sensor Definition
 */

/*
 * MEDIA_RECORDER_INFO_FILESIZE_PROGRESS CallBack, Only Use KT Phone
 * ������ ���� ����� �����ϴµ� ���� ����� APP�� �˷��ֱ� ���ؼ�
 * �߰�
 * KT�������� �����Ѵ�.
 */
#define F_PANTECH_CAMERA_ADD_EVT_RECSIZE


/* ICS���� ���� �߰��� FUSE ������ recording �ð��� ������ file writing �������� ����
 * recording stop �ð��� �������� �̽��� ����.
 * MPEG4Writer���� writing size�� ũ�� ���� �ʹ� �������� ��ó writing ���� �ʵ��� work-around ����
*/
#define F_PANTECH_CAMERA_QBUG_REC_STOP_DELAY

#ifdef F_PANTECH_CAMERA_SKT
/* F_PANTECH_CAMERA_TODO, SKT FOTA DCMO (Device Control Management Object)
 * SKT �⿡�� �����Ǹ�, UI VOB������ define�� ����.
 * "pantech/development/sky_fota/sky_fota.h" ������ �־��� �Ѵ�.
*/
/*#define F_PANTECH_CAMERA_FOTA_DCMO_CAMERA_LOCK*/
#endif

/* ZSL ���忡�� ĸ�� �Ҷ� jpeg encoding ���� rotion ���� �ȵǴ� �̽� ����.
 * �Ϲ� ĸ�Ŀ����� data�� rotion ������ ZSL�ΰ����� header�� rotion ������ �����Ͽ�
 * Viewer�� ���� rotation �� �� �ֵ��� ���� �Ǿ� ����.
 * ZSL ���忡���� �Ϲ� ĸ�Ŀ� �����ϰ� data�� rotation �ϵ��� ���� �ݿ�.
*/
#define F_PANTECH_CAMERA_FIX_ZSL_ROTATiON

/*
 * InitDefaultParameters() �Լ����� surpported camera paramters�� ������ �� �� ī�޶��� �°� ���� �Ѵ�.
 * effect, wb, scene�� ������ ���� �ϴ����� ī�޶��� ������ sub �׸� list �� �޶�����.
 * open �� ī�޶󿡼� ���� ������ sub list masking value�� �޾Ƽ�, ���� ���� ������ sub list�� �����Ѵ�.
 * vendor/qcom/proprietary/mm-camera/targets/tgtcommon/sensor/ �� �� ī�޶� ���Ͽ��� making value�� �����Ѵ�.
*/
#define F_PANTECH_CAMERA_QUERY_SUBPARM

/*
 * ī�޶� �����̹��� ������ �������� �ʾ��� ��, suspend �Ǵ� ���� ���´�.
 * power control �� ���� Ŀ�� �����̹��� suspend �Ǵ� ���� ���´�.
 * �Ϲ����� ���� ī�޶� ������ ī�޶� �����̹��� ���� ��Ű��, �� �� Ŀ�� �����̹��� ��������.
 * HD ������ȭ�� ���� ���� ������ control�� �Ұ����� LCD�� OFF �Ǵ� ��Ȳ���� suspend�� �߻��Ѵ�.
 * �� �� Ŀ�� �����̹��� suspend ���� �ʵ��� �Ѵ�.
 * kernel/arch/arm/mach-msm/include/mach/camera.h 
 * Ŀ�ο����� �����Ǵ� �����̸� �� ���Ͽ��� �����Ͽ� �����Ѵ�.
 * #define F_PANTECH_CAMERA_FIX_SUSPENDLOCK_ADD
*/

/*
* ī�޶� control driver�� ����(waiting) �ð��� mm_camera_interface.c ���� ������ ������ ���� �Ѵ�.
* ������ 10s �������� timeout_ms�� �����ϵ��� �ߴ�.
* EF39/40�� CE1612 ISP FW�� user �������� update�ϱ� ���ؼ��� �ּ� 25s �̻��� �ð��� �ҿ� �ȴ�.
 * kernel/drivers/media/video/msm/msm_camera.c
 * Ŀ�ο����� �����Ǵ� �����̸� �� ���Ͽ��� �����Ͽ� �����Ѵ�.
 * #define F_PANTECH_CAMERA_FIX_MSM_CTRL_TIMEOUT
*/

/*
 * pantech VT ī�޶��� ���� ������ ���� "pantech-vt" �Ķ����͸� �߰� �Ͽ���.
 * "pantech-vt"�� "on"���� ���� �Կ� ���� VT���� video buffer�� rotation �ϴ� �κа�
 * sub camera�� video ���۸� flip ���� �ʵ��� �Ѵ�.
*/
#if !defined(F_PANTECH_CAMERA_TARGET_STARQ)
#define F_PANTECH_CAMERA_CFG_VT
#endif

#ifdef F_PANTECH_CAMERA_CFG_VT
 /* PANTECH_CAMERA_PSJ_110401
 *  VT�� ������ ���� ���� �� ���׿� ���� Feature
 *  VT mainī�޶��� 90�� rotation���� �� 8x60 ���� �ʿ��� 2K align���ۿ� ���� ó���� ����
 * preview buffer�� �������� ������ video buffer�� data�� preview buffer ��������
 * 90�� rotation ��Ų��.
 * �ش� ������ �����ϱ� ���� ���� F_PANTECH_CAMERA_CFG_VT���� �߰��� "pantech-vt"
 * parameter�� "on"���� ���� �Ͽ��� �Ѵ�.
 */
#define F_PANTECH_CAMERA_FIX_VT_PREVIEW

/*
 * pantech VT�� ȣ�� �����Ǹ� ���� ���۸� video ���۷κ��� ���� ���� start recording
 * �� �����ϸ� ������ connect/disconnect �ÿ� �Կ����� �߻��Ѵ�.
 * pantech VT���� �Կ����� �߻��ϴ� ���� ���� ���� CameraService��
 * CAMERA_CMD_SET_SHUTTER_DISABLE commad�� �߰� �Ͽ���.
*/
 #define F_PANTECH_CAMERA_VT_SHUTTER_DISABLE
#endif

/* PANTECH_CAMERA_PSJ_110302
 * ���� FEATURE������ �����ϴ� ������ IPL�Լ��� �����ϱ� ���� IPL LIB�ε�
 * ipl_reflect �׽�Ʈ �Ϸ�
*/
#define F_PANTECH_CAMERA_USE_IPLLIB


/* ygha for CAMNOTE
 * CamNote ���ø����̼ǿ��� �����ϴ� effect�� �����ϱ� ���� SW IPL�� �����ϵ��� �Ѵ�.
 * EF39S ���� ���� �𵨿� �����ȴ�.
*/

#define F_PANTECH_CAMERA_CFG_IPL_SKY_PROCESSING


#ifdef F_PANTECH_CAMERA_CFG_IPL_SKY_PROCESSING
#define F_PANTECH_CAMERA_CFG_CAMNOTE
#define F_PANTECH_CAMERA_CFG_MINIATURE
#define F_PANTECH_CAMERA_CFG_COLOREXTRACTION
#endif

/*
 * ���� ī�޶� �������� ���ڵ� �������� ���ڵ� ���� ���� ķ��Ʈ���� �����ϴ� ī�޶� �������� �߰� �Ѵ�.
 * ī�޶� ������ -> /system/media/audio/ui/camera_click.ogg
 * ķ�ڴ� ������ -> /system/media/audio/ui/VideoRecord.ogg
 * ķ�ڴ� ������ -> /system/media/audio/ui/Cam_End.ogg
 * ķ��Ʈ ������ -> /system/media/audio/ui/CAMNOTE_SOUND_4.ogg
 * ķ�ڴ� ���������� ���� ���쿡�� ķ�ڴ� �������� �����ϵ��� �Ѵ�.
 * ķ��Ʈ �������� ���� ���쿡�� ī�޶� �������� ���� �ϵ��� �Ѵ�.
*/
#define F_PANTECH_CAMERA_ADD_SHUTTER_FILES


/* ���� CS �μ������� �Һ��� �÷� �м��� ���� ���� PC ���α׷��� �����Ͽ�
 * ī�޶� ���� �ð� ������ PC �� �����Ѵ�.
 *
 * ���� ������ ���� Ŀ�ǵ� ���缭�� ���õǾ� �����Ƿ� ���� �ڵ����� ���� Ŀ�ǵ�
 * ���� ���⿡ ���ԵǾ� ������, ���� Ŀ�ǵ� �� PC ���α׷��� �������� �ʰ� ����
 * ���α׷��� �����Ͽ�, �÷��� DIAG ��Ʈ�κ��� ���� �ð� ������ Ȯ���� �� �ִ�.
 *
 * ���� Ŀ�ǵ� ���缭 v10.35 ���� ����
 * PhoneInfoDisplay v4.0 ���α׷����� Ȯ��
 * ���缭�� ���α׷��� DS2�� �ڰ�ȣ ���ӿ��� ���� */
#define F_PANTECH_CAMERA_FACTORY_PROC_CMD

/* ī�޶� ��ġ ���� OPEN �� ������ ���� (�ܼ� I2C ���� R/W ����, ī�޶� ������)
 * ���� ó���� ���� �����Ѵ�.
 *
 * ��ġ ������ OPEN �ϴ� �������� VFE �ʱ�ȭ ���� ī�޶� HW �ʱ�ȭ�� �̷���
 * ���µ�, HW �ʱ�ȭ�� ������ ���� VFE �� �ʱ�ȭ �� ���·� ���Եǰ� ����
 * OPEN �õ� �� HW �ʱ�ȭ�� �����Ѵ� �ϴ����� �̹� VFE �� �ʱ�ȭ�� �����̹Ƿ�
 * VFE �ʱ�ȭ �� ������ �߻��Ѵ�.
 *
 * ȣ������ : vfefn.vfe_init() -> sctrl.s_init()
 *
 * HW �ʱ�ȭ�� ������ ����, �̹� �ʱ�ȭ�� VFE �� RELEASE (vfe_release) ����
 * ���� ���� �õ� �� ���� �����ϵ��� �����Ѵ�.
 *
 * ECLAIR ���������� ���� ���� ���� ó������ �ұ��ϰ� ������ �����Ǿ� ����
 * �ʰų� ���� �ϵ���� �̻��� �߻��� ���� ī�޶� ������ ANR ������ ����
 * ������ �����ǰ� ���� ������ �������� �����Ͽ� �������� �Ұ����ϴ�.
 *
 * ������ �� ������ ����, ISP �ʱ�ȭ �� ISP �� ������ ������ ������ �����ϴ�
 * �������� 3�� �� POLLING �����ϸ�, �̷� ���� Ÿ�Ӿƿ� �߻��ϰ� ANR ������
 * �̾�����. �� ���� ���� ���� ī�޶� ������ �� ������ �����̶� �ϴ����� ANR
 * ���� ���� ������ �� ���������� �����Ǿ����Ƿ� FRAMEWORK ���δ� �� ������
 * ���·� �����ǰ�, �̷� ���� ������ �������� ī�޶� ���� ���� �� "Unable to
 * connect camera device" �˾��� �Բ� ������ ���Կ� �����Ѵ�.
 *
 * ISP �ʱ�ȭ �� ������ ���� ���� ������, ISP �� ���� ������ Ư�� �������͸�
 * 1ȸ READ �ϰ� �� ������ ����, �̸� FRAMWORK �� ���� �������� �����Ͽ�
 * ���������� �����ǵ��� �����Ѵ�.
 *
 * ���� ISP ��ü�� �̻��� �߻��� ���쿡��, PROBE �ÿ� ���� �߻��Ͽ� �ش�
 * �����̽� ���ϵ��� ������ �� �����Ƿ� FRAMWORK ���ο��� �Բ� ó�� �����ϴ�.
 *
 * EF10S �� ����, BAYER ������ Ŀ���ͷ� �����Ǿ� �ְ�, MV9337 �� ON-BOARD
 * �Ǿ� �����Ƿ�, BAYER ������ �����Ǿ� ���� �ʾƵ�, MV9337 �� �����̶���,
 * PROBE �� ���� �����Ͽ�����, EF12S �� ����, ī�޶� ���⿡ MV9335 �� �Բ�
 * �ν����Ǿ� �־�, Ŀ���Ϳ� ������ �������� ������ PROBE �� I2C R/W ���а�
 * ���� �߻�, RETRY �����ϸ鼭 ���� �ð��� 10�� �̻� �����ǰ�, �̷� ����
 * �ٸ� �������� �ʱ�ȭ�� �������� ������ ��ģ��. */
#define F_PANTECH_CAMERA_INVALIDATE_CAMERA_CLIENT


/* �ܸ����� �Կ��� ������ EXIF TAG ���� �� ������ ���� ������ �����Ѵ�. */
#define F_PANTECH_CAMERA_OEM_EXIF_TAG


/* ���� ������ �Կ� �ػ��� ���̺��� �����Ѵ�. 
 *
 * HAL ������ ��ȿ�� �Կ� �ػ󵵸� ���̺� ���·� �����ϰ� ���̺��� ���Ե� 
 * �ػ��� �̿��� ���� ��û�� ������ ó���Ѵ�. */
#define F_PANTECH_CAMERA_CUST_PICTURE_SIZES


/* ���� ������ ������ �ػ��� ���̺��� �����Ѵ�. 
 *
 * HAL ������ ��ȿ�� ������ �ػ󵵸� ���̺� ���·� �����ϰ� ���̺��� ���Ե� 
 * �ػ��� �̿��� ���� ��û�� ������ ó���Ѵ�. */
#define F_PANTECH_CAMERA_CUST_PREVIEW_SIZES


/* ī�޶� IOCTL Ŀ�ǵ� MSM_CAM_IOCTL_SENSOR_IO_CFG �� Ȯ���Ѵ�.
 *
 * �߰��� ���� �� SOC/ISP ī�޶��� �������� �ʰ� �̱����� �κе��� ���� �� �߰� 
 * �����Ѵ�. */
#define F_PANTECH_CAMERA_CUST_MSM_CAMERA_CFG


/* SKYķ�ڴ� ��ȭ������ Qparser�� Ȯ�ν� �����߻�.(deocde thumnail�Ҽ�����)
 * ķ�ڴ� ���ڵ��� ����ķ�ڴ��� SKYķ�ڴ��� ������ �ϳ���
 * app���� �������� stagefrightrecorder�� mMaxFileDurationUs ���̴�.
 * (SKYķ�ڴ�: 3600000000(us)=1�ð� / ����ķ�ڴ�: 600000000(us)=10��.)
 * mMaxFileDurationUs�� ���̷����� Mpeg4write����
 * SKYķ�ڴ��� 64bitfileoffset / ����ķ�ڴ��� 32bitfileoffset�� �����ϰ� �ȴ�.
 * �̸� 32bitfileoffset���� �����ϰ� �����ϱ� ���ؼ� �ش��κ��� �����Ѵ�.
 * �ӽ÷� �����Ǵ� �κ��̹Ƿ� �߰� ���� �� �������� �����͸��� �ʿ���.
*/
#define F_PANTECH_CAMERA_VIDEO_REC_FILEOFFSET


/* PANTECH_CAMERA_PSJ_110401
 * ���� �𵨵鵵 Video buffer�� ���� align�� ���� �ҽ����� ó����  �߾����� 8x60������ 2K(2047) align�� ���� �Ǿ��ִ�.
 * �� ���۸� ����� ���ؼ��� 2K align�� ���۸� �ٽ� �������� ������ �ϴµ� �̿� ���� �۾��� ���Ͽ� ���� ��ȯ�ϴ� �Լ� �߰�
 */
#define F_PANTECH_CAMERA_ADD_ALIGN_VIDEO_BUFFER

/* PANTECH_CAMERA_PSJ_110401
 * GB���� ����ī�޶� ������ �¿찡 ������ �Ǿ������� Surface�� ���ư� �ִ� ���̹Ƿ� 
 * Layer1���� �ٽ� �����ִ� �κ��� �ʿ��ϴ�
 * �� �κ��� GB Framework�� ���ǵ� �κ��̹Ƿ� ����� �´� �������� �� �� Ÿ�𵨰� �����Ͽ� �����Ͽ��� �� ���̴�.
 */
/*#define F_PANTECH_CAMERA_ADD_REFLECT_FOR_SUBCAM*/




/*
*ķ�ڴ� ���� ���Խ� preview size ���� �Ŀ� video size ������ �ϴµ�, ��  �߰��� mPreviewWidth, mPreviewHeight �� 
* video width �� ���� ���� ���� preview callback �� �ð����� �Ǹ� CameraService �ܿ��� copyFrameAndPostCopiedFrame
* �Լ� ���ο��� copy �� data size �� ���� ũ�Ⱑ �ٸ��� �����Ǿ� memcpy copy ������ �߻��ϰ� �Ǵµ�, �̸� �����ϱ� ���� 
* setvideosize �Լ� ���� previewsize �� video size �� ���� �����ϰ� ������. 
*/
#if !defined(F_PANTECH_CAMERA_TARGET_STARQ)
#define F_PANTECH_CAMERA_PREVIEW_CALLBACK_BUFFER_SIZE_FAIL
#endif
/*----------------------------------------------------------------------------*/
/*  SENSOR CONFIGURATION                                                      */
/*  ���� �� ���� ����(ISP)�� ���� ����/�߰��� FEATURE ����                    */
/*----------------------------------------------------------------------------*/
/* ī�޶��� ������ ���� ���� ���� SOC/ISP ī�޶�(��)�� ������ ���� �����Ѵ�.
 *
 * ������ȭ�� ���� �� ���� ī�޶��� �����ϰ�, �ϳ��� SOC Ÿ��, �ٸ� �ϳ���
 * BAYER Ÿ���� ���쿡�� �������� �ʴ´�. ������ ����, BAYER ī�޶��� ����
 * �Ϻ� �ڵ����� �������� �ʴ´�.
 *
 * SOC/ISP ī�޶��� �����ϹǷ�, BAYER ���� �ڵ����� 
 * �������� �ʾҰ�, �Ϻδ� �Ʒ� FEATURE ���� �����Ͽ� �ּ� ó���Ͽ���. */
#define F_PANTECH_CAMERA_YUV_SENSOR_ONLY

#ifdef F_PANTECH_CAMERA_TARGET_EF39S
/* ISP backend camera ISP */
#if (BOARD_REV == PT10)
#define F_PANTECH_CAMERA_ICP_HD
#else
#define F_PANTECH_CAMERA_CE1612
#endif
/* 1.3M front camera sensor */
#define F_PANTECH_CAMERA_S5K6AAFX13
#endif

#ifdef F_PANTECH_CAMERA_TARGET_PRESTO
#if (BOARD_REV >= WS20)
#define F_PANTECH_CAMERA_S5K4ECGX
#else
#define F_PANTECH_CAMERA_MT9P111
#endif
#define F_PANTECH_CAMERA_MT9V113
#endif

#if defined(F_PANTECH_CAMERA_TARGET_EF40S) || \
    defined(F_PANTECH_CAMERA_TARGET_EF40K)
#if (BOARD_REV >= WS20)
#define F_PANTECH_CAMERA_MT9D113
#else
#define F_PANTECH_CAMERA_S5K6AAFX13
#endif
#define F_PANTECH_CAMERA_CE1612
#endif

#if defined(F_PANTECH_CAMERA_TARGET_EF45K) || \
         defined(F_PANTECH_CAMERA_TARGET_EF45KV) || \
    	defined(F_PANTECH_CAMERA_TARGET_EF46L) || \
	defined(F_PANTECH_CAMERA_TARGET_EF47S) || \
	defined(F_PANTECH_CAMERA_TARGET_OSCAR) || \
	defined(F_PANTECH_CAMERA_TARGET_VEGAPVW)
#define F_PANTECH_CAMERA_OV8820	
#define F_PANTECH_CAMERA_YACD5C1SBDBC	
#endif	

#if defined(F_PANTECH_CAMERA_TARGET_CHEETAH) || \
	defined(F_PANTECH_CAMERA_TARGET_ZEPPLIN) 
#define F_PANTECH_CAMERA_S5K4ECGX
#define F_PANTECH_CAMERA_S5K6AAFX13	
#endif

#ifdef F_PANTECH_CAMERA_TARGET_STARQ
#define F_PANTECH_CAMERA_S5K4ECGX
#define F_PANTECH_CAMERA_MT9V113	
#define F_PANTECH_CAMERA_BACKFACE_YUV
#endif

#if defined(F_PANTECH_CAMERA_TARGET_SVLTE) || \
    defined(F_PANTECH_CAMERA_TARGET_CSFB)
#define F_PANTECH_CAMERA_CE1612	
#define F_PANTECH_CAMERA_S5K6AAFX13	
#endif

#define F_PANTECH_CAMERA_CUST_ORIENTATION

#ifdef F_PANTECH_CAMERA_CE1612
#define F_PANTECH_CAMERA_CFG_WDR
#define F_PANTECH_CAMERA_ADD_CFG_UPDATE_ISP
#define F_PANTECH_CAMERA_ADD_CFG_READ_REG

#define F_PANTECH_CAMERA_CFG_STOP_CAPTURE
#endif

#ifdef F_PANTECH_CAMERA_YUV_SENSOR_ONLY
/*  
 * ISP/SOC ī�޶��� ���� ���� �� ī�޶� ���⿡ ���� ���� ������ ������ �ٸ���.
 * �� ���⿡ �°� capability�� ���� �� �� �ֵ��� �Ѵ�.
 */
#define F_PANTECH_CAMERA_CFG_CAPABILITIES

/* ISP ��ü���� ���� ���� ZOOM �� �����ϱ� ���� �������̽��� �߰��Ѵ�. 
 * EF10S/EF12S ������ QUALCOMM ZOOM �� �����ϸ�, ���������� �ڵ����� ���ܵд�.
 *
 * ISP ��ü ZOOM �� ����, ������/������ ���忡�� �̹� ZOOM �� ������ �̹����� 
 * ���µǸ� �� ���� ���带 �����Ѵ�.
 *
 * 1) DIGITAL (SUBSAMPLE & RESIZE)
 *     ������/������ �ػ󵵺��� ������ ������ �����Ѵ�. ISP ���ο��� 
 *     �̹����� SUBSAMPLE �Ͽ� RESIZE �� �����ϸ�, �̷� ���� ZOOM ������
 *     0 �� �ƴ� ������ ������ ���� ������ FPS �� 1/2 �� ���ҵȴ�.
 * 2) SUBSAMPLE ONLY
 *     ������/������ �ػ󵵺��� ������ ������ �����Ѵ�. ISP ���ο��� 
 *     SUBSAMPLE �� �����ϹǷ� ���� �ػ󵵿����� ���� ������ �����ϰ� �ִ� 
 *     �ػ󵵿����� ZOOM ��ü�� �Ұ����ϴ�. ������ FPS �� ���ҵ��� �ʴ´�.
 *
 * QUALCOMM ZOOM ���� ��, ī�޶��� ���� ���� �ػ󵵿��� ���� ���� ZOOM �� 
 * �����ϹǷ� �̸� �����ϸ�, ���� ������ ���� �ش� �ڵ����� ���ܵд�. 
 *
 * ���� FEATURE : F_PANTECH_CAMERA_ADD_CFG_DIMENSION */
/* #define F_PANTECH_CAMERA_ADD_CFG_SZOOM */


/* ISP ���� �����Ǵ� �ն��� ���� ���� (Digital Image Stabilization) �� ����
 * �������̽��� �߰��Ѵ�. 
 *
 * ����/�¿� ���� �������� ���鸱 ���츸 ���� �����ϴ�. 
 * ���� ���带 OFF �̿��� ������ ������ ����, ���� �ն��� ���� ������ 
 * ���õȴ�. */
#if !defined(F_PANTECH_CAMERA_TARGET_STARQ)
#define F_PANTECH_CAMERA_ADD_CFG_ANTISHAKE
#endif

/* AF WINDOW ������ ���� �������̽��� �����Ѵ�. SPOT FOCUS ���� ���� �� 
 * �����Ѵ�.
 *
 * ISP ������ ������ ���� ���� �ػ󵵸� �������� ����/���θ� ���� 16 ���� 
 * �������� �� 256 �� �������� ������ ���� ������ AF WINDOW ������ �����ϴ�. 
 * ���뿡���� ������ �ػ󵵸� �������� �����ڰ� ��ġ�� ������ ��ǥ�� HAL �� 
 * �����ϰ�, HAL ������ �̸� ���� ��ǥ�� ��ȯ�Ͽ� ISP �� �����Ѵ�. 
 * ���� AF ���� �� �� WINDOW �� ���Ե� �̹��������� FOCUS VALUE �� �����Ͽ�
 * ������ ��ġ�� �����Ѵ�.
 *
 * ISP �� ������ ������ ���¿��� QUALCOMM ZOOM �� �����Ͽ� SUBSAMPLE/RESIZE
 * �ϱ� ������ ZOOM �� 0 ���� �̻����� ������ ����, HAL ���� ��ǥ-to-����
 * ��ȯ���� ����������, Ư�� ZOOM ���� �̻��� ���� �� ���� ���� �ȿ� ��ü
 * ������ ������ ���ԵǾ� �����Ƿ� ���� ��ü�� �ǹ̰� ����.
 * �׷��Ƿ�, ������ SPOT FOCUS ���� ���� �ÿ��� ZOOM ������ ������ �� ������ 
 * ó�� �ؾ��Ѵ�. */
#define F_PANTECH_CAMERA_FIX_CFG_FOCUS_RECT

#define F_PANTECH_CAMERA_FIX_CFG_METERING_AREA

/* QUALCOMM BAYER �ַ��� ������ ȭ��Ʈ�뷱�� ���� �������̽��� �����Ѵ�. 
 *
 * ���� ���带 OFF �̿��� ������ ������ ����, ���� ȭ��Ʈ�뷱�� ������ 
 * ���õȴ�. */
#define F_PANTECH_CAMERA_FIX_CFG_WB


/* QUALCOMM BAYER �ַ��� ������ ���� ���� �������̽��� �����Ѵ�. 
 *
 * ���� ���带 OFF �̿��� ������ ������ ����, ���� ���� ������ ���õȴ�. */
#define F_PANTECH_CAMERA_FIX_CFG_EXPOSURE


/* ���� ���� ������ ���� �������̽��� �߰��Ѵ�. 
 *
 * ���� ���带 OFF �̿��� ������ ������ ���� ���� ȭ��Ʈ�뷱��/����/�ն�������/
 * ISO ������ ���õȴ�. ���뿡�� ���� ���带 �ٽ� OFF �� �ʱ�ȭ �ϴ� ����, 
 * ȭ��Ʈ�뷱��/����/�ն�������/ISO �� HAL ���� ���� �������� �ڵ� �����ǹǷ�,
 * ������ ������ �ʿ� ����. (HW ���������̹Ƿ�, HAL ���� �����Ѵ�.) */
#define F_PANTECH_CAMERA_FIX_CFG_SCENE_MODE


/* �ø�Ŀ ������ ���� �������̽��� �����Ѵ�.
 *
 * 2.1 SDK ���� �� �� ���� ���� (OFF/50Hz/60Hz/AUTO) �� ���õǾ� ������, 
 * ISP �� ���� OFF/AUTO �� �������� �ʴ´�. �׷��Ƿ�, ������ OFF �� ���� 
 * �ÿ��� Ŀ�� �����̹����� 60Hz �� �����ϰ�, AUTO �� ������ ���� HAL ���� 
 * �ý��� ���� �� �� ���� �ڵ� ("gsm.operator.numeric", �� 3�ڸ� ����) �� �а�, 
 * ������ Hz ������ ��ȯ�Ͽ� �ش� ������ �����Ѵ�.
 *
 * ��ȹ�� ���� ����, �ø�Ŀ�� �Ϲ����� ������ �ƴϹǷ�, ���� �ڵ带 �ν��Ͽ� 
 * �ڵ����� ������ �� �ֵ��� �ϰ�, ���� ���� �޴��� ���� ó���Ѵ�. */
#define F_PANTECH_CAMERA_FIX_CFG_ANTIBANDING

/*
 * AT&T �⿡�� Shutter sound On/OFF������ �����. �̰��� �߰��ϱ� ���ؼ�
 * �� ���� ������ �߰��ϱ� ���ؼ� ���� �ڵ� 
 */
#ifdef F_PANTECH_CAMERA_ATT
#define F_PANTECH_CAMERA_SET_SHUTTER_SOUND
#endif

/* 
 * ATT�� ���쿡�� FOCUS MODE�� ���� AUTO, INFINITY, MACRO 3���� ���尡 �����Ѵ�.
 * PANTECH_CAMERA�� ���쿡�� Manual���尡 ���縦 �ϰ� �� Manual���忡�� Focus Step�� ���� �� �� �ִ�.
 * ������ ATT�� ���쿡�� �̷��� Focus Step�� ���� �ϴ� UI�� �������� �ʴ´�.
 * INFINITY�� ������ FOCUS_STEP�� MAX�� ���������� �ϰ�,
 * MACRO�� ������ FOCSU_STEP�� MIN������ �����ؾ��ϱ� 
 * setFocusMode���� FOCUS_STEP�� ���� �־��ش�.
 */
#if	0//def F_PANTECH_CAMERA_ATT
#define F_PANTECH_CAMERA_ATT_FOCUS_STEP
/* Add By Lee Jitae 2011-06-08
 * GS3�� AT&T�⿡ 4MP ����� ����� �Ѵٴ� ��û���� �߰��� 
 * �������̴�. ���� ���翡�� ����� �ʴ� ������
 */
#define F_PANTECH_CAMERA_ATT_PICTURE_SIZE
#endif

/* �÷��� LED ������ ���� �������̽��� �����Ѵ�.
 *
 * QUALCOMM ������ ������ IOCTL (MSM_CAM_IOCTL_FLASH_LED_CFG) Ŀ�ǵ带
 * �����Ͽ� �����Ǿ� ������, PMIC ������ �����ϴ� LED �����̹��� �����Ѵ�.
 * MAXIMĨ�� �ĸ�ī�޶��� ��Ʈ�ѷ� FLASH����
 *
 * AUTO ������ ������ ����, ������ �� ���쿡�� AF ���� �� AF/AE �� ����
 * ���� ON �ǰ�, ���� ������ �������� �� �� �� ON �ȴ�. */
#if !defined(F_PANTECH_CAMERA_TARGET_STARQ)
#define F_PANTECH_CAMERA_FIX_CFG_LED_MODE
#endif

/* �÷��� ���� Auto�� ���ؼ� ISP���� AF,Capture flash on�� �������� �ʴ� ����
 * �Ǵ� gpio�� ���� ���� flash�� control �ϴ� ���쿡, ĸ�Ľ� flash on�� �����ϰ�
 * ĸ�� �Ϸ��ÿ� flash off�� ���� �ϵ��� �Ѵ�.
 * �̶�, kernel driver�� sensor_config���� flash on�� ��Ű��, HAL���� ĸ�� frame�� ������ off�Ѵ�.
 * auto�� ���쿡 ī�޶� ������ ���� brightness�� �о �̿� ���� flash on�� �����Ѵ�.
 * ISP ���� AF, Capture flash On/Auto�� �����ϴ� ���쿡�� ���� ���� �ʴ´�.
*/
#ifdef F_PANTECH_CAMERA_TARGET_PRESTO
#define F_PANTECH_CAMERA_LED_MODE_AUTO
#endif

/* ISO ������ ���� �������̽��� �����Ѵ�.
 *
 * ��ȹ�� ���� ����, AUTO ���忡���� ȭ���� ū �̻��� �����Ƿ� ��������
 * ISO �� ������ �� �ִ� �޴��� ���� ó���Ѵ�.
 * ���� ���带 OFF �̿��� ������ ������ ����, ���� ISO ������ ���õȴ�. */
#define F_PANTECH_CAMERA_FIX_CFG_ISO

/* Ư��ȿ�� ������ ���� �������̽��� �����Ѵ�.
 *
 * SDK 2.1 �� ���õ� ȿ���� �� �Ϻθ� �����Ѵ�. MV9337/MV9335 �� ���� SDK ��
 * ���õ��� ���� ȿ���鵵 ���������� ���뿡�� �������� �����Ƿ� ���� �߰���
 * ���� �ʴ´�. */
#define F_PANTECH_CAMERA_FIX_CFG_EFFECT


/* MANUAL FOCUS ������ ���� �������̽��� �����Ѵ�. 
 *
 * MANUAL FOCUS ������ ������ ����, �� ������ ���Ƿ� ������ ��ġ��
 * �̵���ų ����, ������ ������ AF �� �������� �ʴ� ���� �����̸�, �̷� ���� 
 * ISP ���� ������ �����Ͽ� ������ �� �ִ� �ð��� �����Ƿ� �÷����� ON ��
 * ����, ������/������ �̹����� ������ �� �ִ�. �׷��Ƿ� ������ MANUAL FOCUS 
 * ���� ���� �� �ݵ��� �÷��� ���带 OFF �� �����ؾ� �ϰ�, AUTO FOCUS �Ǵ� 
 * SPOT FOCUS ���� ���� �� ���� ������ �������Ѿ� �Ѵ�. */
#define F_PANTECH_CAMERA_FIX_CFG_FOCUS_STEP


/* ���� ������ ���� �������̽��� �����Ѵ�. */
#define F_PANTECH_CAMERA_FIX_CFG_BRIGHTNESS

/* ������ ȸ���� ������ ���� �������̽��� �����Ѵ�.
 *
 * ������ ���� JPEG ���ڵ� �ÿ� �ȸ��ν� ���� (������) ���� �� ī�޶��� 
 * ȸ�� ���¸� �Է��Ͽ��� �Ѵ�. ������ OrientationListener ���� �� �Ʒ��� ����
 * ������ HAL �� ȸ���� ���� ���� ���־��� �Ѵ�.
 * 
 * JPEG ���ڵ�
 *     ���ڵ� ������ ����
 * ������ ����
 *     ���� �� �Ź� ����
*/
#define F_PANTECH_CAMERA_FIX_CFG_ROTATION


/* AF ������ ���� �������̽��� �����Ѵ�. 
 * AF ������ NORMAL, MACRO, SPOT �� �ִ�.
 * NORMAL : 10 ~ ���Ѵ� 
 * MACRO : 10 ~ 30 
 * SPOT : ��ġ ��ǥ (NORMAL )AF
*/
#define F_PANTECH_CAMERA_FIX_CFG_AF

#define F_PANTECH_CAMERA_FIX_CFG_REFLECT

/* VTS���� �����ϴ� feature
 *
 * VTS on���� ������ ���� preview display buffer�� �÷����� �ʰ� 
 * Callback data�� �÷��ִ� ����
*/
#if !defined(F_PANTECH_CAMERA_TARGET_STARQ)
#define F_PANTECH_CAMERA_VTS
#endif

/*============================================*/
/*Morpho HDR���� �����ϴ� feature
 *
 * HDR on���� ������ ���� 2,3 ���� ������ �����Ͽ� processing
*/
#if !defined(F_PANTECH_CAMERA_TARGET_STARQ)
#define F_PANTECH_CAMERA_CFG_HDR 
#endif
/*============================================*/

/* �ȸ��ν� ���� �̹��� ���� ������ ���� �������̽��� �߰��Ѵ�.
 *
 * EF10S/EF12S ������ �ö����� �ַ����� �����ϸ�, ������/������ �̹������� 
 * ���� ��ġ�� �����Ͽ� ���� ������ ����ũ�� Ư��ȿ���� ������ �� �ִ�. 
 *
 * vendor/qcom/android-open/libcamera2/Android.mk ���� �ö����� ���̺귯����
 * ��ũ���Ѿ߸� �����Ѵ�. PANTECH_CAMERA_FD_ENGINE �� 1 �� ������ ���� �ö����� 
 * �ַ����� �����ϰ�, 0 ���� ������ ���� ī�޶� �Ķ����͸� �߰��� ���·� ���� 
 * ���ɵ��� �������� �ʴ´�. �ٸ� �ַ����� ������ ���� �� ���� Ȯ���Ͽ� 
 * �����Ѵ�. */
#if !defined(F_PANTECH_CAMERA_TARGET_STARQ)
#define F_PANTECH_CAMERA_ADD_CFG_FACE_FILTER
#endif
/* ������ FPS ������ ���� �������̽��� �����Ѵ�. 
 *
 * 1 ~ 30 ���� ���� �����ϸ� �ǹ̴� ������ ����.
 *
 * 5 ~ 29 : fixed fps (������ ���� ���� ����) ==> ķ�ڴ� ������ �� ����
 * 30 : 8 ~ 30 variable fps (������ ���� �ڵ� ����) ==> ī�޶� ������ �� ����
 *
 * MV9337/MV9335 �� ������ ���忡�� ���� 1 ~ 30 �����Ӱ� ���� 8 ~ 30 �������� 
 * �����ϸ�, EF10S/EF12S ������ ������ ��ȭ �� 24fps (QVGA MMS �� ���� 15fps) ����
 * �����ϰ�, ī�޶� ������ �ÿ��� ���� 8 ~ 30fps ���� �����Ѵ�. */
#define F_PANTECH_CAMERA_FIX_CFG_PREVIEW_FPS


/* ��Ƽ�� ������ ���� �������̽��� �߰��Ѵ�.
 * 
 * �����Կ�, �����Կ� 4��/9�� ���忡�� �� �Կ� �ø��� ���� ���带 �����ϴ� 
 * ���� �����Ѵ�. ù ��° �Կ����� ������ ������ ������ �����ϰ�, VFE/CAMIF
 * �������� �Ϸ��� �����̹Ƿ�, �� ��° �Կ����ʹ� ������/������/JPEG ���۸�
 * �ʱ�ȭ�ϰ� VFE/CAMIF �� ������ ���ɸ� �۽��Ѵ�.
 *
 * �������� : ���������� �÷��� ���带 �ڵ����� �����ϰ� �����Կ�, �����Կ� 
 * 4��/9�� ������ ���� �� �Կ� ��, ù ��° �Կ������� �÷����� ON �ǰ�, 
 * �� ��°���ʹ� ON ���� �����Ƿ� �����Կ�, �����Կ� 4��/9�� ���忡����
 * ������ �ݵ��� �÷����� OFF �ؾ��ϸ�, �̿� ������ ���� �� ���� ������
 * ������ �������Ѿ� �Ѵ�. */
#define F_PANTECH_CAMERA_ADD_CFG_MULTISHOT



/*  Continuous AF�� ON, OFF�� �� �� �ִ�
 *  AF ������ SOC/ISP ���⿡�� CAF�� �����ϴ� ���� �����Ѵ�.
 */
#define F_PANTECH_CAMERA_ADD_CFG_CAF

#endif /* F_PANTECH_CAMERA_YUV_SENSOR_ONLY */

#if !defined(F_PANTECH_CAMERA_TARGET_STARQ)
#define F_PANTECH_CAMERA_CAF_CIRCLE_DRAW
#endif

#ifdef F_PANTECH_CAMERA_ADD_CFG_FACE_FILTER
/* �ȸ��ν� �ַ��� ���� ��, ������ �ټ��� �󱼵鿡 ���������� ���͸� ������
 * �� �ִ� �������̽��� �߰��Ѵ�.
 *
 * ������ �̹��� �� �ټ��� ���� �������� �����ϰ� �ش� ������ ��ġ�� ����
 * �ش� ���� ������ ���͸� ������ �� ���θ� ON/OFF �������� ������ �� �ִ�.
*/
#define F_PANTECH_CAMERA_ADD_CFG_FACE_FILTER_RECT
#endif

/* 
 * Gingerbread���� OpenCore���� Stagefright�� �����ϵ��� ���� �Ǿ���.
 * EF31S�� EF32K���� ������ recording�� stagefright ������ ������ �Ǿ�
 * �켱 OpenCore�� �����ϵ��� �Ѵ�.
 * Stagefright�� ���ؼ��� ������ ���� �� ���� �Ѵ�.
*/
/*#define F_PANTECH_CAMERA_CFG_OPENCORE*/

#if !defined(F_PANTECH_CAMERA_TARGET_STARQ)
#define F_PANTECH_CAMERA_ADD_CFG_DIMENSION
#endif
/* PANTECH_CAMERA PSJ 110224
 * 1080P�� ������ dynamic�ϰ� �ٲ� �� �ֵ��� �����̹� �� ���� ���� �ڵ� �߰� �� ����
 * ISP�� ������ 1080P�� ���õǸ� MSM ���� �ش� ����� ���� �� �ֵ��� set dimension�� ��
 * ������ set dimension �Լ��� ������ �Ǿ� �־� F_PANTECH_CAMERA_ADD_CFG_DIMENSION feature��
 * dependency�� ������ ����
 */
#ifdef F_PANTECH_CAMERA_ADD_CFG_DIMENSION
#define F_PANTECH_CAMERA_1080P_PREVIEW
#endif

#define F_PANTECH_CAMERA_THUMBNAIL

#define F_PANTECH_CAMERA_QBUG_FIX_ZSL_THUMBNAIL

/*
 * Gingerbread�� CameraService���� lockIfMessageWanted(int32_t msgType) �Լ��� �߰� �Ǿ���.
 * CameraService�� callback ó�� �Լ����� mLock�� check�Ͽ� LOCK �����̸�, UNLOCK���� waiting �Ѵ�.
 * capture ���� ���� UI �κ��� command�� �������� callback �Լ����� �̷� ���� ������ �߻��Ѵ�.
 * capture ���� �� ī�޶� ������ �̷� ���� CameraHAL���� UI�� ���� ���� �Ǵ� ���찡 �߻��Ѵ�.
 * UI�� ���� �����ǰ� CameraHAL �������� �ٽ� Camera�� �����Ǹ� ���������� Open ���� ���Ѵ�.
 * lockIfMessageWanted �Լ��� ���� ���� �ʵ��� �����Ͽ���.
*/
#define F_PANTECH_CAMERA_FIX_CS_TRYLOCK

/*
camera id���� �˻��Ͽ� ���� app���� �ĸ� ī�޶�, ���� ī�޶� ���� ���۽� ���� �����ϰ� �Ǿ�
���Խ� open�� ������ �ñ⿡ �ǰų�(ȨŰ long Ű, ��ȯ), setparameter�� ���õǴ� �������� �߻��Ͽ�,
���� �ǵ����� ���� ���� ���� ������ �ϴ� ������
froyo�� ���������� �� �ĸ� ���� ī�޶��� ���� ī�޶� release �������� ���� �Ұ��ϵ��� ����

HW, QCH ���� ������ ī�޶� ������ �����Ѵٸ� �Ʒ��� ������ �� �׽�Ʈ �� ��.
*/
#define F_PANTECH_CAMERA_FIX_CS_CONNECT


/*
 * zoom crop�� �����ͷ� �޾Ƽ� �����ϴ� ���� ó���� �ʾ��� crop�� data�� refresh �� �� ����
*/
#define F_PANTECH_CAMERA_FIX_PREVIEW_ZOOM

/* CTS qualcomm bug ���� 
 */
#define F_PANTECH_CAMERA_FIX_CFG_FOCUS_DISTANCES

#define F_PANTECH_CAMERA_FIX_CFG_FPS_RANGE

#define F_PANTECH_CAMERA_FIX_CANCEL_AF


/*ī�޶� �� ���Խ� ������ ������ ���� ���� ������ ī�޶� �����̹��� ���� ���� ���� �ʾ�����
�� ���� ���� �ڵ� - �� ���Խ� �����̹� ������ �����̸�, ���� ī�޶� reject�ϰ� driver ����*/
#define F_PANTECH_CAMERA_DEVICE_CONNECT_FAIL_FIXED


/* ī�޶� Open �Ҷ� I2C fail�� ���� ���� ���� �Ѱ���, ������ �ȵǴ� ���� ����
 * Ŀ�� ������ ���� �κ��� ������, ���������� ���ĸ� �и��Ͽ� �����ϰ� �ȴ�.
 * Ŀ�ο����� ���Ĵ� �Ʒ� ���ο� �����Ͽ� �����Ѵ�.
 * kernel/drivers/media/video/msm/msm_camera.c
 * Ŀ�ΰ� ���� ������ �����Ǵ� �����̴�.
 */
#define F_PANTECH_CAMERA_FIX_MSM_OPEN_FAIL

/* vfe�� �� ���� ���� �� ��, ī�޶� ������ vfe�� �߸� �� ������ ���� stop���� ���� ó���� 
config_proc.c�� *((int *)(0xc0debadd)) = 0xdeadbeef; ������ ó���� ���� mediaserver �״� ������
���� ���� �ڵ� ���� */
#define F_PANTECH_CAMERA_DEADBEEF_ERROR_FIX

/* Ŀ�� ���� �ڵ忡�� SKYCDBG/SKYCERR ��ũ�θ� �����Ͽ� ���µǴ� �޽�������
 * Ȱ��ȭ ��Ų��. 
 * kernel/arch/arm/mach-msm/include/mach/camera.h 
 * �� ���Ͽ��� #define F_PANTECH_CAMERA_LOG_PRINTK�� �����Ͽ� �α׸� �� �� �ִ�.
*/
/* ���� ����(vendor)�� SKYCDBG/SKYCERR �޼��� on off */
#define F_PANTECH_CAMERA_LOG_OEM		

/* ���� ������ LOGV/LOGD/LOGI �޼��� on off */
#define F_PANTECH_CAMERA_LOG_VERBOSE

/* QUALCOMM ������ �ڵ忡 ������ �� �޽����� �߰��Ѵ�. */
#define F_PANTECH_CAMERA_LOG_DEBUG

/* Bayer camera�� CAF�ó��������� T-AF(spot focus) ���� CAF mode start�� Full-sweep�� �Ǵ� �ó����� ����.
 * T-AF���� CAF���� �����Ǿ Scene���������� full-sweep�� ���� �ʵ��� ��.
 * T-AF���� CAF�����ð��� Camera application���� �����Ѵ�.
 * private static final int RESET_TOUCH_FOCUS_DELAY = 5000;
 *  In FocusManager.java -> onAutoFocus():
 *           if (mFocusArea != null) {
 *               mHandler.sendEmptyMessageDelayed(RESET_TOUCH_FOCUS, RESET_TOUCH_FOCUS_DELAY);
 *           }       
 * WTR_153611 mainline���� �����Ǿ ������.20120704
*/
/* #define F_PANTECH_CAMERA_TAF_CAF_SCENARIO */

/* Bayer camera�� tuning���� ������������, ��ǰ�������� ��û���� �߰��Ǵ� �κ�.
*/
#define F_PANTECH_CAMERA_HWP_FOR_BAYER

/* AOT(Always On Top) CAMERA �߰� ����.
 * ī�޶� ���ۻ��¸� üũ�ϵ��� CameraService::isRunning() �Լ� �߰�.
*/
#define F_PANTECH_CAMERA_AOT_ISRUNNING
/*
 * ������ ���ڵ� ���۰� ���� ���� ������ ������ ���� ������
 * ȿ���� ���� �� �ý��� ���Ϸ� ���� �Ҹ��� ������ ���� �߻�
 * ���ڵ� ������ start �� �� ������ ���� �� ������ wating
 * EF31S/EF32K ������ Sound�� kernel message�� ������ ���� �Ҹ��� ������,
 * kernel message�� ���ų� release build������ ���� �߻� ����.
*/
#define F_PANTECH_CAMERA_QBUG_REC_BEEP_SOUND


/* 1600x1200, 1600x960 �ػ󵵿��� "zoom" �Ķ����͸� 21 �� ���� �� ������ ��
 * ������ YUV �̹����� CROP �ϴ� �������� �߻��ϴ� BUFFER OVERRUN ������
 * �ӽ� �����Ѵ�.
 *
 * QualcommCameraHardware::receiveRawPicture() ���� crop_yuv420(thumbnail)
 * ȣ�� �� �Ķ����ʹ� width=512, height=384, cropped_width=504,
 * cropped_height=380 �̸� memcpy ���߿� SOURCE �ּҺ��� DESTINATION �ּҰ�
 * �� Ŀ���� ��Ȳ�� �߻��Ѵ�.
 *
 * R5040 ���� QUALCOMM ���� Ȯ�� �� �����Ѵ�. (SR#308616)
 * - R407705 FIXED ISSUE 6 �� ���� */
/* #define F_PANTECH_CAMERA_QBUG_ZOOM_CAUSE_BUFFER_OVERRUN */


/* ���� �ػ󵵿��� ZOOM �� Ư�� ���� �̻����� ������ ����,
 * EXIFTAGID_EXIF_PIXEL_X_DIMENSION, EXIFTAGID_EXIF_PIXEL_Y_DIMENSION �±�
 * ������ �߸��� ���� �����Ǵ� ������ �ӽ� �����Ѵ�.
 *
 * R5040 ���� QUALCOMM ���� Ȯ�� �� �����Ѵ�. (SR#307343)
 * - R4077 FIXED ISSUE 12 �� ����
 * - vendor/qcom/proprietary/mm-still/jpeg/src/jpeg_writer.c �� ���� �ӽ� ����
 *   �ڵ��� ������ �����Ǿ� ���� */
/* #define F_PANTECH_CAMERA_QBUG_EXIF_IMAGE_WIDTH_HEIGHT */


/* PANTECH_CAMERA_PSJ_100610
 * �Կ��� �������� ���� ��Ȳ���� Stop preview�� �Ͽ� �޸𸮰� �����Ǵ� ��Ȳ ����
*/
/* capture ���� �м� �� ���� �Ǿ��� ��*/
/*#define F_PANTECH_CAMERA_QBUG_SNAPSHOT_RELEASE_INTERRUPT*/

/* ������ ��ȭ ����/���Ḧ ������ �ݺ��ϰų�, �̾����� ������ ���¿��� �����Կ�
 * ������ �Կ��� ����, MediaPlayer �� �������ϸ鼭 HALT �߻��Ѵ�.
 *
 * MediaPlayer �� ����, ������ ������ ���� �߿� �� �ٽ� ���� �õ��� ���� 100%
 * �������ϹǷ� ���� ������ �����Ͽ� �����ؾ� �� ����, �ݵ��� ���� ������ �Ϸ�
 * �Ǿ����� ���θ� Ȯ�� �� �����ؾ� �Ѵ�. */
#define F_PANTECH_CAMERA_QBUG_SKIP_CAMERA_SOUND

/* �Կ���/��ȭ�� ���� �߿� ������ ������ ����, CLIENT �Ҹ� �ÿ� �ش� �Կ���/
 * ��ȭ�� ������Ʈ�� ������ disconnect/clear �Ǹ鼭 MEDIA SERVER �� �״� ����
 * �����Ѵ�. */
#define F_PANTECH_CAMERA_QBUG_STOP_CAMERA_SOUND

/* 8x60���� ��ȭ�� ������(MMS/MPEG4/320x240)�� ���� ���ø𵨵鿡�� decoding�� �������� �߻���.
 * ����SR�� ���� ���ó��� workaround�� ������.
*/
#define F_PANTECH_CAMERA_QBUG_DECODING_OTHER_CHIPSET

/* CTS qualcomm bug ����
 */
#define F_PANTECH_CAMERA_QBUG_CTS

#if !defined(F_PANTECH_CAMERA_TARGET_STARQ)	
/* JB OS���� CAFƩ�װ� �� mode���� �����ϰ� ������.  �Ʒ� 2���� feature�� ���� 1���� �����ؾ���.  
  *  - PREVIEW / ZSL / VIDEO / VIDEO HD      
  *  #define F_PANTECH_CAMERA_SEPARATTE_MODE_CAF_TUNNING_FILE : Af_main_cam_0_ov8820~.h���Ϸ� CAF tunning file����. 
  *  #define F_PANTECH_CAMERA_SEPARATTE_MODE_CAF_CHROMATRIX_FILE : chromatix_ov8820~.h���Ϸ� CAF tunning file����. 
*/
//#define F_PANTECH_CAMERA_SEPARATTE_MODE_CAF_TUNNING_FILE
#define F_PANTECH_CAMERA_SEPARATTE_MODE_CAF_CHROMATRIX_FILE
#endif

#if !defined(F_PANTECH_CAMERA_TARGET_STARQ)	
/* beauty mode�� ���� �Կ���, �Կ��� ������ ����  processPreviewFrameWithDisplay()�� ȣ���Ǹ�, waterȿ���� ���� preview ȭ���� �¿� reflect�Ǿ� 
    ������ ���� ����. beauty mode �����Կ��� ������ ������ processPreviewFrameWithDisplay()�� ȣ������ ����. 
*/
#ifdef F_PANTECH_CAMERA_CFG_IPL_SKY_PROCESSING
#define F_PANTECH_CAMERA_BEAUTY_MPDE_TAKE_PICTURE_SKIP_FRAME
#endif
#endif

/* HDR �Կ� �� home key ���� ���� �� ���� halt ���� ���� 
*/
#define F_PANTECH_CAMERA_QBUG_FIX_STOP_CAPTURE  

/* user mode build�� ���� �α� ������ �ʵ��� featureó����. */
#ifdef FEATURE_AARM_RELEASE_MODE
#define F_PANTECH_CAMERA_ERASE_PREVIEW_LOGS
#endif

/*----------------------------------------------------------------------------*/
/*  MODEL-SPECIFIC CONSTANTS                                                  */
/*  ���� ���� ���� ����                                       */
/*----------------------------------------------------------------------------*/

/* camera select enum */
#define C_PANTECH_CAMERA_SELECT_MAIN_CAM 		0
#define C_PANTECH_CAMERA_SELECT_SUB_CAM 		1


/* ī�޶� ���� �ð��� �����ϱ� ���� ������ ���ϸ��̴�. */
#ifdef F_PANTECH_CAMERA_FACTORY_PROC_CMD
#define C_PANTECH_CAMERA_FNAME_FACTORY_PROC_CMD	"/data/.factorycamera.dat"
#endif


/* ���� ������ �ּ�/�ִ� ��Ŀ�� �����̴�. */
#ifdef F_PANTECH_CAMERA_FIX_CFG_FOCUS_STEP
#define C_PANTECH_CAMERA_MIN_FOCUS_STEP 0	/* ���Ѵ� (default) */
#define C_PANTECH_CAMERA_MAX_FOCUS_STEP 9	/* ��ũ�� */
#endif


/* ���� ������ �ּ�/�ִ� ���� �ܰ��̴�. */
#ifdef F_PANTECH_CAMERA_FIX_CFG_BRIGHTNESS
#define C_PANTECH_CAMERA_MIN_BRIGHTNESS 0	/* -4 */
#define C_PANTECH_CAMERA_MAX_BRIGHTNESS 8	/* +4 */
#endif


#ifdef F_PANTECH_CAMERA_OEM_EXIF_TAG
#define C_PANTECH_CAMERA_EXIF_MAKE		"PANTECH"
#define C_PANTECH_CAMERA_EXIF_MAKE_LEN		8		/* including NULL */
#ifdef F_PANTECH_CAMERA_TARGET_EF39S
#define C_PANTECH_CAMERA_EXIF_MODEL		"IM-A800S"
#define C_PANTECH_CAMERA_EXIF_MODEL_LEN		9		/* including NULL */
#endif
#ifdef F_PANTECH_CAMERA_TARGET_EF40S
#define C_PANTECH_CAMERA_EXIF_MODEL		"IM-EF40S"
#define C_PANTECH_CAMERA_EXIF_MODEL_LEN		9		/* including NULL */
#endif
#ifdef F_PANTECH_CAMERA_TARGET_EF40K
#define C_PANTECH_CAMERA_EXIF_MODEL		"IM-EF40K"
#define C_PANTECH_CAMERA_EXIF_MODEL_LEN		9		/* including NULL */
#endif
#ifdef F_PANTECH_CAMERA_TARGET_PRESTO
#define C_PANTECH_CAMERA_EXIF_MODEL		"PRESTO"
#define C_PANTECH_CAMERA_EXIF_MODEL_LEN		7		/* including NULL */
#endif
#ifdef F_PANTECH_CAMERA_TARGET_EF45K
#define C_PANTECH_CAMERA_EXIF_MODEL		"IM-A830K"
#define C_PANTECH_CAMERA_EXIF_MODEL_LEN		9		/* including NULL */
#endif
#ifdef F_PANTECH_CAMERA_TARGET_EF45KV
#define C_PANTECH_CAMERA_EXIF_MODEL		"IM-A830KE"
#define C_PANTECH_CAMERA_EXIF_MODEL_LEN		10		/* including NULL */
#endif
#ifdef F_PANTECH_CAMERA_TARGET_EF46L
#define C_PANTECH_CAMERA_EXIF_MODEL		"IM-A830L"
#define C_PANTECH_CAMERA_EXIF_MODEL_LEN		9		/* including NULL */
#endif
#ifdef F_PANTECH_CAMERA_TARGET_EF47S
#define C_PANTECH_CAMERA_EXIF_MODEL		"IM-A830S"
#define C_PANTECH_CAMERA_EXIF_MODEL_LEN		9		/* including NULL */
#endif
#ifdef F_PANTECH_CAMERA_TARGET_SVLTE
#define C_PANTECH_CAMERA_EXIF_MODEL		"SVLTE"
#define C_PANTECH_CAMERA_EXIF_MODEL_LEN		6		/* including NULL */
#endif
#ifdef F_PANTECH_CAMERA_TARGET_CSFB
#define C_PANTECH_CAMERA_EXIF_MODEL		"CSFB"
#define C_PANTECH_CAMERA_EXIF_MODEL_LEN		5		/* including NULL */
#endif
#ifdef F_PANTECH_CAMERA_TARGET_CHEETAH
#define C_PANTECH_CAMERA_EXIF_MODEL		"CHEETAH"
#define C_PANTECH_CAMERA_EXIF_MODEL_LEN		8		/* including NULL */
#endif
#ifdef F_PANTECH_CAMERA_TARGET_STARQ
#define C_PANTECH_CAMERA_EXIF_MODEL		"ADR910L"
#define C_PANTECH_CAMERA_EXIF_MODEL_LEN		8		/* including NULL */
#endif
#ifdef F_PANTECH_CAMERA_TARGET_OSCAR
#define C_PANTECH_CAMERA_EXIF_MODEL		"P8010"
#define C_PANTECH_CAMERA_EXIF_MODEL_LEN		6		/* including NULL */
#endif
#ifdef F_PANTECH_CAMERA_TARGET_VEGAPVW
#define C_PANTECH_CAMERA_EXIF_MODEL		"VEGAPVW"
#define C_PANTECH_CAMERA_EXIF_MODEL_LEN		8		/* including NULL */
#endif
#ifdef F_PANTECH_CAMERA_TARGET_ZEPPLIN
#define C_PANTECH_CAMERA_EXIF_MODEL		"ZEPPLIN"
#define C_PANTECH_CAMERA_EXIF_MODEL_LEN		8		/* including NULL */
#endif
#ifdef F_PANTECH_CAMERA_TARGET_VEGAPKDDI
#define C_PANTECH_CAMERA_EXIF_MODEL		"VEGAPKDDI"
#define C_PANTECH_CAMERA_EXIF_MODEL_LEN		10		/* including NULL */
#endif
#endif


/* ������ ������ ������ ����, ���� ������ FPS �� �ּ�/�ִ� ���̴�. */
#ifdef F_PANTECH_CAMERA_FIX_CFG_PREVIEW_FPS
/*
#define C_PANTECH_CAMERA_MIN_PREVIEW_FPS	5
#define C_PANTECH_CAMERA_MAX_PREVIEW_FPS	30
*/
#endif

#endif /* F_PANTECH_CAMERA */

#endif /* CUST_PANTECH_CAMERA.h */




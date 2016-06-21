/* Copyright (c) 2011, Code Aurora Forum. All rights reserved.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 and
 * only version 2 as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 */

#include "msm_sensor.h"
#include <linux/regulator/machine.h> 
#include "sensor_ctrl.h"
#include "sensor_i2c.h"

#include "msm_camera_i2c.h"
#include "msm.h"
#include "msm_ispif.h"


#define SENSOR_NAME "mt9v113"
#define PLATFORM_DRIVER_NAME "msm_camera_mt9v113"
#define mt9v113_obj mt9v113_##obj

/*=============================================================
	SENSOR REGISTER DEFINES
==============================================================*/
#define SI2C_SA	(0x78>>1)
extern si2c_const_param_t mt9v113_const_params[SI2C_PID_MAX];
static si2c_param_t mt9v113_params[SI2C_PID_MAX];


#define F_MT9V113_POWER

#ifdef F_MT9V113_POWER

#define CAMIO_RST_N	0
#define CAMIO_STB_N	1
#define CAMV_CORE_1P8V	2
#define CAMV_A_2P8V 3
#define CAMIO_MAX	4

static sgpio_ctrl_t sgpios[CAMIO_MAX] = {
	{CAMIO_RST_N, "CAM_RST_N", 76},
	{CAMIO_STB_N, "CAM_STB_N", 52},
	{CAMV_CORE_1P8V, "CAMV_CORE_1P8V", 96},
	{CAMV_A_2P8V, "CAMV_A_2P8V", 98},			
};

#define CAMV_IO_1P8V	0
#define CAMV_MAX	1

static svreg_ctrl_t svregs[CAMV_MAX] = {
	{CAMV_IO_1P8V, "8921_lvs5", NULL, 0}, /* I2C pull-up */	
};
#endif

DEFINE_MUTEX(mt9v113_mut);
static struct msm_sensor_ctrl_t mt9v113_s_ctrl;

static struct v4l2_subdev_info mt9v113_subdev_info[] = {
	{
	.code   = V4L2_MBUS_FMT_YUYV8_2X8,
	.colorspace = V4L2_COLORSPACE_JPEG,
	.fmt    = 1,
	.order    = 0,
	},
	/* more can be supported, to be added later */
};

#define MT9V113_FULL_SIZE_DUMMY_PIXELS     0
#define MT9V113_FULL_SIZE_DUMMY_LINES    0
#define MT9V113_FULL_SIZE_WIDTH    640 
#define MT9V113_FULL_SIZE_HEIGHT   480 

#define MT9V113_QTR_SIZE_DUMMY_PIXELS  0
#define MT9V113_QTR_SIZE_DUMMY_LINES   0
#define MT9V113_QTR_SIZE_WIDTH     640 
#define MT9V113_QTR_SIZE_HEIGHT    480 

#define MT9V113_HRZ_FULL_BLK_PIXELS   0
#define MT9V113_VER_FULL_BLK_LINES     0
#define MT9V113_HRZ_QTR_BLK_PIXELS    0
#define MT9V113_VER_QTR_BLK_LINES      0

static int sensor_mode = SENSOR_PREVIEW_MODE;


static struct msm_sensor_output_info_t mt9v113_dimensions[] = {
	{
		.x_output = MT9V113_FULL_SIZE_WIDTH, 
		.y_output = MT9V113_FULL_SIZE_HEIGHT,
		.line_length_pclk = MT9V113_FULL_SIZE_WIDTH + MT9V113_HRZ_FULL_BLK_PIXELS ,
		.frame_length_lines = MT9V113_FULL_SIZE_HEIGHT+ MT9V113_VER_FULL_BLK_LINES ,
		.vt_pixel_clk = 60000000,
		.op_pixel_clk = 60000000,	
		.binning_factor = 1,
	},
	{
		.x_output = MT9V113_QTR_SIZE_WIDTH,
		.y_output = MT9V113_QTR_SIZE_HEIGHT,
		.line_length_pclk = MT9V113_QTR_SIZE_WIDTH + MT9V113_HRZ_QTR_BLK_PIXELS,
		.frame_length_lines = MT9V113_QTR_SIZE_HEIGHT+ MT9V113_VER_QTR_BLK_LINES,
		.vt_pixel_clk = 60000000,
		.op_pixel_clk = 60000000,			
		.binning_factor = 1,
	},
	{
		.x_output = MT9V113_QTR_SIZE_WIDTH,
		.y_output = MT9V113_QTR_SIZE_HEIGHT,
		.line_length_pclk = MT9V113_QTR_SIZE_WIDTH + MT9V113_HRZ_QTR_BLK_PIXELS,
		.frame_length_lines = MT9V113_QTR_SIZE_HEIGHT+ MT9V113_VER_QTR_BLK_LINES,
		.vt_pixel_clk = 60000000,
		.op_pixel_clk = 60000000,			
		.binning_factor = 1,
	},
	{
		.x_output = MT9V113_QTR_SIZE_WIDTH,
		.y_output = MT9V113_QTR_SIZE_HEIGHT,
		.line_length_pclk = MT9V113_QTR_SIZE_WIDTH + MT9V113_HRZ_QTR_BLK_PIXELS,
		.frame_length_lines = MT9V113_QTR_SIZE_HEIGHT+ MT9V113_VER_QTR_BLK_LINES,
		.vt_pixel_clk = 60000000,
		.op_pixel_clk = 60000000,			
		.binning_factor = 1,
	},	
};

static struct msm_camera_csid_vc_cfg mt9v113_cid_cfg[] = {
	{0, 0x1E, CSI_DECODE_8BIT}, 
	{1, CSI_EMBED_DATA, CSI_DECODE_8BIT},	
	{2, CSI_RESERVED_DATA, CSI_DECODE_8BIT},
	{3, CSI_RESERVED_DATA, CSI_DECODE_8BIT},		
};

static struct msm_camera_csi2_params mt9v113_csi_params = {
	.csid_params = {
		//.lane_assign = 0xe4,
		.lane_cnt = 1,
		.lut_params = {
			.num_cid = 2,
			.vc_cfg = mt9v113_cid_cfg,
		},
	},
	.csiphy_params = {
		.lane_cnt = 1,
		.settle_cnt = 0x11,
		.lane_mask = 0x1,		
	},
};

static struct msm_camera_csi2_params *mt9v113_csi_params_array[] = {
	&mt9v113_csi_params,
	&mt9v113_csi_params,
	&mt9v113_csi_params,
	&mt9v113_csi_params,	
};

static struct msm_sensor_id_info_t mt9v113_id_info = {
	.sensor_id_reg_addr = 0,
	.sensor_id = 0,
};

static const struct i2c_device_id mt9v113_i2c_id[] = {
	{SENSOR_NAME, (kernel_ulong_t)&mt9v113_s_ctrl},
	{ }
};

static struct i2c_driver mt9v113_i2c_driver = {
	.id_table = mt9v113_i2c_id,
	.probe  = msm_sensor_i2c_probe,
	.driver = {
		.name = SENSOR_NAME,
	},
};

#ifdef F_MT9V113_POWER
int32_t mt9v113_sensor_power_up(struct msm_sensor_ctrl_t *s_ctrl)
{
	int32_t rc = 0;

	SKYCDBG("%s E\n", __func__);

#if 0 // 1031 tmp block
	msm_sensor_probe_on(&s_ctrl->sensor_i2c_client->client->dev);  
	SKYCDBG("%s msm_sensor_probe_on ok\n", __func__);
	msm_camio_clk_rate_set(MSM_SENSOR_MCLK_24HZ);
	SKYCDBG("%s msm_camio_clk_rate_set ok\n", __func__);
#else
    rc = msm_sensor_power_up(s_ctrl);
    SKYCDBG(" %s : msm_sensor_power_up : rc = %d E\n",__func__, rc);  
#endif

	rc = sgpio_init(sgpios, CAMIO_MAX);
	if (rc < 0)
		goto sensor_init_fail;

	rc = svreg_init(svregs, CAMV_MAX);
	if (rc < 0)
		goto sensor_init_fail;

	if (sgpio_ctrl(sgpios, CAMIO_STB_N, 0) < 0)	rc = -EIO;
	if (sgpio_ctrl(sgpios, CAMIO_RST_N, 1) < 0)	rc = -EIO;
	mdelay(1);

	if (svreg_ctrl(svregs, CAMV_IO_1P8V, 1) < 0)	rc = -EIO;
	mdelay(1); /* > 1ms */
	
	if (sgpio_ctrl(sgpios, CAMV_A_2P8V, 1) < 0)	rc = -EIO;	
	mdelay(1);

	if (sgpio_ctrl(sgpios, CAMV_CORE_1P8V, 1) < 0)	rc = -EIO;
	mdelay(1);	

	if (sgpio_ctrl(sgpios, CAMIO_RST_N, 0) < 0)	rc = -EIO;
	mdelay(1); /* > 10 clks (approx. 0.42us) */
	if (sgpio_ctrl(sgpios, CAMIO_RST_N, 1) < 0)	rc = -EIO;
	mdelay(1); /* > 1 clk (apporx. 0.042us) */
	
	msleep(100); /* 500ms PANTECH_CAMERA_TODO */
	//msm_camio_clk_rate_set(24000000);
	msleep(10);

	SKYCDBG("%s X (%d)\n", __func__, rc);
	return rc;
   
sensor_init_fail:
	/*PANTECH_CAMERA_TODO, check correct timing, spec don't have off seq. */
	if (sgpio_ctrl(sgpios, CAMIO_STB_N, 0) < 0)	rc = -EIO;
	if (sgpio_ctrl(sgpios, CAMIO_RST_N, 0) < 0)	rc = -EIO;
	mdelay(1);
	
	if (svreg_ctrl(svregs, CAMV_IO_1P8V, 0) < 0)	rc = -EIO;		
	if (sgpio_ctrl(sgpios, CAMV_CORE_1P8V, 0) < 0)	rc = -EIO;

	if (sgpio_ctrl(sgpios, CAMV_A_2P8V, 0) < 0)	rc = -EIO;	
	mdelay(1);

	svreg_release(svregs, CAMV_MAX);
	sgpio_release(sgpios, CAMIO_MAX);
	return rc;   		
}


int32_t mt9v113_sensor_power_down(struct msm_sensor_ctrl_t *s_ctrl)
{
	int32_t rc = 0;

	SKYCDBG("%s E\n", __func__);
#if 0//1031 tmp block 
	msm_sensor_probe_off(&s_ctrl->sensor_i2c_client->client->dev); 
#else
    msm_sensor_power_down(s_ctrl);
    SKYCDBG(" %s : msm_sensor_power_down : rc = %d E\n",__func__, rc);  
#endif

	/*PANTECH_CAMERA_TODO, check correct timing, spec don't have off seq. */
	if (sgpio_ctrl(sgpios, CAMIO_STB_N, 0) < 0)	rc = -EIO;
	if (sgpio_ctrl(sgpios, CAMIO_RST_N, 0) < 0)	rc = -EIO;
	mdelay(1);
	
	if (svreg_ctrl(svregs, CAMV_IO_1P8V, 0) < 0)	rc = -EIO;		
	if (sgpio_ctrl(sgpios, CAMV_CORE_1P8V, 0) < 0)	rc = -EIO;

	if (sgpio_ctrl(sgpios, CAMV_A_2P8V, 0) < 0)	rc = -EIO;	
	mdelay(1);

	svreg_release(svregs, CAMV_MAX);
	sgpio_release(sgpios, CAMIO_MAX);
	si2c_release();

	SKYCDBG("%s X (%d)\n", __func__, rc);
	return rc;		
}	
#endif


int mt9v113_sensor_init(struct msm_sensor_ctrl_t *s_ctrl)
{
	int rc = 0;

	sensor_mode = SENSOR_PREVIEW_MODE;
	memset(mt9v113_params, 0, sizeof(mt9v113_params));
	
	rc = si2c_init(s_ctrl->sensor_i2c_client->client->adapter, mt9v113_const_params, mt9v113_params);
	if (rc < 0) {
		SKYCDBG("%s err(%d)\n", __func__, rc);
		si2c_release();		
		return rc;
	}	
	
	rc = si2c_write_param(SI2C_SA, SI2C_INIT, mt9v113_params);
	if (rc < 0) {
		SKYCDBG("%s err(%d)\n", __func__, rc);
		si2c_release();		
		return rc;
	}	
	
	return rc;	
}


void mt9v113_sensor_start_stream(struct msm_sensor_ctrl_t *s_ctrl)
{
	SKYCDBG("%s: %d\n", __func__, __LINE__);
}


void mt9v113_sensor_stop_stream(struct msm_sensor_ctrl_t *s_ctrl)
{
	SKYCDBG("%s: %d\n", __func__, __LINE__);
}


int mt9v113_video_config(struct msm_sensor_ctrl_t *s_ctr)
{
	int rc = 0;

	CDBG("%s sensor_mode=%d E\n", __func__, sensor_mode);

//	if (sensor_mode != SENSOR_PREVIEW_MODE)
	{
		rc = si2c_write_param(SI2C_SA, SI2C_PREVIEW, mt9v113_params);
		if (rc < 0) {
			SKYCERR("%s err(%d)\n", __func__, rc);
			return rc;
		}
		sensor_mode = SENSOR_PREVIEW_MODE;
	}
	
	CDBG("%s X\n", __func__);
	return 0;
}


int mt9v113_snapshot_config(struct msm_sensor_ctrl_t *s_ctr)
{
	int rc = 0;

	CDBG("%s sensor_mode=%d E\n", __func__, sensor_mode);

//	if (sensor_mode != SENSOR_SNAPSHOT_MODE)
	{
		rc = si2c_write_param(SI2C_SA, SI2C_SNAPSHOT, mt9v113_params);
		if (rc < 0) {
			SKYCERR("%s err(%d)\n", __func__, rc);
			return rc;
		}
		sensor_mode = SENSOR_SNAPSHOT_MODE;
	}
	
	CDBG("%s X\n", __func__);
	return 0;
}

int mt9v113_zsl_config(struct msm_sensor_ctrl_t *s_ctr)
{
	int rc = 0;

	CDBG("%s sensor_mode=%d E\n", __func__, sensor_mode);

//	if (sensor_mode != SENSOR_ZSL_MODE)
	{
		rc = si2c_write_param(SI2C_SA, SI2C_PREVIEW, mt9v113_params);
		if (rc < 0) {
			SKYCERR("%s err(%d)\n", __func__, rc);
			return rc;
		}
		sensor_mode = SENSOR_ZSL_MODE;
	}
	
	CDBG("%s X\n", __func__);
	return 0;
}


int32_t mt9v113_sensor_setting(struct msm_sensor_ctrl_t *s_ctrl,
			int update_type, int res)
{
	int32_t rc = 0;

	SKYCDBG("%s:[F_PANTECH_CAMERA] %d, %d res=%d\n", __func__, __LINE__,update_type,res);
	
//	if(res != 0)
//		s_ctrl->func_tbl->sensor_stop_stream(s_ctrl);
//	else if(update_type == MSM_SENSOR_UPDATE_PERIODIC)
//	{
//		s5k4ecgx_snapshot_config();
//		sensor_mode = SENSOR_SNAPSHOT_MODE;
//	}

	msleep(30);
	if (update_type == MSM_SENSOR_REG_INIT) {
		SKYCDBG("%s:[F_PANTECH_CAMERA] ==> MSM_SENSOR_REG_INIT  %d\n", __func__, update_type);  
		
		s_ctrl->curr_csi_params = NULL;       
		msm_sensor_enable_debugfs(s_ctrl);
		mt9v113_sensor_init(s_ctrl);
	} else if (update_type == MSM_SENSOR_UPDATE_PERIODIC) {	
//    msm_sensor_write_res_settings(s_ctrl, res);
		
		if (s_ctrl->curr_csi_params != s_ctrl->csi_params[res]) {
			SKYCDBG("%s:[F_PANTECH_CAMERA] ==> MIPI setting  E %d\n", __func__, update_type);
			s_ctrl->curr_csi_params = s_ctrl->csi_params[res];			
			s_ctrl->curr_csi_params->csid_params.lane_assign =
				s_ctrl->sensordata->sensor_platform_info->
				csi_lane_params->csi_lane_assign;		
			s_ctrl->curr_csi_params->csiphy_params.lane_mask =
				s_ctrl->sensordata->sensor_platform_info->
				csi_lane_params->csi_lane_mask;
			v4l2_subdev_notify(&s_ctrl->sensor_v4l2_subdev,
				NOTIFY_CSID_CFG,
				&s_ctrl->curr_csi_params->csid_params);
			mb();
			v4l2_subdev_notify(&s_ctrl->sensor_v4l2_subdev,
				NOTIFY_CSIPHY_CFG,
				&s_ctrl->curr_csi_params->csiphy_params);
			mb();
			msleep(20);
			SKYCDBG("%s:[F_PANTECH_CAMERA] ==> MIPI setting  X %d\n", __func__, update_type);			
		}

		v4l2_subdev_notify(&s_ctrl->sensor_v4l2_subdev,
			NOTIFY_PCLK_CHANGE, &s_ctrl->msm_sensor_reg->
			output_settings[res].op_pixel_clk);

#if 0		
		if (s_ctrl->func_tbl->sensor_start_stream) {
			s_ctrl->func_tbl->sensor_start_stream(s_ctrl);
		}
#else
		switch (res) {
		case 0:
 		    rc = mt9v113_snapshot_config(s_ctrl);	
			 break;
		case 1:
			 rc = mt9v113_video_config(s_ctrl);	
			 break;
		case 2: 
			 rc = mt9v113_video_config(s_ctrl);	
			 break;
		case 3: 
			 rc = mt9v113_zsl_config(s_ctrl); 
			 break;
		default:
			 rc = mt9v113_video_config(s_ctrl);	
			 SKYCDBG("%s fail res=%d\n", __func__, res);
			 break;
		}
		//sensor_mode = res;
		//msleep(150);//msleep(30);
#endif
	}
	SKYCDBG("%s: %d x\n", __func__, __LINE__);
	return rc;
}


#if 1//def F_PANTECH_CAMERA_FIX_CFG_BRIGHTNESS
int mt9v113_sensor_brightness(struct msm_sensor_ctrl_t *s_ctrl, int8_t brightness)
{
	si2c_pid_t pid = SI2C_PID_MAX;
	int rc = 0;

	SKYCDBG("%s brightness=%d\n", __func__, brightness);

	switch (brightness) {
	case 0: pid = SI2C_BRIGHTNESS_M4; break;
	case 1: pid = SI2C_BRIGHTNESS_M3; break;
	case 2: pid = SI2C_BRIGHTNESS_M2; break;
	case 3: pid = SI2C_BRIGHTNESS_M1; break;
	case 4: pid = SI2C_BRIGHTNESS_0; break;
	case 5: pid = SI2C_BRIGHTNESS_P1; break;
	case 6: pid = SI2C_BRIGHTNESS_P2; break;
	case 7: pid = SI2C_BRIGHTNESS_P3; break;
	case 8: pid = SI2C_BRIGHTNESS_P4; break;
	default:
		SKYCDBG("%s err(-EINVAL)\n", __func__);
		return -EINVAL;
	}

	rc = si2c_write_param(SI2C_SA, pid, mt9v113_params);
	if (rc < 0) {
		SKYCDBG("%s err(%d)\n", __func__, rc);
		return rc;
	}

	SKYCDBG("%s X\n", __func__);
	return 0;

}
#endif


#if 1//def F_PANTECH_CAMERA_FIX_CFG_EFFECT
int mt9v113_sensor_effect(struct msm_sensor_ctrl_t *s_ctrl, int8_t effect)
{
	si2c_pid_t pid = SI2C_PID_MAX;
	int rc = 0;

	SKYCDBG("%s effect=%d\n", __func__, effect);

	switch (effect) {
	case 0: pid = SI2C_EFFECT_OFF; break;
	case 1: pid = SI2C_EFFECT_MONO; break;
	case 2: pid = SI2C_EFFECT_NEGATIVE; break;
	case 3: pid = SI2C_EFFECT_SOLARIZE; break;
	case 4: pid = SI2C_EFFECT_SEPIA; break;
	default:
		SKYCDBG("%s err(-EINVAL)\n", __func__);
		return -EINVAL;
	}

	rc = si2c_write_param(SI2C_SA, pid, mt9v113_params);
	if (rc < 0) {
		SKYCDBG("%s err(%d)\n", __func__, rc);
		return rc;
	}

	SKYCDBG("%s X\n", __func__);
	return 0;

}
#endif


#if 1//def F_PANTECH_CAMERA_FIX_CFG_WB
int mt9v113_sensor_wb(struct msm_sensor_ctrl_t *s_ctrl, int8_t wb)
{
	si2c_pid_t pid = SI2C_PID_MAX;
	int rc = 0;

	SKYCDBG("%s wb=%d\n", __func__, wb);

	switch (wb) {
	case 1: pid = SI2C_WB_AUTO; break;
	case 3: pid = SI2C_WB_INCANDESCENT; break;
	case 4: pid = SI2C_WB_FLUORESCENT; break;
	case 5: pid = SI2C_WB_DAYLIGHT; break;
	case 6: pid = SI2C_WB_CLOUDY; break;
	default:
		SKYCDBG("%s err(-EINVAL)\n", __func__);
		return -EINVAL;
	}

	rc = si2c_write_param(SI2C_SA, pid, mt9v113_params);
	if (rc < 0) {
		SKYCDBG("%s err(%d)\n", __func__, rc);
		return rc;
	}

	SKYCDBG("%s X\n", __func__);
	return 0;

}
#endif


#if 1//def F_PANTECH_CAMERA_FIX_CFG_PREVIEW_FPS
int mt9v113_sensor_preview_fps(struct msm_sensor_ctrl_t *s_ctrl, int8_t preview_fps)
{
	si2c_pid_t pid = SI2C_PID_MAX;
	int rc = 0;

	SKYCDBG("%s preview_fps=%d\n", __func__, preview_fps);

	switch (preview_fps) {
	case  0: pid = SI2C_FPS_VARIABLE; break;
	case  7: pid = SI2C_FPS_FIXED7; break;
	case  8: pid = SI2C_FPS_FIXED8; break;
	case 10: pid = SI2C_FPS_FIXED10; break;
	case 15: pid = SI2C_FPS_FIXED15; break;
	case 20: pid = SI2C_FPS_FIXED15; break;
	case 30: pid = SI2C_FPS_FIXED15; break;
	case 31: pid = SI2C_FPS_VARIABLE; break;
	default:
		//PANTECH_CAMERA_TODO
		return 0;
		//SKYCERR("%s err(-EINVAL)\n", __func__);
		//return -EINVAL;
	}

	rc = si2c_write_param(SI2C_SA, pid, mt9v113_params);
	if (rc < 0) {
		SKYCDBG("%s err(%d)\n", __func__, rc);
		return rc;
	}

	SKYCDBG("%s X\n", __func__);
	return 0;
}
#endif

#if 1//def F_PANTECH_CAMERA_FIX_CFG_EXPOSURE
int mt9v113_sensor_exposure(struct msm_sensor_ctrl_t *s_ctrl, int8_t exposure)
{
	si2c_pid_t pid = SI2C_PID_MAX;
	int rc = 0;

	SKYCDBG("%s exposure=%d\n", __func__, exposure);

	switch (exposure) {
	case 0: 		
	case 1: pid = SI2C_EXPOSURE_AVERAGE; break;	
	case 2: 
	case 3: pid = SI2C_EXPOSURE_CENTER; break;
	default:
		SKYCDBG("%s err(-EINVAL)\n", __func__);
		return -EINVAL;
	}

	rc = si2c_write_param(SI2C_SA, pid, mt9v113_params);
	if (rc < 0) {
		SKYCDBG("%s err(%d)\n", __func__, rc);
		return rc;
	}

	SKYCDBG("%s X\n", __func__);
	return 0;
}
#endif

#if 1//def F_PANTECH_CAMERA_FIX_CFG_REFLECT
static int mt9v113_sensor_reflect(struct msm_sensor_ctrl_t *s_ctrl ,int8_t reflect)
{
	si2c_pid_t pid = SI2C_PID_MAX;
	int rc = 0;

	SKYCDBG("%s reflect=%d\n", __func__, reflect);

	switch (reflect) {
	case 0: pid = SI2C_REFLECT_OFF; break;
	case 1: pid = SI2C_REFLECT_MIRROR; break;
	case 2: pid = SI2C_REFLECT_WATER; break;
	case 3: pid = SI2C_REFLECT_MIRROR_WATER; break;
	default:
		SKYCDBG("%s err(-EINVAL)\n", __func__);
		return -EINVAL;
	}

	rc = si2c_write_param(SI2C_SA, pid, mt9v113_params);
	if (rc < 0) {
		SKYCDBG("%s err(%d)\n", __func__, rc);
		return rc;
	}

	SKYCDBG("%s X\n", __func__);
	return 0;

}
#endif

static int __init msm_sensor_init_module(void)
{
	return i2c_add_driver(&mt9v113_i2c_driver);
}

static struct v4l2_subdev_core_ops mt9v113_subdev_core_ops = {
	.ioctl = msm_sensor_subdev_ioctl,
	.s_power = msm_sensor_power,
};

static struct msm_camera_i2c_client mt9v113_sensor_i2c_client = {
	.addr_type = MSM_CAMERA_I2C_WORD_ADDR,
};
static struct v4l2_subdev_video_ops mt9v113_subdev_video_ops = {
	.enum_mbus_fmt = msm_sensor_v4l2_enum_fmt,
};

static struct v4l2_subdev_ops mt9v113_subdev_ops = {
	.core = &mt9v113_subdev_core_ops,
	.video  = &mt9v113_subdev_video_ops,
};

static struct msm_sensor_fn_t mt9v113_func_tbl = {
	.sensor_start_stream = msm_sensor_start_stream,
	.sensor_stop_stream = msm_sensor_stop_stream,
#if 0		
	.sensor_get_pict_fps = msm_sensor_get_pict_fps,
#endif		
	.sensor_setting = mt9v113_sensor_setting,
	.sensor_set_sensor_mode = msm_sensor_set_sensor_mode,
	.sensor_mode_init = msm_sensor_mode_init,
	.sensor_get_output_info = msm_sensor_get_output_info,
	.sensor_config = msm_sensor_config,
#ifdef F_MT9V113_POWER
	.sensor_power_up = mt9v113_sensor_power_up,
	.sensor_power_down = mt9v113_sensor_power_down,
#else
    .sensor_power_up = msm_sensor_power_up,
    .sensor_power_down = msm_sensor_power_down,
#endif
#if 1//def F_PANTECH_CAMERA_FIX_CFG_BRIGHTNESS
    .sensor_set_brightness = mt9v113_sensor_brightness,
#endif    
#if 1//def F_PANTECH_CAMERA_FIX_CFG_EFFECT    
    .sensor_set_effect = mt9v113_sensor_effect,
#endif    
#if 1//def F_PANTECH_CAMERA_FIX_CFG_WB    
    .sensor_set_wb = mt9v113_sensor_wb,
#endif
#if 1//def F_PANTECH_CAMERA_FIX_CFG_EXPOSURE
	.sensor_set_exposure_mode = mt9v113_sensor_exposure,
#endif
#if 1//def F_PANTECH_CAMERA_FIX_CFG_PREVIEW_FPS
	.sensor_set_preview_fps = mt9v113_sensor_preview_fps,
#endif
#if 1//def F_PANTECH_CAMERA_FIX_CFG_REFLECT
	.sensor_set_reflect = mt9v113_sensor_reflect,	 
#endif
	.sensor_get_csi_params = msm_sensor_get_csi_params,
};

static struct msm_sensor_reg_t mt9v113_regs = {
	.default_data_type = MSM_CAMERA_I2C_WORD_DATA,
#if 0
	.start_stream_conf = mt9v113_start_settings,
	.start_stream_conf_size = ARRAY_SIZE(mt9v113_start_settings),
	.stop_stream_conf = mt9v113_stop_settings,
	.stop_stream_conf_size = ARRAY_SIZE(mt9v113_stop_settings),
#endif
#if 0
	.group_hold_on_conf = mt9v113_groupon_settings,
	.group_hold_on_conf_size = ARRAY_SIZE(mt9v113_groupon_settings),
	.group_hold_off_conf = mt9v113_groupoff_settings,
	.group_hold_off_conf_size =
		ARRAY_SIZE(mt9v113_groupoff_settings),
#endif
	.init_settings = NULL, //&mt9v113_init_conf[0],
	.init_size = 0, //ARRAY_SIZE(mt9v113_init_conf),
	.mode_settings = NULL, //mt9v113_confs[0],
	.output_settings = &mt9v113_dimensions[0],
	.num_conf = ARRAY_SIZE(mt9v113_cid_cfg),	
};

static struct msm_sensor_ctrl_t mt9v113_s_ctrl = {
	.msm_sensor_reg = &mt9v113_regs,
	.sensor_i2c_client = &mt9v113_sensor_i2c_client,
	.sensor_i2c_addr = 0x78,
	.sensor_id_info = &mt9v113_id_info,
	.cam_mode = MSM_SENSOR_MODE_INVALID,
	.csi_params = &mt9v113_csi_params_array[0],
	.msm_sensor_mutex = &mt9v113_mut,
	.sensor_i2c_driver = &mt9v113_i2c_driver,
	.sensor_v4l2_subdev_info = mt9v113_subdev_info,
	.sensor_v4l2_subdev_info_size = ARRAY_SIZE(mt9v113_subdev_info),
	.sensor_v4l2_subdev_ops = &mt9v113_subdev_ops,
	.func_tbl = &mt9v113_func_tbl,
	.clk_rate = MSM_SENSOR_MCLK_24HZ,
};

module_init(msm_sensor_init_module);
MODULE_DESCRIPTION("Aptina VGA  YUV Sensor driver");
MODULE_LICENSE("GPL v2");

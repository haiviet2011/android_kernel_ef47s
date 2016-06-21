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


#define SENSOR_NAME "s5k4ecgx"
#define PLATFORM_DRIVER_NAME "msm_camera_s5k4ecgx"
#define s5k4ecgx_obj s5k4ecgx_##obj

#define SKYCDBG2(fmt, args...) printk(KERN_INFO "SKYCDBG: " fmt, ##args)
#define SKYCERR2(fmt, args...) printk(KERN_ERR "SKYCERR: " fmt, ##args)


/*=============================================================
	SENSOR REGISTER DEFINES
==============================================================*/
/* Sensor Model ID */
#define SI2C_SA	(0x5A>>1)
extern si2c_const_param_t s5k4ecgx_const_params[SI2C_PID_MAX];
static si2c_param_t s5k4ecgx_params[SI2C_PID_MAX];


#define F_S5K4ECGX_POWER
#define F_MT9V113_POWER
#undef F_130M_ZSL //charley2

#ifdef F_S5K4ECGX_POWER

#define CAMIO_R_RST_N		0
#define F_CAMIO_RST_N	1
#define F_CAMIO_STB_N	2
#define F_CAMV_CORE_1P8V	3
#define F_CAMV_A_2P8V 4
#define CAMIO_MAX	5

static sgpio_ctrl_t sgpios[CAMIO_MAX] = {
	{CAMIO_R_RST_N,   "CAMIO_R_RST_N",  107},	
	{F_CAMIO_RST_N, "CAM_RST_N", 76},
	{F_CAMIO_STB_N, "CAM_STB_N", 52},
	{F_CAMV_CORE_1P8V, "CAMV_CORE_1P8V", 96},
	{F_CAMV_A_2P8V, "CAMV_A_2P8V", 98},			
};

#define CAMV_IO_1P8V	0
#define CAMV_CORE_1P2V	1
#define CAMV_A_2P8V	2
#define CAMV_AF_2P8V	3
#define CAMV_MAX	4

static svreg_ctrl_t svregs[CAMV_MAX] = {
	{CAMV_IO_1P8V,   "8921_lvs5", NULL, 0},
	{CAMV_CORE_1P2V, "8921_l12",   NULL, 1200},
	{CAMV_A_2P8V,    "8921_l11",  NULL, 2800},
	{CAMV_AF_2P8V,   "8921_l16",   NULL, 2800},
};

#endif

DEFINE_MUTEX(s5k4ecgx_mut);
static struct msm_sensor_ctrl_t s5k4ecgx_s_ctrl;

static struct v4l2_subdev_info s5k4ecgx_subdev_info[] = {
	{
	.code   = V4L2_MBUS_FMT_YUYV8_2X8,
	.colorspace = V4L2_COLORSPACE_JPEG,
	.fmt    = 1,
	.order    = 0,
	},
	/* more can be supported, to be added later */
};

#define S5K4ECGX_FULL_SIZE_DUMMY_PIXELS     0
#define S5K4ECGX_FULL_SIZE_DUMMY_LINES    0
#define S5K4ECGX_FULL_SIZE_WIDTH    2560 
#define S5K4ECGX_FULL_SIZE_HEIGHT   1920 

#define S5K4ECGX_QTR_SIZE_DUMMY_PIXELS  0
#define S5K4ECGX_QTR_SIZE_DUMMY_LINES   0
#define S5K4ECGX_QTR_SIZE_WIDTH     1280 
#define S5K4ECGX_QTR_SIZE_HEIGHT    960 

#define S5K4ECGX_HRZ_FULL_BLK_PIXELS   0
#define S5K4ECGX_VER_FULL_BLK_LINES     0
#define S5K4ECGX_HRZ_QTR_BLK_PIXELS    0
#define S5K4ECGX_VER_QTR_BLK_LINES      0

#define S5K4ECGX_ZSL_SIZE_WIDTH    2560 
#define S5K4ECGX_ZSL_SIZE_HEIGHT   1920 

static int8_t sensor_mode = -1;   			// 0: full size,  1: qtr size, 2: fullhd size, 3: ZSL


static struct msm_sensor_output_info_t s5k4ecgx_dimensions[] = {
	{
		.x_output = S5K4ECGX_FULL_SIZE_WIDTH, 
		.y_output = S5K4ECGX_FULL_SIZE_HEIGHT,
		.line_length_pclk = S5K4ECGX_FULL_SIZE_WIDTH + S5K4ECGX_HRZ_FULL_BLK_PIXELS ,
		.frame_length_lines = S5K4ECGX_FULL_SIZE_HEIGHT+ S5K4ECGX_VER_FULL_BLK_LINES ,
		.vt_pixel_clk = 256000000,
		.op_pixel_clk = 256000000,
		.binning_factor = 1,
	},
	{
		.x_output = S5K4ECGX_QTR_SIZE_WIDTH,
		.y_output = S5K4ECGX_QTR_SIZE_HEIGHT,
		.line_length_pclk = S5K4ECGX_QTR_SIZE_WIDTH + S5K4ECGX_HRZ_QTR_BLK_PIXELS,
		.frame_length_lines = S5K4ECGX_QTR_SIZE_HEIGHT+ S5K4ECGX_VER_QTR_BLK_LINES,
		.vt_pixel_clk = 256000000,
		.op_pixel_clk = 256000000,
		.binning_factor = 1,
	},
	{
		.x_output = S5K4ECGX_QTR_SIZE_WIDTH,
		.y_output = S5K4ECGX_QTR_SIZE_HEIGHT,
		.line_length_pclk = S5K4ECGX_QTR_SIZE_WIDTH + S5K4ECGX_HRZ_QTR_BLK_PIXELS,
		.frame_length_lines = S5K4ECGX_QTR_SIZE_HEIGHT+ S5K4ECGX_VER_QTR_BLK_LINES,
		.vt_pixel_clk = 256000000,
		.op_pixel_clk = 256000000,
		.binning_factor = 1,
	},
#ifdef F_130M_ZSL	
	{
		.x_output = S5K4ECGX_QTR_SIZE_WIDTH,
		.y_output = S5K4ECGX_QTR_SIZE_HEIGHT,
		.line_length_pclk = S5K4ECGX_QTR_SIZE_WIDTH + S5K4ECGX_HRZ_QTR_BLK_PIXELS,
		.frame_length_lines = S5K4ECGX_QTR_SIZE_HEIGHT+ S5K4ECGX_VER_QTR_BLK_LINES,
		.vt_pixel_clk = 256000000,
		.op_pixel_clk = 256000000,
		.binning_factor = 1,
	},
#else	
	{
		.x_output = S5K4ECGX_ZSL_SIZE_WIDTH,
		.y_output = S5K4ECGX_ZSL_SIZE_HEIGHT,
		.line_length_pclk = S5K4ECGX_ZSL_SIZE_WIDTH,
		.frame_length_lines = S5K4ECGX_ZSL_SIZE_HEIGHT,
		.vt_pixel_clk = 256000000,  
		.op_pixel_clk = 256000000, 
		.binning_factor = 1,
	},
#endif	
};

static struct msm_camera_csid_vc_cfg s5k4ecgx_cid_cfg[] = {
	{0, 0x1E, CSI_DECODE_8BIT}, 
	{1, CSI_EMBED_DATA, CSI_DECODE_8BIT},
	{2, CSI_RESERVED_DATA, CSI_DECODE_8BIT},
	{3, CSI_RESERVED_DATA, CSI_DECODE_8BIT},	
};

static struct msm_camera_csi2_params s5k4ecgx_csi_params = {
	.csid_params = {
		//.lane_assign = 0xe4,
		.lane_cnt = 2,
		.lut_params = {
			.num_cid = 2,
			.vc_cfg = s5k4ecgx_cid_cfg,
		},
	},
	.csiphy_params = {
		.lane_cnt = 2,
#ifdef F_130M_ZSL
		.settle_cnt = 0x1b,
#else
		.settle_cnt = 0x1d,
#endif
		.lane_mask = 0x3,		
	},
};


int32_t s5k4ecgx_sensor_power_down(struct msm_sensor_ctrl_t *s_ctrl); 

static struct msm_camera_csi2_params *s5k4ecgx_csi_params_array[] = {
	&s5k4ecgx_csi_params,
	&s5k4ecgx_csi_params,
	&s5k4ecgx_csi_params,
	&s5k4ecgx_csi_params,	
};

static struct msm_sensor_id_info_t s5k4ecgx_id_info = {
	.sensor_id_reg_addr = 0,
	.sensor_id = 0,
};

static const struct i2c_device_id s5k4ecgx_i2c_id[] = {
	{SENSOR_NAME, (kernel_ulong_t)&s5k4ecgx_s_ctrl},
	{ }
};

static struct i2c_driver s5k4ecgx_i2c_driver = {
	.id_table = s5k4ecgx_i2c_id,
	.probe  = msm_sensor_i2c_probe,
	.driver = {
		.name = SENSOR_NAME,
	},
};

#ifdef F_S5K4ECGX_POWER
int32_t s5k4ecgx_sensor_power_up(struct msm_sensor_ctrl_t *s_ctrl)
{
	int32_t rc = 0;

	SKYCDBG("%s E\n", __func__);
#if 0 // 10301 tmp block 
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

#ifdef F_MT9V113_POWER
	if (sgpio_ctrl(sgpios, F_CAMIO_STB_N, 0) < 0)	rc = -EIO;
	if (sgpio_ctrl(sgpios, F_CAMIO_RST_N, 1) < 0)	rc = -EIO;
	mdelay(1);
#endif

	if (sgpio_ctrl(sgpios, CAMIO_R_RST_N, 0) < 0)	rc = -EIO;
	mdelay(1);
	if (svreg_ctrl(svregs, CAMV_CORE_1P2V, 1) < 0)	rc = -EIO;
	mdelay(1); /* > 20us */
	if (svreg_ctrl(svregs, CAMV_A_2P8V, 1) < 0)	rc = -EIO;
	mdelay(1); /* > 15us */
	if (svreg_ctrl(svregs, CAMV_IO_1P8V, 1) < 0)	rc = -EIO;
	mdelay(1); /* > 0ms */
	
#ifdef F_MT9V113_POWER	
	if (sgpio_ctrl(sgpios, F_CAMV_A_2P8V, 1) < 0)	rc = -EIO;	
	mdelay(1);

	if (sgpio_ctrl(sgpios, F_CAMV_CORE_1P8V, 1) < 0)	rc = -EIO;
	mdelay(1);	

	if (sgpio_ctrl(sgpios, F_CAMIO_RST_N, 0) < 0)	rc = -EIO;
	mdelay(1); /* > 10 clks (approx. 0.42us) */
	if (sgpio_ctrl(sgpios, F_CAMIO_RST_N, 1) < 0)	rc = -EIO;
	mdelay(1); /* > 1 clk (apporx. 0.042us) */	
#endif	
	
	//msm_camio_clk_rate_set(24000000);
	msleep(10); /* > 15us */
	
#ifdef F_MT9V113_POWER		
	if (sgpio_ctrl(sgpios, F_CAMIO_STB_N, 1) < 0)	rc = -EIO;	
#endif
	
	if (sgpio_ctrl(sgpios, CAMIO_R_RST_N, 1) < 0)	rc = -EIO;
	mdelay(1); /* > 60us */

	/*PANTECH_CAMERA_TODO, check correct timing, spec don't have AF */
	if (svreg_ctrl(svregs, CAMV_AF_2P8V, 1) < 0)	rc = -EIO;
	mdelay(1);

	sensor_mode = -1;
	SKYCDBG("%s X (%d)\n", __func__, rc);
   return rc;
   
sensor_init_fail:
	
#if 0	
	if (sgpio_ctrl(sgpios, CAMIO_R_RST_N, 0) < 0)	rc = -EIO;
	mdelay(1); /* > 50us */
	/*PANTECH_CAMERA_TODO, check correct timing, spec don't have AF */
	if (svreg_ctrl(svregs, CAMV_AF_2P8V, 0) < 0)	rc = -EIO;
	mdelay(1);
	if (svreg_ctrl(svregs, CAMV_A_2P8V, 0) < 0)	rc = -EIO;
	mdelay(1); /* > 0ms */
	if (svreg_ctrl(svregs, CAMV_CORE_1P2V, 0) < 0)	rc = -EIO;
	mdelay(1); /* > 0ms */
	if (svreg_ctrl(svregs, CAMV_IO_1P8V, 0) < 0)	rc = -EIO;
	mdelay(1); /* > 0ms */
	
	svreg_release(svregs, CAMV_MAX);
	sgpio_release(sgpios, CAMIO_MAX);

#else

	rc = s5k4ecgx_sensor_power_down(s_ctrl);
	
#endif
	return rc;   		
}


int32_t s5k4ecgx_sensor_power_down(struct msm_sensor_ctrl_t *s_ctrl)
{
	int32_t rc = 0;

	SKYCDBG("%s E\n", __func__);
#if 0 // 1031 tmp block 
	msm_sensor_probe_off(&s_ctrl->sensor_i2c_client->client->dev); 
#else
    msm_sensor_power_down(s_ctrl);
    SKYCDBG(" %s : msm_sensor_power_down : rc = %d E\n",__func__, rc);  
#endif

#ifdef F_MT9V113_POWER		
	if (sgpio_ctrl(sgpios, F_CAMIO_STB_N, 0) < 0)	rc = -EIO;
	if (sgpio_ctrl(sgpios, F_CAMIO_RST_N, 0) < 0)	rc = -EIO;
	mdelay(1);
#endif

	if (sgpio_ctrl(sgpios, CAMIO_R_RST_N, 0) < 0)	rc = -EIO;
	mdelay(1); /* > 50us */
	/* MCLK will be disabled once again after this. */
	//(void)msm_camio_clk_disable(CAMIO_CAM_MCLK_CLK);
	//mdelay(1); /*  > 0ms */

	/*PANTECH_CAMERA_TODO, check correct timing, spec don't have AF */
	if (svreg_ctrl(svregs, CAMV_AF_2P8V, 0) < 0)	rc = -EIO;
	mdelay(1);
	if (svreg_ctrl(svregs, CAMV_A_2P8V, 0) < 0)	rc = -EIO;
	mdelay(1); /* > 0ms */
	if (svreg_ctrl(svregs, CAMV_CORE_1P2V, 0) < 0)	rc = -EIO;
	mdelay(1); /* > 0ms */
	if (svreg_ctrl(svregs, CAMV_IO_1P8V, 0) < 0)	rc = -EIO;
	mdelay(1); /* > 0ms */

#ifdef F_MT9V113_POWER		
	if (sgpio_ctrl(sgpios, F_CAMV_CORE_1P8V, 0) < 0)	rc = -EIO;
	mdelay(1);		
	if (sgpio_ctrl(sgpios, F_CAMV_A_2P8V, 0) < 0)	rc = -EIO;	
	mdelay(1);
#endif

	svreg_release(svregs, CAMV_MAX);
	sgpio_release(sgpios, CAMIO_MAX);
	si2c_release();

	SKYCDBG("%s X (%d)\n", __func__, rc);
	return rc;		
}	
#endif


int s5k4ecgx_sensor_init(struct msm_sensor_ctrl_t *s_ctrl)
{
	int rc = 0;

	SKYCDBG2("%s E\n",__func__);

	memset(s5k4ecgx_params, 0, sizeof(s5k4ecgx_params));

	rc = si2c_init(s_ctrl->sensor_i2c_client->client->adapter, s5k4ecgx_const_params, s5k4ecgx_params);
	if (rc < 0) {
		SKYCDBG("%s err(%d)\n", __func__, rc);
		si2c_release();		
		return rc;
	}	

	rc = si2c_write_param(SI2C_SA, SI2C_INIT, s5k4ecgx_params);
	if (rc < 0) {
		SKYCDBG("%s err(%d)\n", __func__, rc);
		si2c_release();		
		return rc;
	}	

#if 0 //charley2
// 0608 jinil add for Camera Initialization Fail Problem...
	rc = si2c_write_param(SI2C_SA, SI2C_FRAMEOFF_LP11, s5k4ecgx_params);
	if (rc < 0) {
		SKYCDBG("%s err(%d)\n", __func__, rc);
		si2c_release();		
		return rc;
	}	
#endif	
	sensor_mode = 3;

	SKYCDBG2("%s: X\n",__func__);	
	return rc;	
}

void s5k4ecgx_sensor_start_stream(struct msm_sensor_ctrl_t *s_ctrl)
{
#if 0
	int rc = 0;

	SKYCDBG("%s E\n", __func__);

	/* start_stream */
	rc = si2c_write_param(SI2C_SA, SI2C_START_STREAM, s5k4ecgx_params);
	if (rc < 0) {
		SKYCDBG("%s err(%d)\n", __func__, rc);		
	}

	SKYCDBG("%s X\n", __func__);	
#else
	SKYCDBG("%s: %d\n", __func__, __LINE__);
#endif
}

void s5k4ecgx_sensor_stop_stream(struct msm_sensor_ctrl_t *s_ctrl)
{
	int rc = 0;

	SKYCDBG("%s E\n", __func__);
	
	if((sensor_mode < 0) || (sensor_mode > 3))
		return;

	/* start_stream */
	rc = si2c_write_param(SI2C_SA, SI2C_STOP_STREAM, s5k4ecgx_params);
	if (rc < 0) {
		SKYCDBG("%s err(%d)\n", __func__, rc);
	}

	sensor_mode = -1;
	SKYCDBG("%s X\n", __func__);	
}


int s5k4ecgx_video_config(struct msm_sensor_ctrl_t *s_ctr)
{
	int rc = 0;

	SKYCDBG("%s sensor_mode=%d E\n", __func__, sensor_mode);

//	if (sensor_mode != SENSOR_PREVIEW_MODE)
	{
		rc = si2c_write_param(SI2C_SA, SI2C_PREVIEW, s5k4ecgx_params);
		if (rc < 0) {
			SKYCDBG("%s err(%d)\n", __func__, rc);
			return rc;
		}
		sensor_mode = 1;
		SKYCDBG("%s sensor_mode=%d \n", __func__, sensor_mode);		
	}

	SKYCDBG("%s X\n", __func__);
	return 0;
}


int s5k4ecgx_snapshot_config(struct msm_sensor_ctrl_t *s_ctr)
{
	int rc = 0;

	SKYCDBG("%s E\n", __func__);

//	if (sensor_mode != SENSOR_SNAPSHOT_MODE)
	{
		rc = si2c_write_param(SI2C_SA, SI2C_SNAPSHOT, s5k4ecgx_params);
		if (rc < 0) {
			SKYCDBG("%s err(%d)\n", __func__, rc);
			return rc;
		}
//	   sensor_mode = 0;
	}
	
	SKYCDBG("%s X\n", __func__);
	return 0;
}


int s5k4ecgx_zsl_config(struct msm_sensor_ctrl_t *s_ctrl)
{
	int rc = 0;

	SKYCDBG("%s sensor_mode=%d E\n", __func__, sensor_mode);

//	if (sensor_mode != SENSOR_ZSL_MODE)
	{
#ifdef F_130M_ZSL	
		rc = si2c_write_param(SI2C_SA, SI2C_PREVIEW, s5k4ecgx_params);
		if (rc < 0) {
			SKYCDBG("%s err(%d)\n", __func__, rc);
			return rc;
		}	
#else
		rc = si2c_write_param(SI2C_SA, SI2C_ZSL, s5k4ecgx_params);
		if (rc < 0) {
			SKYCDBG("%s err(%d)\n", __func__, rc);
			return rc;
		}	
#endif
		sensor_mode = 3;	
		SKYCDBG("%s sensor_mode=%d \n", __func__, sensor_mode);		
	}

	SKYCDBG("%s X\n", __func__);
	return 0;
}


int32_t s5k4ecgx_sensor_setting(struct msm_sensor_ctrl_t *s_ctrl,
			int update_type, int res)
{
	int32_t rc = 0;

	SKYCDBG("%s:[F_PANTECH_CAMERA] %d, %d res=%d\n", __func__, __LINE__,update_type,res);
	
	if(res != 0)
		s_ctrl->func_tbl->sensor_stop_stream(s_ctrl);
//	else if(update_type == MSM_SENSOR_UPDATE_PERIODIC)
//	{
//		s5k4ecgx_snapshot_config();
//	}

	msleep(30);
	if (update_type == MSM_SENSOR_REG_INIT) {
		SKYCDBG("%s:[F_PANTECH_CAMERA] ==> MSM_SENSOR_REG_INIT  %d\n", __func__, update_type);  
		
		s_ctrl->curr_csi_params = NULL;       
		msm_sensor_enable_debugfs(s_ctrl);
		s5k4ecgx_sensor_init(s_ctrl);
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
 		    rc = s5k4ecgx_snapshot_config(s_ctrl);	
			 break;
		case 1:
			 rc = s5k4ecgx_video_config(s_ctrl);	
			 break;
		//case 2: 
		//	 rc = s5k4ecgx_video_config(s_ctrl);	
		//	 break;
		case 3: 
			 rc = s5k4ecgx_zsl_config(s_ctrl); 
			 break;
		default:
			 rc = s5k4ecgx_video_config(s_ctrl);	
			 SKYCDBG("%s fail res=%d\n", __func__, res);
			 break;
		}
		sensor_mode = res;
		SKYCDBG("Sensor setting : Res = %d\n", res);
#endif
	   //msleep(30);

	}
	SKYCDBG("%s: %d x\n", __func__, __LINE__);
	return rc;
}


#if 1//def F_PANTECH_CAMERA_FIX_CFG_BRIGHTNESS
int s5k4ecgx_sensor_brightness(struct msm_sensor_ctrl_t *s_ctrl, int8_t brightness)
{
	si2c_pid_t pid = SI2C_PID_MAX;
	int rc = 0;

	SKYCDBG("%s brightness=%d E\n", __func__, brightness);

	if(sensor_mode == 0) 
		return 0;	

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
		return 0;
	}

	rc = si2c_write_param(SI2C_SA, pid, s5k4ecgx_params);
	if (rc < 0) {
		SKYCDBG("%s err(%d)\n", __func__, rc);
		return rc;
	}

	SKYCDBG("%s X\n", __func__);
	return 0;

}
#endif


#if 1//def F_PANTECH_CAMERA_FIX_CFG_EFFECT
int s5k4ecgx_sensor_effect(struct msm_sensor_ctrl_t *s_ctrl, int8_t effect)
{
	si2c_pid_t pid = SI2C_PID_MAX;
	int rc = 0;

	SKYCDBG("%s effect=%d E\n", __func__, effect);

	if(sensor_mode == 0)
		return 0;	

	switch (effect) {
	case 0: pid = SI2C_EFFECT_OFF; break;
	case 1: pid = SI2C_EFFECT_MONO; break;
	case 2: pid = SI2C_EFFECT_NEGATIVE; break;
	case 3: pid = SI2C_EFFECT_SOLARIZE; break;
	case 4: pid = SI2C_EFFECT_SEPIA; break;
	default:
		return 0;
	}

	rc = si2c_write_param(SI2C_SA, pid, s5k4ecgx_params);
	if (rc < 0) {
		SKYCDBG("%s err(%d)\n", __func__, rc);
		return rc;
	}

	SKYCDBG("%s X\n", __func__);
	return 0;

}
#endif


#if 1//def F_PANTECH_CAMERA_FIX_CFG_WB
int s5k4ecgx_sensor_wb(struct msm_sensor_ctrl_t *s_ctrl, int8_t wb)
{
	si2c_pid_t pid = SI2C_PID_MAX;
	int rc = 0;

	SKYCDBG("%s wb=%d E\n", __func__, wb);

	if(sensor_mode == 0)
		return 0;	

	switch (wb) {
	case 1: pid = SI2C_WB_AUTO; break;
	case 3: pid = SI2C_WB_INCANDESCENT; break;
	case 4: pid = SI2C_WB_FLUORESCENT; break;
	case 5: pid = SI2C_WB_DAYLIGHT; break;
	case 6: pid = SI2C_WB_CLOUDY; break;
	default:
		return 0;
	}

	rc = si2c_write_param(SI2C_SA, pid, s5k4ecgx_params);
	if (rc < 0) {
		SKYCDBG("%s err(%d)\n", __func__, rc);
		return rc;
	}

	SKYCDBG("%s X\n", __func__);
	return 0;

}
#endif


#if 1//def F_PANTECH_CAMERA_FIX_CFG_PREVIEW_FPS
int s5k4ecgx_sensor_preview_fps(struct msm_sensor_ctrl_t *s_ctrl, int8_t preview_fps)
{
	si2c_pid_t pid = SI2C_PID_MAX;
	int rc = 0;

	SKYCDBG("%s preview_fps=%d E\n", __func__, preview_fps);

	if(sensor_mode == 3)
		return 0;	

	switch (preview_fps) {
		case  0: pid = SI2C_FPS_VARIABLE; break;
		case  7: pid = SI2C_FPS_FIXED7; break;
		case  8: pid = SI2C_FPS_FIXED8; break;
		case 10: pid = SI2C_FPS_FIXED10; break;
		case 14: pid = SI2C_FPS_FIXED14; break;
		case 15: pid = SI2C_FPS_FIXED15; break;
		case 20: pid = SI2C_FPS_FIXED20; break;
		case 24: pid = SI2C_FPS_FIXED24; break;
		case 25: pid = SI2C_FPS_FIXED25; break;
	//	case 30: pid = SI2C_FPS_FIXED30; break;
		case 30: pid = SI2C_FPS_VARIABLE; break;
		case 31: pid = SI2C_FPS_VARIABLE; break;
		default:
			//PANTECH_CAMERA_TODO
			return 0;
	}

	rc = si2c_write_param(SI2C_SA, pid, s5k4ecgx_params);
	if (rc < 0) {
		SKYCDBG("%s err(%d)\n", __func__, rc);
		return rc;
	}

	SKYCDBG("%s X\n", __func__);
	return 0;
}
#endif


#if 1//def F_PANTECH_CAMERA_FIX_CFG_EXPOSURE
int s5k4ecgx_sensor_exposure(struct msm_sensor_ctrl_t *s_ctrl, int8_t exposure)
{
	si2c_pid_t pid = SI2C_PID_MAX;
	int rc = 0;

	SKYCDBG("%s exposure=%d E\n", __func__, exposure);
	
	if(sensor_mode == 0)
		return 0;	

	switch (exposure) {
	case 0:			
	case 1: pid = SI2C_EXPOSURE_AVERAGE; break;
	case 2: 
	case 3: pid = SI2C_EXPOSURE_CENTER; break;
	default:
		SKYCDBG("%s err(-EINVAL)\n", __func__);
		return -EINVAL;
	}

	rc = si2c_write_param(SI2C_SA, pid, s5k4ecgx_params);
	if (rc < 0) {
		SKYCDBG("%s err(%d)\n", __func__, rc);
		return rc;
	}

	SKYCDBG("%s X\n", __func__);
	return 0;
}
#endif


#if 1//F_PANTECH_CAMERA_FIX_CFG_SCENE_MODE
static int s5k4ecgx_sensor_scene_mode(struct msm_sensor_ctrl_t *s_ctrl, int8_t scene_mode)
{
	si2c_pid_t pid = SI2C_PID_MAX;
	int rc = 0;

	SKYCDBG("%s scene_mode=%d E\n", __func__, scene_mode);
	
if(sensor_mode == 3){

		SKYCDBG("%s sensor_mode(3) scene mode", __func__);		

	switch (scene_mode) {
	case 0: pid = SI2C_SCENE_ZSL_NORMAL;		break;
	case 1: pid = SI2C_SCENE_PORTRAIT;		break;
	case 2: pid = SI2C_SCENE_LANDSCAPE;		break;
	case 3: pid = SI2C_SCENE_PARTY_INDOOR;	break;
	case 4: pid = SI2C_SCENE_ZSL_SPORTS;		break;
	case 5: pid = SI2C_SCENE_ZSL_NIGHT;			break;
	case 6: pid = SI2C_SCENE_BEACH;			break;
	case 7: pid = SI2C_SCENE_SNOW;			break;
	case 8: pid = SI2C_SCENE_SUNSET;		break;
	case 9: pid = SI2C_SCENE_TEXT;			break;
	default:
		return 0;	
	}

	rc = si2c_write_param(SI2C_SA, pid, s5k4ecgx_params);
	if (rc < 0) {
		SKYCDBG("%s err(%d)\n", __func__, rc);
		return rc;
	}
}
else
{
		SKYCDBG("%s sensor_mode(0) scene mode", __func__);		

	switch (scene_mode) {
	case 0: pid = SI2C_SCENE_NORMAL;		break;
	case 1: pid = SI2C_SCENE_PORTRAIT;		break;
	case 2: pid = SI2C_SCENE_LANDSCAPE;		break;
	case 3: pid = SI2C_SCENE_PARTY_INDOOR;	break;
	case 4: pid = SI2C_SCENE_SPORTS;		break;
	case 5: pid = SI2C_SCENE_NIGHT;			break;
	case 6: pid = SI2C_SCENE_BEACH;			break;
	case 7: pid = SI2C_SCENE_SNOW;			break;
	case 8: pid = SI2C_SCENE_SUNSET;		break;
	case 9: pid = SI2C_SCENE_TEXT;			break;
	default:
		return 0;	
	}

	rc = si2c_write_param(SI2C_SA, pid, s5k4ecgx_params);
	if (rc < 0) {
		SKYCDBG("%s err(%d)\n", __func__, rc);
		return rc;
	}
}	

	SKYCDBG("%s X\n", __func__);
	return 0;
}
#endif


#if 1//def F_PANTECH_CAMERA_FIX_CFG_AF
int s5k4ecgx_sensor_auto_focus(struct msm_sensor_ctrl_t *s_ctrl, int8_t autofocus)
{
	int rc = 0;

	SKYCDBG2("%s autofocus(%d) E\n", __func__, autofocus);

	if(!(sensor_mode > 0 && sensor_mode < 4))
		 return 0;

	if((autofocus != 2) && (autofocus != 6 )) 
		return 0;

	if(autofocus == 6)//Cancel AF
	{
		si2c_cmd_t cmds_cancel_af[] = {
         {SI2C_WR, SI2C_A2D2, 0xFCFC, 0xD000, 0}, 			
         {SI2C_WR, SI2C_A2D2, 0x0028, 0x7000, 0},
         {SI2C_WR, SI2C_A2D2, 0x002A, 0x028C, 0},		
         {SI2C_WR, SI2C_A2D2, 0x0F12, 0x0002, 0},          
         {SI2C_DELAY, SI2C_A1D1, 0, 0, 150}, 					
         {SI2C_EOC, SI2C_A1D1, 0, 0, 0},
		};

		SKYCDBG2("%s cancel af = 6 \n", __func__);

		rc = si2c_write_cmds(SI2C_SA, cmds_cancel_af);
		if (rc < 0) {
			return rc;
		}

		return 0;
	}

	/* auto focus */
	rc = si2c_write_param(SI2C_SA, SI2C_AF_TRIGGER, s5k4ecgx_params);
	if (rc < 0) {
		SKYCDBG("%s err(%d)\n", __func__, rc);
		return rc;
	}

	SKYCDBG("%s X\n", __func__);
	return 0;
}
#endif


#if 1//def F_PANTECH_CAMERA_FIX_CFG_AF
int s5k4ecgx_sensor_check_af(struct msm_sensor_ctrl_t *s_ctrl ,int8_t autofocus)
{
	uint16_t af1 = 0, af2 = 0; 

	si2c_cmd_t cmds_read_af1[] = {
		{SI2C_WR, SI2C_A2D2, 0xFCFC, 0xD000, 0},
		{SI2C_WR, SI2C_A2D2, 0x002C, 0x7000, 0},
		{SI2C_WR, SI2C_A2D2, 0x002E, 0x2EEE, 0},
		{SI2C_EOC, SI2C_A1D1, 0, 0, 0},
	};
	si2c_cmd_t cmds_read_af2[] = {
		{SI2C_WR, SI2C_A2D2, 0xFCFC, 0xD000, 0},
		{SI2C_WR, SI2C_A2D2, 0x002C, 0x7000, 0},
		{SI2C_WR, SI2C_A2D2, 0x002E, 0x2207, 0},
		{SI2C_EOC, SI2C_A1D1, 0, 0, 0},
	};

	SKYCDBG2("%s E\n", __func__);

	if(!(sensor_mode > 0 && sensor_mode < 4))
		 return 0;

	if (si2c_write_cmds(SI2C_SA, cmds_read_af1) < 0) return -EIO;
	if (si2c_read(SI2C_A2D2, SI2C_SA, 0x0F12, &af1) < 0) return -EIO;

	if( af1 == 2 )
	{
		if (si2c_write_cmds(SI2C_SA, cmds_read_af2) < 0) return -EIO;
		if (si2c_read(SI2C_A2D2, SI2C_SA, 0x0F12, &af2) < 0) return -EIO;
	   SKYCDBG2("%s af1 = 2, af2(%d) \n", __func__, af2);			
		if ( (af2 & 0xff00) == 0)
		{
			SKYCDBG2(" success af X");
			return 0;
		}else{
			return -1;
		}
	}
	else if (af1 == 1) {
	   SKYCDBG2("%s af1(%d) X\n", __func__, af1);	
		return -1;
	}	
	
	SKYCDBG2("%s af1(%d) X\n", __func__, af1);		
	return 0;
}
#endif


#if 1//F_PANTECH_CAMERA_FIX_CFG_FOCUS_RECT
static int32_t s5k4ecgx_sensor_focus_rect(struct msm_sensor_ctrl_t *s_ctrl, int32_t focus_rect, int8_t * f_info)
{
	#define FIRST_FOCUS_RECT_SIZE_X 256
	#define FIRST_FOCUS_RECT_SIZE_Y 192	
	#define SECOND_FOCUS_RECT_SIZE_X 128
	#define SECOND_FOCUS_RECT_SIZE_Y 96

	uint16_t touch_X = 0, touch_Y = 0;
	uint16_t preview_width, preview_height;

	uint16_t inner_window_width=0, inner_window_height=0, inner_window_start_X=0, inner_window_start_Y=0;
	uint16_t outer_window_width=0, outer_window_height=0, outer_window_start_X=0, outer_window_start_Y=0;

	uint16_t FstWinSizeX=0, FstWinSizeY=0,FstWinStartX=0, FstWinStartY=0;
	uint16_t ScndWinSizeX=0, ScndWinSizeY=0, ScndWinStartX=0, ScndWinStartY=0;

	int32_t rc = 0;


	SKYCDBG2("%s  focus_rect = %x E\n",__func__, focus_rect);

	if(!(sensor_mode > 0 && sensor_mode < 4))
		 return 0;

	if (focus_rect == 0) {
		/* [TODO] Center Focus Setting */
		return rc;
	}

	FstWinSizeX  = FIRST_FOCUS_RECT_SIZE_X;
	FstWinSizeY  = FIRST_FOCUS_RECT_SIZE_Y;
	ScndWinSizeX = SECOND_FOCUS_RECT_SIZE_X;
	ScndWinSizeY = SECOND_FOCUS_RECT_SIZE_Y;

	preview_width = S5K4ECGX_QTR_SIZE_WIDTH;  
	preview_height = S5K4ECGX_QTR_SIZE_HEIGHT;
	SKYCDBG("%s  preview_width = %d, preview_height = %d\n",__func__, preview_width, preview_height);	

	touch_X = (uint16_t)((focus_rect & 0xffff0000) >> 16);
	touch_Y = (uint16_t)(focus_rect & 0xffff);
	SKYCDBG("%s touch_X = %d, touch_Y = %d\n",__func__, touch_X, touch_Y);	
	
	touch_X = (touch_X * preview_width)/2000;	
	touch_Y = (touch_Y * preview_height)/2000;
	SKYCDBG("%s  touch_X_result = %d, touch_Y_result = %d\n",__func__, touch_X, touch_Y);

	touch_X = (uint16_t)(1279 - touch_X);
	touch_Y = (uint16_t)(959 - touch_Y);

	outer_window_width = ((FstWinSizeX * 1280) / 1024);
	outer_window_height = ((FstWinSizeY * 960) / 1024);	

	inner_window_width = ((ScndWinSizeX * 1280) / 1024);
	inner_window_height = ((ScndWinSizeY * 960) / 1024);	
	
	//================================================//
	// (1-9) Set AF window for Touch AF ( set X axis)                                        //
	//================================================//
	if (touch_X <= (inner_window_width/2))
	{ 
		inner_window_start_X = 0;
		outer_window_start_X = 0;
	}
	else if (touch_X <= (outer_window_width/2))
	{ 
		inner_window_start_X = touch_X - (inner_window_width/2);
		outer_window_start_X = 0;
	}
	else if (touch_X >= (1279 - inner_window_width/2)) 
	{
		inner_window_start_X = 1279 - inner_window_width;
		outer_window_start_X = 1279 - outer_window_width;
	}
	else if (touch_X >= (1279 - outer_window_width/2))
	{
		inner_window_start_X = touch_X - (inner_window_width/2);
		outer_window_start_X = 1279 - outer_window_width;
	}
	else
	{ 
		inner_window_start_X = touch_X - (inner_window_width/2);
		outer_window_start_X = touch_X - (outer_window_width/2);
	}

	//================================================//
	// (1-9) Set AF window for Touch AF ( set Y axis)                                        //
	//================================================//
	if (touch_Y <= (inner_window_height/2))
	{ 
		inner_window_start_Y = 0;
		outer_window_start_Y = 0;
	}
	else if (touch_Y <= (outer_window_height/2))
	{ 
		inner_window_start_Y = touch_Y-inner_window_height/2;
		outer_window_start_Y = 0;
	}
	else if (touch_Y >= (959 - inner_window_height/2))
	{
		inner_window_start_Y = 959 - inner_window_height;
		outer_window_start_Y = 959 - outer_window_height;
	}
	else if (touch_Y >= (959 - outer_window_height/2))	
	{
		inner_window_start_Y = touch_Y - (inner_window_height/2);
		outer_window_start_Y = 959 - outer_window_height;
	}
	else
	{ 
		inner_window_start_Y = touch_Y - (inner_window_height/2);
		outer_window_start_Y = touch_Y - (outer_window_height/2);
	}

	SKYCDBG("%s: inner_window_width = %d, inner_window_height = %d\n", __func__, inner_window_width, inner_window_height);
	SKYCDBG("%s: inner_window_start_X = %d, inner_window_start_Y = %d\n", __func__, inner_window_start_X, inner_window_start_Y);

	SKYCDBG("%s: outer_window_width = %d, outer_window_height = %d\n", __func__, outer_window_width, outer_window_height);
	SKYCDBG("%s: outer_window_start_X = %d, outer_window_start_Y = %d\n\n", __func__, outer_window_start_X, outer_window_start_Y);

	//================================================//
	// (1-10) Set AF window for Touch AF                                                         //
	//================================================//
	//Write value to sensor register
	//write inner window start X, outer window start X
	ScndWinStartX = (inner_window_start_X * 1024) / 1280;
	FstWinStartX = (outer_window_start_X * 1024) / 1280;

	// write inner window start Y, outer window start Y
	ScndWinStartY = (inner_window_start_Y * 1024) / 960;
	FstWinStartY = (outer_window_start_Y * 1024) / 960;

	SKYCDBG("%s: FstWinSizeX = %d, FstWinSizeY = %d\n", __func__, FstWinSizeX, FstWinSizeY);
	SKYCDBG("%s: FstWinStartX = %d, FstWinStartY = %d\n", __func__, FstWinStartX, FstWinStartY);

	SKYCDBG("%s: ScndWinSizeX = %d, ScndWinSizeY = %d\n", __func__, ScndWinSizeX, ScndWinSizeY);
	SKYCDBG("%s: ScndWinStartX = %d, ScndWinStartY = %d\n", __func__, ScndWinStartX, ScndWinStartY);

	{
		si2c_cmd_t cmds_write_focus_rect[] = {
			/*============================================================================*/
			{SI2C_WR, SI2C_A2D2, 0x002A, 0x0294, 0},
			{SI2C_WR, SI2C_A2D2, 0x0F12, FstWinStartX, 0},		// 0100 REG_TC_AF_FstWinStartX
			{SI2C_WR, SI2C_A2D2, 0x0F12, FstWinStartY, 0},		// 00E3 REG_TC_AF_FstWinStartY
			{SI2C_WR, SI2C_A2D2, 0x0F12, FstWinSizeX, 0},		// 0200 REG_TC_AF_FstWinSizeX
			{SI2C_WR, SI2C_A2D2, 0x0F12, FstWinSizeY, 0},		// 0238 REG_TC_AF_FstWinSizeY
			{SI2C_WR, SI2C_A2D2, 0x0F12, ScndWinStartX, 0},		// 01C6 REG_TC_AF_ScndWinStartX
			{SI2C_WR, SI2C_A2D2, 0x0F12, ScndWinStartY, 0},		// 0166 REG_TC_AF_ScndWinStartY
			{SI2C_WR, SI2C_A2D2, 0x0F12, ScndWinSizeX, 0},		// 0074 REG_TC_AF_ScndWinSizeX
			{SI2C_WR, SI2C_A2D2, 0x0F12, ScndWinSizeY, 0},		// 0132 REG_TC_AF_ScndWinSizeY
			{SI2C_WR, SI2C_A2D2, 0x0F12, 0x0001, 0},			// REG_TC_AF_WinSizesUpdated	
			{SI2C_DELAY, SI2C_A1D1, 0, 0, 150}, 				// 1 frame delay			
			{SI2C_EOC, SI2C_A1D1, 0, 0, 0},
			/*============================================================================*/
		};

		if (si2c_write_cmds(SI2C_SA, cmds_write_focus_rect) < 0)
		{
			SKYCDBG2("%s error.\n", __func__);
			rc = -EIO;
		}
	}

	SKYCDBG2("%s X\n",__func__);
	return rc;		
}
#endif

static int __init msm_sensor_init_module(void)
{
	return i2c_add_driver(&s5k4ecgx_i2c_driver);
}

static struct v4l2_subdev_core_ops s5k4ecgx_subdev_core_ops = {
	.ioctl = msm_sensor_subdev_ioctl,
	.s_power = msm_sensor_power,
};
static struct msm_camera_i2c_client s5k4ecgx_sensor_i2c_client = {
	.addr_type = MSM_CAMERA_I2C_WORD_ADDR,
};

static struct v4l2_subdev_video_ops s5k4ecgx_subdev_video_ops = {
	.enum_mbus_fmt = msm_sensor_v4l2_enum_fmt,
};

static struct v4l2_subdev_ops s5k4ecgx_subdev_ops = {
	.core = &s5k4ecgx_subdev_core_ops,
	.video  = &s5k4ecgx_subdev_video_ops,
};

static struct msm_sensor_fn_t s5k4ecgx_func_tbl = {
	.sensor_start_stream = s5k4ecgx_sensor_start_stream,
	.sensor_stop_stream = s5k4ecgx_sensor_stop_stream,	
#if 0
	.sensor_get_pict_fps = msm_sensor_get_pict_fps,
#endif
	.sensor_setting = s5k4ecgx_sensor_setting,
	.sensor_set_sensor_mode = msm_sensor_set_sensor_mode,
	.sensor_mode_init = msm_sensor_mode_init,
	.sensor_get_output_info = msm_sensor_get_output_info,
	.sensor_config = msm_sensor_config,
#ifdef F_S5K4ECGX_POWER
	.sensor_power_up = s5k4ecgx_sensor_power_up,
	.sensor_power_down = s5k4ecgx_sensor_power_down,
#else
    .sensor_power_up = msm_sensor_power_up,
    .sensor_power_down = msm_sensor_power_down,
#endif
#if 1//def F_PANTECH_CAMERA_FIX_CFG_BRIGHTNESS
    .sensor_set_brightness = s5k4ecgx_sensor_brightness,
#endif    
#if 1//def F_PANTECH_CAMERA_FIX_CFG_EFFECT    
    .sensor_set_effect = s5k4ecgx_sensor_effect,
#endif    
#if 1//def F_PANTECH_CAMERA_FIX_CFG_WB    
    .sensor_set_wb = s5k4ecgx_sensor_wb,
#endif	
#if 1//def F_PANTECH_CAMERA_FIX_CFG_EXPOSURE
	.sensor_set_exposure_mode = s5k4ecgx_sensor_exposure,
#endif
#if 1//def F_PANTECH_CAMERA_FIX_CFG_PREVIEW_FPS
	.sensor_set_preview_fps = s5k4ecgx_sensor_preview_fps,
#endif
#if 1//def F_PANTECH_CAMERA_FIX_CFG_AF
	.sensor_set_auto_focus = s5k4ecgx_sensor_auto_focus,
#endif
#if 1//def F_PANTECH_CAMERA_FIX_CFG_SCENE_MODE
	.sensor_set_scene_mode = s5k4ecgx_sensor_scene_mode,
#endif
#if 1//def F_PANTECH_CAMERA_FIX_CFG_AF
	.sensor_check_af = s5k4ecgx_sensor_check_af,
#endif
#if 1//def F_PANTECH_CAMERA_FIX_CFG_FOCUS_RECT
    .sensor_set_focus_rect = s5k4ecgx_sensor_focus_rect,
#endif
	.sensor_get_csi_params = msm_sensor_get_csi_params,
};

static struct msm_sensor_reg_t s5k4ecgx_regs = {
	.default_data_type = MSM_CAMERA_I2C_WORD_DATA,
#if 0
	.start_stream_conf = s5k4ecgx_start_settings,
	.start_stream_conf_size = ARRAY_SIZE(s5k4ecgx_start_settings),
	.stop_stream_conf = s5k4ecgx_stop_settings,
	.stop_stream_conf_size = ARRAY_SIZE(s5k4ecgx_stop_settings),
#endif
#if 0
	.group_hold_on_conf = s5k4ecgx_groupon_settings,
	.group_hold_on_conf_size = ARRAY_SIZE(s5k4ecgx_groupon_settings),
	.group_hold_off_conf = s5k4ecgx_groupoff_settings,
	.group_hold_off_conf_size =
		ARRAY_SIZE(s5k4ecgx_groupoff_settings),
#endif
	.init_settings = NULL, //&s5k4ecgx_init_conf[0],
	.init_size = 0, //ARRAY_SIZE(s5k4ecgx_init_conf),
	.mode_settings = NULL, //&s5k4ecgx_confs[0],
	.output_settings = &s5k4ecgx_dimensions[0],
	.num_conf = ARRAY_SIZE(s5k4ecgx_cid_cfg),
};

static struct msm_sensor_ctrl_t s5k4ecgx_s_ctrl = {
	.msm_sensor_reg = &s5k4ecgx_regs,
	.sensor_i2c_client = &s5k4ecgx_sensor_i2c_client,
	.sensor_i2c_addr = 0x5A,
	.sensor_id_info = &s5k4ecgx_id_info,
	.cam_mode = MSM_SENSOR_MODE_INVALID,
	.csi_params = &s5k4ecgx_csi_params_array[0],
	.msm_sensor_mutex = &s5k4ecgx_mut,
	.sensor_i2c_driver = &s5k4ecgx_i2c_driver,
	.sensor_v4l2_subdev_info = s5k4ecgx_subdev_info,
	.sensor_v4l2_subdev_info_size = ARRAY_SIZE(s5k4ecgx_subdev_info),
	.sensor_v4l2_subdev_ops = &s5k4ecgx_subdev_ops,
	.func_tbl = &s5k4ecgx_func_tbl,
	.clk_rate = MSM_SENSOR_MCLK_24HZ,
};

module_init(msm_sensor_init_module);
MODULE_DESCRIPTION("Samsung LSI 5M YUV Sensor driver");
MODULE_LICENSE("GPL v2");

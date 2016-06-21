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

#include "msm_fb.h"
#include "mipi_dsi.h"
#include "mipi_lgd.h"


static struct msm_panel_info pinfo;

#if defined(MIPI_CLOCK_370MBPS)
static struct mipi_dsi_phy_ctrl dsi_video_mode_phy_db = {
	/* 480*800, RGB888, 2 Lane 60 fps 370Mbps video mode */
  /* regulator */
  {0x03, 0x0a, 0x04, 0x00, 0x20},
  /* timing */
  {0xab, 0x8a, 0x18, 0x00, 0x92, 0x97, 0x1b, 0x8c,
   0x0c, 0x03, 0x04, 0xa0},
  /* phy ctrl */
  {0x5f, 0x00, 0x00, 0x10},
  /* strength */
  {0xff, 0x00, 0x06, 0x00},
  /* pll control */
//  {0x0, 0x0d, 0x31, 0xda, 0x00, 0x50, 0x48, 0x63,
//  {0x0, 0x5d, 0x01, 0x1a, 0x00, 0x50, 0x48, 0x63,
  {0x0, 0x7d, 0x31, 0xda, 0x00, 0x50, 0x48, 0x63,
   0x31, 0x0f, 0x07,
   0x00, 0x14, 0x03, 0x00, 0x02, 0x00, 0x20, 0x00, 0x01 },
};
#elif defined(MIPI_CLOCK_350MBPS)
static struct mipi_dsi_phy_ctrl dsi_video_mode_phy_db = {
	/* 480*800, RGB888, 2 Lane 60 fps 300Mbps video mode */
  /* regulator */
  {0x03, 0x0a, 0x04, 0x00, 0x20},
  /* timing */
  {0xab, 0x8a, 0x18, 0x00, 0x92, 0x97, 0x1b, 0x8c,
   0x0c, 0x03, 0x04, 0xa0},
  /* phy ctrl */
  {0x5f, 0x00, 0x00, 0x10},
  /* strength */
  {0xff, 0x00, 0x06, 0x00},
  /* pll control */
//  {0x0, 0x0d, 0x31, 0xda, 0x00, 0x50, 0x48, 0x63,
//  {0x0, 0x5d, 0x01, 0x1a, 0x00, 0x50, 0x48, 0x63,
  {0x0, 0x5d, 0x31, 0xda, 0x00, 0x50, 0x48, 0x63,
   0x31, 0x0f, 0x07,
   0x00, 0x14, 0x03, 0x00, 0x02, 0x00, 0x20, 0x00, 0x01 },
};
#elif defined(MIPI_CLOCK_320MBPS)
static struct mipi_dsi_phy_ctrl dsi_video_mode_phy_db = {
/* 480*800, RGB888, 2 Lane 52.7 fps video mode */

  /* regulator */
 {0x03, 0x0a, 0x04, 0x00, 0x20},
  /* timing */
  {0xab, 0x8a, 0x18, 0x00, 0x92, 0x97, 0x1b, 0x8c,
  0x0c, 0x03, 0x04, 0xa0},
  /* phy ctrl */
  {0x5f, 0x00, 0x00, 0x10},
  /* strength */
  {0xff, 0x00, 0x06, 0x00},
  /* pll control */
   {0x0, 0x3f, 0x31, 0xda, 0x00, 0x50, 0x48, 0x63,
    0x31, 0x0f, 0x03,
    0x00, 0x14, 0x03, 0x00, 0x02, 0x00, 0x20, 0x00, 0x01 },
};
#elif defined(MIPI_CLOCK_327MBPS)
static struct mipi_dsi_phy_ctrl dsi_video_mode_phy_db = {
/* 480*800, RGB888, 2 Lane 52.7 fps video mode */

  /* regulator */
 {0x03, 0x0a, 0x04, 0x00, 0x20},
  /* timing */
  {0xab, 0x8a, 0x18, 0x00, 0x92, 0x97, 0x1b, 0x8c,
  0x0c, 0x03, 0x04, 0xa0},
  /* phy ctrl */
  {0x5f, 0x00, 0x00, 0x10},
  /* strength */
  {0xff, 0x00, 0x06, 0x00},
  /* pll control */
   {0x0, 0x46, 0x31, 0xda, 0x00, 0x50, 0x48, 0x63,
    0x31, 0x0f, 0x03,
    0x00, 0x14, 0x03, 0x00, 0x02, 0x00, 0x20, 0x00, 0x01 },
};
#elif defined(MIPI_CLOCK_328MBPS)
static struct mipi_dsi_phy_ctrl dsi_video_mode_phy_db = {
/* 480*800, RGB888, 2 Lane 52.7 fps video mode */

  /* regulator */
 {0x03, 0x0a, 0x04, 0x00, 0x20},
  /* timing */
  {0xab, 0x8a, 0x18, 0x00, 0x92, 0x97, 0x1b, 0x8c,
  0x0c, 0x03, 0x04, 0xa0},
  /* phy ctrl */
  {0x5f, 0x00, 0x00, 0x10},
  /* strength */
  {0xff, 0x00, 0x06, 0x00},
  /* pll control */
   {0x0, 0x47, 0x31, 0xda, 0x00, 0x50, 0x48, 0x63,
    0x31, 0x0f, 0x03,
    0x00, 0x14, 0x03, 0x00, 0x02, 0x00, 0x20, 0x00, 0x01 },
};
#elif defined(MIPI_CLOCK_330MBPS)
static struct mipi_dsi_phy_ctrl dsi_video_mode_phy_db = {
/* 480*800, RGB888, 2 Lane 52.7 fps video mode */

  /* regulator */
 {0x03, 0x0a, 0x04, 0x00, 0x20},
  /* timing */
  {0xab, 0x8a, 0x18, 0x00, 0x92, 0x97, 0x1b, 0x8c,
  0x0c, 0x03, 0x04, 0xa0},
  /* phy ctrl */
  {0x5f, 0x00, 0x00, 0x10},
  /* strength */
  {0xff, 0x00, 0x06, 0x00},
  /* pll control */
   {0x0, 0x49, 0x31, 0xda, 0x00, 0x50, 0x48, 0x63,
    0x31, 0x0f, 0x03,
    0x00, 0x14, 0x03, 0x00, 0x02, 0x00, 0x20, 0x00, 0x01 },
};
#elif defined(MIPI_CLOCK_334MBPS)
static struct mipi_dsi_phy_ctrl dsi_video_mode_phy_db = {
/* 480*800, RGB888, 2 Lane 52.7 fps video mode */

  /* regulator */
 {0x03, 0x0a, 0x04, 0x00, 0x20},
  /* timing */
  {0xab, 0x8a, 0x18, 0x00, 0x92, 0x97, 0x1b, 0x8c,
  0x0c, 0x03, 0x04, 0xa0},
  /* phy ctrl */
  {0x5f, 0x00, 0x00, 0x10},
  /* strength */
  {0xff, 0x00, 0x06, 0x00},
  /* pll control */
   {0x0, 0x4d, 0x31, 0xda, 0x00, 0x50, 0x48, 0x63,
    0x31, 0x0f, 0x03,
    0x00, 0x14, 0x03, 0x00, 0x02, 0x00, 0x20, 0x00, 0x01 },
};
#else
static struct mipi_dsi_phy_ctrl dsi_video_mode_phy_db = {
	/* 480*800, RGB888, 2 Lane 60 fps 200Mbps video mode */
    /* regulator */
  {0x03, 0x0a, 0x04, 0x00, 0x20},
  /* timing */
  {0xab, 0x8a, 0x18, 0x00, 0x92, 0x97, 0x1b, 0x8c,
   0x0c, 0x03, 0x04, 0xa0},
  /* phy ctrl */
  {0x5f, 0x00, 0x00, 0x10},
  /* strength */
  {0xff, 0x00, 0x06, 0x00},
  /* pll control */
  {0x0, 0x2f, 0x31, 0xda, 0x00, 0x50, 0x48, 0x63,
   0x31, 0x0f, 0x07,
   0x00, 0x14, 0x03, 0x00, 0x02, 0x00, 0x20, 0x00, 0x01 },
};
#endif

static int __init mipi_video_lgd_wvga_pt_init(void)
{
	int ret;

#ifdef CONFIG_FB_MSM_MIPI_PANEL_DETECT
	if (msm_fb_detect_client("mipi_video_lgd_wvga"))
		return 0;
#endif

	pinfo.xres = 480;
	pinfo.yres = 800;
	/*
	 *
	 * Panel's Horizontal input timing requirement is to
	 * include dummy(pad) data of 200 clk in addition to
	 * width and porch/sync width values
	 */

	pinfo.lcdc.xres_pad = 0;
	pinfo.lcdc.yres_pad = 0;

	pinfo.type = MIPI_VIDEO_PANEL;
	pinfo.pdest = DISPLAY_1;
	pinfo.wait_cycle = 0;
	pinfo.bpp = 24;
#if 0
	pinfo.lcdc.h_back_porch = 84;//32;
	pinfo.lcdc.h_front_porch = 74;//64;
	pinfo.lcdc.h_pulse_width = 20;//16;
	pinfo.lcdc.v_back_porch = 20;
	pinfo.lcdc.v_front_porch = 10;
	pinfo.lcdc.v_pulse_width = 8;
#else
#if defined(MIPI_CLOCK_370MBPS)
	pinfo.lcdc.h_back_porch = 106;
	pinfo.lcdc.h_front_porch = 12;//8->14
	pinfo.lcdc.h_pulse_width = 30;
	pinfo.lcdc.v_back_porch = 8;
	pinfo.lcdc.v_front_porch = 8;
	pinfo.lcdc.v_pulse_width = 2;
#else
	pinfo.lcdc.h_back_porch = 86;
	pinfo.lcdc.h_front_porch = 8;//8->14
	pinfo.lcdc.h_pulse_width = 20;
	pinfo.lcdc.v_back_porch = 8;
	pinfo.lcdc.v_front_porch = 8;
	pinfo.lcdc.v_pulse_width = 2;
#endif

#endif
	pinfo.lcdc.border_clr = 0;	/* blk */
	pinfo.lcdc.underflow_clr = 0xff;	/* blue */
	pinfo.lcdc.hsync_skew = 0;
	pinfo.bl_max = 16;
	pinfo.bl_min = 1;
	pinfo.fb_num = 2;
#if defined(MIPI_CLOCK_370MBPS)
    	pinfo.clk_rate = 370000000;
#elif defined(MIPI_CLOCK_350MBPS)
    	pinfo.clk_rate = 350000000;
#elif defined(MIPI_CLOCK_334MBPS)
    	pinfo.clk_rate = 334000000;
#elif defined(MIPI_CLOCK_330MBPS)
    	pinfo.clk_rate = 330000000;
#elif defined(MIPI_CLOCK_327MBPS)
    	pinfo.clk_rate = 327000000;
#elif defined(MIPI_CLOCK_328MBPS)
    	pinfo.clk_rate = 328000000;
#elif defined(MIPI_CLOCK_320MBPS)
    	pinfo.clk_rate = 320000000;
#else
    	pinfo.clk_rate = 300000000;
#endif
	pinfo.mipi.mode = DSI_VIDEO_MODE;    

	pinfo.mipi.pulse_mode_hsa_he = TRUE;
	pinfo.mipi.hfp_power_stop = FALSE;
	pinfo.mipi.hbp_power_stop = TRUE;  
	pinfo.mipi.hsa_power_stop = TRUE; 
	pinfo.mipi.eof_bllp_power_stop = TRUE; 
	pinfo.mipi.bllp_power_stop = TRUE;
	pinfo.mipi.traffic_mode = DSI_BURST_MODE;
	pinfo.mipi.dst_format = DSI_VIDEO_DST_FORMAT_RGB888;
	pinfo.mipi.vc = 0;
	pinfo.mipi.rgb_swap = DSI_RGB_SWAP_RGB;
	pinfo.mipi.data_lane0 = TRUE;
	pinfo.mipi.data_lane1 = TRUE;
#if defined(MIPI_CLOCK_350MBPS)
	pinfo.mipi.t_clk_post =0x21;
	pinfo.mipi.t_clk_pre =0x2e;
#elif defined(MIPI_CLOCK_370MBPS)
	pinfo.mipi.t_clk_post =0x21;
	pinfo.mipi.t_clk_pre =0x2e;
#elif defined(MIPI_CLOCK_334MBPS)
	pinfo.mipi.t_clk_post =0x21;
	pinfo.mipi.t_clk_pre =0x2e;
#elif defined(MIPI_CLOCK_330MBPS)
	pinfo.mipi.t_clk_post =0x21;
	pinfo.mipi.t_clk_pre =0x2e;
#elif defined(MIPI_CLOCK_327MBPS)
	pinfo.mipi.t_clk_post =0x21;
	pinfo.mipi.t_clk_pre =0x2d;
#elif defined(MIPI_CLOCK_328MBPS)
	pinfo.mipi.t_clk_post =0x21;
	pinfo.mipi.t_clk_pre =0x2d;
#elif defined(MIPI_CLOCK_320MBPS)
	pinfo.mipi.t_clk_post =0x21;
	pinfo.mipi.t_clk_pre =0x2d;
#else
    pinfo.mipi.t_clk_post =0x21;
	pinfo.mipi.t_clk_pre =0x2d;
#endif

	pinfo.mipi.esc_byte_ratio = 2;
	pinfo.mipi.stream = 0; /* dma_p */
	pinfo.mipi.mdp_trigger = 0;
	pinfo.mipi.dma_trigger = DSI_CMD_TRIGGER_SW;
//	pinfo.mipi.frame_rate = 60;
	pinfo.mipi.frame_rate = 56;
	pinfo.mipi.dsi_phy_db = &dsi_video_mode_phy_db;
	pinfo.mipi.tx_eot_append = TRUE;
	pinfo.mipi.force_clk_lane_hs = 1;

	ret = mipi_lgd_device_register(&pinfo, MIPI_DSI_PRIM,
						MIPI_DSI_PANEL_WVGA_PT);
	if (ret)
		printk(KERN_ERR "%s: failed to register device!\n", __func__);

	return ret;
}

module_init(mipi_video_lgd_wvga_pt_init);


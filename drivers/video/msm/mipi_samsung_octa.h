
/* Copyright (c) 2009-2010, Code Aurora Forum. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are
 * met:
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above
 *       copyright notice, this list of conditions and the following
 *       disclaimer in the documentation and/or other materials provided
 *       with the distribution.
 *     * Neither the name of Code Aurora Forum, Inc. nor the names of its
 *       contributors may be used to endorse or promote products derived
 *       from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED "AS IS" AND ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS
 * BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR
 * BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
 * OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN
 * IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */

#ifndef MIPI_OSCAR_H
#define MIPI_OSCAR_H
#include "msm_fb.h"
#include "mipi_dsi.h"

struct Lcd_State_Info {
    boolean disp_powered_up;
    boolean disp_initialized;
    boolean disp_on;
	boolean backlightoff;
	boolean backlight_cnt;
	boolean backlight_control;
	boolean firstCnt;
	boolean chargerFlag;
	//for mtp read
#ifdef CONFIG_F_SKYDISP_SMART_DIMMING
	char mtp_buffer[30];
	char gamma_buffer[13][25];
	int mtp_count;
	boolean CompleteSmart;
	struct delayed_work mtp_work;
#endif
#ifdef CONFIG_F_SKYDISP_ACL_FOR_AMOLED
	boolean acl_flag;
	int acl_data;
#endif
#ifdef CONFIG_F_SKYDISP_LCD_MIPI_CELL
	volatile int Cell_read_flag;
	int id_read_val;
#endif

	struct dsi_buf oscar_tx_buf;
	struct dsi_buf oscar_rx_buf;
	struct dcs_cmd_req cmdreq;

	struct msm_panel_common_pdata * mipi_oscar_pdata;

	
};

int mipi_oscar_device_register(struct msm_panel_info *pinfo,
					u32 channel, u32 panel);
extern struct Lcd_State_Info Oscar_State;

#endif  /* MIPI_SAMSUNG_H */


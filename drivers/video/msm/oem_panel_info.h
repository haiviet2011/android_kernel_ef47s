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

#ifndef MIPI_OEM_OSCAR_H
#define MIPI_OEM_OSCAR_H

char Gamma_Set190[26] = {0xfa,0x02,0x58,0x42,0x56,0xA7,0xBF,0xAA,0xB2,0xC1,0xB9,0xBC,0xC7,0xBE,0x91,0x9F,0x90,0xAD,0xB5,0xAB,0x00,0xC5,0x00,0xB8,0x00,0xE3};
char Gamma_Set180[26] = {0xfa,0x02,0x58,0x42,0x56,0xAB,0xC2,0xAE,0xB3,0xC1,0xB9,0xBB,0xC6,0xBE,0x91,0x9F,0x90,0xAE,0xB5,0xAB,0x00,0xC1,0x00,0xB5,0x00,0xDE};
char Gamma_Set170[26] = {0xfa,0x02,0x58,0x42,0x56,0xAF,0xC5,0xB2,0xB1,0xC0,0xB6,0xBD,0xC8,0xC1,0x90,0x9E,0x8F,0xAF,0xB7,0xAD,0x00,0xBD,0x00,0xB1,0x00,0xD9};
char Gamma_Set160[26] = {0xfa,0x02,0x58,0x42,0x56,0xA2,0xB7,0xA5,0xB3,0xC2,0xB9,0xC0,0xCA,0xC4,0x90,0x9E,0x8F,0xB0,0xB8,0xAF,0x00,0xB8,0x00,0xAC,0x00,0xD3};
char Gamma_Set150[26] = {0xfa,0x02,0x58,0x42,0x56,0xA6,0xBA,0xA9,0xB1,0xC1,0xB6,0xC2,0xCC,0xC7,0x8E,0x9D,0x8D,0xB2,0xBA,0xB1,0x00,0xB4,0x00,0xA9,0x00,0xCF};
char Gamma_Set140[26] = {0xfa,0x02,0x58,0x42,0x56,0xAA,0xBE,0xAC,0xB1,0xC1,0xB6,0xBF,0xC9,0xC5,0x90,0x9F,0x8F,0xB3,0xBB,0xB3,0x00,0xAF,0x00,0xA4,0x00,0xC9};
char Gamma_Set130[26] = {0xfa,0x02,0x58,0x42,0x56,0xA2,0xB3,0xA4,0xAD,0xBF,0xB2,0xC1,0xCB,0xC8,0x90,0x9F,0x8F,0xB5,0xBD,0xB4,0x00,0xAB,0x00,0x9F,0x00,0xC3};
char Gamma_Set120[26] = {0xfa,0x02,0x58,0x42,0x56,0xA2,0xB3,0xA4,0xB0,0xC1,0xB4,0xC6,0xD0,0xCD,0x8E,0x9E,0x8C,0xB7,0xBF,0xB7,0x00,0xA6,0x00,0x9B,0x00,0xBD};
char Gamma_Set110[26] = {0xfa,0x02,0x58,0x42,0x56,0xA7,0xB7,0xA9,0xAF,0xC0,0xB2,0xC5,0xCF,0xCC,0x8E,0x9E,0x8D,0xB7,0xBF,0xB7,0x00,0xA2,0x00,0x97,0x00,0xB8};
char Gamma_Set100[26] = {0xfa,0x02,0x58,0x42,0x56,0x9E,0xAC,0xA0,0xAB,0xBD,0xAE,0xC7,0xD1,0xCE,0x90,0x9F,0x8F,0xB8,0xC0,0xB8,0x00,0x9D,0x00,0x92,0x00,0xB3};
char Gamma_Set90[26]  = {0xfa,0x02,0x58,0x42,0x56,0xA4,0xB0,0xA6,0xA9,0xBD,0xAC,0xC6,0xD0,0xCE,0x91,0xA1,0x91,0xB9,0xC1,0xB9,0x00,0x98,0x00,0x8E,0x00,0xAD};
char Gamma_Set80[26]  = {0xfa,0x02,0x58,0x42,0x56,0x95,0x9F,0x97,0xAA,0xBE,0xAD,0xC5,0xD0,0xCC,0x90,0xA0,0x91,0xB9,0xC2,0xB9,0x00,0x93,0x00,0x89,0x00,0xA8};
char Gamma_Set70[26]  = {0xfa,0x02,0x58,0x42,0x56,0x9B,0xA3,0x9C,0xAB,0xBF,0xAD,0xC4,0xCF,0xCA,0x90,0xA0,0x92,0xBB,0xC4,0xBB,0x00,0x8D,0x00,0x84,0x00,0xA1};




char Etc_Cond_Set1_0[3] = {0xF0,0x5A,0x5A};
char Etc_Cond_Set1_1[3] = {0xF1,0x5A,0x5A};
char Etc_Cond_Set1_2[3] = {0xFC,0x5A,0x5A};

char Panel_Cond_Set[14] = {0xF8,0x27,0x27,0x08,0x08,0x4E,0xAA,0x5E,0x8A,0x10,0x3F,0x10,0x10,0x00};
char Gamma_Set[26]      = {0xfa,0x02,0x58,0x42,0x56,0x9B,0xA3,0x9C,0xAB,0xBF,0xAD,0xC4,0xCF,0xCA,0x90,0xA0,0x92,0xBB,0xC4,0xBB,0x00,0x8D,0x00,0x84,0x00,0xA1};


char Gamma_Set_Eable[2] = {0xFA,0x03};

char Etc_cond_Set2_0[4] = {0xF6,0x00,0x84,0x09};

char Etc_cond_Set2_1[2] = {0xB0,0x09};
char Etc_cond_Set2_2[2] = {0xD5,0x64};
char Etc_cond_Set2_3[2] = {0xB0,0x0B};

char Etc_cond_Set2_4[4] = {0xD5,0xA4,0x7E,0x20};

char Etc_cond_Set2_5[2] = {0xB0,0x08};
char Etc_cond_Set2_6[2] = {0xFD,0xF8};
char Etc_cond_Set2_7[2] = {0xB0,0x04};
char Etc_cond_Set2_8[2] = {0xF2,0x4D};
char Etc_cond_Set2_9[2] = {0xB0,0x05};
char Etc_cond_Set2_10[2]= {0xFD,0x1F};

char Etc_cond_Set2_11[4]= {0xb1,0x01,0x00,0x16};
char Etc_cond_Set2_12[5]= {0xb2,0x15,0x15,0x15,0x15};
char Etc_cond_Set2_13[1]= {0x11};//0x05

char Memory_Window_Set2_0[1] = {0x35};
char Memory_Window_Set2_1[5] = {0x2a,0x00,0x1e,0x02,0x39};
char Memory_Window_Set2_2[5] = {0x2b,0x00,0x00,0x03,0xbf};
char Memory_Window_Set2_3[2] = {0xd1,0x8a};

char dis_on[1] 			= {0x29};//sleep_out

char dis_off[1] 		= {0x28};
char sleep_in[1]		= {0x10};

#ifdef CONFIG_F_SKYDISP_ACL_FOR_AMOLED
 char acl_on[2] 		 = {0xc0,0x01};
 char acl_off[2]		 = {0xc0,0x00};
 
 char acl_data10[29] = {0xc1,0x47,0x53,0x13,0x53,0x00,0x00,0x01,0xDF,0x00,0x00,0x03,0x1F ,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x05,0x0A,0x11,0x11,0x00};
 char acl_data30[29] = {0xc1,0x47,0x53,0x13,0x53,0x00,0x00,0x01,0xDF,0x00,0x00,0x03,0x1F ,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x02,0x06,0x0D,0x14,0x1C,0x23,0x2C,0x2C,0x00};
 char acl_data50[29] = {0xc1,0x47,0x53,0x13,0x53,0x00,0x00,0x01,0xDF,0x00,0x00,0x03,0x1F ,0x00,0x00,0x00,0x00,0x00,0x00,0x03,0x0F,0x1C,0x28,0x36,0x43,0x51,0x5E,0x5E,0x00};
 
 static struct dsi_cmd_desc oscar_acl_control10[]=
 {
	 
	 {DTYPE_DCS_LWRITE, 1, 0, 0, 0, sizeof(acl_data10), acl_data10}
 };
 
 
 static struct dsi_cmd_desc oscar_acl_control30[]=
 {
	 
	 {DTYPE_DCS_LWRITE, 1, 0, 0, 0, sizeof(acl_data30), acl_data30}
 };
 
 
 static struct dsi_cmd_desc oscar_acl_control50[]=
 {
 
	 {DTYPE_DCS_LWRITE, 1, 0, 0, 0, sizeof(acl_data50), acl_data50}
 };
 
 static struct dsi_cmd_desc oscar_acl_on[]=
 {
	 {DTYPE_DCS_WRITE1, 1, 0, 0, 0, sizeof(acl_on), acl_on}
 };
 
 static struct dsi_cmd_desc oscar_acl_off[]=
 {
	 {DTYPE_DCS_WRITE1, 1, 0, 0, 0, sizeof(acl_off), acl_off}
 
 };
 
#endif

 struct dsi_cmd_desc oscar_sleep_in[]=
{
	{DTYPE_DCS_WRITE, 1, 0, 0, 0, sizeof(dis_off), dis_off},
	{DTYPE_DCS_WRITE, 1, 0, 0, 120, sizeof(sleep_in), sleep_in}
};

 struct dsi_cmd_desc oscar_sleep_out[]=
{
	{DTYPE_DCS_WRITE, 1, 0, 0, 0, sizeof(dis_on), dis_on}
};



 struct dsi_cmd_desc oscar_display_init_cmds[]=
{
	{DTYPE_DCS_LWRITE, 1, 0, 0, 0, sizeof(Etc_Cond_Set1_0), Etc_Cond_Set1_0},
	{DTYPE_DCS_LWRITE, 1, 0, 0, 0, sizeof(Etc_Cond_Set1_1), Etc_Cond_Set1_1},
	{DTYPE_DCS_LWRITE, 1, 0, 0, 0, sizeof(Etc_Cond_Set1_2), Etc_Cond_Set1_2},
	{DTYPE_DCS_LWRITE, 1, 0, 0, 0, sizeof(Panel_Cond_Set), Panel_Cond_Set},
	{DTYPE_DCS_LWRITE, 1, 0, 0, 0, sizeof(Gamma_Set70), Gamma_Set70},
	
	{DTYPE_DCS_WRITE1, 1, 0, 0, 0, sizeof(Gamma_Set_Eable), Gamma_Set_Eable},
	
	{DTYPE_DCS_LWRITE, 1, 0, 0, 0, sizeof(Etc_cond_Set2_0), Etc_cond_Set2_0},
	
	{DTYPE_DCS_WRITE1, 1, 0, 0, 0, sizeof(Etc_cond_Set2_1), Etc_cond_Set2_1},
	{DTYPE_DCS_WRITE1, 1, 0, 0, 0, sizeof(Etc_cond_Set2_2), Etc_cond_Set2_2},
	{DTYPE_DCS_WRITE1, 1, 0, 0, 0, sizeof(Etc_cond_Set2_3), Etc_cond_Set2_3},
	
	{DTYPE_DCS_LWRITE, 1, 0, 0, 0, sizeof(Etc_cond_Set2_4), Etc_cond_Set2_4},
	
	{DTYPE_DCS_WRITE1, 1, 0, 0, 0, sizeof(Etc_cond_Set2_5), Etc_cond_Set2_5},
	{DTYPE_DCS_WRITE1, 1, 0, 0, 0, sizeof(Etc_cond_Set2_6), Etc_cond_Set2_6},
	{DTYPE_DCS_WRITE1, 1, 0, 0, 0, sizeof(Etc_cond_Set2_7), Etc_cond_Set2_7},
	{DTYPE_DCS_WRITE1, 1, 0, 0, 0, sizeof(Etc_cond_Set2_8), Etc_cond_Set2_8},
	{DTYPE_DCS_WRITE1, 1, 0, 0, 0, sizeof(Etc_cond_Set2_9), Etc_cond_Set2_9},
	{DTYPE_DCS_WRITE1, 1, 0, 0, 0, sizeof(Etc_cond_Set2_10), Etc_cond_Set2_10},
	
	{DTYPE_DCS_LWRITE, 1, 0, 0, 0, sizeof(Etc_cond_Set2_11), Etc_cond_Set2_11},
	{DTYPE_DCS_LWRITE, 1, 0, 0, 0, sizeof(Etc_cond_Set2_12), Etc_cond_Set2_12},
	
	{DTYPE_DCS_WRITE, 1, 0, 0, 120, sizeof(Etc_cond_Set2_13), Etc_cond_Set2_13},

	{DTYPE_DCS_WRITE, 1, 0, 0, 0, sizeof(Memory_Window_Set2_0), Memory_Window_Set2_0},
	{DTYPE_DCS_LWRITE, 1, 0, 0, 0, sizeof(Memory_Window_Set2_1), Memory_Window_Set2_1},
	{DTYPE_DCS_LWRITE, 1, 0, 0, 0, sizeof(Memory_Window_Set2_2), Memory_Window_Set2_2},
	{DTYPE_DCS_WRITE1, 1, 0, 0, 0, sizeof(Memory_Window_Set2_3), Memory_Window_Set2_3},

#ifdef CONFIG_F_SKYDISP_ACL_FOR_AMOLED
	{DTYPE_DCS_WRITE1, 1, 0, 0, 0, sizeof(acl_on), acl_on},
	{DTYPE_DCS_LWRITE, 1, 0, 0, 0, sizeof(acl_data10), acl_data10}

#endif
};
 
 struct dsi_cmd_desc oscar_backlight_190_cmds[]=
{
	{DTYPE_DCS_LWRITE, 1, 0, 0, 0, sizeof(Gamma_Set190), Gamma_Set190},
	{DTYPE_DCS_WRITE1, 1, 0, 0, 0, sizeof(Gamma_Set_Eable), Gamma_Set_Eable}

};

 struct dsi_cmd_desc oscar_backlight_180_cmds[]=
{
	{DTYPE_DCS_LWRITE, 1, 0, 0, 0, sizeof(Gamma_Set180), Gamma_Set180},
	{DTYPE_DCS_WRITE1, 1, 0, 0, 0, sizeof(Gamma_Set_Eable), Gamma_Set_Eable}

};
 struct dsi_cmd_desc oscar_backlight_170_cmds[]=
{
	{DTYPE_DCS_LWRITE, 1, 0, 0, 0, sizeof(Gamma_Set170), Gamma_Set170},
	{DTYPE_DCS_WRITE1, 1, 0, 0, 0, sizeof(Gamma_Set_Eable), Gamma_Set_Eable}

};

 struct dsi_cmd_desc oscar_backlight_160_cmds[]=
{
	{DTYPE_DCS_LWRITE, 1, 0, 0, 0, sizeof(Gamma_Set160), Gamma_Set160},
	{DTYPE_DCS_WRITE1, 1, 0, 0, 0, sizeof(Gamma_Set_Eable), Gamma_Set_Eable}

};
 struct dsi_cmd_desc oscar_backlight_150_cmds[]=
{
	{DTYPE_DCS_LWRITE, 1, 0, 0, 0, sizeof(Gamma_Set150), Gamma_Set150},
	{DTYPE_DCS_WRITE1, 1, 0, 0, 0, sizeof(Gamma_Set_Eable), Gamma_Set_Eable}

};

 struct dsi_cmd_desc oscar_backlight_140_cmds[]=
{
	{DTYPE_DCS_LWRITE, 1, 0, 0, 0, sizeof(Gamma_Set140), Gamma_Set140},
	{DTYPE_DCS_WRITE1, 1, 0, 0, 0, sizeof(Gamma_Set_Eable), Gamma_Set_Eable}

};
 struct dsi_cmd_desc oscar_backlight_130_cmds[]=
{
	{DTYPE_DCS_LWRITE, 1, 0, 0, 0, sizeof(Gamma_Set130), Gamma_Set130},
	{DTYPE_DCS_WRITE1, 1, 0, 0, 0, sizeof(Gamma_Set_Eable), Gamma_Set_Eable}

};

 struct dsi_cmd_desc oscar_backlight_120_cmds[]=
{
	{DTYPE_DCS_LWRITE, 1, 0, 0, 0, sizeof(Gamma_Set120), Gamma_Set120},
	{DTYPE_DCS_WRITE1, 1, 0, 0, 0, sizeof(Gamma_Set_Eable), Gamma_Set_Eable}

};

 struct dsi_cmd_desc oscar_backlight_110_cmds[]=
{
	{DTYPE_DCS_LWRITE, 1, 0, 0, 0, sizeof(Gamma_Set110), Gamma_Set110},
	{DTYPE_DCS_WRITE1, 1, 0, 0, 0, sizeof(Gamma_Set_Eable), Gamma_Set_Eable}

};

 struct dsi_cmd_desc oscar_backlight_100_cmds[]=
{
	{DTYPE_DCS_LWRITE, 1, 0, 0, 0, sizeof(Gamma_Set100), Gamma_Set100},
	{DTYPE_DCS_WRITE1, 1, 0, 0, 0, sizeof(Gamma_Set_Eable), Gamma_Set_Eable}

};
 struct dsi_cmd_desc oscar_backlight_90_cmds[]=
{
	{DTYPE_DCS_LWRITE, 1, 0, 0, 0, sizeof(Gamma_Set90), Gamma_Set90},
	{DTYPE_DCS_WRITE1, 1, 0, 0, 0, sizeof(Gamma_Set_Eable), Gamma_Set_Eable}

};

 struct dsi_cmd_desc oscar_backlight_80_cmds[]=
{
	{DTYPE_DCS_LWRITE, 1, 0, 0, 0, sizeof(Gamma_Set80), Gamma_Set80},
	{DTYPE_DCS_WRITE1, 1, 0, 0, 0, sizeof(Gamma_Set_Eable), Gamma_Set_Eable}

};
 struct dsi_cmd_desc oscar_backlight_70_cmds[]=
{
	{DTYPE_DCS_LWRITE, 1, 0, 0, 0, sizeof(Gamma_Set70), Gamma_Set70},
	{DTYPE_DCS_WRITE1, 1, 0, 0, 0, sizeof(Gamma_Set_Eable), Gamma_Set_Eable}

};
 #ifdef CONFIG_F_SKYDISP_LCD_MIPI_CELL
char ID_read[1] 		= {0xD4};//sleep_out
char Cell_on[2] 		= {0xB1,0x0B};
char Cell_off[2] 		= {0xB1,0x0A};

char Cell_on300[5] 		= {0xB2};
char Cell_on200[5] 		= {0xB2};
char Cell_on160[5] 		= {0xB2};
char Cell_on90[5] 		= {0xB2};

static struct dsi_cmd_desc oscar_panel_cell=
{
	DTYPE_DCS_READ, 1, 0, 0, 5, sizeof(ID_read), ID_read
};
static struct dsi_cmd_desc Cell_on_cmd[]=
{
	{DTYPE_DCS_WRITE1, 1, 0, 0, 0, sizeof(Cell_on), Cell_on},
	{DTYPE_DCS_LWRITE, 1, 0, 0, 0, sizeof(Cell_on90), Cell_on90}
};


#endif
 #ifdef CONFIG_F_SKYDISP_SMART_DIMMING
//for smart dimming ----------------------------------------------
char read_panel[2]	= { 0xd3, 0x00 };
char write_gpara1[2]		= { 0xB0, 0x0A };
char write_gpara2[2]		= { 0xB0, 0x14 };

struct dsi_cmd_desc samsung_oled_hd_read_panel[] ={
	{DTYPE_DCS_READ, 1, 0, 0, 0, sizeof(read_panel), read_panel},
};
 
struct dsi_cmd_desc samsung_oled_hd_gpara11_cmd[] ={
	 { DTYPE_DCS_LWRITE, 1, 0, 1, 0, sizeof(write_gpara1), write_gpara1},
};
struct dsi_cmd_desc samsung_oled_hd_gpara21_cmd[] ={
	 { DTYPE_DCS_LWRITE, 1, 0, 1, 0, sizeof(write_gpara2), write_gpara2},
};
//--------------------------------------------------------------

char Smart_Gamma_Set190[26];
char Smart_Gamma_Set180[26];
char Smart_Gamma_Set170[26];
char Smart_Gamma_Set160[26];
char Smart_Gamma_Set150[26];
char Smart_Gamma_Set140[26];
char Smart_Gamma_Set130[26];
char Smart_Gamma_Set120[26];
char Smart_Gamma_Set110[26];
char Smart_Gamma_Set100[26];
char Smart_Gamma_Set90[26];
char Smart_Gamma_Set80[26];
char Smart_Gamma_Set70[26];

static struct dsi_cmd_desc Smart_oscar_backlight_190_cmds[]=
{
	{DTYPE_DCS_LWRITE, 1, 0, 0, 0, sizeof(Smart_Gamma_Set190), Smart_Gamma_Set190},
	{DTYPE_DCS_WRITE1, 1, 0, 0, 0, sizeof(Gamma_Set_Eable), Gamma_Set_Eable}
#ifdef CONFIG_F_SKYDISP_LCD_MIPI_CELL
	,{DTYPE_DCS_LWRITE, 1, 0, 0, 0, sizeof(Cell_on200), Cell_on200}
#endif
};

static struct dsi_cmd_desc Smart_oscar_backlight_180_cmds[]=
{
	{DTYPE_DCS_LWRITE, 1, 0, 0, 0, sizeof(Smart_Gamma_Set180), Smart_Gamma_Set180},
	{DTYPE_DCS_WRITE1, 1, 0, 0, 0, sizeof(Gamma_Set_Eable), Gamma_Set_Eable}
#ifdef CONFIG_F_SKYDISP_LCD_MIPI_CELL
	,{DTYPE_DCS_LWRITE, 1, 0, 0, 0, sizeof(Cell_on200), Cell_on200}
#endif
};
static struct dsi_cmd_desc Smart_oscar_backlight_170_cmds[]=
{
	{DTYPE_DCS_LWRITE, 1, 0, 0, 0, sizeof(Smart_Gamma_Set170), Smart_Gamma_Set170},
	{DTYPE_DCS_WRITE1, 1, 0, 0, 0, sizeof(Gamma_Set_Eable), Gamma_Set_Eable}
#ifdef CONFIG_F_SKYDISP_LCD_MIPI_CELL
	,{DTYPE_DCS_LWRITE, 1, 0, 0, 0, sizeof(Cell_on200), Cell_on200}
#endif
};

static struct dsi_cmd_desc Smart_oscar_backlight_160_cmds[]=
{
	{DTYPE_DCS_LWRITE, 1, 0, 0, 0, sizeof(Smart_Gamma_Set160), Smart_Gamma_Set160},
	{DTYPE_DCS_WRITE1, 1, 0, 0, 0, sizeof(Gamma_Set_Eable), Gamma_Set_Eable}
#ifdef CONFIG_F_SKYDISP_LCD_MIPI_CELL
	,{DTYPE_DCS_LWRITE, 1, 0, 0, 0, sizeof(Cell_on200), Cell_on200}
#endif
};
static struct dsi_cmd_desc Smart_oscar_backlight_150_cmds[]=
{
	{DTYPE_DCS_LWRITE, 1, 0, 0, 0, sizeof(Smart_Gamma_Set150), Smart_Gamma_Set150},
	{DTYPE_DCS_WRITE1, 1, 0, 0, 0, sizeof(Gamma_Set_Eable), Gamma_Set_Eable}
#ifdef CONFIG_F_SKYDISP_LCD_MIPI_CELL
	,{DTYPE_DCS_LWRITE, 1, 0, 0, 0, sizeof(Cell_on160), Cell_on160}
#endif
};

static struct dsi_cmd_desc Smart_oscar_backlight_140_cmds[]=
{
	{DTYPE_DCS_LWRITE, 1, 0, 0, 0, sizeof(Smart_Gamma_Set140), Smart_Gamma_Set140},
	{DTYPE_DCS_WRITE1, 1, 0, 0, 0, sizeof(Gamma_Set_Eable), Gamma_Set_Eable}
#ifdef CONFIG_F_SKYDISP_LCD_MIPI_CELL
	,{DTYPE_DCS_LWRITE, 1, 0, 0, 0, sizeof(Cell_on160), Cell_on160}
#endif
};
static struct dsi_cmd_desc Smart_oscar_backlight_130_cmds[]=
{
	{DTYPE_DCS_LWRITE, 1, 0, 0, 0, sizeof(Smart_Gamma_Set130), Smart_Gamma_Set130},
	{DTYPE_DCS_WRITE1, 1, 0, 0, 0, sizeof(Gamma_Set_Eable), Gamma_Set_Eable}
#ifdef CONFIG_F_SKYDISP_LCD_MIPI_CELL
	,{DTYPE_DCS_LWRITE, 1, 0, 0, 0, sizeof(Cell_on160), Cell_on160}
#endif
};

static struct dsi_cmd_desc Smart_oscar_backlight_120_cmds[]=
{
	{DTYPE_DCS_LWRITE, 1, 0, 0, 0, sizeof(Smart_Gamma_Set120), Smart_Gamma_Set120},
	{DTYPE_DCS_WRITE1, 1, 0, 0, 0, sizeof(Gamma_Set_Eable), Gamma_Set_Eable}
#ifdef CONFIG_F_SKYDISP_LCD_MIPI_CELL
	,{DTYPE_DCS_LWRITE, 1, 0, 0, 0, sizeof(Cell_on160), Cell_on160}
#endif
};

static struct dsi_cmd_desc Smart_oscar_backlight_110_cmds[]=
{
	{DTYPE_DCS_LWRITE, 1, 0, 0, 0, sizeof(Smart_Gamma_Set110), Smart_Gamma_Set110},
	{DTYPE_DCS_WRITE1, 1, 0, 0, 0, sizeof(Gamma_Set_Eable), Gamma_Set_Eable}
#ifdef CONFIG_F_SKYDISP_LCD_MIPI_CELL
	,{DTYPE_DCS_LWRITE, 1, 0, 0, 0, sizeof(Cell_on160), Cell_on160}
#endif
};

static struct dsi_cmd_desc Smart_oscar_backlight_100_cmds[]=
{
	{DTYPE_DCS_LWRITE, 1, 0, 0, 0, sizeof(Smart_Gamma_Set100), Smart_Gamma_Set100},
	{DTYPE_DCS_WRITE1, 1, 0, 0, 0, sizeof(Gamma_Set_Eable), Gamma_Set_Eable}
#ifdef CONFIG_F_SKYDISP_LCD_MIPI_CELL
	,{DTYPE_DCS_LWRITE, 1, 0, 0, 0, sizeof(Cell_on160), Cell_on160}
#endif
};
static struct dsi_cmd_desc Smart_oscar_backlight_90_cmds[]=
{
	{DTYPE_DCS_LWRITE, 1, 0, 0, 0, sizeof(Smart_Gamma_Set90), Smart_Gamma_Set90},
	{DTYPE_DCS_WRITE1, 1, 0, 0, 0, sizeof(Gamma_Set_Eable), Gamma_Set_Eable}
#ifdef CONFIG_F_SKYDISP_LCD_MIPI_CELL
	,{DTYPE_DCS_LWRITE, 1, 0, 0, 0, sizeof(Cell_on90), Cell_on90}
#endif
};

static struct dsi_cmd_desc Smart_oscar_backlight_80_cmds[]=
{
	{DTYPE_DCS_LWRITE, 1, 0, 0, 0, sizeof(Smart_Gamma_Set80), Smart_Gamma_Set80},
	{DTYPE_DCS_WRITE1, 1, 0, 0, 0, sizeof(Gamma_Set_Eable), Gamma_Set_Eable}
#ifdef CONFIG_F_SKYDISP_LCD_MIPI_CELL
	,{DTYPE_DCS_LWRITE, 1, 0, 0, 0, sizeof(Cell_on90), Cell_on90}
#endif
};
static struct dsi_cmd_desc Smart_oscar_backlight_70_cmds[]=
{
	{DTYPE_DCS_LWRITE, 1, 0, 0, 0, sizeof(Smart_Gamma_Set70), Smart_Gamma_Set70},
	{DTYPE_DCS_WRITE1, 1, 0, 0, 0, sizeof(Gamma_Set_Eable), Gamma_Set_Eable}
#ifdef CONFIG_F_SKYDISP_LCD_MIPI_CELL
	,{DTYPE_DCS_LWRITE, 1, 0, 0, 0, sizeof(Cell_on90), Cell_on90}
#endif
};
#endif


#endif

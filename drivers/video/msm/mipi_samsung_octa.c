/* Copyright (c) 2008-2010, Code Aurora Forum. All rights reserved.
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
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
 * 02110-1301, USA.
 *
 */

#include "msm_fb.h"
#include "mipi_dsi.h"
#include "oem_panel_info.h"
#include "mipi_samsung_octa.h"
#include <mach/gpio.h>
#include <asm/irq.h>
#include <asm/system.h>
#include <linux/platform_device.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include "mdp4.h"

#define GPIO_HIGH_VALUE 1
#define GPIO_LOW_VALUE  0

extern struct fb_info *registered_fb[FB_MAX]; //kernel FB

struct Lcd_State_Info Oscar_State = {0,};
#ifdef CONFIG_F_SKYDISP_LCD_MIPI_CELL
static void mipi_oscar_cell_read(void);
#endif

static int mipi_oscar_lcd_on(struct platform_device *pdev)
{


	struct msm_fb_data_type *mfd;
	struct fb_info *fbi;

	mfd = platform_get_drvdata(pdev);
	fbi = mfd->fbi;
	if (!mfd)
		return -ENODEV;
	if (mfd->key != MFD_KEY)
		return -EINVAL;


	if (Oscar_State.disp_initialized == false) {
		mdelay(10);
		mipi_set_tx_power_mode(0);	
		
		Oscar_State.cmdreq.cmds = oscar_display_init_cmds;
		Oscar_State.cmdreq.cmds_cnt = ARRAY_SIZE(oscar_display_init_cmds);
		Oscar_State.cmdreq.flags = CMD_REQ_COMMIT;
		Oscar_State.cmdreq.rlen = 0;
		Oscar_State.cmdreq.cb = NULL;
		mipi_dsi_cmdlist_put(&Oscar_State.cmdreq);


#ifdef CONFIG_F_SKYDISP_ACL_FOR_AMOLED						
		
		switch(Oscar_State.acl_data)
		{
			case 10: Oscar_State.cmdreq.cmds = oscar_acl_control10;
					 Oscar_State.cmdreq.cmds_cnt = ARRAY_SIZE(oscar_acl_control10);
				break;
			case 30: 
					 Oscar_State.cmdreq.cmds = oscar_acl_control30;
					 Oscar_State.cmdreq.cmds_cnt = ARRAY_SIZE(oscar_acl_control30);
						
				break;
			case 50: 	
					 Oscar_State.cmdreq.cmds = oscar_acl_control50;
					 Oscar_State.cmdreq.cmds_cnt = ARRAY_SIZE(oscar_acl_control50);
				break;
		}
		
		Oscar_State.cmdreq.flags = CMD_REQ_COMMIT;
		Oscar_State.cmdreq.rlen = 0;
		Oscar_State.cmdreq.cb = NULL;
		mipi_dsi_cmdlist_put(&Oscar_State.cmdreq);		
#endif	

		mipi_set_tx_power_mode(1);

		if(Oscar_State.Cell_read_flag == false){				   //read ID3
			mipi_dsi_cmd_bta_sw_trigger(); 
			mipi_oscar_cell_read();
			pr_info("oscar_mipi_cell-read\n");
			Oscar_State.Cell_read_flag = true;
		}
#ifdef CONFIG_F_SKYDISP_LCD_MIPI_CELL
		mipi_set_tx_power_mode(0);					//after read id, 
		Oscar_State.cmdreq.cmds = Cell_on_cmd;
		Oscar_State.cmdreq.cmds_cnt = ARRAY_SIZE(Cell_on_cmd);
		Oscar_State.cmdreq.flags = CMD_REQ_COMMIT;
		Oscar_State.cmdreq.rlen = 0;
		Oscar_State.cmdreq.cb = NULL;
		mipi_dsi_cmdlist_put(&Oscar_State.cmdreq);

		mipi_set_tx_power_mode(1);		
#endif

		Oscar_State.disp_initialized = true;
		pr_info("[%s on] Oscar_State.acl_data = %d",__func__,Oscar_State.acl_data);
	}


	Oscar_State.disp_on = true;



	return 0;
}

static int mipi_oscar_lcd_off(struct platform_device *pdev)
{
	struct msm_fb_data_type *mfd;



	mfd = platform_get_drvdata(pdev);

	if (!mfd)
		return -ENODEV;
	if (mfd->key != MFD_KEY)
		return -EINVAL;

	if (Oscar_State.disp_on == true) {
	
		mipi_set_tx_power_mode(0);	
			
		Oscar_State.cmdreq.cmds = oscar_sleep_in;
		Oscar_State.cmdreq.cmds_cnt = ARRAY_SIZE(oscar_sleep_in);
		Oscar_State.cmdreq.flags = CMD_REQ_COMMIT;
		Oscar_State.cmdreq.rlen = 0;
		Oscar_State.cmdreq.cb = NULL;
		mipi_dsi_cmdlist_put(&Oscar_State.cmdreq);	
		
		mipi_set_tx_power_mode(1);	

		Oscar_State.disp_on = false;
		Oscar_State.disp_initialized = false;
		pr_info("[%s]",__func__);
	}
   	Oscar_State.backlight_cnt = false;
	Oscar_State.disp_powered_up = false;


	return 0;
	
}
static void backlight_lcd_on(void)
{
	
	if(Oscar_State.backlight_cnt == true)
	{
			
			Oscar_State.cmdreq.cmds = oscar_sleep_out;
			Oscar_State.cmdreq.cmds_cnt = ARRAY_SIZE(oscar_sleep_out);
			Oscar_State.cmdreq.flags = CMD_REQ_COMMIT;
			Oscar_State.cmdreq.rlen = 0;
			Oscar_State.cmdreq.cb = NULL;
			mipi_dsi_cmdlist_put(&Oscar_State.cmdreq);	
			
			Oscar_State.backlight_cnt = false;	
			pr_info("[%s] initial LCD on\n",__func__);
	}	


}
static void mipi_oscar_set_backlight(struct msm_fb_data_type *mfd)
{

	if(!mfd)
		return;
	if(mfd->key != MFD_KEY)
		return;
	if(mfd->panel_power_on == FALSE)
		return;
	
	mipi_set_tx_power_mode(0);
	
	backlight_lcd_on();
	
	switch(mfd->bl_level){
		case 13:
#ifdef CONFIG_F_SKYDISP_SMART_DIMMING
			if(Oscar_State.CompleteSmart == true)
				Oscar_State.cmdreq.cmds = Smart_oscar_backlight_190_cmds;
			else
#endif
				Oscar_State.cmdreq.cmds = oscar_backlight_190_cmds;
			break;
		case 12:
#ifdef CONFIG_F_SKYDISP_SMART_DIMMING
			if(Oscar_State.CompleteSmart == true)
				Oscar_State.cmdreq.cmds = Smart_oscar_backlight_180_cmds;				
			else
#endif
				Oscar_State.cmdreq.cmds = oscar_backlight_180_cmds;

			break;
		case 11:
#ifdef CONFIG_F_SKYDISP_SMART_DIMMING	
			if(Oscar_State.CompleteSmart == true)
				Oscar_State.cmdreq.cmds = Smart_oscar_backlight_170_cmds;						
			else
#endif	
				Oscar_State.cmdreq.cmds = oscar_backlight_170_cmds;
						
			break;
		case 10:
#ifdef CONFIG_F_SKYDISP_SMART_DIMMING				
			if(Oscar_State.CompleteSmart == true)
				Oscar_State.cmdreq.cmds = Smart_oscar_backlight_160_cmds;							
			else
#endif	
		    	Oscar_State.cmdreq.cmds = oscar_backlight_160_cmds;
			
			break;
		case 9:
#ifdef CONFIG_F_SKYDISP_SMART_DIMMING	
			if(Oscar_State.CompleteSmart == true)
				Oscar_State.cmdreq.cmds = Smart_oscar_backlight_150_cmds;	
			else
#endif
			Oscar_State.cmdreq.cmds = oscar_backlight_150_cmds;

			break;
		case 8:
#ifdef CONFIG_F_SKYDISP_SMART_DIMMING	
			if(Oscar_State.CompleteSmart == true)
				Oscar_State.cmdreq.cmds = Smart_oscar_backlight_140_cmds;
			else
#endif
				Oscar_State.cmdreq.cmds = oscar_backlight_140_cmds;
				
			break;
		case 7:
#ifdef CONFIG_F_SKYDISP_SMART_DIMMING				
			if(Oscar_State.CompleteSmart == true)
				Oscar_State.cmdreq.cmds = Smart_oscar_backlight_130_cmds;
			else
#endif
				Oscar_State.cmdreq.cmds = oscar_backlight_130_cmds;

			break;
		case 6:
#ifdef CONFIG_F_SKYDISP_SMART_DIMMING	
			if(Oscar_State.CompleteSmart == true)
				Oscar_State.cmdreq.cmds = Smart_oscar_backlight_120_cmds;
			else
#endif
				Oscar_State.cmdreq.cmds = oscar_backlight_120_cmds;
				
			
			break;
		case 5:
#ifdef CONFIG_F_SKYDISP_SMART_DIMMING	
			if(Oscar_State.CompleteSmart == true)
				Oscar_State.cmdreq.cmds = Smart_oscar_backlight_110_cmds;	
			else
#endif
				Oscar_State.cmdreq.cmds = oscar_backlight_110_cmds;

			break;
		case 4:
#ifdef CONFIG_F_SKYDISP_SMART_DIMMING	
			if(Oscar_State.CompleteSmart == true)
				Oscar_State.cmdreq.cmds = Smart_oscar_backlight_100_cmds;			
			else
#endif
				Oscar_State.cmdreq.cmds = oscar_backlight_100_cmds;
				
			break;
		case 3:
#ifdef CONFIG_F_SKYDISP_SMART_DIMMING	
			if(Oscar_State.CompleteSmart == true)
				Oscar_State.cmdreq.cmds = Smart_oscar_backlight_90_cmds;
			else
#endif
				Oscar_State.cmdreq.cmds = oscar_backlight_90_cmds;

			break;
		case 2:
#ifdef CONFIG_F_SKYDISP_SMART_DIMMING	
			if(Oscar_State.CompleteSmart == true)
				Oscar_State.cmdreq.cmds = Smart_oscar_backlight_80_cmds;
			else
#endif
				Oscar_State.cmdreq.cmds = oscar_backlight_80_cmds;

			break;
		case 1:
#ifdef CONFIG_F_SKYDISP_SMART_DIMMING	
			if(Oscar_State.CompleteSmart == true)
				Oscar_State.cmdreq.cmds = Smart_oscar_backlight_70_cmds;
			else
#endif
				Oscar_State.cmdreq.cmds = oscar_backlight_70_cmds;
			
			
			break;
		case 0:
#ifdef CONFIG_F_SKYDISP_SMART_DIMMING
			if(Oscar_State.CompleteSmart == true)
				Oscar_State.cmdreq.cmds = Smart_oscar_backlight_70_cmds;		
			else
#endif	
				Oscar_State.cmdreq.cmds = oscar_backlight_70_cmds;
				
			if(Oscar_State.backlight_control == true)
				Oscar_State.backlight_cnt = true;

			break;

		}
#ifdef CONFIG_F_SKYDISP_SMART_DIMMING
	if(Oscar_State.CompleteSmart == true)
			Oscar_State.cmdreq.cmds_cnt = ARRAY_SIZE(Smart_oscar_backlight_70_cmds);
	else
#endif
			Oscar_State.cmdreq.cmds_cnt = ARRAY_SIZE(oscar_backlight_70_cmds);
	
	Oscar_State.cmdreq.flags = CMD_REQ_COMMIT;
	Oscar_State.cmdreq.rlen = 0;
	Oscar_State.cmdreq.cb = NULL;
	mipi_dsi_cmdlist_put(&Oscar_State.cmdreq);	
	
	mipi_set_tx_power_mode(1);

	pr_info("[%s] Bl_level = %d Oscar_State.CompleteSmart = %s %d\n",__func__,mfd->bl_level,Oscar_State.CompleteSmart ?"On" : "Off",ARRAY_SIZE(Smart_oscar_backlight_70_cmds));

}

extern struct fb_info *registered_fb[FB_MAX]; 
extern int mipi_dsi_cdp_panel_power_Oscar(int on);
void oscar_lcd_poweroff(void)
{
    struct fb_info *info; 
    struct msm_fb_data_type *mfd;

    info = registered_fb[0];
	mfd = (struct msm_fb_data_type *)info->par;
	if(mfd->panel_power_on == FALSE)
		return;
	
	mipi_set_tx_power_mode(0);	

	
	Oscar_State.cmdreq.cmds = oscar_sleep_in;
	Oscar_State.cmdreq.cmds_cnt = ARRAY_SIZE(oscar_sleep_in);
	Oscar_State.cmdreq.flags = CMD_REQ_COMMIT;
	Oscar_State.cmdreq.rlen = 0;
	Oscar_State.cmdreq.cb = NULL;
	mipi_dsi_cmdlist_put(&Oscar_State.cmdreq);	
	
	mipi_set_tx_power_mode(1);	

	mdelay(110);
	//mipi_dsi_cdp_panel_power(0);
	mipi_dsi_cdp_panel_power_Oscar(0);
	pr_info("[%s] \n",__func__);

}

#ifdef CONFIG_F_SKYDISP_ACL_FOR_AMOLED
void acl_data(struct msm_fb_data_type *mfd, int data)
{
	mutex_lock(&mfd->dma->ov_mutex);	

	mipi_set_tx_power_mode(0);

	switch(data){
		case 10 : Oscar_State.cmdreq.cmds = oscar_acl_control10;
		          Oscar_State.cmdreq.cmds_cnt = ARRAY_SIZE(oscar_acl_control10);
			      Oscar_State.acl_data=data;
			break;
		case 30 : Oscar_State.cmdreq.cmds = oscar_acl_control30;
		          Oscar_State.cmdreq.cmds_cnt = ARRAY_SIZE(oscar_acl_control30);
				  Oscar_State.acl_data=data;
			break;
		case 50 : Oscar_State.cmdreq.cmds = oscar_acl_control50;
		          Oscar_State.cmdreq.cmds_cnt = ARRAY_SIZE(oscar_acl_control50);
			      Oscar_State.acl_data=data;
			break;
	}
	Oscar_State.cmdreq.flags = CMD_REQ_COMMIT;
	Oscar_State.cmdreq.rlen = 0;
	Oscar_State.cmdreq.cb = NULL;
	mipi_dsi_cmdlist_put(&Oscar_State.cmdreq);	

	mipi_set_tx_power_mode(1);	
	mutex_unlock(&mfd->dma->ov_mutex);
	pr_info("Oled Acl Data= %d\n",data);
}


void acl_contol(struct msm_fb_data_type *mfd, int state)
{
	mutex_lock(&mfd->dma->ov_mutex);	

	mipi_set_tx_power_mode(0);

	if(state == true){
		Oscar_State.cmdreq.cmds = oscar_acl_on;
		Oscar_State.cmdreq.cmds_cnt = ARRAY_SIZE(oscar_acl_on);
		Oscar_State.acl_flag = true;
	}
	else{ 

		Oscar_State.cmdreq.cmds = oscar_acl_off;
		Oscar_State.cmdreq.cmds_cnt = ARRAY_SIZE(oscar_acl_off);
		Oscar_State.acl_flag = false;
	}
	
	Oscar_State.cmdreq.flags = CMD_REQ_COMMIT;
	Oscar_State.cmdreq.rlen = 0;
	Oscar_State.cmdreq.cb = NULL;
	mipi_dsi_cmdlist_put(&Oscar_State.cmdreq);	
	
	mipi_set_tx_power_mode(1);	
	mutex_unlock(&mfd->dma->ov_mutex);
	pr_info("Oled Acl %s \n",state ? "On" : "Off");
}

#endif
#ifdef CONFIG_F_SKYDISP_LCD_MIPI_CELL
void mipi_samsung_cell_panel(uint8 data)
{
	int i;
	Oscar_State.id_read_val  = data;
	printk("################# = %d\n",data);
	if(Oscar_State.id_read_val != 0x00){
	
		for(i=1; i<5;i++)
		{
			Cell_on300[i] = Oscar_State.id_read_val;
			Cell_on200[i] = Oscar_State.id_read_val + 0x06;
			Cell_on160[i] = Oscar_State.id_read_val + 0x08;
			Cell_on90[i]  = Oscar_State.id_read_val + 0x0B;
			if(Cell_on300[1] >= 0x28)
			{
				Cell_on300[i] = 0x28;
			}
			else if(Cell_on200[1] >= 0x28)
			{
				Cell_on200[i] = 0x28;
			}
			else if(Cell_on160[1] >= 0x28)
			{
				Cell_on160[i] = 0x28;
			}
			else if(Cell_on90[1] >= 0x28)
			{
				Cell_on90[i] = 0x28;
			}

		}
		
	}
	else{
		
		for(i=1; i<5;i++)
		{
			Cell_on300[i] = 0x15;
			Cell_on200[i] = 0x1D;
			Cell_on160[i] = 0x20;
			Cell_on90[i]  = 0x25;
		}
	
	}

	for(i=0; i<5;i++){
		printk("##Cell_on300 = 0x%x \n",Cell_on300[i]);
		printk("##Cell_on200 = 0x%x \n",Cell_on200[i]);
		printk("##Cell_on160 = 0x%x \n",Cell_on160[i]);
		printk("##Cell_on90  = 0x%x \n",Cell_on90[i]);
	}

}
static void mipi_oscar_cell_read(void)
{

	mipi_dsi_cmd_bta_sw_trigger(); 
	Oscar_State.cmdreq.cmds = &oscar_panel_cell; 
	Oscar_State.cmdreq.cmds_cnt = 1; 
	Oscar_State.cmdreq.flags = CMD_REQ_RX | CMD_REQ_COMMIT; 
	Oscar_State.cmdreq.rlen = 1; 
	Oscar_State.cmdreq.cb = mipi_samsung_cell_panel; 
	mipi_dsi_cmdlist_put(&Oscar_State.cmdreq);	
}
#endif

#ifdef CONFIG_F_SKYDISP_SMART_DIMMING
void mtp_write(void)
{

	int jj;
	int ii;
	for(jj=0;jj<25;jj++){
		Smart_Gamma_Set190[jj+1] = Oscar_State.gamma_buffer[0][jj];
		Smart_Gamma_Set180[jj+1] = Oscar_State.gamma_buffer[1][jj];
		Smart_Gamma_Set170[jj+1] = Oscar_State.gamma_buffer[2][jj];
		Smart_Gamma_Set160[jj+1] = Oscar_State.gamma_buffer[3][jj];
		Smart_Gamma_Set150[jj+1] = Oscar_State.gamma_buffer[4][jj];
		Smart_Gamma_Set140[jj+1] = Oscar_State.gamma_buffer[5][jj];
		Smart_Gamma_Set130[jj+1] = Oscar_State.gamma_buffer[6][jj];
		Smart_Gamma_Set120[jj+1] = Oscar_State.gamma_buffer[7][jj];
		Smart_Gamma_Set110[jj+1] = Oscar_State.gamma_buffer[8][jj];
		Smart_Gamma_Set100[jj+1] = Oscar_State.gamma_buffer[9][jj];
		Smart_Gamma_Set90[jj+1] = Oscar_State.gamma_buffer[10][jj];
		Smart_Gamma_Set80[jj+1] = Oscar_State.gamma_buffer[11][jj];
		Smart_Gamma_Set70[jj+1] = Oscar_State.gamma_buffer[12][jj];				
	}

	Smart_Gamma_Set190[0] = 0xfa;
	Smart_Gamma_Set180[0] = 0xfa;
	Smart_Gamma_Set170[0] = 0xfa;
	Smart_Gamma_Set160[0] = 0xfa;
	Smart_Gamma_Set150[0] = 0xfa;
	Smart_Gamma_Set140[0] = 0xfa;
	Smart_Gamma_Set130[0] = 0xfa;
	Smart_Gamma_Set120[0] = 0xfa;
	Smart_Gamma_Set110[0] = 0xfa;
	Smart_Gamma_Set100[0] = 0xfa;
	Smart_Gamma_Set90[0] = 0xfa;
	Smart_Gamma_Set80[0] = 0xfa;
	Smart_Gamma_Set70[0] = 0xfa;
	Oscar_State.CompleteSmart=true;

	for(ii = 0;ii < 13;ii++){
		printk(KERN_WARNING"\n");
		for(jj=0;jj<25;jj++)
			printk(KERN_WARNING"[%s]gamma val = 0x%x\n",__func__,Oscar_State.gamma_buffer[ii][jj]);
	}

	printk(KERN_WARNING"[%s]Smart Dimming 0n \n",__func__);
}


void mipi_samsung_panel(uint8 data)
{
	
	Oscar_State.mtp_buffer[Oscar_State.mtp_count] = data;
	pr_info("MTP%d = %d\n",Oscar_State.mtp_count,Oscar_State.mtp_buffer[Oscar_State.mtp_count]); 
	msleep(1);
	Oscar_State.mtp_count++; 
}
void mtp_read_for_smartdimming(void)
{

	struct fb_info *info; 
    struct msm_fb_data_type *mfd;

    info = registered_fb[0];
	mfd = (struct msm_fb_data_type *)info->par;

	
	
	mipi_dsi_cmd_bta_sw_trigger(); 
	Oscar_State.cmdreq.cmds = samsung_oled_hd_read_panel; 
	Oscar_State.cmdreq.cmds_cnt = 1; 
	Oscar_State.cmdreq.flags = CMD_REQ_RX | CMD_REQ_COMMIT; 
	Oscar_State.cmdreq.rlen = 10; 
	Oscar_State.cmdreq.cb = mipi_samsung_panel; 
	mipi_dsi_cmdlist_put(&Oscar_State.cmdreq);	

	
	mipi_set_tx_power_mode(0);
	Oscar_State.cmdreq.cmds = samsung_oled_hd_gpara11_cmd;
	Oscar_State.cmdreq.cmds_cnt = ARRAY_SIZE(samsung_oled_hd_gpara11_cmd);
	Oscar_State.cmdreq.cmds_cnt = 1; 
	Oscar_State.cmdreq.flags = CMD_REQ_COMMIT;
	Oscar_State.cmdreq.rlen = 0;
	Oscar_State.cmdreq.cb = NULL;
	mipi_dsi_cmdlist_put(&Oscar_State.cmdreq);	
	mipi_set_tx_power_mode(1);

	mipi_dsi_cmd_bta_sw_trigger(); 
	Oscar_State.cmdreq.cmds = samsung_oled_hd_read_panel; 
	Oscar_State.cmdreq.cmds_cnt = 1; 
	Oscar_State.cmdreq.flags = CMD_REQ_RX | CMD_REQ_COMMIT; 
	Oscar_State.cmdreq.rlen = 10; 
	Oscar_State.cmdreq.cb = mipi_samsung_panel; 
	mipi_dsi_cmdlist_put(&Oscar_State.cmdreq);

	mipi_set_tx_power_mode(0);
	Oscar_State.cmdreq.cmds = samsung_oled_hd_gpara21_cmd;
	Oscar_State.cmdreq.cmds_cnt = ARRAY_SIZE(samsung_oled_hd_gpara21_cmd);
	Oscar_State.cmdreq.cmds_cnt = 1; 
	Oscar_State.cmdreq.flags = CMD_REQ_COMMIT;
	Oscar_State.cmdreq.rlen = 0;
	Oscar_State.cmdreq.cb = NULL;
	mipi_dsi_cmdlist_put(&Oscar_State.cmdreq);	
	
	mipi_set_tx_power_mode(1);
	mipi_dsi_cmd_bta_sw_trigger(); 
	Oscar_State.cmdreq.cmds = samsung_oled_hd_read_panel; 
	Oscar_State.cmdreq.cmds_cnt = 1; 
	Oscar_State.cmdreq.flags = CMD_REQ_RX | CMD_REQ_COMMIT; 
	Oscar_State.cmdreq.rlen = 10; 
	Oscar_State.cmdreq.cb = mipi_samsung_panel; 
	mipi_dsi_cmdlist_put(&Oscar_State.cmdreq);


	Oscar_State.mtp_buffer[6] = Oscar_State.mtp_buffer[6] & 0x01;
	Oscar_State.mtp_buffer[14] = Oscar_State.mtp_buffer[14] & 0x01;
	Oscar_State.mtp_buffer[22] = Oscar_State.mtp_buffer[22] & 0x01;

}

void mtp_work_fnc(struct work_struct *work)
{
	mipi_set_tx_power_mode(0);
	mtp_read_for_smartdimming();
	mipi_set_tx_power_mode(1);

}
#endif
//-----------------------------------------------------------------------------
static int __devinit mipi_oscar_lcd_probe(struct platform_device *pdev)
{
	
	
	if (pdev->id == 0) {
        Oscar_State.mipi_oscar_pdata = pdev->dev.platform_data;
		return 0;
	}

	msm_fb_add_device(pdev);
	//for smart dimming -----------------------------------------------
#ifdef CONFIG_F_SKYDISP_SMART_DIMMING
	INIT_DELAYED_WORK(&Oscar_State.mtp_work, mtp_work_fnc);
	schedule_delayed_work(&Oscar_State.mtp_work, 2 *HZ);
#endif

	return 0;
}

static struct platform_driver this_driver = {
	.probe  = mipi_oscar_lcd_probe,
	.driver = {
		.name   = "mipi_oscar",
	},
};

static struct msm_fb_panel_data oscar_panel_data = {
       .on             = mipi_oscar_lcd_on,
       .off            = mipi_oscar_lcd_off,
       .set_backlight  = mipi_oscar_set_backlight,
};

static int ch_used[3];

int mipi_oscar_device_register(struct msm_panel_info *pinfo,
					u32 channel, u32 panel)
{
	struct platform_device *pdev = NULL;
	int ret;

	if ((channel >= 3) || ch_used[channel])
		return -ENODEV;

	ch_used[channel] = TRUE;

	pdev = platform_device_alloc("mipi_oscar", (panel << 8)|channel);
	if (!pdev)
		return -ENOMEM;

	oscar_panel_data.panel_info = *pinfo;

	ret = platform_device_add_data(pdev, &oscar_panel_data,
		sizeof(oscar_panel_data));
	if (ret) {
		printk(KERN_ERR
		  "%s: platform_device_add_data failed!\n", __func__);
		goto err_device_put;
	}

	ret = platform_device_add(pdev);
	if (ret) {
		printk(KERN_ERR
		  "%s: platform_device_register failed!\n", __func__);
		goto err_device_put;
	}

	return 0;

err_device_put:
	platform_device_put(pdev);
	return ret;
}

static int __init mipi_oscar_lcd_init(void)
{


    Oscar_State.disp_powered_up = true;

    mipi_dsi_buf_alloc(&Oscar_State.oscar_tx_buf, DSI_BUF_SIZE);
    mipi_dsi_buf_alloc(&Oscar_State.oscar_rx_buf, DSI_BUF_SIZE);



    return platform_driver_register(&this_driver);

}

module_init(mipi_oscar_lcd_init);


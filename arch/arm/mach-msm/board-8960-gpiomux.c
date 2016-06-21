/* Copyright (c) 2011-2012, Code Aurora Forum. All rights reserved.
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

#include <linux/gpio.h>
#include <asm/mach-types.h>
#include <mach/gpiomux.h>
#include <mach/socinfo.h>
#include "devices.h"
#include "board-8960.h"

/* The SPI configurations apply to GSBI 1*/
static struct gpiomux_setting spi_active = {
	.func = GPIOMUX_FUNC_1,
	.drv = GPIOMUX_DRV_12MA,
	.pull = GPIOMUX_PULL_NONE,
};

static struct gpiomux_setting spi_suspended_config = {
	.func = GPIOMUX_FUNC_GPIO,
	.drv = GPIOMUX_DRV_2MA,
	.pull = GPIOMUX_PULL_DOWN,
};

static struct gpiomux_setting spi_active_config2 = {
	.func = GPIOMUX_FUNC_2,
	.drv = GPIOMUX_DRV_8MA,
	.pull = GPIOMUX_PULL_NONE,
};

static struct gpiomux_setting spi_suspended_config2 = {
	.func = GPIOMUX_FUNC_GPIO,
	.drv = GPIOMUX_DRV_2MA,
	.pull = GPIOMUX_PULL_UP,
};

#ifdef CONFIG_PANTECH_CAMERA_FLASH
static struct gpiomux_setting gsbi1_active_config = {
	.func = GPIOMUX_FUNC_1,
	.drv = GPIOMUX_DRV_8MA, //GPIOMUX_DRV_12MA ?
	.pull = GPIOMUX_PULL_NONE,
};

static struct gpiomux_setting gsbi1_suspended_config = {
	.func = GPIOMUX_FUNC_1,//GPIOMUX_FUNC_GPIO,
	.drv = GPIOMUX_DRV_2MA,
	.pull = GPIOMUX_PULL_DOWN,//GPIOMUX_PULL_KEEPER,//GPIOMUX_PULL_DOWN,
};
#endif

#if defined(CONFIG_PANTECH_PMIC_MAX17058)
#if defined(T_STARQ)
static struct gpiomux_setting gsbi1_active_config = {
	.func = GPIOMUX_FUNC_1,
	.drv = GPIOMUX_DRV_2MA,
	.pull = GPIOMUX_PULL_NONE,
};
static struct gpiomux_setting gsbi1_suspended_config = {
	.func = GPIOMUX_FUNC_1,
	.drv = GPIOMUX_DRV_2MA,
	.pull = GPIOMUX_PULL_NONE,
};
#endif
#endif // #if defined(CONFIG_PANTECH_PMIC_MAX17058)

//#ifdef CONFIG_PANTECH_CAMERA //AF
#if defined(CONFIG_OV8820_ACT) || defined(CONFIG_S5K3H2_ACT)
static struct gpiomux_setting gsbi2_active_cfg = {
	.func = GPIOMUX_FUNC_1,
	.drv = GPIOMUX_DRV_8MA,
	.pull = GPIOMUX_PULL_NONE,
};
static struct gpiomux_setting gsbi2_suspended_cfg = {
	.func = GPIOMUX_FUNC_1, /*i2c suspend*/
	.drv = GPIOMUX_DRV_2MA,
	.pull = GPIOMUX_PULL_DOWN,//GPIOMUX_PULL_KEEPER, //GPIOMUX_PULL_DOWN
};
#endif

#ifdef CONFIG_TOUCHSCREEN_QT602240_MSM8960 //P12281
static struct gpiomux_setting gsbi3_suspended_cfg = {
	.func = GPIOMUX_FUNC_1,
	.drv = GPIOMUX_DRV_2MA,
	.pull = GPIOMUX_PULL_KEEPER,
};
#endif

static struct gpiomux_setting gsbi3_active_cfg = {
	.func = GPIOMUX_FUNC_1,
	.drv = GPIOMUX_DRV_8MA,
	.pull = GPIOMUX_PULL_NONE,
};

static struct gpiomux_setting external_vfr[] = {
	/* Suspended state */
	{
		.func = GPIOMUX_FUNC_3,
		.drv = GPIOMUX_DRV_2MA,
		.pull = GPIOMUX_PULL_KEEPER,
	},
	/* Active state */
	{
		.func = GPIOMUX_FUNC_3,
		.drv = GPIOMUX_DRV_2MA,
		.pull = GPIOMUX_PULL_KEEPER,
	},
};

#ifdef CONFIG_PANTECH_GPIO_SLEEP_CONFIG
#if defined(CONFIG_MACH_MSM8960_STARQ) || defined(CONFIG_MACH_MSM8960_OSCAR)
static struct gpiomux_setting gsbi5_out_np_low = {
	.func = GPIOMUX_FUNC_1,
	.drv = GPIOMUX_DRV_8MA,
	.pull = GPIOMUX_PULL_NONE,
	.dir = GPIOMUX_OUT_LOW,
};
#endif /* CONFIG_MACH_MSM8960_STARQ || CONFIG_MACH_MSM8960_OSCAR */
static struct gpiomux_setting gsbi_uart = {
	.func = GPIOMUX_FUNC_1,
	.drv = GPIOMUX_DRV_8MA,
	.pull = GPIOMUX_PULL_DOWN,
};
#else
static struct gpiomux_setting gsbi_uart = {
	.func = GPIOMUX_FUNC_1,
	.drv = GPIOMUX_DRV_8MA,
	.pull = GPIOMUX_PULL_NONE,
};
#endif /* CONFIG_PANTECH_GPIO_SLEEP_CONFIG */

#if defined(CONFIG_PANTECH_PMIC_MAX17058)
#if defined(T_OSCAR)
static struct gpiomux_setting gsbi9_active_cfg = {
	.func = GPIOMUX_FUNC_2,
	.drv = GPIOMUX_DRV_2MA,
	.pull = GPIOMUX_PULL_NONE,
};
static struct gpiomux_setting gsbi9_suspended_cfg = {
	.func = GPIOMUX_FUNC_2, /*i2c suspend*/
	.drv = GPIOMUX_DRV_2MA,
	.pull = GPIOMUX_PULL_NONE,
};
#endif
#endif // #if defined(CONFIG_PANTECH_PMIC_MAX17058)
static struct gpiomux_setting gsbi10 = {
	.func = GPIOMUX_FUNC_2,
	.drv = GPIOMUX_DRV_8MA,
	.pull = GPIOMUX_PULL_NONE,
};

static struct gpiomux_setting gsbi12 = {
	.func = GPIOMUX_FUNC_1,
	.drv = GPIOMUX_DRV_8MA,
	.pull = GPIOMUX_PULL_NONE,
};

static struct gpiomux_setting cdc_mclk = {
	.func = GPIOMUX_FUNC_1,
	.drv = GPIOMUX_DRV_8MA,
	.pull = GPIOMUX_PULL_NONE,
};

#ifndef CONFIG_PN544
static struct gpiomux_setting audio_auxpcm[] = {
	/* Suspended state */
	{
		.func = GPIOMUX_FUNC_GPIO,
		.drv = GPIOMUX_DRV_2MA,
		.pull = GPIOMUX_PULL_DOWN,
	},
	/* Active state */
	{
		.func = GPIOMUX_FUNC_1,
		.drv = GPIOMUX_DRV_2MA,
		.pull = GPIOMUX_PULL_NONE,
	},
};
#endif

#if defined(CONFIG_KS8851) || defined(CONFIG_KS8851_MODULE)
static struct gpiomux_setting gpio_eth_config = {
	.pull = GPIOMUX_PULL_NONE,
	.drv = GPIOMUX_DRV_8MA,
	.func = GPIOMUX_FUNC_GPIO,
};
#endif

static struct gpiomux_setting slimbus = {
	.func = GPIOMUX_FUNC_1,
	.drv = GPIOMUX_DRV_8MA,
	.pull = GPIOMUX_PULL_KEEPER,
};

static struct gpiomux_setting wcnss_5wire_suspend_cfg = {
	.func = GPIOMUX_FUNC_GPIO,
	.drv  = GPIOMUX_DRV_2MA,
	.pull = GPIOMUX_PULL_UP,
};

static struct gpiomux_setting wcnss_5wire_active_cfg = {
	.func = GPIOMUX_FUNC_1,
	.drv  = GPIOMUX_DRV_6MA,
	.pull = GPIOMUX_PULL_DOWN,
};

static struct gpiomux_setting cyts_resout_sus_cfg = {
	.func = GPIOMUX_FUNC_GPIO,
	.drv = GPIOMUX_DRV_6MA,
#ifdef CONFIG_PANTECH_CAMERA
	.pull = GPIOMUX_PULL_DOWN,
#else
	.pull = GPIOMUX_PULL_UP,
#endif
};

static struct gpiomux_setting cyts_resout_act_cfg = {
	.func = GPIOMUX_FUNC_GPIO,
	.drv = GPIOMUX_DRV_6MA,
	.pull = GPIOMUX_PULL_UP,
};

static struct gpiomux_setting cyts_sleep_sus_cfg = {
	.func = GPIOMUX_FUNC_GPIO,
	.drv = GPIOMUX_DRV_6MA,
	.pull = GPIOMUX_PULL_DOWN,
};

static struct gpiomux_setting cyts_sleep_act_cfg = {
	.func = GPIOMUX_FUNC_GPIO,
	.drv = GPIOMUX_DRV_6MA,
	.pull = GPIOMUX_PULL_DOWN,
};

static struct gpiomux_setting cyts_int_act_cfg = {
	.func = GPIOMUX_FUNC_GPIO,
	.drv = GPIOMUX_DRV_8MA,
	.pull = GPIOMUX_PULL_UP,
};

static struct gpiomux_setting cyts_int_sus_cfg = {
	.func = GPIOMUX_FUNC_GPIO,
	.drv = GPIOMUX_DRV_2MA,
	.pull = GPIOMUX_PULL_DOWN,
};

#ifdef CONFIG_USB_EHCI_MSM_HSIC
static struct gpiomux_setting hsic_act_cfg = {
	.func = GPIOMUX_FUNC_1,
	.drv = GPIOMUX_DRV_12MA,
	.pull = GPIOMUX_PULL_NONE,
};

static struct gpiomux_setting hsic_sus_cfg = {
	.func = GPIOMUX_FUNC_GPIO,
	.drv = GPIOMUX_DRV_2MA,
	.pull = GPIOMUX_PULL_DOWN,
	.dir = GPIOMUX_OUT_LOW,
};

static struct gpiomux_setting hsic_hub_act_cfg = {
	.func = GPIOMUX_FUNC_GPIO,
	.drv = GPIOMUX_DRV_2MA,
	.pull = GPIOMUX_PULL_NONE,
};
#endif

static struct gpiomux_setting hap_lvl_shft_suspended_config = {
	.func = GPIOMUX_FUNC_GPIO,
	.drv = GPIOMUX_DRV_2MA,
	.pull = GPIOMUX_PULL_DOWN,
};

static struct gpiomux_setting hap_lvl_shft_active_config = {
	.func = GPIOMUX_FUNC_GPIO,
	.drv = GPIOMUX_DRV_8MA,
	.pull = GPIOMUX_PULL_UP,
};

static struct gpiomux_setting ap2mdm_cfg = {
	.func = GPIOMUX_FUNC_GPIO,
	.drv = GPIOMUX_DRV_8MA,
	.pull = GPIOMUX_PULL_DOWN,
};

static struct gpiomux_setting mdm2ap_status_cfg = {
	.func = GPIOMUX_FUNC_GPIO,
	.drv = GPIOMUX_DRV_8MA,
	.pull = GPIOMUX_PULL_NONE,
};

static struct gpiomux_setting mdm2ap_errfatal_cfg = {
	.func = GPIOMUX_FUNC_GPIO,
	.drv = GPIOMUX_DRV_16MA,
	.pull = GPIOMUX_PULL_DOWN,
};

static struct gpiomux_setting ap2mdm_kpdpwr_n_cfg = {
	.func = GPIOMUX_FUNC_GPIO,
	.drv = GPIOMUX_DRV_8MA,
	.pull = GPIOMUX_PULL_DOWN,
};

static struct gpiomux_setting mdp_vsync_suspend_cfg = {
	.func = GPIOMUX_FUNC_GPIO,
	.drv = GPIOMUX_DRV_2MA,
	.pull = GPIOMUX_PULL_DOWN,
};

static struct gpiomux_setting mdp_vsync_active_cfg = {
	.func = GPIOMUX_FUNC_1,
	.drv = GPIOMUX_DRV_2MA,
	.pull = GPIOMUX_PULL_DOWN,
};

#ifdef CONFIG_FB_MSM_HDMI_MSM_PANEL
static struct gpiomux_setting hdmi_suspend_cfg = {
	.func = GPIOMUX_FUNC_GPIO,
	.drv = GPIOMUX_DRV_2MA,
	.pull = GPIOMUX_PULL_DOWN,
};

static struct gpiomux_setting hdmi_active_1_cfg = {
	.func = GPIOMUX_FUNC_1,
	.drv = GPIOMUX_DRV_2MA,
	.pull = GPIOMUX_PULL_UP,
};

static struct gpiomux_setting hdmi_active_2_cfg = {
	.func = GPIOMUX_FUNC_1,
	.drv = GPIOMUX_DRV_2MA,
	.pull = GPIOMUX_PULL_DOWN,
};

#if defined(CONFIG_FB_MSM_HDMI_MHL_8334) || defined(CONFIG_FB_MSM_HDMI_MHL_9244)
static struct gpiomux_setting hdmi_active_3_cfg = {
	.func = GPIOMUX_FUNC_GPIO,
	.drv = GPIOMUX_DRV_2MA,
	.pull = GPIOMUX_PULL_UP,
	.dir = GPIOMUX_IN,
};

static struct gpiomux_setting hdmi_active_4_cfg = {
	.func = GPIOMUX_FUNC_GPIO,
	.drv = GPIOMUX_DRV_2MA,
	.pull = GPIOMUX_PULL_UP,
	.dir = GPIOMUX_OUT_HIGH,
};
#endif
#endif

#if defined(CONFIG_KS8851) || defined(CONFIG_KS8851_MODULE)
static struct msm_gpiomux_config msm8960_ethernet_configs[] = {
	{
		.gpio = 90,
		.settings = {
			[GPIOMUX_SUSPENDED] = &gpio_eth_config,
		}
	},
#if !defined(CONFIG_MACH_MSM8960_STARQ)
	{
		.gpio = 89,
		.settings = {
			[GPIOMUX_SUSPENDED] = &gpio_eth_config,
		}
	},
#endif
};
#endif

#if defined(CONFIG_MACH_MSM8960_STARQ)
static struct gpiomux_setting lcd_backlight_active_cfg = {
	.func = GPIOMUX_FUNC_GPIO,
	.drv = GPIOMUX_DRV_2MA,
	.pull = GPIOMUX_PULL_DOWN,
	.dir = GPIOMUX_OUT_HIGH,
};
static struct gpiomux_setting lcd_backlight_suspend_cfg = {
	.func = GPIOMUX_FUNC_GPIO,
	.drv = GPIOMUX_DRV_2MA,
	.pull = GPIOMUX_PULL_DOWN,
	.dir = GPIOMUX_OUT_LOW,
};
static struct msm_gpiomux_config msm8960_starq_lcd_bl_configs[] = {
	{
		.gpio = 89,
		.settings = {
			[GPIOMUX_ACTIVE] = &lcd_backlight_active_cfg,
			[GPIOMUX_SUSPENDED] = &lcd_backlight_suspend_cfg,
		}
	},
};
#endif

static struct msm_gpiomux_config msm8960_fusion_gsbi_configs[] = {
/*	{
		.gpio = 93,
		.settings = {
			[GPIOMUX_SUSPENDED] = &gsbi9_suspended_cfg,
			[GPIOMUX_ACTIVE] = &gsbi9_active_cfg,
		}
	},
	{
		.gpio = 94,
		.settings = {
			[GPIOMUX_SUSPENDED] = &gsbi9_suspended_cfg,
			[GPIOMUX_ACTIVE] = &gsbi9_active_cfg,
		}
	},
	{
		.gpio = 95,
		.settings = {
			[GPIOMUX_SUSPENDED] = &gsbi9_suspended_cfg,
			[GPIOMUX_ACTIVE] = &gsbi9_active_cfg,
		}
	},
	{
		.gpio = 96,
		.settings = {
			[GPIOMUX_SUSPENDED] = &gsbi9_suspended_cfg,
			[GPIOMUX_ACTIVE] = &gsbi9_active_cfg,
		}
	},	*/
};

static struct msm_gpiomux_config msm8960_gsbi_configs[] __initdata = {
	{
		.gpio      = 6,		/* GSBI1 QUP SPI_DATA_MOSI */
		.settings = {
			[GPIOMUX_SUSPENDED] = &spi_suspended_config,
			[GPIOMUX_ACTIVE] = &spi_active,
		},
	},
	{
		.gpio      = 7,		/* GSBI1 QUP SPI_DATA_MISO */
		.settings = {
			[GPIOMUX_SUSPENDED] = &spi_suspended_config,
			[GPIOMUX_ACTIVE] = &spi_active,
		},
	},
#ifdef CONFIG_PANTECH_CAMERA_FLASH
	{
		.gpio      = 8,	/* GSBI1 I2C QUP SDA */
		.settings = {
			[GPIOMUX_SUSPENDED] = &gsbi1_suspended_config,
			[GPIOMUX_ACTIVE] = &gsbi1_active_config,                
		},
	},
	{
		.gpio      = 9,	/* GSBI1 I2C QUP SCL */
		.settings = {
			[GPIOMUX_SUSPENDED] = &gsbi1_suspended_config,
			[GPIOMUX_ACTIVE] = &gsbi1_active_config,                
		},
	},
#else	
#if defined(CONFIG_PANTECH_PMIC_MAX17058)
#if defined(T_STARQ)
	{
		.gpio      = 8,	/* GSBI1 I2C QUP SDA */
		.settings = {
			[GPIOMUX_SUSPENDED] = &gsbi1_suspended_config,
			[GPIOMUX_ACTIVE] = &gsbi1_active_config,                
		},
	},
	{
		.gpio      = 9,	/* GSBI1 I2C QUP SCL */
		.settings = {
			[GPIOMUX_SUSPENDED] = &gsbi1_suspended_config,
			[GPIOMUX_ACTIVE] = &gsbi1_active_config,                
		},
	},
#else
	{
		.gpio      = 8,		/* GSBI1 QUP SPI_CS_N */
		.settings = {
			[GPIOMUX_SUSPENDED] = &spi_suspended_config,
			[GPIOMUX_ACTIVE] = &spi_active,
		},
	},
	{
		.gpio      = 9,		/* GSBI1 QUP SPI_CLK */
		.settings = {
			[GPIOMUX_SUSPENDED] = &spi_suspended_config,
			[GPIOMUX_ACTIVE] = &spi_active,
		},
	},
#endif
#else
	{
		.gpio      = 8,		/* GSBI1 QUP SPI_CS_N */
		.settings = {
			[GPIOMUX_SUSPENDED] = &spi_suspended_config,
			[GPIOMUX_ACTIVE] = &spi_active,
		},
	},
	{
		.gpio      = 9,		/* GSBI1 QUP SPI_CLK */
		.settings = {
			[GPIOMUX_SUSPENDED] = &spi_suspended_config,
			[GPIOMUX_ACTIVE] = &spi_active,
		},
	},
#endif
#endif
    //#ifdef CONFIG_PANTECH_CAMERA //AF
#if defined(CONFIG_OV8820_ACT) || defined(CONFIG_S5K3H2_ACT)
    {
        .gpio      = 12,    /* GSBI2 I2C QUP SDA */
        .settings = {
            [GPIOMUX_SUSPENDED] = &gsbi2_suspended_cfg,
            [GPIOMUX_ACTIVE] = &gsbi2_active_cfg,
        },
    },
    {
        .gpio      = 13,    /* GSBI2 I2C QUP SCL */
        .settings = {
            [GPIOMUX_SUSPENDED] = &gsbi2_suspended_cfg,
            [GPIOMUX_ACTIVE] = &gsbi2_active_cfg,
        },
    },
#endif
	{
		.gpio      = 14,		/* GSBI1 SPI_CS_1 */
		.settings = {
			[GPIOMUX_SUSPENDED] = &spi_suspended_config2,
			[GPIOMUX_ACTIVE] = &spi_active_config2,
		},
	},
	{
		.gpio      = 16,	/* GSBI3 I2C QUP SDA */
		.settings = {
			[GPIOMUX_SUSPENDED] = &gsbi3_suspended_cfg,
			[GPIOMUX_ACTIVE] = &gsbi3_active_cfg,
		},
	},
	{
		.gpio      = 17,	/* GSBI3 I2C QUP SCL */
		.settings = {
			[GPIOMUX_SUSPENDED] = &gsbi3_suspended_cfg,
			[GPIOMUX_ACTIVE] = &gsbi3_active_cfg,
		},
	},
#if defined(CONFIG_PANTECH_PMIC_MAX17058)
#if defined(T_OSCAR)
	{
        .gpio      = 95,    /* GSBI9 I2C QUP SDA */
        .settings = {
            [GPIOMUX_SUSPENDED] = &gsbi9_suspended_cfg,
            [GPIOMUX_ACTIVE] = &gsbi9_active_cfg,
        },
    },
    {
        .gpio      = 96,    /* GSBI9 I2C QUP SCL */
        .settings = {
            [GPIOMUX_SUSPENDED] = &gsbi9_suspended_cfg,
            [GPIOMUX_ACTIVE] = &gsbi9_active_cfg,
        },
    },
#endif
#endif  // #if defined(CONFIG_PANTECH_PMIC_MAX17058)
	{
		.gpio      = 44,	/* GSBI12 I2C QUP SDA */
		.settings = {
			[GPIOMUX_SUSPENDED] = &gsbi12,
		},
	},
	{
		.gpio      = 45,	/* GSBI12 I2C QUP SCL */
		.settings = {
			[GPIOMUX_SUSPENDED] = &gsbi12,
		},
	},
	{
		.gpio      = 73,	/* GSBI10 I2C QUP SDA */
		.settings = {
			[GPIOMUX_SUSPENDED] = &gsbi10,
		},
	},
	{
		.gpio      = 74,	/* GSBI10 I2C QUP SCL */
		.settings = {
			[GPIOMUX_SUSPENDED] = &gsbi10,
		},
	},
};

static struct msm_gpiomux_config msm8960_gsbi5_uart_configs[] __initdata = {
	{
		.gpio      = 22,	/* GSBI5 UART2 */
		.settings = {
#ifdef CONFIG_PANTECH_GPIO_SLEEP_CONFIG
#if defined(CONFIG_MACH_MSM8960_STARQ) || defined(CONFIG_MACH_MSM8960_OSCAR)
            [GPIOMUX_SUSPENDED] = &gsbi5_out_np_low,
#else 
			[GPIOMUX_SUSPENDED] = &gsbi_uart, 
#endif /* defined(CONFIG_MACH_MSM8960_STARQ) || defined(CONFIG_MACH_MSM8960_OSCAR) */
#else
			[GPIOMUX_SUSPENDED] = &gsbi_uart, 
#endif /* CONFIG_PANTECH_GPIO_SLEEP_CONFIG */
		},
	},
	{
		.gpio      = 23,        /* GSBI5 UART2 */
		.settings = {
			[GPIOMUX_SUSPENDED] = &gsbi_uart,
		},
	},
	{
		.gpio      = 24,        /* GSBI5 UART2 */
		.settings = {
			[GPIOMUX_SUSPENDED] = &gsbi_uart,
		},
	},
	{
		.gpio      = 25,        /* GSBI5 UART2 */
		.settings = {
			[GPIOMUX_SUSPENDED] = &gsbi_uart,
		},
	},
};

static struct msm_gpiomux_config msm8960_external_vfr_configs[] __initdata = {
	{
		.gpio      = 23,        /* EXTERNAL VFR */
		.settings = {
			[GPIOMUX_SUSPENDED] = &external_vfr[0],
			[GPIOMUX_ACTIVE] = &external_vfr[1],
		},
	},
};

static struct msm_gpiomux_config msm8960_gsbi8_uart_configs[] __initdata = {
	{
		.gpio      = 34,        /* GSBI8 UART3 */
		.settings = {
			[GPIOMUX_SUSPENDED] = &gsbi_uart,
		},
	},
	{
		.gpio      = 35,        /* GSBI8 UART3 */
		.settings = {
			[GPIOMUX_SUSPENDED] = &gsbi_uart,
		},
	},
	{
		.gpio      = 36,        /* GSBI8 UART3 */
		.settings = {
			[GPIOMUX_SUSPENDED] = &gsbi_uart,
		},
	},
	{
		.gpio      = 37,        /* GSBI8 UART3 */
		.settings = {
			[GPIOMUX_SUSPENDED] = &gsbi_uart,
		},
	},
};

static struct msm_gpiomux_config msm8960_slimbus_config[] __initdata = {
	{
		.gpio	= 60,		/* slimbus data */
		.settings = {
			[GPIOMUX_SUSPENDED] = &slimbus,
		},
	},
	{
		.gpio	= 61,		/* slimbus clk */
		.settings = {
			[GPIOMUX_SUSPENDED] = &slimbus,
		},
	},
};

static struct msm_gpiomux_config msm8960_audio_codec_configs[] __initdata = {
	{
		.gpio = 59,
		.settings = {
			[GPIOMUX_SUSPENDED] = &cdc_mclk,
		},
	},
};

#ifndef CONFIG_PN544
// p11515 - Gpio_66 is used for NFC( PN544 ) Enable pin.
static struct msm_gpiomux_config msm8960_audio_auxpcm_configs[] __initdata = {
	{
		.gpio = 63,
		.settings = {
			[GPIOMUX_SUSPENDED] = &audio_auxpcm[0],
			[GPIOMUX_ACTIVE] = &audio_auxpcm[1],
		},
	},
	{
		.gpio = 64,
		.settings = {
			[GPIOMUX_SUSPENDED] = &audio_auxpcm[0],
			[GPIOMUX_ACTIVE] = &audio_auxpcm[1],
		},
	},
	{
		.gpio = 65,
		.settings = {
			[GPIOMUX_SUSPENDED] = &audio_auxpcm[0],
			[GPIOMUX_ACTIVE] = &audio_auxpcm[1],
		},
	},
	{
		.gpio = 66,
		.settings = {
			[GPIOMUX_SUSPENDED] = &audio_auxpcm[0],
			[GPIOMUX_ACTIVE] = &audio_auxpcm[1],
		},
	},
};
#endif

static struct msm_gpiomux_config wcnss_5wire_interface[] = {
	{
		.gpio = 84,
		.settings = {
			[GPIOMUX_ACTIVE]    = &wcnss_5wire_active_cfg,
			[GPIOMUX_SUSPENDED] = &wcnss_5wire_suspend_cfg,
		},
	},
	{
		.gpio = 85,
		.settings = {
			[GPIOMUX_ACTIVE]    = &wcnss_5wire_active_cfg,
			[GPIOMUX_SUSPENDED] = &wcnss_5wire_suspend_cfg,
		},
	},
	{
		.gpio = 86,
		.settings = {
			[GPIOMUX_ACTIVE]    = &wcnss_5wire_active_cfg,
			[GPIOMUX_SUSPENDED] = &wcnss_5wire_suspend_cfg,
		},
	},
	{
		.gpio = 87,
		.settings = {
			[GPIOMUX_ACTIVE]    = &wcnss_5wire_active_cfg,
			[GPIOMUX_SUSPENDED] = &wcnss_5wire_suspend_cfg,
		},
	},
	{
		.gpio = 88,
		.settings = {
			[GPIOMUX_ACTIVE]    = &wcnss_5wire_active_cfg,
			[GPIOMUX_SUSPENDED] = &wcnss_5wire_suspend_cfg,
		},
	},
};

static struct msm_gpiomux_config msm8960_cyts_configs[] __initdata = {
	{	/* TS INTERRUPT */
		.gpio = 11,
		.settings = {
			[GPIOMUX_ACTIVE]    = &cyts_int_act_cfg,
			[GPIOMUX_SUSPENDED] = &cyts_int_sus_cfg,
		},
	},
	{	/* TS SLEEP */
		.gpio = 50,
		.settings = {
			[GPIOMUX_ACTIVE]    = &cyts_sleep_act_cfg,
			[GPIOMUX_SUSPENDED] = &cyts_sleep_sus_cfg,
		},
	},
	{	/* TS RESOUT */
		.gpio = 52,
		.settings = {
			[GPIOMUX_ACTIVE]    = &cyts_resout_act_cfg,
			[GPIOMUX_SUSPENDED] = &cyts_resout_sus_cfg,
		},
	},
};

#ifdef CONFIG_TOUCHSCREEN_QT602240_MSM8960 // p11223 added
static struct gpiomux_setting qt602240_sleep_sus_cfg = {
	.func = GPIOMUX_FUNC_GPIO,
	.drv = GPIOMUX_DRV_6MA,
	.pull = GPIOMUX_PULL_DOWN,
};

static struct gpiomux_setting qt602240_sleep_act_cfg = {
	.func = GPIOMUX_FUNC_GPIO,
	.drv = GPIOMUX_DRV_6MA,
	.pull = GPIOMUX_PULL_DOWN,
};

static struct gpiomux_setting qt602240_int_act_cfg = {
	.func = GPIOMUX_FUNC_GPIO,
	.drv = GPIOMUX_DRV_8MA,
	.pull = GPIOMUX_PULL_UP,
};

static struct gpiomux_setting qt602240_int_sus_cfg = {
	.func = GPIOMUX_FUNC_GPIO,
	.drv = GPIOMUX_DRV_2MA,
	.pull = GPIOMUX_PULL_DOWN,
};

static struct msm_gpiomux_config msm8960_qt602240_configs[] __initdata = {
	{	/* qt602240 INTERRUPT */
		.gpio = 11,
		.settings = {
			[GPIOMUX_ACTIVE]    = &qt602240_int_act_cfg,
			[GPIOMUX_SUSPENDED] = &qt602240_int_sus_cfg,
		},
	},
	{	/* qt602240 SLEEP */
	#if defined (CONFIG_MACH_MSM8960_STARQ)  // p11223
		.gpio = 99,
	#else	
		.gpio = 50,
	#endif
		.settings = {
			[GPIOMUX_ACTIVE]    = &qt602240_sleep_act_cfg,
			[GPIOMUX_SUSPENDED] = &qt602240_sleep_sus_cfg,
		},
	},
};
#endif

#ifdef CONFIG_TOUCHSCREEN_MELFAS_TS //dhyang

static struct gpiomux_setting melfas_int_act_cfg = {
	.func = GPIOMUX_FUNC_GPIO,
	.drv = GPIOMUX_DRV_8MA,
	.pull = GPIOMUX_PULL_UP,
};
static struct gpiomux_setting melfas_int_sus_cfg = {
	.func = GPIOMUX_FUNC_GPIO,
	.drv = GPIOMUX_DRV_2MA,
	.pull = GPIOMUX_PULL_DOWN,
};
static struct msm_gpiomux_config msm8960_melfas_configs[] __initdata = {
	{	/* melfas INTERRUPT */
		.gpio = 11,
		.settings = {
			[GPIOMUX_ACTIVE]    = &melfas_int_act_cfg,
			[GPIOMUX_SUSPENDED] = &melfas_int_sus_cfg,
		},
	},
};
#endif 
#ifdef CONFIG_USB_EHCI_MSM_HSIC
static struct msm_gpiomux_config msm8960_hsic_configs[] = {
	{
		.gpio = 150,               /*HSIC_STROBE */
		.settings = {
			[GPIOMUX_ACTIVE] = &hsic_act_cfg,
			[GPIOMUX_SUSPENDED] = &hsic_sus_cfg,
		},
	},
	{
		.gpio = 151,               /* HSIC_DATA */
		.settings = {
			[GPIOMUX_ACTIVE] = &hsic_act_cfg,
			[GPIOMUX_SUSPENDED] = &hsic_sus_cfg,
		},
	},
};

static struct msm_gpiomux_config msm8960_hsic_hub_configs[] = {
	{
		.gpio = 91,               /* HSIC_HUB_RESET */
		.settings = {
			[GPIOMUX_ACTIVE] = &hsic_hub_act_cfg,
			[GPIOMUX_SUSPENDED] = &hsic_sus_cfg,
		},
	},
};
#endif

#ifdef CONFIG_MMC_MSM_SDC4_SUPPORT
static struct gpiomux_setting sdcc4_clk_actv_cfg = {
	.func = GPIOMUX_FUNC_2,
	.drv = GPIOMUX_DRV_8MA,
	.pull = GPIOMUX_PULL_NONE,
};

static struct gpiomux_setting sdcc4_cmd_data_0_3_actv_cfg = {
	.func = GPIOMUX_FUNC_2,
	.drv = GPIOMUX_DRV_8MA,
	.pull = GPIOMUX_PULL_UP,
};

static struct gpiomux_setting sdcc4_suspend_cfg = {
	.func = GPIOMUX_FUNC_GPIO,
	.drv = GPIOMUX_DRV_2MA,
	.pull = GPIOMUX_PULL_DOWN,
};

static struct gpiomux_setting sdcc4_data_1_suspend_cfg = {
	.func = GPIOMUX_FUNC_GPIO,
	.drv = GPIOMUX_DRV_8MA,
	.pull = GPIOMUX_PULL_UP,
};

static struct msm_gpiomux_config msm8960_sdcc4_configs[] __initdata = {
	{
		/* SDC4_DATA_3 */
		.gpio      = 83,
		.settings = {
			[GPIOMUX_ACTIVE]    = &sdcc4_cmd_data_0_3_actv_cfg,
			[GPIOMUX_SUSPENDED] = &sdcc4_suspend_cfg,
		},
	},
	{
		/* SDC4_DATA_2 */
		.gpio      = 84,
		.settings = {
			[GPIOMUX_ACTIVE]    = &sdcc4_cmd_data_0_3_actv_cfg,
			[GPIOMUX_SUSPENDED] = &sdcc4_suspend_cfg,
		},
	},
	{
		/* SDC4_DATA_1 */
		.gpio      = 85,
		.settings = {
			[GPIOMUX_ACTIVE]    = &sdcc4_cmd_data_0_3_actv_cfg,
			[GPIOMUX_SUSPENDED] = &sdcc4_data_1_suspend_cfg,
		},
	},
	{
		/* SDC4_DATA_0 */
		.gpio      = 86,
		.settings = {
			[GPIOMUX_ACTIVE]    = &sdcc4_cmd_data_0_3_actv_cfg,
			[GPIOMUX_SUSPENDED] = &sdcc4_suspend_cfg,
		},
	},
	{
		/* SDC4_CMD */
		.gpio      = 87,
		.settings = {
			[GPIOMUX_ACTIVE]    = &sdcc4_cmd_data_0_3_actv_cfg,
			[GPIOMUX_SUSPENDED] = &sdcc4_suspend_cfg,
		},
	},
	{
		/* SDC4_CLK */
		.gpio      = 88,
		.settings = {
			[GPIOMUX_ACTIVE]    = &sdcc4_clk_actv_cfg,
			[GPIOMUX_SUSPENDED] = &sdcc4_suspend_cfg,
		},
	},
};
#endif


static struct msm_gpiomux_config hap_lvl_shft_config[] __initdata = {
	{
		.gpio = 47,
		.settings = {
			[GPIOMUX_SUSPENDED] = &hap_lvl_shft_suspended_config,
			[GPIOMUX_ACTIVE] = &hap_lvl_shft_active_config,
		},
	},
};

static struct msm_gpiomux_config sglte_configs[] __initdata = {
	/* AP2MDM_STATUS */
	{
		.gpio = 77,
		.settings = {
			[GPIOMUX_SUSPENDED] = &ap2mdm_cfg,
		}
	},
	/* MDM2AP_STATUS */
	{
		.gpio = 24,
		.settings = {
			[GPIOMUX_SUSPENDED] = &mdm2ap_status_cfg,
		}
	},
	/* MDM2AP_ERRFATAL */
	{
		.gpio = 40,
		.settings = {
			[GPIOMUX_SUSPENDED] = &mdm2ap_errfatal_cfg,
		}
	},
	/* AP2MDM_ERRFATAL */
	{
		.gpio = 80,
		.settings = {
			[GPIOMUX_SUSPENDED] = &ap2mdm_cfg,
		}
	},
	/* AP2MDM_KPDPWR_N */
	{
		.gpio = 79,
		.settings = {
			[GPIOMUX_SUSPENDED] = &ap2mdm_kpdpwr_n_cfg,
		}
	},
	/* AP2MDM_PMIC_PWR_EN */
	{
		.gpio = 22,
		.settings = {
			[GPIOMUX_SUSPENDED] = &ap2mdm_kpdpwr_n_cfg,
		}
	},
	/* AP2MDM_SOFT_RESET */
	{
		.gpio = 78,
		.settings = {
			[GPIOMUX_SUSPENDED] = &ap2mdm_cfg,
		}
	},
};

static struct msm_gpiomux_config msm8960_mdp_vsync_configs[] __initdata = {
	{
		.gpio = 0,
		.settings = {
			[GPIOMUX_ACTIVE]    = &mdp_vsync_active_cfg,
			[GPIOMUX_SUSPENDED] = &mdp_vsync_suspend_cfg,
		},
	}
};

#ifdef CONFIG_FB_MSM_HDMI_MSM_PANEL
static struct msm_gpiomux_config msm8960_hdmi_configs[] __initdata = {
	{
		.gpio = 99,
		.settings = {
			[GPIOMUX_ACTIVE]    = &hdmi_active_1_cfg,
			[GPIOMUX_SUSPENDED] = &hdmi_suspend_cfg,
		},
	},
	{
		.gpio = 100,
		.settings = {
			[GPIOMUX_ACTIVE]    = &hdmi_active_1_cfg,
			[GPIOMUX_SUSPENDED] = &hdmi_suspend_cfg,
		},
	},
	{
		.gpio = 101,
		.settings = {
			[GPIOMUX_ACTIVE]    = &hdmi_active_1_cfg,
			[GPIOMUX_SUSPENDED] = &hdmi_suspend_cfg,
		},
	},
	{
		.gpio = 102,
		.settings = {
			[GPIOMUX_ACTIVE]    = &hdmi_active_2_cfg,
			[GPIOMUX_SUSPENDED] = &hdmi_suspend_cfg,
		},
	},
#ifdef CONFIG_FB_MSM_HDMI_MHL_9244
		{
		.gpio = 15,
		.settings = {
			[GPIOMUX_ACTIVE]    = &hdmi_active_3_cfg,
			[GPIOMUX_SUSPENDED] = &hdmi_suspend_cfg,
		},
	},
	{
		.gpio = 66,
		.settings = {
			[GPIOMUX_ACTIVE]    = &hdmi_active_4_cfg,
			[GPIOMUX_SUSPENDED] = &hdmi_suspend_cfg,
		},
	},
#endif
#ifdef CONFIG_FB_MSM_HDMI_MHL_8334
		{
		.gpio = 4,
		.settings = {
			[GPIOMUX_ACTIVE]    = &hdmi_active_3_cfg,
			[GPIOMUX_SUSPENDED] = &hdmi_suspend_cfg,
		},
	},
	{
		.gpio = 15,
		.settings = {
			[GPIOMUX_ACTIVE]    = &hdmi_active_4_cfg,
			[GPIOMUX_SUSPENDED] = &hdmi_suspend_cfg,
		},
	},
#endif /* CONFIG_FB_MSM_HDMI_MHL */
};
#endif

#ifdef CONFIG_PANTECH_CHARGER_WIRELESS
#if defined(CONFIG_MACH_MSM8960_STARQ)
#define W_CHG_FULL 0
#define USB_CHG_DET 1
#else
#define W_CHG_FULL 0
#define USB_CHG_DET 1
#endif
static struct gpiomux_setting wireless_fulldet_suspend_cfg = {
	.func = GPIOMUX_FUNC_GPIO,
	.drv = GPIOMUX_DRV_2MA,
	.pull = GPIOMUX_PULL_DOWN,
};
static struct gpiomux_setting wireless_fulldet_active_cfg = {
	.func = GPIOMUX_FUNC_GPIO,
	.drv = GPIOMUX_DRV_2MA,
	.pull = GPIOMUX_PULL_DOWN,
};
static struct gpiomux_setting wireless_usbdet_suspend_cfg = {
	.func = GPIOMUX_FUNC_GPIO,
	.drv = GPIOMUX_DRV_2MA,
	.pull = GPIOMUX_PULL_DOWN,
	.dir = GPIOMUX_OUT_LOW,
};
static struct gpiomux_setting wireless_usbdet_active_cfg = {
	.func = GPIOMUX_FUNC_GPIO,
	.drv = GPIOMUX_DRV_2MA,
	.pull = GPIOMUX_PULL_DOWN,
	.dir = GPIOMUX_OUT_LOW,
};
static struct msm_gpiomux_config msm8960_wireless_charger_configs[] __initdata = {
	{
		.gpio = W_CHG_FULL,
		.settings = {
			[GPIOMUX_ACTIVE]    = &wireless_fulldet_active_cfg,
			[GPIOMUX_SUSPENDED] = &wireless_fulldet_suspend_cfg,
		},
	},
	{
		.gpio = USB_CHG_DET,
		.settings = {
			[GPIOMUX_ACTIVE]    = &wireless_usbdet_active_cfg,
			[GPIOMUX_SUSPENDED] = &wireless_usbdet_suspend_cfg,
		},
	},
};
#endif
#ifdef CONFIG_PANTECH_PMIC  // gpio-config for QC recommendation (pull-up) 
static struct gpiomux_setting pm_irq_suspend_cfg = {
	.func = GPIOMUX_FUNC_GPIO,
	.drv = GPIOMUX_DRV_2MA,
	.pull = GPIOMUX_PULL_UP,
	.dir = GPIOMUX_IN,
};
static struct gpiomux_setting pm_irq_active_cfg = {
	.func = GPIOMUX_FUNC_GPIO,
	.drv = GPIOMUX_DRV_2MA,
	.pull = GPIOMUX_PULL_UP,
	.dir = GPIOMUX_IN,
};
static struct msm_gpiomux_config msm8960_pm_irq_configs[] __initdata = {
	{
		.gpio = 103,
		.settings = {
			[GPIOMUX_ACTIVE]    = &pm_irq_active_cfg,
			[GPIOMUX_SUSPENDED] = &pm_irq_suspend_cfg,
		},
	},
	{
		.gpio = 104,
		.settings = {
			[GPIOMUX_ACTIVE]    = &pm_irq_active_cfg,
			[GPIOMUX_SUSPENDED] = &pm_irq_suspend_cfg,
		},
	},
};
#endif

//chjeon20120211@LS1 add
#ifdef CONFIG_PANTECH_GPIO_SLEEP_CONFIG
#if defined(CONFIG_MACH_MSM8960_STARQ) || defined(CONFIG_MACH_MSM8960_OSCAR)
static struct gpiomux_setting msm8960_gpio_suspend_in_pd_cfg = {
	.func = GPIOMUX_FUNC_GPIO,
	.drv = GPIOMUX_DRV_2MA,
	.pull = GPIOMUX_PULL_DOWN,
	.dir = GPIOMUX_IN,
};

#if defined (CONFIG_MACH_MSM8960_STARQ)
static struct gpiomux_setting msm8960_gpio_suspend_in_pd_func1 = {
	.func = GPIOMUX_FUNC_1,
	.drv = GPIOMUX_DRV_2MA,
	.pull = GPIOMUX_PULL_DOWN,
	.dir = GPIOMUX_IN,
};
#endif /* CONFIG_MACH_MSM8960_STARQ */
#endif /* CONFIG_MACH_MSM8960_STARQ || CONFIG_MACH_MSM8960_OSCAR */

#if defined(CONFIG_MACH_MSM8960_STARQ) 
static struct msm_gpiomux_config msm8960_sleep_gpio_gpio_configs[] __initdata = {
	{
		.gpio = 12,
		.settings = {
			[GPIOMUX_ACTIVE]    = &msm8960_gpio_suspend_in_pd_cfg,
			[GPIOMUX_SUSPENDED] = &msm8960_gpio_suspend_in_pd_cfg,
		},
	},
	{
		.gpio = 13,
		.settings = {
			[GPIOMUX_ACTIVE]    = &msm8960_gpio_suspend_in_pd_cfg,
			[GPIOMUX_SUSPENDED] = &msm8960_gpio_suspend_in_pd_cfg,
		},
	},
	{
		.gpio = 18,
		.settings = {
			[GPIOMUX_ACTIVE]    = &msm8960_gpio_suspend_in_pd_cfg,
			[GPIOMUX_SUSPENDED] = &msm8960_gpio_suspend_in_pd_cfg,
		},
	},
	{
		.gpio = 19,
		.settings = {
			[GPIOMUX_ACTIVE]    = &msm8960_gpio_suspend_in_pd_cfg,
			[GPIOMUX_SUSPENDED] = &msm8960_gpio_suspend_in_pd_cfg,
		},
	},
	{
		.gpio = 32,
		.settings = {
			[GPIOMUX_ACTIVE]    = &msm8960_gpio_suspend_in_pd_cfg,
			[GPIOMUX_SUSPENDED] = &msm8960_gpio_suspend_in_pd_cfg,
		},
	},
	{
		.gpio = 33,
		.settings = {
			[GPIOMUX_ACTIVE]    = &msm8960_gpio_suspend_in_pd_cfg,
			[GPIOMUX_SUSPENDED] = &msm8960_gpio_suspend_in_pd_cfg,
		},
	},
	{
		.gpio = 53,
		.settings = {
			[GPIOMUX_ACTIVE]    = &msm8960_gpio_suspend_in_pd_cfg,
			[GPIOMUX_SUSPENDED] = &msm8960_gpio_suspend_in_pd_cfg,
		},
	},
	{
		.gpio = 67,
		.settings = {
			[GPIOMUX_ACTIVE]    = &msm8960_gpio_suspend_in_pd_cfg,
			[GPIOMUX_SUSPENDED] = &msm8960_gpio_suspend_in_pd_cfg,
		},
	},
	{
		.gpio = 69,
		.settings = {
			[GPIOMUX_ACTIVE]    = &msm8960_gpio_suspend_in_pd_cfg,
			[GPIOMUX_SUSPENDED] = &msm8960_gpio_suspend_in_pd_cfg,
		},
	},
	{
		.gpio = 73,
		.settings = {
			[GPIOMUX_ACTIVE]    = &msm8960_gpio_suspend_in_pd_cfg,
			[GPIOMUX_SUSPENDED] = &msm8960_gpio_suspend_in_pd_cfg,
		},
	},
	{
		.gpio = 74,
		.settings = {
			[GPIOMUX_ACTIVE]    = &msm8960_gpio_suspend_in_pd_cfg,
			[GPIOMUX_SUSPENDED] = &msm8960_gpio_suspend_in_pd_cfg,
		},
	},
	{
		.gpio = 90,
		.settings = {
			[GPIOMUX_ACTIVE]    = &msm8960_gpio_suspend_in_pd_cfg,
			[GPIOMUX_SUSPENDED] = &msm8960_gpio_suspend_in_pd_cfg,
		},
	},
	{
		.gpio = 100,
		.settings = {
			[GPIOMUX_ACTIVE]    = &msm8960_gpio_suspend_in_pd_cfg,
			[GPIOMUX_SUSPENDED] = &msm8960_gpio_suspend_in_pd_cfg,
		},
	},
	{
		.gpio = 101,
		.settings = {
			[GPIOMUX_ACTIVE]    = &msm8960_gpio_suspend_in_pd_cfg,
			[GPIOMUX_SUSPENDED] = &msm8960_gpio_suspend_in_pd_cfg,
		},
	},
	{
		.gpio = 128,
		.settings = {
			[GPIOMUX_ACTIVE]    = &msm8960_gpio_suspend_in_pd_func1,
			[GPIOMUX_SUSPENDED] = &msm8960_gpio_suspend_in_pd_func1,
		},
	},
	{
		.gpio = 135,
		.settings = {
			[GPIOMUX_ACTIVE]    = &msm8960_gpio_suspend_in_pd_func1,
			[GPIOMUX_SUSPENDED] = &msm8960_gpio_suspend_in_pd_func1,
		},
	},
	{
		.gpio = 136,
		.settings = {
			[GPIOMUX_ACTIVE]    = &msm8960_gpio_suspend_in_pd_func1,
			[GPIOMUX_SUSPENDED] = &msm8960_gpio_suspend_in_pd_func1,
		},
	},
	{
		.gpio = 139,
		.settings = {
			[GPIOMUX_ACTIVE]    = &msm8960_gpio_suspend_in_pd_func1,
			[GPIOMUX_SUSPENDED] = &msm8960_gpio_suspend_in_pd_func1,
		},
	},
	{
		.gpio = 145,
		.settings = {
			[GPIOMUX_ACTIVE]    = &msm8960_gpio_suspend_in_pd_func1,
			[GPIOMUX_SUSPENDED] = &msm8960_gpio_suspend_in_pd_func1,
		},
	},
	{
		.gpio = 146,
		.settings = {
			[GPIOMUX_ACTIVE]    = &msm8960_gpio_suspend_in_pd_func1,
			[GPIOMUX_SUSPENDED] = &msm8960_gpio_suspend_in_pd_func1,
		},
	},
	{
		.gpio = 147,
		.settings = {
			[GPIOMUX_ACTIVE]    = &msm8960_gpio_suspend_in_pd_func1,
			[GPIOMUX_SUSPENDED] = &msm8960_gpio_suspend_in_pd_func1,
		},
	},
	{
		.gpio = 148,
		.settings = {
			[GPIOMUX_ACTIVE]    = &msm8960_gpio_suspend_in_pd_func1,
			[GPIOMUX_SUSPENDED] = &msm8960_gpio_suspend_in_pd_func1,
		},
	},
};
#elif defined(CONFIG_MACH_MSM8960_OSCAR) /* CONFIG_MACH_MSM8960_STARQ */
static struct msm_gpiomux_config msm8960_sleep_gpio_gpio_configs[] __initdata = {
	{
		.gpio = 18,
		.settings = {
			[GPIOMUX_ACTIVE]    = &msm8960_gpio_suspend_in_pd_cfg,
			[GPIOMUX_SUSPENDED] = &msm8960_gpio_suspend_in_pd_cfg,
		},
	},
	{
		.gpio = 19,
		.settings = {
			[GPIOMUX_ACTIVE]    = &msm8960_gpio_suspend_in_pd_cfg,
			[GPIOMUX_SUSPENDED] = &msm8960_gpio_suspend_in_pd_cfg,
		},
	},
	{
		.gpio = 32,
		.settings = {
			[GPIOMUX_ACTIVE]    = &msm8960_gpio_suspend_in_pd_cfg,
			[GPIOMUX_SUSPENDED] = &msm8960_gpio_suspend_in_pd_cfg,
		},
	},
	{
		.gpio = 33,
		.settings = {
			[GPIOMUX_ACTIVE]    = &msm8960_gpio_suspend_in_pd_cfg,
			[GPIOMUX_SUSPENDED] = &msm8960_gpio_suspend_in_pd_cfg,
		},
	},
	{
		.gpio = 73,
		.settings = {
			[GPIOMUX_ACTIVE]    = &msm8960_gpio_suspend_in_pd_cfg,
			[GPIOMUX_SUSPENDED] = &msm8960_gpio_suspend_in_pd_cfg,
		},
	},
	{
		.gpio = 74,
		.settings = {
			[GPIOMUX_ACTIVE]    = &msm8960_gpio_suspend_in_pd_cfg,
			[GPIOMUX_SUSPENDED] = &msm8960_gpio_suspend_in_pd_cfg,
		},
	},
	{
		.gpio = 89,
		.settings = {
			[GPIOMUX_ACTIVE]    = &msm8960_gpio_suspend_in_pd_cfg,
			[GPIOMUX_SUSPENDED] = &msm8960_gpio_suspend_in_pd_cfg,
		},
	},
	{
		.gpio = 90,
		.settings = {
			[GPIOMUX_ACTIVE]    = &msm8960_gpio_suspend_in_pd_cfg,
			[GPIOMUX_SUSPENDED] = &msm8960_gpio_suspend_in_pd_cfg,
		},
	},
	{
		.gpio = 99,
		.settings = {
			[GPIOMUX_ACTIVE]    = &msm8960_gpio_suspend_in_pd_cfg,
			[GPIOMUX_SUSPENDED] = &msm8960_gpio_suspend_in_pd_cfg,
		},
	},
	{
		.gpio = 100,
		.settings = {
			[GPIOMUX_ACTIVE]    = &msm8960_gpio_suspend_in_pd_cfg,
			[GPIOMUX_SUSPENDED] = &msm8960_gpio_suspend_in_pd_cfg,
		},
	},
	{
		.gpio = 101,
		.settings = {
			[GPIOMUX_ACTIVE]    = &msm8960_gpio_suspend_in_pd_cfg,
			[GPIOMUX_SUSPENDED] = &msm8960_gpio_suspend_in_pd_cfg,
		},
	},
};

#endif /* CONFIG_MACH_MSM8960_OSCAR */
#endif /* CONFIG_PANTECH_GPIO_SLEEP_CONFIG */

#ifdef CONFIG_MMC_MSM_SDC2_SUPPORT
static struct gpiomux_setting sdcc2_clk_actv_cfg = {
	.func = GPIOMUX_FUNC_2,
	.drv = GPIOMUX_DRV_8MA,
	.pull = GPIOMUX_PULL_NONE,
};

static struct gpiomux_setting sdcc2_cmd_data_0_3_actv_cfg = {
	.func = GPIOMUX_FUNC_2,
	.drv = GPIOMUX_DRV_8MA,
	.pull = GPIOMUX_PULL_UP,
};

static struct gpiomux_setting sdcc2_suspend_cfg = {
	.func = GPIOMUX_FUNC_GPIO,
	.drv = GPIOMUX_DRV_2MA,
	.pull = GPIOMUX_PULL_DOWN,
};

static struct gpiomux_setting sdcc2_data_1_suspend_cfg = {
	.func = GPIOMUX_FUNC_GPIO,
	.drv = GPIOMUX_DRV_8MA,
	.pull = GPIOMUX_PULL_UP,
};

static struct msm_gpiomux_config msm8960_sdcc2_configs[] __initdata = {
	{
		/* DATA_3 */
		.gpio      = 92,
		.settings = {
			[GPIOMUX_ACTIVE]    = &sdcc2_cmd_data_0_3_actv_cfg,
			[GPIOMUX_SUSPENDED] = &sdcc2_suspend_cfg,
		},
	},
	{
		/* DATA_2 */
		.gpio      = 91,
		.settings = {
		[GPIOMUX_ACTIVE]    = &sdcc2_cmd_data_0_3_actv_cfg,
		[GPIOMUX_SUSPENDED] = &sdcc2_suspend_cfg,
		},
	},
#if !defined(CONFIG_MACH_MSM8960_STARQ) && !defined(CONFIG_MACH_MSM8960_OSCAR)
	{
		/* DATA_1 */
		.gpio      = 90,
		.settings = {
			[GPIOMUX_ACTIVE]    = &sdcc2_cmd_data_0_3_actv_cfg,
			[GPIOMUX_SUSPENDED] = &sdcc2_data_1_suspend_cfg,
		},
	},
	{
		/* DATA_0 */
		.gpio      = 89,
		.settings = {
			[GPIOMUX_ACTIVE]    = &sdcc2_cmd_data_0_3_actv_cfg,
			[GPIOMUX_SUSPENDED] = &sdcc2_suspend_cfg,
		},
	},
#endif /* !defined(CONFIG_MACH_MSM8960_STARQ) && !defined(CONFIG_MACH_MSM8960_OSCAR */
	{
		/* CMD */
		.gpio      = 97,
		.settings = {
			[GPIOMUX_ACTIVE]    = &sdcc2_cmd_data_0_3_actv_cfg,
			[GPIOMUX_SUSPENDED] = &sdcc2_suspend_cfg,
		},
	},
	{
		/* CLK */
		.gpio      = 98,
		.settings = {
			[GPIOMUX_ACTIVE]    = &sdcc2_clk_actv_cfg,
			[GPIOMUX_SUSPENDED] = &sdcc2_suspend_cfg,
		},
	},
};
#endif

#ifdef CONFIG_PANTECH_SND //kdkim
static struct gpiomux_setting heaset_detect_active_cfg = {
	.func = GPIOMUX_FUNC_GPIO,
	.drv = GPIOMUX_DRV_2MA,
	.pull = GPIOMUX_PULL_DOWN,
	.dir = GPIOMUX_IN,
};

static struct gpiomux_setting heaset_detect_suspend_cfg = {
	.func = GPIOMUX_FUNC_GPIO,
	.drv = GPIOMUX_DRV_2MA,
	.pull = GPIOMUX_PULL_DOWN,
	.dir = GPIOMUX_IN,
};

static struct msm_gpiomux_config headset_detect_irq_configs[] __initdata = {
	{
#if defined(T_STARQ)       
		.gpio = 50,
#else // T_OSCAR, T_EF45K, T_EF46L, T_EF47S
		.gpio = 35,
#endif
		.settings = {
			[GPIOMUX_ACTIVE]    = &heaset_detect_active_cfg,
			[GPIOMUX_SUSPENDED] = &heaset_detect_suspend_cfg,
		},
	},	
};
#endif /* CONFIG_PANTECH_SND */

int __init msm8960_init_gpiomux(void)
{
	int rc = msm_gpiomux_init(NR_GPIO_IRQS);
	if (rc) {
		pr_err(KERN_ERR "msm_gpiomux_init failed %d\n", rc);
		return rc;
	}
#if defined(CONFIG_MACH_MSM8960_STARQ) /* Backlight GPIO Initialized for STARQ  shinjg */
        msm_gpiomux_install(msm8960_starq_lcd_bl_configs,
                        ARRAY_SIZE(msm8960_starq_lcd_bl_configs));
	gpio_request(89, "mipi_backlight");
	gpio_direction_output(89, 1);
#endif

#if defined(CONFIG_KS8851) || defined(CONFIG_KS8851_MODULE)
	msm_gpiomux_install(msm8960_ethernet_configs,
			ARRAY_SIZE(msm8960_ethernet_configs));
#endif

	msm_gpiomux_install(msm8960_gsbi_configs,
			ARRAY_SIZE(msm8960_gsbi_configs));

	msm_gpiomux_install(msm8960_cyts_configs,
			ARRAY_SIZE(msm8960_cyts_configs));
#ifdef CONFIG_TOUCHSCREEN_QT602240_MSM8960
  msm_gpiomux_install(msm8960_qt602240_configs,
			ARRAY_SIZE(msm8960_qt602240_configs));
#endif
#ifdef CONFIG_TOUCHSCREEN_MELFAS_TS //dhyang
  msm_gpiomux_install(msm8960_melfas_configs,
			ARRAY_SIZE(msm8960_melfas_configs));
#endif
	msm_gpiomux_install(msm8960_slimbus_config,
			ARRAY_SIZE(msm8960_slimbus_config));

	msm_gpiomux_install(msm8960_audio_codec_configs,
			ARRAY_SIZE(msm8960_audio_codec_configs));

#ifndef CONFIG_PN544
	msm_gpiomux_install(msm8960_audio_auxpcm_configs,
			ARRAY_SIZE(msm8960_audio_auxpcm_configs));
#endif

	msm_gpiomux_install(wcnss_5wire_interface,
			ARRAY_SIZE(wcnss_5wire_interface));

#ifdef CONFIG_MMC_MSM_SDC4_SUPPORT
	msm_gpiomux_install(msm8960_sdcc4_configs,
		ARRAY_SIZE(msm8960_sdcc4_configs));
#endif

	if (machine_is_msm8960_mtp() || machine_is_msm8960_fluid() ||
		machine_is_msm8960_liquid() || machine_is_msm8960_cdp())
		msm_gpiomux_install(hap_lvl_shft_config,
			ARRAY_SIZE(hap_lvl_shft_config));

#ifdef CONFIG_USB_EHCI_MSM_HSIC
	if ((SOCINFO_VERSION_MAJOR(socinfo_get_version()) != 1) &&
		machine_is_msm8960_liquid())
		msm_gpiomux_install(msm8960_hsic_configs,
			ARRAY_SIZE(msm8960_hsic_configs));

	if ((SOCINFO_VERSION_MAJOR(socinfo_get_version()) != 1) &&
			machine_is_msm8960_liquid())
		msm_gpiomux_install(msm8960_hsic_hub_configs,
			ARRAY_SIZE(msm8960_hsic_hub_configs));
#endif

#ifdef CONFIG_FB_MSM_HDMI_MSM_PANEL
	msm_gpiomux_install(msm8960_hdmi_configs,
			ARRAY_SIZE(msm8960_hdmi_configs));
#endif

	msm_gpiomux_install(msm8960_mdp_vsync_configs,
			ARRAY_SIZE(msm8960_mdp_vsync_configs));

#ifdef CONFIG_PANTECH_CHARGER_WIRELESS
	msm_gpiomux_install(msm8960_wireless_charger_configs,
			ARRAY_SIZE(msm8960_wireless_charger_configs));
#endif

#ifdef CONFIG_PANTECH_PMIC // gpio-config for QC recommendation (pull-up) 
	msm_gpiomux_install(msm8960_pm_irq_configs,
			ARRAY_SIZE(msm8960_pm_irq_configs));
#endif

#ifdef CONFIG_PANTECH_SND //kdkim
	msm_gpiomux_install(headset_detect_irq_configs,
			ARRAY_SIZE(headset_detect_irq_configs));
#endif /* CONFIG_PANTECH_SND */

	if (socinfo_get_platform_subtype() == PLATFORM_SUBTYPE_SGLTE)
		msm_gpiomux_install(msm8960_gsbi8_uart_configs,
			ARRAY_SIZE(msm8960_gsbi8_uart_configs));
	else
		msm_gpiomux_install(msm8960_gsbi5_uart_configs,
			ARRAY_SIZE(msm8960_gsbi5_uart_configs));

	if (socinfo_get_platform_subtype() == PLATFORM_SUBTYPE_SGLTE) {
		/* For 8960 Fusion 2.2 Primary IPC */
		msm_gpiomux_install(msm8960_fusion_gsbi_configs,
			ARRAY_SIZE(msm8960_fusion_gsbi_configs));
		/* For SGLTE 8960 Fusion External VFR */
		msm_gpiomux_install(msm8960_external_vfr_configs,
			ARRAY_SIZE(msm8960_external_vfr_configs));
	}

#ifdef CONFIG_PANTECH_GPIO_SLEEP_CONFIG
#if (defined(CONFIG_MACH_MSM8960_STARQ) || defined(CONFIG_MACH_MSM8960_OSCAR))
	msm_gpiomux_install(msm8960_sleep_gpio_gpio_configs,
			ARRAY_SIZE(msm8960_sleep_gpio_gpio_configs));
#endif /* defined(CONFIG_MACH_MSM8960_STARQ) || defined(CONFIG_MACH_MSM8960_OSCAR */
#endif /* CONFIG_PANTECH_GPIO_SLEEP_CONFIG */

#ifdef CONFIG_MMC_MSM_SDC2_SUPPORT
	msm_gpiomux_install(msm8960_sdcc2_configs,
		ARRAY_SIZE(msm8960_sdcc2_configs));
#endif

	if (socinfo_get_platform_subtype() == PLATFORM_SUBTYPE_SGLTE)
		msm_gpiomux_install(sglte_configs,
			ARRAY_SIZE(sglte_configs));

	return 0;
}

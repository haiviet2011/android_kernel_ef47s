/* Copyright (c) 2011, PANTECH. All rights reserved.
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

#ifndef _S5K4ECGX_H_
#define _S5K4ECGX_H_

int s5k4ecgx_sensor_init(struct msm_sensor_ctrl_t *s_ctrl);

int s5k4ecgx_video_config(void);

int s5k4ecgx_snapshot_config(void);

int s5k4ecgx_zsl_config(void);

#endif /* _S5K4ECGX_H_ */

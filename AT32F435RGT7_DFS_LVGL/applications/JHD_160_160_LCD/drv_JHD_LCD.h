/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2026-04-25     mutou       the first version
 */
#ifndef APPLICATIONS_JHD_160_160_LCD_DRV_JHD_LCD_H_
#define APPLICATIONS_JHD_160_160_LCD_DRV_JHD_LCD_H_

#include <drv_common.h>

void Drv_JHD_LCD_Init(void);
void LCD_Write_Data(void *Data, uint16_t len);
void LCD_Write_CMD(uint8_t Cmd);

#endif /* APPLICATIONS_JHD_160_160_LCD_DRV_JHD_LCD_H_ */

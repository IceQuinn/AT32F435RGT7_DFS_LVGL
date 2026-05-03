/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2026-05-02     mutou       the first version
 */
#include "ui_desktop.h"


#include <lvgl.h>

lv_obj_t * scr_boot;
lv_obj_t * scr_main;

void boot_ui_create(void)
{
    // 启动画面
    scr_boot = lv_obj_create(NULL);

    lv_obj_t * label = lv_label_create(scr_boot);
    lv_label_set_text(label, "My Device\nLoading...");
    lv_obj_center(label);

    // 主界面
    scr_main = lv_obj_create(NULL);

    lv_obj_t * cont = lv_label_create(scr_main);

    lv_obj_set_size(cont, LV_PCT(100), LV_PCT(100));
    lv_obj_center(cont);

    // 垂直布局
    lv_obj_set_flex_flow(cont, LV_FLEX_FLOW_COLUMN);

    // 去掉容器样式（单色屏建议）
    lv_obj_set_style_border_width(cont, 0, 0);
    lv_obj_set_style_bg_opa(cont, LV_OPA_TRANSP, 0);

    // 子对象间距
    lv_obj_set_style_pad_row(cont, 10, 0);
    lv_obj_set_style_pad_all(cont, 10, 0);

    // =========================================================
    // ===== 上侧：时间卡片 =====
    // =========================================================
    lv_obj_t * card_time = lv_obj_create(cont);
    lv_obj_set_size(card_time, LV_PCT(100), LV_PCT(48));

    // 样式（单色屏）
    lv_obj_set_style_radius(card_time, 0, 0);
    lv_obj_set_style_border_width(card_time, 2, 0);
    lv_obj_set_style_border_color(card_time, lv_color_black(), 0);

    // 时间
    lv_obj_t * time_label = lv_label_create(card_time);
    lv_label_set_text(time_label, "14:23:05");
    lv_obj_align(time_label, LV_ALIGN_CENTER, 0, -20);

    // 日期
    lv_obj_t * date_label = lv_label_create(card_time);
    lv_label_set_text(date_label, "2026-05-02");
    lv_obj_align(date_label, LV_ALIGN_CENTER, 0, 20);

    // =========================================================
    // ===== 右侧：天气卡片 =====
    // =========================================================
    lv_obj_t * card_weather = lv_obj_create(cont);
    lv_obj_set_size(card_weather, LV_PCT(100), LV_PCT(48));

    lv_obj_set_style_radius(card_weather, 0, 0);
    lv_obj_set_style_border_width(card_weather, 2, 0);
    lv_obj_set_style_border_color(card_weather, lv_color_black(), 0);

    // 天气图标（单色可以用文本代替）
    lv_obj_t * weather_icon = lv_label_create(card_weather);
    lv_label_set_text(weather_icon, "Cloudy");
    lv_obj_align(weather_icon, LV_ALIGN_CENTER, 0, -20);

    // 温度
    lv_obj_t * temp_label = lv_label_create(card_weather);
    lv_label_set_text(temp_label, "25C");
    lv_obj_align(temp_label, LV_ALIGN_CENTER, 0, 0);

    // 城市
    lv_obj_t * city_label = lv_label_create(card_weather);
    lv_label_set_text(city_label, "Tokyo");
    lv_obj_align(city_label, LV_ALIGN_CENTER, 0, 20);

}

static void boot_to_main_cb(lv_timer_t * t)
{
    lv_scr_load(scr_main);
}


void lv_user_gui_init(void)
{
    boot_ui_create();

    // 先显示启动界面
    lv_scr_load(scr_boot);

    // 3秒后切换
    lv_timer_create(boot_to_main_cb, 3000, NULL);
}

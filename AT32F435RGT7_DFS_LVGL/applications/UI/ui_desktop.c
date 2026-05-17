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
#include <time.h>

#include "hy.h"

lv_obj_t * scr_boot;

lv_obj_t *img;
lv_obj_t * scr_main;

lv_obj_t * time_label;
lv_obj_t * weekday_label;
lv_obj_t * addr_label;
lv_obj_t * weather_label;



void boot_ui_create(void)
{


    img = lv_img_create(lv_scr_act());

    lv_img_set_src(img, &hy1);

    lv_obj_center(img);

    // 主界面
    scr_main = lv_obj_create(NULL);

    lv_obj_t * cont = lv_obj_create(scr_main);

    lv_obj_set_size(cont, LV_PCT(100), LV_PCT(100));
    lv_obj_center(cont);

    // 垂直布局
    lv_obj_set_flex_flow(cont, LV_FLEX_FLOW_COLUMN);

    // 去掉容器样式（单色屏建议）
    lv_obj_set_style_border_width(cont, 0, 0);
    lv_obj_set_style_bg_opa(cont, LV_OPA_TRANSP, 0);

    // 子对象间距
    // 控制子对象行之间间距
    lv_obj_set_style_pad_row(cont, 0, 0);
    // 一次性设置对象四个方向的内边距
    lv_obj_set_style_pad_all(cont, 0, 0);

    // =========================================================
    // ===== 上侧：时间卡片 =====
    // =========================================================
    // 创建一个通用控件
    lv_obj_t * card_time = lv_obj_create(cont);
    lv_obj_set_size(card_time, LV_PCT(100), LV_PCT(50));
//    lv_obj_set_style_pad_all(card_time, 0, 0);


    // 样式（单色屏）
    lv_obj_set_style_radius(card_time, 0, 0);
    lv_obj_set_style_border_width(card_time, 2, 0);
    lv_obj_set_style_border_color(card_time, lv_color_black(), 0);

    // 时间
    char time_str[20] = "2026-05-02 14:23:05";
    time_label = lv_label_create(card_time);
    lv_label_set_text(time_label, time_str);
    lv_obj_align(time_label, LV_ALIGN_TOP_LEFT, 0, -14);
    lv_obj_set_style_pad_all(time_label, 0, 0);
    // 周
    weekday_label = lv_label_create(card_time);
    // 设置对象相对于参考对象的位置（对齐）的函数
    // obj：要移动的对象
    // align：对齐方式
    // x_ofs：水平方向偏移（右为正）
    // y_ofs：垂直方向偏移（下为正）
    // 默认字符高度为14
    lv_obj_align(weekday_label, LV_ALIGN_TOP_LEFT, 0, 0);

    // 地址
    addr_label  = lv_label_create(card_time);
    lv_obj_align(addr_label, LV_ALIGN_TOP_LEFT, 0, 14);

    // 天气
    weather_label  = lv_label_create(card_time);
    lv_obj_align(weather_label, LV_ALIGN_TOP_LEFT, 0, 28);
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

uint32_t time_stamp = 1777904743;
uint32_t Year, Month, Day, Hour, Minute, Second;
static void boot_to_main_cb(lv_timer_t * t)
{
    char time_str[20];
    time_stamp++;
    time_t tm_t = time_stamp;
    struct tm *tm = localtime(&tm_t);

    Year = tm->tm_year + 1900;
    Month = tm->tm_mon + 1;
    Day = tm->tm_mday;
    Hour = tm->tm_hour;
    Minute = tm->tm_min;
    Second = tm->tm_sec;

    rt_snprintf(time_str, sizeof(time_str), "%04d-%02d-%02d %02d:%02d:%02d",
              Year, Month, Day, Hour, Minute, Second);
    lv_label_set_text(time_label, time_str);

    lv_label_set_text(weekday_label, "week2");

    lv_label_set_text(addr_label, "Wuhan");
    lv_label_set_text(weather_label, "clear");


    lv_scr_load(scr_main);
}


void lv_user_gui_init(void)
{
    boot_ui_create();

    // 先显示启动界面
    lv_scr_load(img);

    // 3秒后切换
    lv_timer_create(boot_to_main_cb, 1000, NULL);
}

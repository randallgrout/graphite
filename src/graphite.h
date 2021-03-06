// Copyright 2016 Stefan Heule
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//        http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#ifndef GRAPHITE_GRAPHITE_H
#define GRAPHITE_GRAPHITE_H

#include <pebble.h>

// fctx headers
#include <pebble-fctx/fctx.h>
#include <pebble-fctx/ffont.h>

// I don't know how to pass parameters to the compiler, so I'm using this file
// for various configurations
#include "config.h"


////////////////////////////////////////////
//// Configuration constants
////////////////////////////////////////////

// -- autogen
// -- ## for key in configuration
// -- ##   if not key["local"]
// -- #define {{ key["key"] }} {{ key["id"] }}
// -- ##   endif
// -- ## endfor
#define CONFIG_VIBRATE_DISCONNECT 1
#define CONFIG_VIBRATE_RECONNECT 2
#define CONFIG_MESSAGE_DISCONNECT 3
#define CONFIG_MESSAGE_RECONNECT 4
#define CONFIG_WEATHER_REFRESH 10
#define CONFIG_WEATHER_EXPIRATION 11
#define CONFIG_WEATHER_REFRESH_FAILED 12
#define CONFIG_COLOR_TOPBAR_BG 13
#define CONFIG_COLOR_INFO_BELOW 14
#define CONFIG_COLOR_PROGRESS_BAR 15
#define CONFIG_COLOR_PROGRESS_BAR2 16
#define CONFIG_COLOR_TIME 17
#define CONFIG_COLOR_PERC 18
#define CONFIG_COLOR_WIDGET_1 19
#define CONFIG_COLOR_WIDGET_2 20
#define CONFIG_COLOR_WIDGET_3 21
#define CONFIG_COLOR_WIDGET_4 22
#define CONFIG_COLOR_WIDGET_5 23
#define CONFIG_COLOR_WIDGET_6 24
#define CONFIG_COLOR_BACKGROUND 25
#define CONFIG_COLOR_DAY 26
#define CONFIG_COLOR_NIGHT 27
#define CONFIG_COLOR_BAT_30 28
#define CONFIG_COLOR_BAT_20 29
#define CONFIG_COLOR_BAT_10 30
#define CONFIG_LOWBAT_COL 31
#define CONFIG_WIDGET_1 33
#define CONFIG_WIDGET_2 34
#define CONFIG_WIDGET_3 35
#define CONFIG_WIDGET_4 36
#define CONFIG_WIDGET_5 37
#define CONFIG_WIDGET_6 38
#define CONFIG_PROGRESS 39
#define CONFIG_TIME_FORMAT 40
#define CONFIG_INFO_BELOW 41
#define CONFIG_UPDATE_SECOND 42
#define CONFIG_SHOW_DAYNIGHT 46
#define CONFIG_STEP_GOAL 47
#define CONFIG_TZ_0_FORMAT 51
#define CONFIG_TZ_1_FORMAT 52
#define CONFIG_TZ_2_FORMAT 53
#define CONFIG_HOURLY_VIBRATE 54
#define CONFIG_SUNRISE_FORMAT 55
#define CONFIG_WIDGET_7 56
#define CONFIG_WIDGET_8 57
#define CONFIG_WIDGET_9 58
#define CONFIG_WIDGET_10 59
#define CONFIG_WIDGET_11 60
#define CONFIG_WIDGET_12 61
#define CONFIG_TIMEOUT_2ND_WIDGETS 62
#define CONFIG_2ND_WIDGETS 63
#define CONFIG_WEATHER_SUNRISE_EXPIRATION 64
#define CONFIG_COLOR_QUIET_MODE 65
#define CONFIG_QUIET_COL 66
#define CONFIG_PHONE_BATTERY_EXPIRATION 67
#define CONFIG_PHONE_BATTERY_REFRESH 68
#define CONFIG_UPDATE_PHONEBAT_ON_SHAKE 69
// -- end autogen

// -- autogen
// -- #define GRAPHITE_N_CONFIG {{ num_config_items }}
#define GRAPHITE_N_CONFIG 69
// -- end autogen

// -- autogen
// -- ## for key in message_keys
// -- #define {{ key["key"] }} {{ key["id"] }}
// -- ## endfor
#define MSG_KEY_WEATHER_TEMP_LOW 100
#define MSG_KEY_WEATHER_TEMP_HIGH 101
#define MSG_KEY_WEATHER_TEMP_CUR 102
#define MSG_KEY_WEATHER_ICON_CUR 103
#define MSG_KEY_WEATHER_PERC_DATA 104
#define MSG_KEY_WEATHER_PERC_DATA_LEN 105
#define MSG_KEY_WEATHER_PERC_DATA_TS 106
#define MSG_KEY_FETCH_WEATHER 107
#define MSG_KEY_WEATHER_FAILED 108
#define MSG_KEY_JS_READY 109
#define MSG_KEY_FETCH_TZ_0 110
#define MSG_KEY_TZ_0 111
#define MSG_KEY_FETCH_TZ_1 112
#define MSG_KEY_TZ_1 113
#define MSG_KEY_FETCH_TZ_2 114
#define MSG_KEY_TZ_2 115
#define MSG_KEY_WEATHER_SUNRISE 116
#define MSG_KEY_WEATHER_SUNSET 117
#define MSG_KEY_PHONEBAT 118
#define MSG_KEY_FETCH_PHONEBAT 119
#define PERSIST_KEY_WEATHER 201
#define PERSIST_KEY_TZ 202
#define PERSIST_KEY_PHONEBAT 203
// -- end autogen


////////////////////////////////////////////
//// Configuration values
////////////////////////////////////////////

#define GRAPHITE_STRINGCONFIG_MAXLEN 50

// -- autogen
// -- ## for key in configuration
// -- ##   if not key["local"]
// -- ##   if key["type"] != "string"
// -- extern {{ key["type"] | replace("string", "char") }} {{ key["key"] | lower }};
// -- ##   else
// -- extern char {{ key["key"] | lower }}[GRAPHITE_STRINGCONFIG_MAXLEN+1];
// -- ##   endif
// -- ##   endif
// -- ## endfor
extern uint8_t config_vibrate_disconnect;
extern uint8_t config_vibrate_reconnect;
extern uint8_t config_message_disconnect;
extern uint8_t config_message_reconnect;
extern uint16_t config_weather_refresh;
extern uint16_t config_weather_expiration;
extern uint16_t config_weather_refresh_failed;
extern uint8_t config_color_topbar_bg;
extern uint8_t config_color_info_below;
extern uint8_t config_color_progress_bar;
extern uint8_t config_color_progress_bar2;
extern uint8_t config_color_time;
extern uint8_t config_color_perc;
extern uint8_t config_color_widget_1;
extern uint8_t config_color_widget_2;
extern uint8_t config_color_widget_3;
extern uint8_t config_color_widget_4;
extern uint8_t config_color_widget_5;
extern uint8_t config_color_widget_6;
extern uint8_t config_color_background;
extern uint8_t config_color_day;
extern uint8_t config_color_night;
extern uint8_t config_color_bat_30;
extern uint8_t config_color_bat_20;
extern uint8_t config_color_bat_10;
extern uint8_t config_lowbat_col;
extern uint8_t config_widget_1;
extern uint8_t config_widget_2;
extern uint8_t config_widget_3;
extern uint8_t config_widget_4;
extern uint8_t config_widget_5;
extern uint8_t config_widget_6;
extern uint8_t config_progress;
extern char config_time_format[GRAPHITE_STRINGCONFIG_MAXLEN+1];
extern char config_info_below[GRAPHITE_STRINGCONFIG_MAXLEN+1];
extern uint8_t config_update_second;
extern uint8_t config_show_daynight;
extern uint16_t config_step_goal;
extern char config_tz_0_format[GRAPHITE_STRINGCONFIG_MAXLEN+1];
extern char config_tz_1_format[GRAPHITE_STRINGCONFIG_MAXLEN+1];
extern char config_tz_2_format[GRAPHITE_STRINGCONFIG_MAXLEN+1];
extern uint8_t config_hourly_vibrate;
extern char config_sunrise_format[GRAPHITE_STRINGCONFIG_MAXLEN+1];
extern uint8_t config_widget_7;
extern uint8_t config_widget_8;
extern uint8_t config_widget_9;
extern uint8_t config_widget_10;
extern uint8_t config_widget_11;
extern uint8_t config_widget_12;
extern uint16_t config_timeout_2nd_widgets;
extern uint8_t config_2nd_widgets;
extern uint16_t config_weather_sunrise_expiration;
extern uint8_t config_color_quiet_mode;
extern uint8_t config_quiet_col;
extern uint16_t config_phone_battery_expiration;
extern uint16_t config_phone_battery_refresh;
extern uint8_t config_update_phonebat_on_shake;
// -- end autogen


////////////////////////////////////////////
//// Complications
////////////////////////////////////////////

// widgets take a parameter draw and only will actually draw the content
// if draw==true.  Otherwise they just return the width of the widget.
typedef fixed_t (*widget_render_t)(FContext* fctx, bool draw, FPoint position, GTextAlignment align, uint8_t foreground_color, uint8_t background_color);
extern widget_render_t widgets[];


////////////////////////////////////////////
//// Global variables
////////////////////////////////////////////

extern Window *window;
extern Layer *layer_background;
extern char buffer_1[GRAPHITE_STRINGCONFIG_MAXLEN+1];
extern char buffer_2[GRAPHITE_STRINGCONFIG_MAXLEN+1];
extern fixed_t height;
extern fixed_t width;
extern fixed_t height_full;
extern FFont* font_main;
extern FFont* font_weather;
extern FFont* font_icon;
extern fixed_t fontsize_widgets;

extern bool show_bluetooth_popup;
extern AppTimer *timer_bluetooth_popup;
extern bool show_secondary_widgets;

// this definition should be updated whenever the Weather struct, or it's semantic meaning changes.  this ensures that no outdated values are read from storage
#define GRAPHITE_WEATHER_VERSION 3
// -- autogen
// -- #define GRAPHITE_WEATHER_PERC_MAX_LEN {{ perc_max_len }}
#define GRAPHITE_WEATHER_PERC_MAX_LEN 30
// -- end autogen
#define GRAPHITE_UNKNOWN_WEATHER 32767
typedef struct {
    uint8_t version;
    time_t timestamp;
    int8_t icon;
    int16_t temp_cur;
    int16_t temp_low;
    int16_t temp_high;
    uint8_t perc_data[GRAPHITE_WEATHER_PERC_MAX_LEN];
    uint8_t perc_data_len; // maybe not all perc data items are valid
    time_t perc_data_ts;
    time_t sunrise;
    time_t sunset;
    bool failed;
} __attribute__((__packed__)) Weather;

extern Weather weather;
extern bool js_ready;
extern AppTimer * weather_request_timer;

// this definition should be updated whenever the Weather struct, or it's semantic meaning changes.  this ensures that no outdated values are read from storage
#define GRAPHITE_PHONE_BATTERY_VERSION 1
typedef struct {
    uint8_t version;
    uint8_t level;
    time_t timestamp;
} __attribute__((__packed__)) PhoneBattery;
extern PhoneBattery phonebat;
extern AppTimer * phone_battery_request_timer;

// -- autogen
// -- #define GRAPHITE_NUM_TZS {{ num_tzs }}
// -- #define GRAPHITE_TZ_MAX_DATAPOINTS {{ tz_max_datapoints }}
#define GRAPHITE_NUM_TZS 3
#define GRAPHITE_TZ_MAX_DATAPOINTS 3
// -- end autogen
#define GRAPHITE_TZ_DATA_VERSION 1

typedef struct {
    bool valid;
    int32_t untils[GRAPHITE_TZ_MAX_DATAPOINTS];
    int16_t offsets[GRAPHITE_TZ_MAX_DATAPOINTS];
} __attribute__((__packed__)) TZData;

typedef struct {
    uint16_t version;
    TZData data[GRAPHITE_NUM_TZS];
} __attribute__((__packed__)) TimeZoneInfo;
extern TimeZoneInfo tzinfo;


////////////////////////////////////////////
//// Static configuration and useful macros
////////////////////////////////////////////

#define COLOR(c) ((GColor8) { .argb = (c) })
#define MAX(x,y) ((x) < (y) ? (y) : (x))

#define GRAPHITE_BLUETOOTH_POPUP_MS 5000

#define GRAPHITE_OUTBOX_SIZE 100
#define GRAPHITE_WEATHER_N_INTS 6 // 3 temps + 1 icon + data len + data timestamp
#define GRAPHITE_WEATHER_HOURS 30
// 100 + an upper bound for all the configuration items we have OR the amount of data sent as weather update
#define GRAPHITE_INBOX_SIZE (100 + MAX(1 + (GRAPHITE_N_CONFIG) * (7+4), GRAPHITE_WEATHER_N_INTS * 4 + GRAPHITE_WEATHER_HOURS * 4))

#define PIX(x) (INT_TO_FIXED(x))
// returns a fixed_t value that corresponds to a relatively scaled version, where 1 rem is 1/200 of the screen width
#define REM(x) ((fixed_t)(INT_TO_FIXED(x) * PBL_DISPLAY_WIDTH / 200))
// round to a nearest pixel (from fixed to fixed)
#define FIXED_ROUND(x) ((x) % FIXED_POINT_SCALE < FIXED_POINT_SCALE/2 ? (x) - ((x) % FIXED_POINT_SCALE) : (x) + FIXED_POINT_SCALE - ((x) % FIXED_POINT_SCALE))

#if defined(PBL_PLATFORM_EMERY) || defined(PBL_PLATFORM_DIORITE)
#define IF_HR(a, b) (a)
#else
#define IF_HR(a, b) (b)
#endif

////////////////////////////////////////////
//// includes
////////////////////////////////////////////

#include "settings.h"
#include "ui-util.h"
#include "ui.h"
#include "widgets.h"

#endif //GRAPHITE_GRAPHITE_H

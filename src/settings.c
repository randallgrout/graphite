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

#include <pebble.h>
#include "settings.h"
#include "redshift.h"


static void update_weather_helper(void *unused);

void set_weather_timer(int timeout_min) {
    const uint32_t timeout_ms = timeout_min * 1000 * 60;
    if (weather_request_timer) {
        if (!app_timer_reschedule(weather_request_timer, timeout_ms)) {
            weather_request_timer = app_timer_register(timeout_ms, update_weather_helper, NULL);
        }
    } else {
        weather_request_timer = app_timer_register(timeout_ms, update_weather_helper, NULL);
    }
}

/**
 * Update the weather information (and schedule a periodic timer to update again)
 */
void update_weather() {
    // return if we don't want weather information
    if (config_weather_refresh == 0) return;

    bool need_weather = false;
    uint32_t timeout_min = config_weather_refresh;
    if (weather.timestamp == 0) {
        need_weather = true;
    } else {
        need_weather = (time(NULL) - weather.timestamp) > (config_weather_refresh * 60);
        if (!need_weather) {
            timeout_min = (time(NULL) - weather.timestamp) / 60;
        }
    }
    set_weather_timer(timeout_min);
    if (!need_weather) return;

    // actually update the weather by sending a request
    DictionaryIterator *iter;
    app_message_outbox_begin(&iter);
    dict_write_uint8(iter, MSG_KEY_FETCH_WEATHER, 1);
    app_message_outbox_send();
// -- build=debug
// --     APP_LOG(APP_LOG_LEVEL_INFO, "requesting weather update");
    APP_LOG(APP_LOG_LEVEL_INFO, "requesting weather update");
// -- end build
}

/**
 * Utility function.
 */
static void update_weather_helper(void *unused) {
    update_weather();
}

/**
 * Helpers to process new configuration.
 */
bool sync_helper_uint8_t(const uint32_t key, DictionaryIterator *iter, uint8_t *value) {
    Tuple *new_tuple = dict_find(iter, key);
    if (new_tuple == NULL) return false;
    if ((*value) != new_tuple->value->uint8) {
        (*value) = new_tuple->value->uint8;
        persist_write_int(key, *value);
        return true;
    }
    return false;
}
bool sync_helper_uint16_t(const uint32_t key, DictionaryIterator *iter, uint16_t *value) {
    Tuple *new_tuple = dict_find(iter, key);
    if (new_tuple == NULL) return false;
    if ((*value) != new_tuple->value->uint16) {
        (*value) = new_tuple->value->uint16;
        persist_write_int(key, *value);
        return true;
    }
    return false;
}
bool sync_helper_string(const uint32_t key, DictionaryIterator *iter, char *buffer) {
    int maxlen = REDSHIFT_STRINGCONFIG_MAXLEN;
    Tuple *new_tuple = dict_find(iter, key);
    if (new_tuple == NULL) return false;
    if (strncmp(buffer, new_tuple->value->cstring, maxlen) != 0) {
        strncpy(buffer, new_tuple->value->cstring, maxlen);
        persist_write_string(key, buffer);
        return true;
    }
    return false;
}

void inbox_received_handler(DictionaryIterator *iter, void *context) {
// -- build=debug
// --     APP_LOG(APP_LOG_LEVEL_DEBUG, "received message");
    APP_LOG(APP_LOG_LEVEL_DEBUG, "received message");
// -- end build

    bool dirty = false;
// -- autogen
// -- ## for key in configuration
// -- ##   if not key["local"]
// --     dirty |= sync_helper_{{ key["type"] }}({{ key["key"] }}, iter, {% if key["type"] != "string" %}&{% endif %}{{ key["key"] | lower }});
// -- ##   endif
// -- ## endfor
    dirty |= sync_helper_uint8_t(CONFIG_VIBRATE_DISCONNECT, iter, &config_vibrate_disconnect);
    dirty |= sync_helper_uint8_t(CONFIG_VIBRATE_RECONNECT, iter, &config_vibrate_reconnect);
    dirty |= sync_helper_uint8_t(CONFIG_MESSAGE_DISCONNECT, iter, &config_message_disconnect);
    dirty |= sync_helper_uint8_t(CONFIG_MESSAGE_RECONNECT, iter, &config_message_reconnect);
    dirty |= sync_helper_uint16_t(CONFIG_WEATHER_REFRESH, iter, &config_weather_refresh);
    dirty |= sync_helper_uint16_t(CONFIG_WEATHER_EXPIRATION, iter, &config_weather_expiration);
    dirty |= sync_helper_uint16_t(CONFIG_WEATHER_REFRESH_FAILED, iter, &config_weather_refresh_failed);
    dirty |= sync_helper_uint8_t(CONFIG_COLOR_TOPBAR_BG, iter, &config_color_topbar_bg);
    dirty |= sync_helper_uint8_t(CONFIG_COLOR_INFO_BELOW, iter, &config_color_info_below);
    dirty |= sync_helper_uint8_t(CONFIG_COLOR_PROGRESS_BAR, iter, &config_color_progress_bar);
    dirty |= sync_helper_uint8_t(CONFIG_COLOR_PROGRESS_BAR2, iter, &config_color_progress_bar2);
    dirty |= sync_helper_uint8_t(CONFIG_COLOR_TIME, iter, &config_color_time);
    dirty |= sync_helper_uint8_t(CONFIG_COLOR_PERC, iter, &config_color_perc);
    dirty |= sync_helper_uint8_t(CONFIG_COLOR_BOTTOM_COMPLICATIONS, iter, &config_color_bottom_complications);
    dirty |= sync_helper_uint8_t(CONFIG_COLOR_BACKGROUND, iter, &config_color_background);
    dirty |= sync_helper_uint8_t(CONFIG_COLOR_TOP_COMPLICATIONS, iter, &config_color_top_complications);
    dirty |= sync_helper_uint8_t(CONFIG_COLOR_DAY, iter, &config_color_day);
    dirty |= sync_helper_uint8_t(CONFIG_COLOR_NIGHT, iter, &config_color_night);
    dirty |= sync_helper_uint8_t(CONFIG_COLOR_BAT_30, iter, &config_color_bat_30);
    dirty |= sync_helper_uint8_t(CONFIG_COLOR_BAT_20, iter, &config_color_bat_20);
    dirty |= sync_helper_uint8_t(CONFIG_COLOR_BAT_10, iter, &config_color_bat_10);
    dirty |= sync_helper_uint8_t(CONFIG_LOWBAT_COL, iter, &config_lowbat_col);
    dirty |= sync_helper_uint8_t(CONFIG_COMPLICATION_1, iter, &config_complication_1);
    dirty |= sync_helper_uint8_t(CONFIG_COMPLICATION_2, iter, &config_complication_2);
    dirty |= sync_helper_uint8_t(CONFIG_COMPLICATION_3, iter, &config_complication_3);
    dirty |= sync_helper_uint8_t(CONFIG_COMPLICATION_4, iter, &config_complication_4);
    dirty |= sync_helper_uint8_t(CONFIG_COMPLICATION_5, iter, &config_complication_5);
    dirty |= sync_helper_uint8_t(CONFIG_COMPLICATION_6, iter, &config_complication_6);
    dirty |= sync_helper_uint8_t(CONFIG_PROGRESS, iter, &config_progress);
    dirty |= sync_helper_string(CONFIG_TIME_FORMAT, iter, config_time_format);
    dirty |= sync_helper_string(CONFIG_INFO_BELOW, iter, config_info_below);
    dirty |= sync_helper_uint8_t(CONFIG_UPDATE_SECOND, iter, &config_update_second);
    dirty |= sync_helper_uint8_t(CONFIG_SHOW_DAYNIGHT, iter, &config_show_daynight);
    dirty |= sync_helper_uint16_t(CONFIG_STEP_GOAL, iter, &config_step_goal);
// -- end autogen

    bool ask_for_weather_update = true;

    Tuple *icon_tuple = dict_find(iter, MSG_KEY_WEATHER_ICON_CUR);
    Tuple *tempcur_tuple = dict_find(iter, MSG_KEY_WEATHER_TEMP_CUR);
    Tuple *templow_tuple = dict_find(iter, MSG_KEY_WEATHER_TEMP_LOW);
    Tuple *temphigh_tuple = dict_find(iter, MSG_KEY_WEATHER_TEMP_HIGH);
    Tuple *perc_data_tuple = dict_find(iter, MSG_KEY_WEATHER_PERC_DATA);
    Tuple *perc_data_ts_tuple = dict_find(iter, MSG_KEY_WEATHER_PERC_DATA_TS);
    Tuple *perc_data_len_tuple = dict_find(iter, MSG_KEY_WEATHER_PERC_DATA_LEN);
    if (icon_tuple && tempcur_tuple && templow_tuple && temphigh_tuple) {
        weather.version = REDSHIFT_WEATHER_VERSION;
        weather.timestamp = time(NULL);
        weather.icon = icon_tuple->value->int8;
        weather.temp_cur = tempcur_tuple->value->int8;
        weather.temp_low = templow_tuple->value->int8;
        weather.temp_high = temphigh_tuple->value->int8;

        if (perc_data_tuple && perc_data_ts_tuple && perc_data_len_tuple) {
            weather.perc_data_len = perc_data_len_tuple->value->uint8;
            weather.perc_data_ts = perc_data_ts_tuple->value->int32;
            for (int i = 0; i < weather.perc_data_len && i < REDSHIFT_WEATHER_PERC_MAX_LEN; i++) {
                weather.perc_data[i] = perc_data_tuple->value->data[i];
            }
        } else {
            weather.perc_data_len = 0;
            weather.perc_data_ts = 0;
        }

        weather.failed = false;
        persist_write_data(PERSIST_KEY_WEATHER, &weather, sizeof(Weather));
        dirty = true;
        ask_for_weather_update = false;
    }
    if (dict_find(iter, MSG_KEY_WEATHER_FAILED)) {
        // retry early when weather update failed
        set_weather_timer(config_weather_refresh_failed);
        ask_for_weather_update = false;
        weather.failed = true;
    }

    if (dict_find(iter, MSG_KEY_JS_READY)) {
        js_ready = true;
    }
    if (dirty) {
        // make sure we update tick frequency if necessary
        subscribe_tick(true);
        layer_mark_dirty(layer_background);
    }
    if (ask_for_weather_update) {
        update_weather();
    }
}

/**
 * Read a value from the persistent storage (or load the default value).
 */
void read_config_uint8_t(const uint32_t key, uint8_t *value) {
    if (persist_exists(key)) {
        *value = persist_read_int(key);
    } else {
        persist_write_int(key, *value);
    }
}
void read_config_uint16_t(const uint32_t key, uint16_t *value) {
    if (persist_exists(key)) {
        *value = persist_read_int(key);
    } else {
        persist_write_int(key, *value);
    }
}
void read_config_string(const uint32_t key, char *buffer) {
    if (persist_exists(key)) {
        persist_read_string(key, buffer, REDSHIFT_STRINGCONFIG_MAXLEN);
    } else {
        persist_write_string(key, buffer);
    }
}


/**
 * Read all items from the configuration storage.
 */
void read_config_all() {

// -- autogen
// -- ## for key in configuration
// -- ##   if not key["local"]
// --     read_config_{{ key["type"] }}({{ key["key"] }}, {% if key["type"] != "string" %}&{% endif %}{{ key["key"] | lower }});
// -- ##   endif
// -- ## endfor
    read_config_uint8_t(CONFIG_VIBRATE_DISCONNECT, &config_vibrate_disconnect);
    read_config_uint8_t(CONFIG_VIBRATE_RECONNECT, &config_vibrate_reconnect);
    read_config_uint8_t(CONFIG_MESSAGE_DISCONNECT, &config_message_disconnect);
    read_config_uint8_t(CONFIG_MESSAGE_RECONNECT, &config_message_reconnect);
    read_config_uint16_t(CONFIG_WEATHER_REFRESH, &config_weather_refresh);
    read_config_uint16_t(CONFIG_WEATHER_EXPIRATION, &config_weather_expiration);
    read_config_uint16_t(CONFIG_WEATHER_REFRESH_FAILED, &config_weather_refresh_failed);
    read_config_uint8_t(CONFIG_COLOR_TOPBAR_BG, &config_color_topbar_bg);
    read_config_uint8_t(CONFIG_COLOR_INFO_BELOW, &config_color_info_below);
    read_config_uint8_t(CONFIG_COLOR_PROGRESS_BAR, &config_color_progress_bar);
    read_config_uint8_t(CONFIG_COLOR_PROGRESS_BAR2, &config_color_progress_bar2);
    read_config_uint8_t(CONFIG_COLOR_TIME, &config_color_time);
    read_config_uint8_t(CONFIG_COLOR_PERC, &config_color_perc);
    read_config_uint8_t(CONFIG_COLOR_BOTTOM_COMPLICATIONS, &config_color_bottom_complications);
    read_config_uint8_t(CONFIG_COLOR_BACKGROUND, &config_color_background);
    read_config_uint8_t(CONFIG_COLOR_TOP_COMPLICATIONS, &config_color_top_complications);
    read_config_uint8_t(CONFIG_COLOR_DAY, &config_color_day);
    read_config_uint8_t(CONFIG_COLOR_NIGHT, &config_color_night);
    read_config_uint8_t(CONFIG_COLOR_BAT_30, &config_color_bat_30);
    read_config_uint8_t(CONFIG_COLOR_BAT_20, &config_color_bat_20);
    read_config_uint8_t(CONFIG_COLOR_BAT_10, &config_color_bat_10);
    read_config_uint8_t(CONFIG_LOWBAT_COL, &config_lowbat_col);
    read_config_uint8_t(CONFIG_COMPLICATION_1, &config_complication_1);
    read_config_uint8_t(CONFIG_COMPLICATION_2, &config_complication_2);
    read_config_uint8_t(CONFIG_COMPLICATION_3, &config_complication_3);
    read_config_uint8_t(CONFIG_COMPLICATION_4, &config_complication_4);
    read_config_uint8_t(CONFIG_COMPLICATION_5, &config_complication_5);
    read_config_uint8_t(CONFIG_COMPLICATION_6, &config_complication_6);
    read_config_uint8_t(CONFIG_PROGRESS, &config_progress);
    read_config_string(CONFIG_TIME_FORMAT, config_time_format);
    read_config_string(CONFIG_INFO_BELOW, config_info_below);
    read_config_uint8_t(CONFIG_UPDATE_SECOND, &config_update_second);
    read_config_uint8_t(CONFIG_SHOW_DAYNIGHT, &config_show_daynight);
    read_config_uint16_t(CONFIG_STEP_GOAL, &config_step_goal);
// -- end autogen

    if (persist_exists(PERSIST_KEY_WEATHER) && persist_get_size(PERSIST_KEY_WEATHER) == sizeof(Weather)) {
        Weather tmp;
        persist_read_data(PERSIST_KEY_WEATHER, &tmp, sizeof(Weather));
        // make sure we are reading weather info that's consistent with the current version number
        if (tmp.version == REDSHIFT_WEATHER_VERSION) {
            weather = tmp;
        } else {
            weather.timestamp = 0;
        }
    } else {
        weather.timestamp = 0;
    }

    js_ready = false;
}

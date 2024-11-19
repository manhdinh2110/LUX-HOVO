#include <string.h>

#include "screens.h"
#include "images.h"
#include "fonts.h"
#include "actions.h"
#include "vars.h"
#include "styles.h"
#include "ui.h"

objects_t objects;
lv_obj_t *tick_value_change_obj;
uint8_t hour = 0;
uint8_t minute = 0;
uint8_t second = 0;
unsigned long previousMillis = 0;
const long interval = 1000;  // 1 second interval

void create_screen_main() {
    lv_obj_t *obj = lv_obj_create(0);
    objects.main = obj;
    lv_obj_set_pos(obj, 0, 0);
    lv_obj_set_size(obj, 800, 480);
    lv_obj_clear_flag(obj, LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_SNAPPABLE|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_CHAIN);
    lv_obj_set_style_bg_color(obj, lv_color_hex(0xff040000), LV_PART_MAIN | LV_STATE_DEFAULT);
    {
        lv_obj_t *parent_obj = obj;
        {
            lv_obj_t *obj = lv_img_create(parent_obj);
            lv_obj_set_pos(obj, 150, 207);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_img_set_src(obj, &img_logo_black);
            lv_obj_add_flag(obj, LV_OBJ_FLAG_ADV_HITTEST);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
            lv_obj_set_style_max_width(obj, 800, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_max_height(obj, 480, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
    }
}

void tick_screen_main() {
}

void create_screen_page_clock() {
    lv_obj_t *obj = lv_obj_create(0);
    objects.page_clock = obj;
    lv_obj_set_pos(obj, 0, 0);
    lv_obj_set_size(obj, 800, 480);
    lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_set_style_bg_color(obj, lv_color_hex(0xff0a0a0a), LV_PART_MAIN | LV_STATE_CHECKED);
    lv_obj_set_style_bg_color(obj, lv_color_hex(0xfffdf9f9), LV_PART_MAIN | LV_STATE_DEFAULT);
    {
        lv_obj_t *parent_obj = obj;
        {
            lv_obj_t *obj = lv_img_create(parent_obj);
            lv_obj_set_pos(obj, 280, 189);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_img_set_src(obj, &img_bg);
            lv_obj_add_flag(obj, LV_OBJ_FLAG_ADV_HITTEST);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            lv_obj_t *obj = lv_img_create(parent_obj);
            lv_obj_set_pos(obj, 397, 305);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_img_set_src(obj, &img_sec_dot);
            lv_obj_add_flag(obj, LV_OBJ_FLAG_ADV_HITTEST);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
            lv_obj_set_style_line_rounded(obj, false, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            // clock_hour
            lv_obj_t *obj = lv_img_create(parent_obj);
            objects.clock_hour = obj;
            lv_obj_set_pos(obj, 391, 232);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_img_set_src(obj, &img_clock_hour);
            lv_img_set_pivot(obj, 9.5, 76);
            lv_obj_add_flag(obj, LV_OBJ_FLAG_ADV_HITTEST);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
        }
        {
            // clock_min
            lv_obj_t *obj = lv_img_create(parent_obj);
            objects.clock_min = obj;
            lv_obj_set_pos(obj, 391, 203);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_img_set_src(obj, &img_clock_min);
            lv_img_set_pivot(obj, 9.5, 106.9);
            lv_obj_add_flag(obj, LV_OBJ_FLAG_ADV_HITTEST);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
        }
        {
            // clock_sec
            lv_obj_t *obj = lv_img_create(parent_obj);
            objects.clock_sec = obj;
            lv_obj_set_pos(obj, 395, 214);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_img_set_src(obj, &img_clock_sec);
            lv_img_set_pivot(obj, 5.5, 95.6);
            lv_obj_add_flag(obj, LV_OBJ_FLAG_ADV_HITTEST);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
        }
        {
            lv_obj_t *obj = lv_img_create(parent_obj);
            lv_obj_set_pos(obj, 225, 33);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_img_set_src(obj, &img_logo_red);
            lv_obj_add_flag(obj, LV_OBJ_FLAG_ADV_HITTEST);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
            lv_obj_set_style_max_width(obj, 800, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_max_height(obj, 480, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
    }
}

/*CLOCKING*/
void display_time(uint8_t hour, uint8_t min, uint8_t sec)
{
   //  struct tm timeinfo;

   //  if (!getLocalTime(&timeinfo))
   //  {
   //      USBSerial.println("Failed to obtain time");
   //      return;
   //  }
   //  else
   //  {
      //   int year = timeinfo.tm_year + 1900;
      //   int month = timeinfo.tm_mon + 1;
      //   int day = timeinfo.tm_mday;
      //   int hour = timeinfo.tm_hour;
      //   int min = timeinfo.tm_min;
      //   int sec = timeinfo.tm_sec;

        int sec_angle = 3600 * sec / 60;
        int min_angle = 3600 * min / 60 + 60 * sec / 60;
        int hour_angle = 3600 * (hour % 12) / 12 + 300 * min / 60;

        lv_img_set_angle(objects.clock_hour, hour_angle);
        lv_img_set_angle(objects.clock_min, min_angle);
        lv_img_set_angle(objects.clock_sec, sec_angle);
   // }
   loadScreen(SCREEN_ID_PAGE_CLOCK);
}

void tick_screen_page_clock() {
    unsigned long currentMillis = millis();
  
  // Check if it's time to update the clock (every second)
  if (currentMillis - previousMillis >= interval) {
   previousMillis = currentMillis;  // Save the last time update
   
   second++;  // Increment second
   
   if (second >= 60) {
      second = 0;
      minute++;  // Increment minute if seconds roll over
      
      if (minute >= 60) {
         minute = 0;
         hour++;  // Increment hour if minutes roll over
         
         if (hour >= 24) {
            hour = 0;  // Reset to 0 when hour reaches 24
         }
      }
   }
   
   // Call your function to display the updated time
   display_time(hour, minute, second);
  }
}


void create_screens() {
    lv_disp_t *dispp = lv_disp_get_default();
    lv_theme_t *theme = lv_theme_default_init(dispp, lv_palette_main(LV_PALETTE_BLUE), lv_palette_main(LV_PALETTE_RED), false, LV_FONT_DEFAULT);
    lv_disp_set_theme(dispp, theme);
    
    create_screen_main();
    create_screen_page_clock();
}

typedef void (*tick_screen_func_t)();

tick_screen_func_t tick_screen_funcs[] = {
    tick_screen_main,
    tick_screen_page_clock,
};

void tick_screen(int screen_index) {
    tick_screen_funcs[screen_index]();
}

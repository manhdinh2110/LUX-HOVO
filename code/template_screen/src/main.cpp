/*******************************************************************************
 * LVGL Hello World
 * This is a simple example for LVGL - Light and Versatile Graphics Library
 * import from: https://github.com/lvgl/lv_demos.git
 *
 * Dependent libraries:
 * LVGL: https://github.com/lvgl/lvgl.git
 *
 * LVGL Configuration file:
 * Copy your_arduino_path/libraries/lvgl/lv_conf_template.h
 * to your_arduino_path/libraries/lv_conf.h
 * Then find and set:
 * #define LV_COLOR_DEPTH     16
 * #define LV_TICK_CUSTOM     1
 * 
 * For SPI display set color swap can be faster, parallel screen don't set!
 * #define LV_COLOR_16_SWAP   1
 * 
 * Optional: Show CPU usage and FPS count
 * #define LV_USE_PERF_MONITOR 1
 ******************************************************************************/
#include <lvgl.h>
#include <ui.h>
#include <screens.h>
#include <images.h>
/*******************************************************************************
 * Start of Arduino_GFX setting
 *
 * Arduino_GFX try to find the settings depends on selected board in Arduino IDE
 * Or you can define the display dev kit not in the board list
 * Defalult pin list for non display dev kit:
 * Arduino Nano, Micro and more: CS:  9, DC:  8, RST:  7, BL:  6, SCK: 13, MOSI: 11, MISO: 12
 * ESP32 various dev board     : CS:  5, DC: 27, RST: 33, BL: 22, SCK: 18, MOSI: 23, MISO: nil
 * ESP32-C3 various dev board  : CS:  7, DC:  2, RST:  1, BL:  3, SCK:  4, MOSI:  6, MISO: nil
 * ESP32-S2 various dev board  : CS: 34, DC: 35, RST: 33, BL: 21, SCK: 36, MOSI: 35, MISO: nil
 * ESP32-S3 various dev board  : CS: 40, DC: 41, RST: 42, BL: 48, SCK: 36, MOSI: 35, MISO: nil
 * ESP8266 various dev board   : CS: 15, DC:  4, RST:  2, BL:  5, SCK: 14, MOSI: 13, MISO: 12
 * Raspberry Pi Pico dev board : CS: 17, DC: 27, RST: 26, BL: 28, SCK: 18, MOSI: 19, MISO: 16
 * RTL8720 BW16 old patch core : CS: 18, DC: 17, RST:  2, BL: 23, SCK: 19, MOSI: 21, MISO: 20
 * RTL8720_BW16 Official core  : CS:  9, DC:  8, RST:  6, BL:  3, SCK: 10, MOSI: 12, MISO: 11
 * RTL8722 dev board           : CS: 18, DC: 17, RST: 22, BL: 23, SCK: 13, MOSI: 11, MISO: 12
 * RTL8722_mini dev board      : CS: 12, DC: 14, RST: 15, BL: 13, SCK: 11, MOSI:  9, MISO: 10
 * Seeeduino XIAO dev board    : CS:  3, DC:  2, RST:  1, BL:  0, SCK:  8, MOSI: 10, MISO:  9
 * Teensy 4.1 dev board        : CS: 39, DC: 41, RST: 40, BL: 22, SCK: 13, MOSI: 11, MISO: 12
 ******************************************************************************/
#include <Arduino_GFX_Library.h>


#define ESP32_8048S070

#define TFT_BL 2

#include <Arduino_GFX_Library.h>
#define GFX_BL 2
Arduino_ESP32RGBPanel *rgbpanel = new Arduino_ESP32RGBPanel(
    41 /* DE */, 40 /* VSYNC */, 39 /* HSYNC */, 42 /* PCLK */,
    14 /* R0 */, 21 /* R1 */, 47 /* R2 */, 48 /* R3 */, 45 /* R4 */,
    9 /* G0 */, 46 /* G1 */, 3 /* G2 */, 8 /* G3 */, 16 /* G4 */, 1 /* G5 */,
    15 /* B0 */, 7 /* B1 */, 6 /* B2 */, 5 /* B3 */, 4 /* B4 */,
    0 /* hsync_polarity */, 180 /* hsync_front_porch */, 30 /* hsync_pulse_width */, 16 /* hsync_back_porch */,
    0 /* vsync_polarity */, 12 /* vsync_front_porch */, 13 /* vsync_pulse_width */, 10 /* vsync_back_porch */);
Arduino_RGB_Display *gfx = new Arduino_RGB_Display(
    800 /* width */, 480 /* height */, rgbpanel, 0 /* rotation */, true /* auto_flush */);
/*******************************************************************************
 * End of Arduino_GFX setting
 ******************************************************************************/

/* Change to your screen resolution */
static uint32_t screenWidth;
static uint32_t screenHeight;
static lv_disp_draw_buf_t draw_buf;
static lv_color_t *disp_draw_buf;
static lv_disp_drv_t disp_drv;
// uint8_t hour = 0;
// uint8_t minute = 0;
// uint8_t second = 0;
// unsigned long previousMillis = 0;
// const long interval = 1000;  // 1 second interval

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

/* Display flushing */
void my_disp_flush(lv_disp_drv_t *disp, const lv_area_t *area, lv_color_t *color_p)
{
   uint32_t w = (area->x2 - area->x1 + 1);
   uint32_t h = (area->y2 - area->y1 + 1);

#if (LV_COLOR_16_SWAP != 0)
   gfx->draw16bitBeRGBBitmap(area->x1, area->y1, (uint16_t *)&color_p->full, w, h);
#else
   gfx->draw16bitRGBBitmap(area->x1, area->y1, (uint16_t *)&color_p->full, w, h);
#endif

   lv_disp_flush_ready(disp);
}

void setup()
{
   // Init Display
   gfx->begin();
   // gfx->fillScreen(BLACK);
     
   pinMode(TFT_BL, OUTPUT);
   digitalWrite(TFT_BL, HIGH);

   lv_init();

   screenWidth = gfx->width();
   screenHeight = gfx->height();
#ifdef ESP32
   disp_draw_buf = (lv_color_t *)heap_caps_malloc(sizeof(lv_color_t) * screenWidth * 10, MALLOC_CAP_INTERNAL | MALLOC_CAP_8BIT);
#else
   disp_draw_buf = (lv_color_t *)malloc(sizeof(lv_color_t) * screenWidth * 10);
#endif
   if (!disp_draw_buf)
   {
      Serial.println("LVGL disp_draw_buf allocate failed!");
   }
   else
   {
      lv_disp_draw_buf_init(&draw_buf, disp_draw_buf, NULL, screenWidth * 10);

      /* Initialize the display */
      lv_disp_drv_init(&disp_drv);
      /* Change the following line to your display resolution */
      disp_drv.hor_res = screenWidth;
      disp_drv.ver_res = screenHeight;
      disp_drv.flush_cb = my_disp_flush;
      disp_drv.draw_buf = &draw_buf;
      lv_disp_drv_register(&disp_drv);

      /* Initialize the (dummy) input device driver */
      static lv_indev_drv_t indev_drv;
      lv_indev_drv_init(&indev_drv);
      indev_drv.type = LV_INDEV_TYPE_POINTER;
      lv_indev_drv_register(&indev_drv);

      // /* Create simple label */
      ui_init();
   }
}

void loop()
{
   lv_timer_handler(); /* let the GUI do its work */
   // ui_tick();
   tick_screen_page_clock();

//    unsigned long currentMillis = millis();
  
//   // Check if it's time to update the clock (every second)
//   if (currentMillis - previousMillis >= interval) {
//    previousMillis = currentMillis;  // Save the last time update
   
//    second++;  // Increment second
   
//    if (second >= 60) {
//       second = 0;
//       minute++;  // Increment minute if seconds roll over
      
//       if (minute >= 60) {
//          minute = 0;
//          hour++;  // Increment hour if minutes roll over
         
//          if (hour >= 24) {
//             hour = 0;  // Reset to 0 when hour reaches 24
//          }
//       }
//    }
   
//    // Call your function to display the updated time
//    display_time(hour, minute, second);
//   }
  delay(5);
}


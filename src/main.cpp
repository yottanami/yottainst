#include <lvgl.h>
#include <XPT2046_Touchscreen.h>
#include <SPI.h>

//#if LV_USE_TFT_ESPI
#include <TFT_eSPI.h>
//#endif


// XPT2046_Touchscreen
#define CS_PIN  5
#define TIRQ_PIN  4

#define TFT_HOR_RES   320
#define TFT_VER_RES   240


XPT2046_Touchscreen ts(CS_PIN, TIRQ_PIN);
TFT_eSPI tft = TFT_eSPI(TFT_HOR_RES, TFT_VER_RES); 

/*LVGL draw into this buffer, 1/10 screen size usually works well. The size is in bytes*/
#define DRAW_BUF_SIZE (TFT_HOR_RES * TFT_VER_RES / 10 * (LV_COLOR_DEPTH / 8))
uint32_t draw_buf[DRAW_BUF_SIZE / 4];


#include "main_menu.h"
#include "synthesizer.h"

#if LV_USE_LOG != 0
void print_logs( lv_log_level_t level, const char * buf )
{
    LV_UNUSED(level);
    Serial.println(buf);
    Serial.flush();
}
#endif

/* LVGL calls it when a rendered image needs to copied to the display*/
void my_disp_flush( lv_display_t *disp, const lv_area_t *area, uint8_t * px_map)
{
  uint32_t w = ( area->x2 - area->x1 + 1 );
  uint32_t h = ( area->y2 - area->y1 + 1 );

  tft.startWrite();
  tft.setAddrWindow(area->x1, area->y1, w, h);
  tft.pushColors((uint16_t *)px_map, w * h, true);
  tft.endWrite();

  lv_disp_flush_ready(disp);
}




void my_touchpad_read( lv_indev_t * indev, lv_indev_data_t * data ) 
{
  bool touched = ts.touched();
  TS_Point p = ts.getPoint();

  int x = map(p.y, 400, 3829, 1, TFT_VER_RES);
  int y = map(p.x, 540, 3756, 1, TFT_HOR_RES);
  if(!touched) {    
    data->state = LV_INDEV_STATE_RELEASED;
  } else {
    data->state = LV_INDEV_STATE_PRESSED;

    data->point.x = x;
    data->point.y = y;
  }
}

void setup()
{
    Serial.begin( 115200 );

    lv_init();
    tft.begin(); /* TFT init */
    tft.setRotation(3); /* Landscape orientation */
    ts.begin();
    //tft.setRotation(0);
    ts.setRotation(0);
    
    /* register print function for debugging */
    #if LV_USE_LOG != 0
       lv_log_register_print_cb( print_logs );
    #endif

    lv_display_t * disp;
    #if LV_USE_TFT_ESPI
      disp = lv_tft_espi_create(TFT_HOR_RES, TFT_VER_RES, draw_buf, sizeof(draw_buf));
    #else
      disp = lv_display_create(TFT_HOR_RES, TFT_VER_RES);
      lv_display_set_flush_cb(disp, my_disp_flush);
      lv_display_set_buffers(disp, draw_buf, NULL, sizeof(draw_buf), LV_DISPLAY_RENDER_MODE_PARTIAL);
    #endif

    /*Initialize the (dummy) input device driver*/
    lv_indev_t * indev = lv_indev_create();
    lv_indev_set_type(indev, LV_INDEV_TYPE_POINTER); /*Touchpad should have POINTER type*/
    lv_indev_set_read_cb(indev, my_touchpad_read);
 
    main_menu.render();
    		// lv_obj_t * btn = lv_btn_create(lv_scr_act());
		// lv_obj_add_event_cb(btn, btn_event_cb, LV_EVENT_PRESSED, NULL); 
		// lv_obj_align( btn, LV_ALIGN_CENTER, 0, 0 );
		// 			lv_obj_t * label;
		// label = lv_label_create(btn);
		// lv_label_set_text(label, "Hell Yeah");

    synthesizer.setup();
    Serial.println( "Setup done" );
}

void loop()
{
    lv_task_handler(); /* let the GUI do its work */
    lv_tick_inc(5); /* tell LVGL how much time has passed */
    usbMIDI.read();
    synthesizer.loop();
}

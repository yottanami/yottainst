/* void render_main_menu(){ */
/*     lv_obj_t * btn = lv_btn_create(lv_scr_act()); */
/*     lv_obj_add_event_cb(btn, btn_event_cb, LV_EVENT_PRESSED, NULL);  */
/*     lv_obj_align( btn, LV_ALIGN_CENTER, 0, 0 ); */
/*           lv_obj_t * label; */
/*     label = lv_label_create(btn); */
/*     lv_label_set_text(label, "Hell Yeah"); */
/* } */
# include "Arduino.h"
# include "main_menu.h"
#include <lvgl.h>


MainMenu::MainMenu(){
}


void MainMenu::eventHandler(lv_event_t * event){
  Serial.println("lv_event_get_target(event)");
}

void MainMenu::render(){
  lv_obj_t * btn = lv_btn_create(lv_scr_act());
  lv_obj_add_event_cb(btn, eventHandler, LV_EVENT_PRESSED, NULL);
  lv_obj_align( btn, LV_ALIGN_CENTER, 0, 0 );
  lv_obj_t * label;
  label = lv_label_create(btn);
  lv_label_set_text(label, "Hell Yeah");


    // lv_obj_t * menu = lv_menu_create(lv_scr_act());
    // lv_obj_set_size(menu, lv_disp_get_hor_res(NULL), lv_disp_get_ver_res(NULL));
    // lv_obj_center(menu);

    // lv_obj_t * cont;
    // lv_obj_t * label;

    // /*Create a sub page*/
    // lv_obj_t * sub_page = lv_menu_page_create(menu, NULL);
    // lv_menu_set_mode_root_back_button(sub_page, LV_MENU_ROOT_BACK_BUTTON_ENABLED);
    
    // cont = lv_menu_cont_create(sub_page);
    // label = lv_label_create(cont);
    // lv_label_set_text(label, "Synth Mode");

    // /*Create a main page*/
    // lv_obj_t * main_page = lv_menu_page_create(menu, NULL);
    // //lv_obj_add_event_cb(main_page, eventHandler, LV_EVENT_CLICKED, main_page);

    // cont = lv_menu_cont_create(main_page);
    // label = lv_label_create(cont);
    // lv_label_set_text(label, "Synth Mode");
    // //lv_menu_set_load_page_event(menu, cont, sub_page);

    // cont = lv_menu_cont_create(main_page);
    // label = lv_label_create(cont);
    // lv_label_set_text(label, "Sequencer Mode");

    // cont = lv_menu_cont_create(main_page);
    // label = lv_label_create(cont);
    // lv_label_set_text(label, "Sampler Mode");
    // lv_menu_set_load_page_event(menu, cont, sub_page);

    // lv_menu_set_page(menu, main_page);
     
}
  


MainMenu main_menu = MainMenu();

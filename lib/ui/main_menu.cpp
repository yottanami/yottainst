# include "Arduino.h"
# include "main_menu.h"
#include <lvgl.h>


MainMenu::MainMenu(){
}


void MainMenu::eventHandler(lv_event_t * event){
  Serial.println("lv_event_get_target(event)");

  // if event is  set mode to SEQ

  // if (
  //   globalMode = SEQ;
  // }else{
  //      globalMode = SYNTH;
  // }
}

void MainMenu::render(){
    /*Create a menu object*/
    lv_obj_t * menu = lv_menu_create(lv_scr_act());
    lv_obj_set_size(menu, lv_disp_get_hor_res(NULL), lv_disp_get_ver_res(NULL));
    lv_obj_center(menu);

    lv_obj_t * cont;
    lv_obj_t * label;


    lv_obj_t * synth_page = lv_menu_page_create(menu, NULL);

    cont = lv_menu_cont_create(synth_page);
    label = lv_label_create(cont);
    lv_label_set_text(label, "SYNTH PAGE");

    lv_obj_t * arpeggiator_page = lv_menu_page_create(menu, NULL);

    cont = lv_menu_cont_create(arpeggiator_page);
    label = lv_label_create(cont);
    lv_label_set_text(label, "ARPEGGIATOR PAGE");

    lv_obj_t * sequencer_page = lv_menu_page_create(menu, NULL);

    cont = lv_menu_cont_create(sequencer_page);
    label = lv_label_create(cont);
    lv_label_set_text(label, "SEQUENCER PAGE");
    

    /*Create a main page*/
    lv_obj_t * main_page = lv_menu_page_create(menu, NULL);

    cont = lv_menu_cont_create(main_page);
    label = lv_label_create(cont);
    lv_label_set_text(label, "SYNTHESIZER");
    lv_menu_set_load_page_event(menu, cont, synth_page);
    lv_obj_add_event_cb(cont, eventHandler, LV_EVENT_PRESSED, NULL);

    cont = lv_menu_cont_create(main_page);
    label = lv_label_create(cont);
    lv_label_set_text(label, "ARPEGGIATOR");
    lv_menu_set_load_page_event(menu, cont, arpeggiator_page);
    lv_obj_add_event_cb(cont, eventHandler, LV_EVENT_PRESSED, NULL);

    cont = lv_menu_cont_create(main_page);
    label = lv_label_create(cont);
    lv_label_set_text(label, "SEQUENCER");
    lv_menu_set_load_page_event(menu, cont, sequencer_page);
    lv_obj_add_event_cb(cont, eventHandler, LV_EVENT_PRESSED, NULL);

    lv_menu_set_page(menu, main_page);
     
}

MainMenu main_menu = MainMenu();

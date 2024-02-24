#ifndef MAIN_MENU_H
#define MAIN_MENU_H
#include <lvgl.h>

class MainMenu {
public:
  MainMenu();
  void render();
private:
  static void eventHandler(lv_event_t * event);
};

extern MainMenu main_menu;

#endif

#include "Views.h"

#include <unistd.h>

using namespace Views;

WINDOW * NCursesKeyboard::_window;

NCursesKeyboard::NCursesKeyboard (WINDOW * window) {
  onKeyPressed=nullptr;
  onArrowUp=nullptr;
  onArrowDown=nullptr;
  onArrowLeft=nullptr;
  onArrowRight=nullptr;
  onPageUp=nullptr;
  onPageDown=nullptr;
  _window = window;
  // Enable keyboard for first standart screen
  keypad(_window, true);
  noecho();
  nodelay(_window, true);
  timeout(0);
  set_escdelay(100);
};

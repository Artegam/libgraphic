#include "InputDevices.h"

#include <unistd.h>

using namespace InputDevices;

WINDOW * NCursesKeyboard::_window;
unsigned char NCursesKeyboard::_key;

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

unsigned char NCursesKeyboard::listenChar () {
  return wgetch(_window);
}

unsigned char NCursesKeyboard::listen () {
  _key = 0x00;
  _key = listenChar();
  execute();
  return _key;
}

void NCursesKeyboard::setEvent (unsigned char key, void (*fct)()) {
  _events[key] = fct;
};

void NCursesKeyboard::execute () {
  if(onKeyPressed != nullptr) onKeyPressed(_key);
  if(_events[_key] != nullptr) _events[_key]();
}

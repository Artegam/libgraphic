#ifndef INPUTDEVICES_H
#define INPUTDEVICES_H

#include <ncurses.h>
#include <map>

// Keyboard keys
const int KEYB_ARROW_DOWN  = 2;
const int KEYB_ARROW_UP    = 3;
const int KEYB_ARROW_LEFT  = 4;
const int KEYB_ARROW_RIGHT = 5;
const int KEYB_ENTER       = 10;
const int KEYB_CR          = 13;
const int KEYB_SPACE       = 32;
const int KEYB_ESCAPE      = 27;
const int KEYB_PAGEDOWN    = 82;
const int KEYB_PAGEUP      = 83;

namespace InputDevices {
  typedef void (*fctptr)();
  class Device {};
  class Keyboard : public Device {};
  class NCursesKeyboard : public Keyboard {
    private:
      static WINDOW * _window;
      static unsigned char _key;

      void (*onKeyPressed)(unsigned char key);
      void (*onArrowUp)();
      void (*onArrowDown)();
      void (*onArrowLeft)();
      void (*onArrowRight)();
      void (*onPageUp)();
      void (*onPageDown)();
      std::map<int, fctptr> _events;
    public:
      NCursesKeyboard (WINDOW * window);
      static unsigned char listenChar ();
      unsigned char listen ();
      void execute ();
      void setOnKeyPressed (void (*fct)(unsigned char key)) {onKeyPressed = fct;};
      void setEvent (unsigned char key, void (*fct)());
      unsigned char key() {return _key;};
  };
};
#endif


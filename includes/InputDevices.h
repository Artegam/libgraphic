#ifndef INPUTDEVICES_H
#define INPUTDEVICES_H

#include <ncurses.h>

// Keyboard keys
const int KEYB_DOWN     = 2;
const int KEYB_UP       = 3;
const int KEYB_LEFT     = 4;
const int KEYB_RIGHT    = 5;
const int KEYB_ENTER    = 10;
const int KEYB_CR       = 13;
const int KEYB_SPACE    = 32;
const int KEYB_ESCAPE   = 27;
const int KEYB_PAGEDOWN = 82;
const int KEYB_PAGEUP   = 83;

namespace InputDevices {
  class Device {};
  class Keyboard : public Device {};
  class NCursesKeyboard : public Keyboard {
    private:
      static WINDOW * _window;
      static unsigned char _key;

      void (*onKeyPressed)(unsigned char key);
      void (*onPageUp)();
      void (*onPageDown)();
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


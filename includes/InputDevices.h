#ifndef INPUTDEVICES_H
#define INPUTDEVICES_H

#include <ncurses.h>

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


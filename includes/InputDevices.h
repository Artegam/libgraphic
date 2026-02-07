#ifndef INPUTDEVICES_H
#define INPUTDEVICES_H

#include <ncurses.h>

namespace InputDevices {

  class Device {};
  class Keyboard : public Device {};
  class NCursesKeyboard : public Keyboard {
    private:
      WINDOW * _window;
      unsigned char _key;

      void (*onKeyPressed)(unsigned char key);
    public:
      NCursesKeyboard (WINDOW * window);
      unsigned char listen ();
      void execute ();
      void setOnKeyPressed (void (*fct)(unsigned char key)) {onKeyPressed = fct;};
      unsigned char key() {return _key;};
  };
};
#endif


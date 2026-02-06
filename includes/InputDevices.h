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
      static bool _running;
      static unsigned int _interval;

      void (*onKeyPressed)();
    public:
      NCursesKeyboard (WINDOW * window);
      void start ();
      void stop ();
      static void listen ();

      //void onKeyPressed ();
  };
  WINDOW * NCursesKeyboard::_window;
  unsigned char NCursesKeyboard::_key;
  bool NCursesKeyboard::_running;
  unsigned int NCursesKeyboard::_interval;

};

#endif


#ifndef INPUTDEVICES_H
#define INPUTDEVICES_H

#include <map>

#include "Events.h"

// Standart Keyboard keys TODO: Put this data in a configuration file
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
  class Keyboard : public Device {
    protected:
      void (*onKeyPressed)(unsigned char key);
      void (*onArrowUp)();
      void (*onArrowDown)();
      void (*onArrowLeft)();
      void (*onArrowRight)();
      void (*onPageUp)();
      void (*onPageDown)();
      std::map<unsigned char, int> keymap;
      std::map<int, fctptr> _events;
      unsigned char _key;
    public:
      void execute (events::BaseEvent * object = nullptr) {
        if(onKeyPressed != nullptr) onKeyPressed(_key);
        if(_events[keymap[_key]] != nullptr) _events[keymap[_key]]();
        if(object != nullptr)
          switch(keymap[_key]) {
            case events::VALIDATE:
              object->onValidate();
              break;
          }
      };
      void setOnKeyPressed (void (*fct)(unsigned char key)) {onKeyPressed = fct;};
      void setEvent (const unsigned int event, void (*fct)()) {_events[event] = fct;};
      void setKey (const unsigned int event, const unsigned char key) {keymap[key] = event;};
      void setKeymap (const std::map<unsigned char, int> customKeymap) {keymap = customKeymap;};
      unsigned char key() {return _key;};
  };
};
#endif


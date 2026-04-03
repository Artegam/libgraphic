#ifndef EVENTS_H
#define EVENTS_H


namespace events {

  // Events codes
  const unsigned int VALIDATE = 1;
  const unsigned int PAGEUP   = 2;
  const unsigned int PAGEDOWN = 3;

  class BaseEvent {
    public:
      void (*onValidate)();
  };
}

#endif


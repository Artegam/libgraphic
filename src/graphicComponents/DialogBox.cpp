#include "GraphicComponents.h"

using namespace GraphicComponents;

DialogBox::DialogBox (const int window, const int x, const int y, const unsigned int height, const unsigned int width, const string label, string message, unsigned int buttons, const string name) : Screen (window, x, y, label, name) {
  _height = height;
  _width = width;
  setColor(DIALOG_COLOR);

  // Bi buttons
  if(buttons == OK)
    _ok = new Button(window, (width/2), (height-2), "OK", "OK");
  else if(buttons == OK_CANCEL) {
    _ok = new Button(window, (width/3), (height-2), "OK", "OK");
    _cancel = new Button(window, 2*(width/3), (height-2), "Cancel", "CANCEL");
    add(_cancel);
  }
    add(_ok);
  //this->select(0);

  if(message.size() > 0) {
    Text * _t = new Text(window, 4, 3, message, "Message");
    _t->setColor(DIALOG_COLOR);
    this->add(_t);
  }
}

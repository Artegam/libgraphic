#include "GraphicComponents.h"

using namespace GraphicComponents;

DialogBox::DialogBox (const int window, const int x, const int y, const unsigned int height, const unsigned int width, const string label, string message, unsigned int buttons, const string name) : Screen (window, x, y, label, name) {
  _height = height;
  _width = width;

  // Bi buttons
  if(buttons == OK)
    add(new Button(window, x+(width/2), y+(height-2), "OK", "OK"));
  else if(buttons == OK_CANCEL) {
    add(new Button(window, x+(width/3), y+(height-2), "OK", "OK"));
    add(new Button(window, x+2*(width/3), y+(height-2), "Cancel", "CANCEL"));
  }
  //this->select(0);

  if(message.size() > 0) {
    Text * _t = new Text(window, x+4, y+3, message, "Message");
    _t->setColor(DIALOG_COLOR);
    this->add(_t);
  }
}

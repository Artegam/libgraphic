#include "GraphicComponents.h"

using namespace GraphicComponents;

DialogBox::DialogBox (const int window, const int x, const int y, const unsigned int height, const unsigned int width, const string label, string message, const string name) : Screen (window, x, y, label, name) {
  _height = height;
  _width = width;

  //this->add(new Button(window, (width/2), (height-2), "OK", "OK")); //mono button
  // Bi buttons
  this->add(new Button(window, (width/3), (height-2), "OK", "OK"));
  this->add(new Button(window, 2*(width/3), (height-2), "Cancel", "CANCEL"));
  //this->select(0);

  if(message.size() > 0)
    this->add(new Text(window, 4, 3, message));

}

#include "GraphicComponents.h"

using namespace GraphicComponents;


ComplexHMenu::ComplexHMenu (const int window, const int x, const int y, list<string> items, const string name) : HMenu (window, x, y, items, name) {
  _height = 1;
  _width = _maxWidth;
  _message = new Text(window, 0, 0, "", "title");
  _message->align(Text::RIGHT);
  setColor(HMENU_COLOR);
  _message->setColor(HMENU_COLOR);
}

ComplexHMenu::ComplexHMenu (const int window, const int x, const int y, list<Text *> items, const string name) : HMenu (window, x, y, items, name) {
  _height = 1;
  _width = _maxWidth;
  _message = new Text(window, 0, 0, "", "title");
  _message->align(Text::RIGHT);
  setColor(HMENU_COLOR);
  _message->setColor(HMENU_COLOR);
}

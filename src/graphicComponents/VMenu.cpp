#include "GraphicComponents.h"

using namespace GraphicComponents;


VMenu::VMenu (const int window, const int x, const int y, list<string> items, const string name) : Menu (window, x, y, items, name) {
  _width = 0;
  for(list<string>::iterator it = items.begin(); it != items.end(); it++)
    if(_width < (int)it->size())
      _width = it->size();
}

VMenu::VMenu (const int window, const int x, const int y, list<Text *> items, const string name) : Menu (window, x, y, items, name) {
}

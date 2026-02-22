#include "GraphicComponents.h"

using namespace GraphicComponents;


HMenu::HMenu (const int window, const int x, const int y, list<string> items, const string name) : Menu (window, x, y, items, name) {
  _height = 1;
  _width = 666;
}

HMenu::HMenu (const int window, const int x, const int y, list<Text *> items, const string name) : Menu (window, x, y, items, name) {
  _height = 1;
  _width = 666;
}

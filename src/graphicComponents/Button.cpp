#include "GraphicComponents.h"

using namespace GraphicComponents;


Button::Button (const int window, const int x, const int y, const string label, const string name, Composite* parent) : GraphicComponent(window, x, y, name, parent) {
  _label = label;
  _height = 3;
  _width = label.size() + 2;
  _selectable = true;
}

const string Button::label() {
  return _label;
}

#include "GraphicComponents.h"

using namespace GraphicComponents;


Text::Text (const int window, const int x, const int y, const string label, const string name): GraphicComponent(window, x, y, name) {
  _label = label;
}

void Text::setLabel (const string label) {
  _label=label;
}

const string Text::label() {
  return _label;
}

#include "GraphicComponents.h"

using namespace GraphicComponents;


Leaf::Leaf(const int window, const int x, const int y, const string name): GraphicComponent(window, x, y, name) {
}

void Leaf::select() {
  if(_selectable)
    _selected = true;
}

void Leaf::select(const int idComponent) {
}

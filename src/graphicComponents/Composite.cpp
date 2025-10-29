#include "GraphicComponents.h"

using namespace GraphicComponents;

Composite::Composite () {
}

Composite::Composite (const int window, const int x, const int y, const string name) : GraphicComponent(window, x, y, name) {
}

void Composite::add (GraphicComponent * gc) {
  _components.push_back(gc);
  if(gc->getSelectSize() > 0)
    _selectSize = gc->getSelectSize();
}

void Composite::add (list<GraphicComponent *> lst) {
  _components.insert(_components.end(), lst.begin(), lst.end());
}

void Composite::addBeginning (GraphicComponent * gc) {
  _components.insert(_components.begin(), gc);
}

void Composite::removeBeginning () {
  _components.pop_front();
}

void Composite::replace(unsigned int index, unsigned int size, list<GraphicComponent *> lst) {
  list<GraphicComponent *>::iterator start = _components.begin();
  list<GraphicComponent *>::iterator end = _components.begin();
  advance(start, index);
  advance(end, index+size); //[ASC] il y a peut etre un -1 a mettre
  _components.erase(start, end);
  _components.insert(_components.begin(), lst.begin(), lst.end());
}

list<GraphicComponent *> Composite::components() {
  return _components;
}

void Composite::select(const int index) {
  GraphicComponent::select(index);
}

void Composite::resize(const int height, const int width) {
  GraphicComponent::resize(height, width);
}


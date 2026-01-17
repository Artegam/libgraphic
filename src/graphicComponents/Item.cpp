#include "GraphicComponents.h"

using namespace GraphicComponents;

Item::Item (string name) : Atom (name) {
  fct = [] (Item * i) {
    i->select();
  };
}

Item::Item (Node * parent, string name) : Atom (parent, name) {
  fct = [] (Item * i) {
    i->select();
  };
}

void Item::select () {
  _selected = !_selected;
}

bool Item::isSelected () {
  return _selected;
}

string Item::getName () {
  return Atom::getName();
}

bool Item::validate () {
  fct(this);
  return true;
}

void Item::clear () {
  _selected = false;
}

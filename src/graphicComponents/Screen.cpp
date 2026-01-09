#include "GraphicComponents.h"

using namespace GraphicComponents;


Screen::Screen () : GraphicComposite () {
}

Screen::Screen (const int window, const int x, const int y, const string label, const string name) : GraphicComposite(window, x, y, name) {
  _label = label;
}

void Screen::select(const int index) {
  GraphicComposite::select(index);

  list<GraphicComponent *> lst;
  lst = _components;

  for(list<GraphicComponent *>::iterator it = lst.begin(); it != lst.cend(); it++) {
    if (Menu * menu = dynamic_cast<Menu*>(*it); menu != nullptr)
      menu->select(index);
  }
}

void Screen::selectNext () {
  list<GraphicComponent *> lst;

  for(list<GraphicComponent *>::iterator it = _components.begin(); it != _components.end(); it++) {
    if((*it)->isSelectable())
      lst.push_front((*it));
  }

  if(!lst.empty()) {
    list<GraphicComponent *>::iterator it = lst.begin();
    advance(it, _selectedIndex);
    (*it)->unselect();
    it++;
    if(it == lst.end())
      it = lst.begin();
    (*it)->select();
  }
}

string Screen::label() {
  return _label;
}

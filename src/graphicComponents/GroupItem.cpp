#include "GraphicComponents.h"

using namespace GraphicComponents;

GroupItem::GroupItem (string name) : Node (name) {
}

GroupItem::GroupItem (Node * parent, string name) : Node (parent, name) {
}

void GroupItem::setDefault (const int index) {
  unsigned int idx = 0;
  if(index > 0 && _children.size() >= (const unsigned int)index) {
    idx = index;
    _defaultItem = idx;
    _selectedItem = idx;
    this->display();
  }
}

void GroupItem::selectItem (const int index) {
  list<Item *> lst = castList<Item *>(getChildren());
  list<Item *>::iterator it = lst.begin();

  for(it = lst.begin(); it != lst.end(); it++)
    if((*it) != nullptr)
      (*it)->clear();

  if((long unsigned int)index < lst.size()) {
    it = lst.begin();
    advance(it, index);
    _selectedItem = index;
    (*it)->validate();
  }
}

Item * GroupItem::getSelectedItem () {
  list<Item *> lst = castList<Item *>(getChildren());
  list<Item *>::iterator it = lst.begin();
  advance(it, _selectedItem);
  return (*it);
}

void GroupItem::display () {
  Item * item = getSelectedItem();
  if(item != nullptr) item->select();
}

const int GroupItem::size() {
  return _children.size();
}

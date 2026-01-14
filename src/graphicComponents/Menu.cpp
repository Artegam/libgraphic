#include "GraphicComponents.h"

using namespace GraphicComponents;


Menu::Menu (const int window, const int x, const int y, list<string> items, const string name) : GraphicComposite(window, x, y, name) {
  list<string>::iterator it;
  unsigned int pos = y;

  _items.clear();
  for(it = items.begin(); it != items.end(); it++) {
    Text * t = new Text(window, x, pos, (*it), (*it));
    _items.push_back(t);
    pos++;
  }
  _selectSize = _items.size();
}

Menu::Menu (const int window, const int x, const int y, list<Text *> items, const string name) : GraphicComposite(window, x, y, name) {
  _items = items;
  list<Text *>::iterator it;

  for(it = items.begin(); it != items.end(); it++) {
    if (GroupItem* grp = dynamic_cast<GroupItem*>(*it); grp != nullptr) {
      _selectSize += grp->size();
    } else {
      _selectSize++;
    }
  }
}

list<string> Menu::items() {
  list<string> stringItems;
  for(list<Text*>::iterator it = _items.begin(); it != _items.end(); it++)
    stringItems.push_back((*it)->label());
  return stringItems;
}

void Menu::select (const int index) {
  _selectedIndex = index;
  for(list<Text *>::iterator it = _items.begin();it != _items.end(); it++) {
    //TODO: A corriger car il va faire pour tout les groupes
    if (GroupItem* grp = dynamic_cast<GroupItem*>(*it); grp != nullptr) {
      grp->selectItem(index);
    }
  }
}

map<char, int> Menu::shortcuts() {
  map<char, int> shortcuts;
  list<string> itemsList = items();
  unsigned int i = 0;

  for(list<string>::iterator it = itemsList.begin(); it!=itemsList.end(); it++) {
    string::iterator it_str = (*it).begin();
    shortcuts[std::tolower(*it_str)] = i;
    i++;
  }

  return shortcuts;
}

Text * Menu::validation(int cursor) {
 list<Text*>::iterator it = _items.begin();
 advance(it, cursor);
 return (*it);
}

Text * Menu::itemSelected () {
  if(_selectedIndex < 0)
    _selectedIndex = 0;
  else
    _selectedIndex = _selectedIndex%_items.size();

  list<Text *>::iterator it = _items.begin();
  advance(it, _selectedIndex);
  return *it;
}

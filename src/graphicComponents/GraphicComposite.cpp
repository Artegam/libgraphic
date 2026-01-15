#include "GraphicComponents.h"
#include <iostream>
using namespace std;

using namespace GraphicComponents;

GraphicComposite::GraphicComposite () {
}

GraphicComposite::GraphicComposite(const int window, const int x, const int y, const string name) {
  this->_window = window;
  this->_x = x;
  this->_y = y;
  _selectSize = 0;
  _name = name;
}

Component* GraphicComposite::selectedComponent () {
  if(_children.size() > 0) {
    list<Component*>::iterator i = _children.begin();
    advance(i, _selectedIndex);
    return *i;
  }
  return nullptr;
}

void GraphicComposite::select (const int index) {
  _selectSize = _components.size();
  cout << "taille max confirmée : " << _selectSize << endl;
  cout << "la selection : " << index << endl;
  this->unselectAll();
  if (index < 0)
    _selectedIndex = 0;
  else
    _selectedIndex = index;
  Component* c = selectedComponent();
  GraphicComposite * gc = nullptr;
  GraphicLeaf * gl = nullptr;

  if(c != nullptr) {
    if (gc = dynamic_cast<GraphicComposite*>(c); gc != nullptr) {
      //gc->select(); //TODO: A Ameliorer ici. Pourquoi ne pas pouvoir selectionner un graphic composite ?
    } else if (gl = dynamic_cast<GraphicLeaf*>(c); gl != nullptr) {
      gl->select();
    }
  }
}

const int GraphicComposite::selected () {
  if(_selectedIndex == 0)
    for(list<GraphicComponent*>::iterator i = _components.begin(); i!=_components.end(); i++) {
      if((*i)->isSelected()) {
        _selectedIndex = distance(_components.begin(), i);
        break;
      }
    }
  return _selectedIndex;
}

const int GraphicComposite::getComponentsCount() {
  return _children.size();
}

/*
void GraphicComposite::resize(const int height, const int width) {
  _height = height;
  _width = width;
}

void GraphicComposite::setSelectSize (const int size) {
  _selectSize = size;
}

const int GraphicComposite::getSelectSize() {
  return _selectSize;
}

void GraphicComposite::select () {
  _selected = true;
}

void GraphicComposite::unselect () {
  _selected = false;
}

void GraphicComposite::unselectAll () {
  _selectedIndex = 0;
  for(list<GraphicComposite*>::iterator i = _components.begin(); i!=_components.end(); i++)
    (*i)->unselect();
}

const int GraphicComposite::selected () {
  if(_selectedIndex == 0)
    for(list<GraphicComposite*>::iterator i = _components.begin(); i!=_components.end(); i++) {
      if((*i)->isSelected()) {
        _selectedIndex = distance(_components.begin(), i);
        break;
      }
    }

  return _selectedIndex;
}

const bool GraphicComposite::isValidated () {
  return _validated;
}

const bool GraphicComposite::isSelectable () {return _selectable;}
const bool GraphicComposite::isSelected () {return _selected;}

const int GraphicComposite::id() {
  if(_parent)
    return _parent->getPosition(this);
  return -1;
}

const int GraphicComposite::window() {
  return _window;
}

const int GraphicComposite::x() {
  return _x;
}

const int GraphicComposite::y() {
  return _y;
}

const unsigned int GraphicComposite::width() {
  return _width;
}

const unsigned int GraphicComposite::height() {
  return _height;
}

const basic GraphicComposite::getBasic() {
  basic b;
  b.x = _x;
  b.y = _y;
  b.width = _width;
  b.height = _height;
  return b;
}

cursor GraphicComposite::getCursor () {
  return _cursor;
}

const string GraphicComposite::getName() {
  return _name;
}
*/

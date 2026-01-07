#include "GraphicComponents.h"
#include <iostream>
using namespace std;

using namespace GraphicComponents;

GraphicComponent::GraphicComponent () {
}

GraphicComponent::GraphicComponent(const int window, const int x, const int y, const string name, Composite* parent) {
  this->_window = window;
  this->_x = x;
  this->_y = y;
  _selectSize = 0;
  _name = name;
  _parent = parent;
}

void GraphicComponent::resize(const int height, const int width) {
  _height = height;
  _width = width;
}

void GraphicComponent::setSelectSize (const int size) {
  _selectSize = size;
}

const int GraphicComponent::getComponentsCount() {
  return _components.size();
}

const int GraphicComponent::getSelectSize() {
  return _selectSize;
}

void GraphicComponent::select () {
  _selected = true;
}

void GraphicComponent::select (const int index) {
  cout << "taille max confirmée : " << _selectSize << endl;
  cout << "la selection : " << index << endl;
  this->unselectAll();
  if (index < 0)
    _selectedIndex = 0;
  else if(index > _selectSize)
    _selectedIndex = _selectSize;
  else
    _selectedIndex = index;
  GraphicComponent* gc = selectedComponent();
  if(gc != nullptr) gc->select();
}

void GraphicComponent::unselect () {
  _selected = false;
}

void GraphicComponent::unselectAll () {
  _selectedIndex = 0;
  for(list<GraphicComponent*>::iterator i = _components.begin(); i!=_components.end(); i++)
    (*i)->unselect();
}

const int GraphicComponent::selected () {
  if(_selectedIndex == 0)
    for(list<GraphicComponent*>::iterator i = _components.begin(); i!=_components.end(); i++) {
      if((*i)->isSelected()) {
        _selectedIndex = distance(_components.begin(), i);
        break;
      }
    }

  return _selectedIndex;
}

GraphicComponent* GraphicComponent::selectedComponent () {
  if(_components.size() > 0) {
    list<GraphicComponent*>::iterator i = _components.begin();
    advance(i, _selectedIndex);
    return *i;
  }
  return nullptr;
}

const bool GraphicComponent::isValidated () {
  return _validated;
}

const bool GraphicComponent::isSelectable () {return _selectable;}
const bool GraphicComponent::isSelected () {return _selected;}

const int GraphicComponent::id() {
  if(_parent)
    return _parent->getPosition(this);
  return -1;
}

const int GraphicComponent::window() {
  return _window;
}

const int GraphicComponent::x() {
  return _x;
}

const int GraphicComponent::y() {
  return _y;
}

const unsigned int GraphicComponent::width() {
  return _width;
}

const unsigned int GraphicComponent::height() {
  return _height;
}

const basic GraphicComponent::getBasic() {
  basic b;
  b.x = _x;
  b.y = _y;
  b.width = _width;
  b.height = _height;
  return b;
}

cursor GraphicComponent::getCursor () {
  return _cursor;
}

const string GraphicComponent::getName() {
  return _name;
}

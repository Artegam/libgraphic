#include "GraphicComponents.h"

using namespace GraphicComponents;

ScrollBar::ScrollBar(const int window, const int x, const int y, const string name) : Leaf(window, x, y, name) {
  _height = 12;
  _width = 1;
}

void ScrollBar::down() {
  if(_cursor+_unit <= _max)
    _cursor += _unit;
  else
    _cursor = _max;
}

void ScrollBar::up() {
  if(_cursor-_unit > 1)
    _cursor -= _unit;
  else
    _cursor = 0;
}

void ScrollBar::update(const unsigned int n) {
  if(n < 0)
    _cursor = 0;
  else if (n*_unit > _max)
    _cursor = _max;
  else
    _cursor=(_unit*n);
}

ScrollBarData ScrollBar::getScrollBar() {
  ScrollBarData data;
  data.unit = _unit;
  data.cursor = _cursor;
  data.max = _max; 
  return data;
}

void ScrollBar::resize(const int height, const int width) {
  GraphicComponent::resize(height, width);
  _max = height-2;
  _unit = 1.0;
}

void ScrollBar::resize(const int height, const int width, const unsigned int count) {
  resize(height, width);
  if(count == 0) //[ASC] protection
    _unit = (double)_max;
  else {
    _unit = ((double)1/_max);
    //if((float)(_max % count)/count > 0.5)
    //  _unit++;
  }
}

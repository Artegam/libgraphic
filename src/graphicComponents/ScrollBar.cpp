#include "GraphicComponents.h"

using namespace GraphicComponents;

ScrollBar::ScrollBar(const int window, const int x, const int y, const string name) : Leaf(window, x, y, name) {
  _height = 12;
  _width = 1;
}

void ScrollBar::down() {
  if(_cpt < _cpt_max)
    _cpt++;
  _cursor=_cpt/_unit;
}

void ScrollBar::up() {
  if(_cpt > 1)
    _cpt--;
  _cursor=_cpt/_unit;
}

void ScrollBar::update(const unsigned int n) {
  if(n < 0)             // Borne inferieure
    _cpt=0;
  else if(n > _cpt_max) // Borne superieure
    _cpt=_cpt_max;
  else                  // Interval
    _cpt=n;
  _cursor=_cpt/_unit;
}

ScrollBarData ScrollBar::getScrollBar() {
  ScrollBarData data;
  data.unit = _unit;
  data.cursor = _cursor;
  data.max = _max; 
  data.cpt = _cpt;
  data.cpt_max =_cpt_max;
  return data;
}

void ScrollBar::resize(const int height, const int width) {
  GraphicComponent::resize(height, width);
  _max = height-2;
  _unit = 1.0;
}

void ScrollBar::resize(const int height, const int width, const unsigned int count) {
  _cpt_max = count;
  resize(height, width);
  if(count == 0) //[ASC] protection
    _cpt_max = _max;
  _unit = ((double)_cpt_max/_max);
}

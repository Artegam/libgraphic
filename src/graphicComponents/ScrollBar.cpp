#include "GraphicComponents.h"

using namespace GraphicComponents;

ScrollBar::ScrollBar(const int window, const int x, const int y, const string name) : Leaf(window, x, y, name) {
  _height = 12;
  _width = 1;
}

void ScrollBar::down() {
  if(data.cursor<=data.max) {
   if(data.cursor+data.unit > data.max)
     data.cursor=data.max;
   else
     data.cursor+=data.unit;
  }
}

void ScrollBar::up() {
  if(data.cursor>1) {
    if(data.cursor-data.unit <= 0)
      data.cursor = 1;
    else
      data.cursor-=data.unit;
  }
}

void ScrollBar::update(const unsigned int n) {
  if(data.cursor>1 && (data.unit*n) > data.max)
    data.cursor=data.max;
  else
    data.cursor=(data.unit*n);
}

ScrollBarData ScrollBar::getScrollBar() {
  return data;
}

void ScrollBar::resize(const int height, const int width) {
  GraphicComponent::resize(height, width);
  data.max = height-2;
  data.unit = 1;
}

void ScrollBar::resize(const int height, const int width, const unsigned int count) {
  resize(height, width);
  if(count == 0) //[ASC] protection
    data.unit = data.max;
  else {
    data.unit = data.max / count;
    if((float)(data.max % count)/count > 0.5)
      data.unit++;
  }
}

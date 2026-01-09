#include "GraphicComponents.h"
#include <iostream>
using namespace std;

using namespace GraphicComponents;

GraphicLeaf::GraphicLeaf () {
}

GraphicLeaf::GraphicLeaf(const int window, const int x, const int y, const string name) {
  this->_window = window;
  this->_x = x;
  this->_y = y;
  _selectSize = 0;
  _name = name;
}


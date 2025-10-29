#include "GraphicComponents.h"

using namespace GraphicComponents;

Input::Input (const int window, const int x, const int y, const unsigned int height, const unsigned int width, const string label, const string name): Text(window, x, y, label, name) {
  _width = width;
  _height = height;
  _cursor_x = x;
  _cursor_y = y;
  _selectable = true;
}

const string Input::value() {
  return _buffer;
}

pair<int, int> Input::cursor () {
  pair<int, int> p;
  p.first = _cursor_x;
  p.second = _cursor_y;
  return p;
}

void Input::setch (char c) {
  if(c == 0x7F) //del
    _buffer=_buffer.substr(0,_buffer.length()-1);
  else
    _buffer+=c;
}

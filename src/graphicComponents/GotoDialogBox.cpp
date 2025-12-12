#include "GraphicComponents.h"
#include <stdexcept>

using namespace GraphicComponents;

GotoDialogBox::GotoDialogBox (const int window, const int x, const int y, const unsigned int height, const unsigned int width, const string label) : DialogBox (window, x, y, height, width, label, "", OK_CANCEL, "GOTO") {
  this->unselectAll();
  Input * in = new Input(window, 2, 3, 1, 5, "Numero de la page: ");
  in->select();
  this->add(in);
  _in = in;
}

unsigned int GotoDialogBox::to () {
  try {
    return stoi(_in->value());
  } catch (const std::invalid_argument& ia) {
    return 0;
  }
}

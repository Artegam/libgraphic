#include "GraphicComponents.h"

using namespace GraphicComponents;

OpenDialogBox::OpenDialogBox (const int window, const int x, const int y, const unsigned int height, const unsigned int width, const string label, const string name) : DialogBox (window, x, y, height, width, label, "", OK_CANCEL, name) {
  Input * in = new Input(window, 2, 3, 1, 25, "Nom de fichier: ");
  in->select();
  this->unselectAll();
  this->add(in);
}

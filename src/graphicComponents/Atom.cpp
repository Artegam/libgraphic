#include "GraphicComponents.h"

using namespace GraphicComponents;

Atom::Atom (string name) {_name=name;_parent = this;}
Atom::Atom (Atom * parent, string name) : Atom (name){_parent=parent;}

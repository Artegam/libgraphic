#include "Composite.h"

// [ASC] Design pattern Composite
void Component::execute () {};
void Leaf::execute () {};
void Composite::add (Component c) {children.push_back(c);};
void Composite::remove (Component c) {
  for(list<Component>::iterator it = children.begin(); it != children.end(); it++)
    if(&(*it) == &c)
      children.erase(it);
};
list<Component> Composite::getChildren () {return children;};
void Composite::execute () {};
// [ASC] Fin du design pattern


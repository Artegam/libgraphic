#include "Composite.h"

// [ASC] Design pattern Composite
void Component::execute () {};
int Component::eval () {return _result;};
void Leaf::execute () {};
void Composite::add (Component* c) {children.push_back(c);};
void Composite::clear () {children.clear();}
void Composite::remove () {remove(*children.begin());}
void Composite::remove (Component* c) {
  for(list<Component*>::iterator it = children.begin(); it != children.end(); it++)
    if((*it) == c)
      children.erase(it);
};
list<Component*> Composite::getChildren () {return children;};
void Composite::execute () {};
int Composite::eval () {return -1;};
int Composite::getPosition (Component* c) {
  int cpt = 0;
  for(list<Component*>::iterator it = children.begin(); it != children.end(); it++) {
    if((*it) == c)
      return cpt;
    cpt++;
  }
  return -1;
};
// [ASC] Fin du design pattern


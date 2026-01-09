#include "Composite.h"

// [ASC] Design pattern Composite
void Component::execute () {};
int Component::eval () {return _result;};
void Leaf::execute () {};
void Composite::add (Component* c) {_children.push_back(c);};
void Composite::clear () {_children.clear();}
void Composite::remove () {if(_children.size()>0) remove(_children.back());}
void Composite::remove (Component* c) {_children.remove(c);};
list<Component*> Composite::getChildren () {return _children;};
void Composite::execute () {};
int Composite::eval () {return -1;};
int Composite::getPosition (Component* c) {
  int cpt = 0;
  for(list<Component*>::iterator it = _children.begin(); it != _children.end(); it++) {
    if((*it) == c)
      return cpt;
    cpt++;
  }
  return -1;
};
// [ASC] Fin du design pattern


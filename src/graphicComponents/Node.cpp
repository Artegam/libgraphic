#include "GraphicComponents.h"

using namespace GraphicComponents;


Node::Node (string name) : Atom(name) {
  _parent = this;
}

Node::Node (Node * parent, string name) : Atom(parent, name){
}

void Node::erase (unsigned int position) {
  list<Component *>::iterator it = _children.begin();
  advance(it, position);
  _children.erase(it);
}

list<Atom *> Node::getChildren () {
  return castList<Atom *>(_children);
}

Atom * Node::getParent () {
  return _parent;
}

Atom * Node::getNode(string name) {
  list<Atom *> lst = getChildren();
  for(list<Atom *>::iterator it = lst.begin(); it != lst.end(); it++) {
    if((*it) != nullptr && (*it)->getName() == name)
      return (*it);
  }
  return nullptr;
}

Atom * Node::getNode(const unsigned int position) {
  list<Atom *> lst = getChildren();
  list<Atom *>::iterator it = lst.begin();
  advance(it, position);
  return *it;
}

const unsigned int Node::getRank (string name) {
  list<Atom *> lst = getChildren();
  unsigned int rank = 0;
  for(list<Atom *>::iterator it = lst.begin(); it != lst.end(); it++) {
    if((*it)->getName() == name)
      return rank;
    rank++;
  }
  return rank;
}

// Calcule un offset a partir de la longueur des noms des nodes
const unsigned int Node::getNameOffset (string name) {
  list<Atom *> lst = getChildren();
  unsigned int len = 1;
  for(list<Atom *>::iterator it = lst.begin(); it != lst.end(); it++) {
    if((*it)->getName() == name)
      return len;
    len+=(*it)->getName().size()+2;
  }
  return len;
}

bool Node::validate () {
  try {
    //fct();
    return false;
  } catch (std::bad_function_call& e) {
    // Needs to put the logger here !!!
    //std::cout << "ERROR: Bad function call\n";
  }
}

void Node::attach(GraphicComponent * comp) {
  gc = comp;
}

void Node::detach() {
  gc = NULL;
}

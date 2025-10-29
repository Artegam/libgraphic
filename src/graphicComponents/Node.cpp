#include "GraphicComponents.h"

using namespace GraphicComponents;


Node::Node (string name) {
  _name = name;
  _parent = this;
}

Node::Node (Node * parent, string name) {
  _name = name;
  _parent = parent;
}

void Node::add (Node * node) {
  this->children.push_back(node);
}

void Node::add (string name) {
  Node * node = new Node(this, name);
  this->children.push_back(node);
}

void Node::addItem (string name) {
  Item * item = new Item(this, name);
  this->children.push_back(item);
}

void Node::addGroup (string name) {
  GroupItem * group = new GroupItem(this, name);
  this->children.push_back(group);
}

void Node::erase (unsigned int position) {
  list<Node *>::iterator it = this->children.begin();
  advance(it, position);
  this->children.erase(it);
}

list<Node *> Node::getChildren () {
  return this->children;
}

string Node::getName () {
  return _name;
}

Node * Node::getParent () {
  return _parent;
}

Node * Node::getNode(string name) {
  list<Node *>::iterator it;
  for(it = children.begin(); it != children.end(); it++) {
    if((*it)->getName() == name)
      return (*it);
  }

  return NULL;
}

Node * Node::getNode(const unsigned int position) {
  list<Node *>::iterator it = children.begin();
  advance(it, position);
  return *it;
}

const unsigned int Node::getRank (string name) {
  list<Node *>::iterator it;
  unsigned int rank = 0;
  for(it = children.begin(); it != children.end(); it++) {
    if((*it)->getName() == name)
      return rank;
    rank++;
  }
  return rank;
}

// Calcule un offset a partir de la longueur des noms des nodes
const unsigned int Node::getNameOffset (string name) {
  list<Node *>::iterator it;
  unsigned int len = 1;
  for(it = children.begin(); it != children.end(); it++) {
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

void Node::clear () {
}

void Node::attach(GraphicComponent * comp) {
  gc = comp;
}

void Node::detach() {
  gc = NULL;
}

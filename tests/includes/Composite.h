#ifndef COMPOSITE_H
#define COMPOSITE_H

#include <list>

using namespace std;

// [ASC] Design pattern Composite
class Component { // Interface
  public:
    void execute ();
};

class Leaf : Component {
  public:
    void execute ();
};

class Composite : Component {
  private:
    list <Component> children;
  public:
    void add (Component c);
    void remove (Component c);
    list<Component> getChildren ();
    void execute ();
};
// [ASC] Fin du design pattern

#endif

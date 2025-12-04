#ifndef COMPOSITE_H
#define COMPOSITE_H

#include <list>

using namespace std;

// [ASC] Design pattern Composite
class Component { // Interface
  protected:
    int _result = -1;
  public:
    virtual ~Component() {}
    void execute ();
    int eval ();
};

class Leaf : public virtual Component {
  public:
    void execute ();
};

class Composite : public virtual Component {
  protected:
    list <Component*> children;
  public:
    void add (Component* c);
    void remove (Component* c);
    list<Component*> getChildren ();
    void execute ();
    virtual int eval ();
};
// [ASC] Fin du design pattern

#endif

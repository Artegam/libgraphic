#ifndef GRAPHICCOMPONENTS_H
#define GRAPHICCOMPONENTS_H

#include <string>
#include <list>
#include <map>
#include <functional>

#include "Composite.h"

using namespace std;

namespace GraphicComponents {

  struct basic {
    unsigned int x;
    unsigned int y;
    unsigned int width;
    unsigned int height;
  };

  struct tab {
    unsigned int rows;
    unsigned int cols;
    unsigned int colmaxsize = 0;
    unsigned int rowmaxsize = 0;
    list<unsigned int> colssizes;
    list<unsigned int> rowssizes;
  };

  struct cursor {
    unsigned int row = 0;
    unsigned int col = 0;
  };

  class Utils {
    public:
      const unsigned int occurences(const string str, char c);
  };

  class GraphicComponent {
    protected:
      int _x;
      int _y;
      int _height;
      int _width;
      int _id = -1;
      string _name;
      bool _validated = false;
      bool _selectable = false;
      bool _selected = false;
      int _window;
      int _selectedIndex = 0;
      int _selectSize;
      list<GraphicComponent *> _components;
      cursor _cursor;

    public:
      GraphicComponent();
      GraphicComponent(const int window, const int x, const int y, const string name = "default graphic component");
      virtual void select ();
      virtual void unselect ();
      virtual void unselectAll();
      const bool isValidated ();
      const bool isSelectable ();
      const bool isSelected ();
      void setSelectSize(const int size);
      void setId (const int n);
      const int getSelectSize();
      virtual void resize(const int height, const int width);
      const int id();
      const int window();
      const int x();
      const int y();
      const unsigned int height ();
      const unsigned int width ();
      const basic getBasic();
      cursor getCursor ();
      const string getName();
  };

  class GraphicLeaf : public GraphicComponent, public virtual Leaf {
    public:
      GraphicLeaf();
      GraphicLeaf(const int window, const int x, const int y, const string name = "default graphic leaf");
  };

  class GraphicComposite : public GraphicComponent, public virtual Composite {
    private:
    public:
      GraphicComposite();
      GraphicComposite(const int window, const int x, const int y, const string name = "default graphic composite");
      Component * selectedComponent ();
      virtual void select (const int idComponent);
      virtual const int selected ();
      const int getComponentsCount();
      void add (GraphicComposite* gc) {gc->setId(_children.size());Composite::add(gc);};
      void add (GraphicLeaf* gl) {gl->setId(_children.size());Composite::add(gl);};
  };

  class Screen : public GraphicComposite {
    private:
      string _label;
    public:
      int backgroundColor = 0;
      int textColor = 7;

      Screen ();
      Screen (const int window, const int x, const int y, const string label, const string name = "default screen");
      void selectNext ();
      void select (const int index);
      void remove () {Composite::remove ();};
      void remove (Component* c) {Composite::remove (c);};
      string label ();
      list<Component *> getGraphicComponents () {
        list<Component *> lst;
        for(list<Component*>::iterator it = _children.begin(); it != _children.end(); it++)
          lst.push_back(*it);
        return lst;
      };
  };

  class Text : public virtual GraphicLeaf {
    private:
      string _label;
    public:
      Text (const int window, const int x, const int y, const string label, const string name = "default text");
      void setLabel (const string label);
      const string label ();
  };

  class Input : public Text {
    private:
      string _buffer;
      unsigned int _cursor_x = 0;
      unsigned int _cursor_y = 0;
    public:
      Input (const int window, const int x, const int y, const unsigned int height, const unsigned int width, const string label, const string name = "default input");
      const string value();
      pair<int, int> cursor ();
      void setch (char c);
//[ASC] faire une fonction pour attendre la saisie clavier ??
  };

  class Selector : public Text {
    public:
      Selector (const int window, const int x, const int y, const string label, const string name = "default selector");
  };

  class DialogBox : public Screen {
    private:
    public:
      static const unsigned int OK        = 0;
      static const unsigned int OK_CANCEL = 1;
      DialogBox (const int window, const int x, const int y, const unsigned int height, const unsigned int width, const string label, string message = "", unsigned int buttons = OK, const string name = "default dialogbox");
  };

  class OpenDialogBox : public DialogBox {
    public:
      OpenDialogBox (const int window, const int x, const int y, const unsigned int height, const unsigned int width, const string label, const string name = "default opendialogbox");
  };

  class GotoDialogBox : public DialogBox {
    private:
      Input * _in = NULL;
    public:
      GotoDialogBox (const int window, const int x, const int y, const unsigned int height, const unsigned int width, const string label);
      unsigned int to();
  };

  class Menu : public virtual GraphicComposite {
    private:
      list<Text *> _items;
    public:
      Menu (const int window, const int x, const int y, list<string> items, const string name = "default menu");
      Menu (const int window, const int x, const int y, list<Text *> items, const string name = "default menu");
      list<string> items ();
      void select (const int index);
      map<char, int> shortcuts ();
      Text * validation (int cursor = 0);
      Text * itemSelected ();
  };

  class HMenu : public Menu {
    private:
    public:
      HMenu (const int window, const int x, const int y, list<string> items, const string name = "default hmenu");
      HMenu (const int window, const int x, const int y, list<Text *> items, const string name = "default hmenu");
  };

  class VMenu : public Menu {
    private:
    public:
      VMenu (const int window, const int x, const int y, list<string> items, const string name = "default vmenu");
      VMenu (const int window, const int x, const int y, list<Text *> items, const string name = "default vmenu");
  };

  class Button : public virtual GraphicLeaf {
    private:
      string _label;
    public:
      Button (const int window, const int x, const int y, const string label, const string name = "default button");
      const string label();
  };

  class Image : public virtual GraphicLeaf {
    private:
  };

  class Cell : public virtual GraphicLeaf {
    private:
      string _value;
      bool _select = false;
    public:
      Cell (const int window, const int x, const int y, const string value, const string name = "default cell");
      void setWidth (const unsigned int w);
      void setHeight (const unsigned int h);
      const string value ();
      void setValue (const string value);
      void select ();
      bool isSelected();
  };

  class Table : public virtual GraphicLeaf {
    private:
      tab _t;
      list<Cell*> cells;
    public:
      Table (const int window, const int x, const int y, const unsigned int rows, const unsigned int cols, string defaultval = "-", const string name = "default table");
      list<Cell*> getCells ();
      list<Cell*> getRow (unsigned int n);
      Cell getCell (const unsigned int pos);
      Cell * getCell (unsigned int row, unsigned int col);
      const tab getTab ();
      void setValue (unsigned int row, unsigned int col, string value);
      void setValue (unsigned int row, unsigned int col, const char * value);
      void updateLengths ();
      void select (unsigned int row, unsigned int col);
      void setCursor(unsigned int row, unsigned int col);
  };

  class ScrollBarData {
    public:
      double unit = 1.0;
      unsigned int cursor = 1;
      unsigned int max = 10;
      unsigned int cpt_max = 100;
      unsigned int cpt = 0;
  };

  class ScrollBar : public virtual GraphicLeaf {
    private:
      double _unit = 1.0;
      unsigned int _cursor = 1;
      unsigned int _max = 10;
      unsigned int _cpt_max = 100;
      unsigned int _cpt = 0;
    public:
      ScrollBar(const int window, const int x, const int y, const string name = "default scrollbar");
      void down();
      void up();
      void update(const unsigned int n = 0);
      ScrollBarData getScrollBar();
      void resize(const int height, const int width);
      void resize(const int height, const int width, const unsigned int count);
  };

  class Calendar : public virtual GraphicLeaf {
    private:
      Table * _daily;
      Selector * _month;
      Selector * _year;
    public:
      Calendar (const int window, const int x, const int y, const string name = "default calendar");
      Selector getMonth ();
      Selector getYear ();
      Table getDaily ();
  };

  class Agenda : public virtual GraphicLeaf {
    private:
      Table * _hourly;
      Selector * _day = nullptr;
      Selector * _month = nullptr;
      Selector * _year = nullptr;
      Text * _name;
    public:
      Agenda (const int window, const int x, const int y, const string name = "default agenda");
      Selector getDay ();
      Selector getMonth ();
      Selector getYear ();
      Table getHourly ();
      Text getName ();
  };

  class Atom {
    protected:
      string _name;
      Atom * _parent;
    public:
      Atom (string name);
      Atom (Atom * parent, string name);
      virtual string getName () {return _name;};
      virtual void clear () {};
  };

  class Node: public Atom, public virtual Composite {
    private:
      GraphicComponent * gc = NULL;

    protected:

    public:
      template <typename R, typename C>
      R cast(C c) {return dynamic_cast<R>(c);};
      template <typename R, typename C>
      list<R> castList(list<C> l) {
        list<R> lst;
        for(typename list<C>::iterator it = l.begin(); it != l.end(); it++)
          lst.push_back(cast<R>(*it));
        return lst;
      };

      Node (string name);
      Node (Node * parent, string name);
      template <typename C>
      void add (C c) {_children.push_back(c);};
      void erase (unsigned int position);
      list<Atom *> getChildren ();
      Node * getParent ();
      Node * getNode(string name);
      Node * getNode(const unsigned int position);
      const unsigned int getRank (string name);
      const unsigned int getNameOffset (string name);
      virtual bool validate ();
      virtual void clear () {};
      void attach(GraphicComponent * comp);
      void detach();
  };

  class Item : public Atom, public virtual Leaf { //[ASC] A reflexionner ici pas possible heritage diamant
    private:
      bool _selected = false;
      std::function<void(Item *)> fct;

    public:
      Item (string name);
      Item (Node * parent, string name);
      void select ();
      bool isSelected ();
      string getName ();
      bool validate ();
      void clear ();
  };

  class GroupItem : public Node {
    private:
      unsigned int _defaultItem;
      unsigned int _selectedItem;

    public:
      GroupItem (string name);
      GroupItem (Node * parent, string name);
      void setDefault (const int index);
      Item * getSelectedItem ();
      void display ();
      void selectItem (const int index);
      const int size();
  };

  class GraphicParser {
    public:
      GraphicComponent * to_graphicComponent(Component * c) {
        if (GraphicComposite * gc = dynamic_cast<GraphicComposite*>(c); gc != nullptr)
          return (GraphicComponent*)gc;
        else if (GraphicLeaf * gl = dynamic_cast<GraphicLeaf*>(c); gl != nullptr)
          return (GraphicComponent*)gl;
        else
          return nullptr;
      };
      GraphicComposite * to_graphicComposite(Component * c) {
        GraphicComposite * gc = dynamic_cast<GraphicComposite*>(c);
        return gc;
      };
      list<GraphicComponent *> to_graphicComponentList(list<Component *> l) {
        list<GraphicComponent *> lst;
        for(list<Component*>::iterator it = l.begin(); it != l.end(); it++)
          lst.push_back(to_graphicComponent(*it));
        return lst;
      };
      template <typename R, typename C>
      list<R*> castList(list<C*> l) {
        list<R*> lst;
        for(typename list<C*>::iterator it = l.begin(); it != l.end(); it++)
          lst.push_back(dynamic_cast<R*>(*it));
        return lst;
      };

  };

};

#endif

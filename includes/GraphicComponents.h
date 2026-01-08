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

  class GraphicComponent : public virtual Component {
    protected:
      int _x;
      int _y;
      int _height;
      int _width;
      int _id;
      string _name;
      bool _validated = false;
      bool _selectable = false;
      bool _selected = false;
      int _window;
      int _selectedIndex = 0;
      int _selectSize;
      list<GraphicComponent *> _components;
      cursor _cursor;
      Composite * _parent;

    public:
      GraphicComponent();
      GraphicComponent(const int window, const int x, const int y, const string name = "default", Composite* parent = nullptr);
      virtual void select ();
      virtual void select (const int idComponent);
      virtual void unselect ();
      virtual void unselectAll();
      virtual const int selected ();
      GraphicComponent * selectedComponent ();
      const bool isValidated ();
      const bool isSelectable ();
      const bool isSelected ();
      void setSelectSize(const int size);
      const int getSelectSize();
      const int getComponentsCount();
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

  class Screen : public GraphicComponent, public virtual Composite {
    private:
      string _label;
    public:
      int backgroundColor = 0;
      int textColor = 7;

      Screen ();
      Screen (const int window, const int x, const int y, const string label, const string name = "default screen");
      void selectNext ();
      void select (const int index);
      string label ();
      GraphicComponent * selectedComponent () {return GraphicComponent::selectedComponent();};
      list<GraphicComponent *> getGraphicComponents () {
        list<GraphicComponent *> lst;
        for(list<Component*>::iterator it = children.begin(); it != children.end(); it++)
          if (GraphicComponent * component = dynamic_cast<GraphicComponent*>(*it); component != nullptr)
            lst.push_back(component);
        return lst;
      };
  };

  class Text : public GraphicComponent, public virtual Leaf {
    private:
      string _label;
    public:
      Text (const int window, const int x, const int y, const string label, const string name = "default text", Composite* parent = nullptr);
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

  class Menu : public GraphicComponent, public virtual Leaf {
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

  class Button : public GraphicComponent, public virtual Leaf {
    private:
      string _label;
    public:
      Button (const int window, const int x, const int y, const string label, const string name = "default button", Composite* parent = nullptr);
      const string label();
  };

  class Image : public GraphicComponent, public virtual Leaf {
    private:
  };

  class Cell : public GraphicComponent, public virtual Leaf {
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

  class Table : public GraphicComponent, public virtual Leaf {
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

  class ScrollBar : public GraphicComponent, public virtual Leaf {
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

  class Calendar : public GraphicComponent, public virtual Leaf {
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

  class Agenda : public GraphicComponent, public virtual Leaf {
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

  class Node {
    private:
      string _name;
      Node * _parent;
      GraphicComponent * gc = NULL;

    protected:
      list<Node *> children;
    public:
      Node (string name);
      Node (Node * parent, string name);
      void add (Node * node);
      void add (string name);
      void addItem (string name);
      void addGroup (string name);
      void erase (unsigned int position);
      list<Node *> getChildren ();
      virtual string getName ();
      Node * getParent ();
      Node * getNode(string name);
      Node * getNode(const unsigned int position);
      const unsigned int getRank (string name);
      const unsigned int getNameOffset (string name);
      virtual bool validate ();
      virtual void clear ();
      void attach(GraphicComponent * comp);
      void detach();
  };

  class Item : public Node {
    private:
      bool selected = false;
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
      unsigned int defaultItem;
      unsigned int selectedItem;

    public:
      GroupItem (string name);
      GroupItem (Node * parent, string name);
      void setDefault (const int index);
      Item * getSelectedItem ();
      void display ();
      void selectItem (const int index);
      const int size();
  };

};

#endif

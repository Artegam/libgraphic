#include <tests/LibGraphicTestManager.h>

//GraphicComponentTests
void GraphicComponentTests::execute () {
  const int MAIN = 0;
  GraphicComponents::GraphicComponent * gc = new GraphicComponents::GraphicComponent();
  GraphicComponents::GraphicComponent * gc2 = new GraphicComponents::GraphicComponent(MAIN, 0, 0);
  GraphicComponents::GraphicComponent * gc3 = new GraphicComponents::GraphicComponent(MAIN, 0, 0, "my graphic component");
  assert(gc != nullptr, "Graphic Component (0 argument)");
  assert(gc2 != nullptr, "Graphic Component constructor (3 arguments)");
  assert(gc3 != nullptr, "Graphic Component constructor (4 arguments)");

  //test void methods with no arguments first
  gc->select();
  gc->unselect();
  gc->unselectAll();

  //test void methods with arguments
  gc->setSelectSize(10);
  gc->resize(20, 30);

  //test return values methods with no arguments
  assert(gc->isValidated(), false, "gc is validated");
  assert(gc->isSelectable(), false, "gc is selectable");
  assert(gc->isSelected(), false, "gc is selected");
  assert(gc->getSelectSize(), 10, "gc select size is 10");
  assert(gc->id(), -1, "gc id is -1 by default");
  assert(gc->window(), 0, "gc window is 0");
  assert(gc->x(), 0, "gc x position is 0");
  assert(gc->y(), 0, "gc y position is 0");
  assert(gc->height(), (unsigned int) 20, "gc height is 20");
  assert(gc->width(), (unsigned int)30, "gc width is 30");
  assert(gc->getName().c_str(), "default", "gc name is 'default'");
  assert(gc3->getName().c_str(), "my graphic component", "gc3 name is 'my graphic component'");

  //test returned objects
  GraphicComponents::basic b = gc->getBasic();
  GraphicComponents::cursor c = gc->getCursor();
  assert(b.x, (unsigned int)0, "gc basic x is 0");
  assert(b.y, (unsigned int)0, "gc basic y is 0");
  assert(b.height, (unsigned int)20, "gc basic height is 20");
  assert(b.width, (unsigned int)30, "gc basic width is 30");
  assert(c.row, (unsigned int)0, "gc cursor row is 0");
  assert(c.col, (unsigned int)0, "gc cursor col is 0");
}

void GraphicCompositeTests::execute () {
  const int MAIN = 0;
  GraphicComponents::GraphicComposite * gc = new GraphicComponents::GraphicComposite();
  GraphicComponents::GraphicComposite * gc2 = new GraphicComponents::GraphicComposite(MAIN, 0, 0);
  GraphicComponents::GraphicComposite * gc3 = new GraphicComponents::GraphicComposite(MAIN, 0, 0, "my graphic component");
  assert(gc != nullptr, "Graphic Component (0 argument)");
  assert(gc2 != nullptr, "Graphic Component constructor (3 arguments)");
  assert(gc3 != nullptr, "Graphic Component constructor (4 arguments)");

  GraphicComponents::Text * t2 = new GraphicComponents::Text(MAIN, 0, 0, "text2");

  gc3->add(new GraphicComponents::Text(MAIN, 0, 0, "text1"));
  gc3->add(t2);
  gc3->add(new GraphicComponents::Text(MAIN, 0, 0, "text3"));
  assert(gc3->getComponentsCount(), 3, "gc components count is 3");

  gc3->select(2);
  assert(gc3->selected(), 2, "The select component is 2");
  Component* c = gc3->selectedComponent();
  assert(c != nullptr, "The selected component is not nullptr");
  assert(c, (Component*)t2, "The selected component is t2");
}

//ScreenTests
void ScreenTests::execute () {
  try {
    const int MAIN = 0;
    GraphicComponents::Screen * scr = new GraphicComponents::Screen(MAIN, 0, 0, "Screen label");
    assert(scr != nullptr, "Screen constructor (4 arguments)");
    GraphicComponents::Screen * scr2 = new GraphicComponents::Screen(MAIN, 0, 0, "Screen label", "my screen name");
    assert(scr2 != nullptr, "Screen constructor (4 arguments)");

    //test void methods with no arguments first
    scr->selectNext();

    // void methods with arguments
    scr->select(0);
    scr->remove();
    // SEGFAULT use case
    scr->add(new GraphicComponents::DialogBox(MAIN, 20, 10, 8, 45, "titre", "message"));
    scr->remove();

    // Assert methods with return statement
    assert(scr->label() == "Screen label", "Label is 'Screen label'");
    GraphicComponents::GraphicParser p;
    list<GraphicComponents::GraphicComponent *> lst = p.to_graphicComponentList(scr->getGraphicComponents());
    assert(lst.size() == 0, "Number of graphic components is 0");
  } catch (int errorNum) {
    string message = string(__FILE__)+":"+to_string(__LINE__)+" ERROR number " + to_string(errorNum);
    assert(false, message.c_str());
  }
}

void TextTests::execute () {
  const int MAIN = 0;
  // test constructors
  GraphicComponents::Text * t = new GraphicComponents::Text(MAIN, 0, 0, "my text");
  GraphicComponents::Text * t1 = new GraphicComponents::Text(MAIN, 0, 0, "my text", "thing text");
  assert(t != nullptr, "Text constructor (4 arguments)");
  assert(t1 != nullptr, "Text constructor (5 arguments)");

  //test void return methods
  t->setLabel("new label");

  //test returned values methods
  assert(t->label().c_str(), "new label", "t with 'new label' label");
}

void InputTests::execute () {
  const int MAIN = 0;

  GraphicComponents::Input * in = new GraphicComponents::Input(MAIN, 0, 0, 20, 30, "Saisie: ");
  GraphicComponents::Input * in1 = new GraphicComponents::Input(MAIN, 0, 0, 20, 30, "Saisie: ", "mon input");
  assert(in != nullptr, "Input constructor (6 arguments)");
  assert(in1 != nullptr, "Input constructor (7 arguments)");

  //tests void returned methods
  in->setch('a');

  //tests valued returned methids
  assert(in->value().c_str(), "a", "in has 'a' value");
  pair<int, int> c = in->cursor();
  assert(c.first, 0, "in cursor first");
  assert(c.second, 0, "in cursor second");
}

//Selector
void SelectorTests::execute () {
  const int MAIN = 0;

  GraphicComponents::Selector * sel = new GraphicComponents::Selector(MAIN, 0, 0, "Selector0");
  GraphicComponents::Selector * sel1 = new GraphicComponents::Selector(MAIN, 0, 0, "Selector0", "my selector");
  assert(sel != nullptr, "Selector constructor (4 args)");
  assert(sel1 != nullptr, "Selector constructor (5 args)");
}

//Scrollbar
void ScrollbarTests::execute () {
  GraphicComponents::ScrollBar b(0, 8, 5); //screen, position
  GraphicComponents::ScrollBarData data = b.getScrollBar(); // recupere les donnees
  assert(data.unit == 1.0, "Valeur par defaut de unit");
  assert(data.cursor == 1, "Valeur par defaut de cursor");
  assert(data.max == 10, "Valeur par defaut de max");
  b.resize(12, 1, 100); // hauteur, largeur, nombre de blocks
  b.update(5); // aller au block numero 5
  data = b.getScrollBar(); // recupere les donnees
  assert(data.max == 10, "Calcul de la valeur max");
  assert(data.unit == ((double)100/10.0), "Calcul de la valeur d'une unite pour 100 blocks");
  b.resize(16, 1, 1760); // hauteur, largeur, nombre de blocks
  data = b.getScrollBar(); // recupere les donnees
  assert(data.unit == ((double)1760/14.0), "Calcul de la valeur d'une unite pour 1760 blocks");
  b.update(10);
  data = b.getScrollBar(); // recupere les donnees
  assert(data.cpt == 10, "Verifie le cpt apres mise a jour");
  assert(data.cursor == (unsigned int)(10/data.unit), "Verifie le cuseur apres mise a jour");
  b.update(1512);
  data = b.getScrollBar(); // recupere les donnees
  assert(data.cursor == (unsigned int)(1512/data.unit), "Verifie le cuseur apres mise a jour 2");
  assert(b.x() == 8, "Verifie la position x");
  assert(b.y() == 5, "Verifie la position y");
  assert(b.y()+data.cursor == 17, "Verifie la position du curseur de la barre");
}

//Dialogbox
void DialogboxTests::execute () {
  const int MAIN = 0;
  string titre = "DialogboxTitre";
  string message = "DialogboxMessage";

  //tests constants
  assert(GraphicComponents::DialogBox::OK, (unsigned int)0, "OK constant");
  assert(GraphicComponents::DialogBox::OK_CANCEL, (unsigned int)1, "OK_CANCEL constant");
  //tests constructors
  GraphicComponents::DialogBox * d = new GraphicComponents::DialogBox(MAIN, 0, 0, 20, 30, "test");
  GraphicComponents::DialogBox * d1 = new GraphicComponents::DialogBox(MAIN, 0, 0, 20, 30, "test", "my dialogbox message");
  GraphicComponents::DialogBox * d2 = new GraphicComponents::DialogBox(MAIN, 0, 0, 20, 30, "test", "my dialogbox message", GraphicComponents::DialogBox::OK_CANCEL);
  GraphicComponents::DialogBox * d3 = new GraphicComponents::DialogBox(MAIN, 0, 0, 20, 30, "test", "my dialogbox message", GraphicComponents::DialogBox::OK_CANCEL, "my dialogbox");
  assert(d != nullptr, "DialogBox constructor (6 args)");
  assert(d1 != nullptr, "DialogBox constructor (7 args)");
  assert(d2 != nullptr, "DialogBox constructor (8 args)");
  assert(d3 != nullptr, "DialogBox constructor (9 args)");

  GraphicComponents::DialogBox diag(MAIN, 20, 10, 8, 45, titre, message);
  GraphicComponents::GraphicParser p;
  list<GraphicComponents::GraphicComponent *> lst = p.to_graphicComponentList(diag.getGraphicComponents());
  assert((int)lst.size(), 2, "Verifie le nb de composants graphiques");
  list<GraphicComponents::GraphicComponent *>::iterator it = lst.begin();
  GraphicComponents::Button* b = dynamic_cast<GraphicComponents::Button*>(*it);
  assert(b != nullptr, "First object is not nullptr Button component");
  assert(b->id(), 0, "First object id is 0");
  assert(b->label().c_str(), "OK", "First object is OK Button");
  assert(b->x(), 22, "OK Button X position");
  assert(b->y(), 6, "OK Button Y position");
  it++;
  GraphicComponents::Text* gc = dynamic_cast<GraphicComponents::Text*>(*it);
  assert(gc != nullptr, "Second object is Text component");
  assert(gc->id(), 1, "Second object id is 1");

  GraphicComponents::DialogBox diag2(MAIN, 20, 10, 10, 66, titre, message, GraphicComponents::DialogBox::OK_CANCEL);
  lst = p.to_graphicComponentList(diag2.getGraphicComponents());
  assert((int)lst.size(), 3, "(2 boutons) Verifie le nb de composants graphiques");
  it = lst.begin();
  b = dynamic_cast<GraphicComponents::Button*>(*it);
  assert(b != nullptr, "(2 boutons) First object is Button component");
  assert(b->id(), 0, "(2 boutons) First object id is 0");
  assert(b->label().c_str(), "OK", "(2 boutons) First object is OK Button");
  assert(b->x(), 22, "(2 boutons) OK Button X position");
  assert(b->y(), 8, "(2 boutons) OK Button Y position");
  it++;

  b = dynamic_cast<GraphicComponents::Button*>(*it);
  assert(b != nullptr, "(2 boutons) Second object is Button component");
  assert(b->id(), 1, "(2 boutons) Second object id is 1");
  assert(b->label().c_str(), "Cancel", "(2 boutons) Second object is Cancel Button");
  assert(b->x(), 44, "(2 boutons) Cancel Button X position");
  assert(b->y(), 8, "(2 boutons) Cancel Button Y position");
  it++;

  gc = dynamic_cast<GraphicComponents::Text*>(*it);
  assert(gc != nullptr, "(2 boutons) Third object is Text component");
  assert(gc->id(), 2, "(2 boutons) Third object id is 2");
}

void OpenDialogboxTests::execute () {
  const int MAIN = 0;
  GraphicComponents::OpenDialogBox * open = new GraphicComponents::OpenDialogBox(MAIN, 0, 0, 20, 30, "open file");
  GraphicComponents::OpenDialogBox * open1 = new GraphicComponents::OpenDialogBox(MAIN, 0, 0, 20, 30, "open file", "my open dialogbox");
  assert(open != nullptr, "OpenDialogBox constructor (6 args)");
  assert(open1 != nullptr, "OpenDialogBox constructor (7 args)");
}

void GotoDialogboxTests::execute () {
  const int MAIN = 0;
  GraphicComponents::GotoDialogBox * g = new GraphicComponents::GotoDialogBox(MAIN, 0, 0, 20, 30, "my goto dialogbox");
  assert(g != nullptr, "GotoDialogbox constructor (6 args)");
  //tests returned values methods
  assert(g->to(), (unsigned int)0, "GotoDialogbox to 0 by default");
}

void MenuTests::execute () {
  const int MAIN = 0;
  list<string> lst0;
  list<string> lst;
  lst.push_back("item1");
  lst.push_back("item2");
  lst.push_back("item3");
  list<GraphicComponents::Text *> lst2;
  GraphicComponents::Text* titem = new GraphicComponents::Text(MAIN, 2, 0, "item3");
  lst2.push_back(new GraphicComponents::Text(MAIN, 0, 0, "item1"));
  lst2.push_back(new GraphicComponents::Text(MAIN, 1, 0, "item2"));
  lst2.push_back(titem);
  GraphicComponents::Menu * m = new GraphicComponents::Menu(MAIN, 0, 0, lst0);
  GraphicComponents::Menu * m1 = new GraphicComponents::Menu(MAIN, 0, 0, lst, "my menu with string list");
  GraphicComponents::Menu * m2 = new GraphicComponents::Menu(MAIN, 0, 0, lst2);
  GraphicComponents::Menu * m3 = new GraphicComponents::Menu(MAIN, 0, 0, lst2, "my menu with Text* list");
  assert(m != nullptr, "Menu constructor string list (4 args)");
  assert(m1 != nullptr, "Menu constructor string list (5 args)");
  assert(m2 != nullptr, "Menu constructor Text* list (4 args)");
  assert(m3 != nullptr, "Menu constructor Text* list (5 args)");
  //tests with void returned methods
  m->select(2);
  m1->select(2);
  //tests with value returned methods
  list<string> l = m1->items();
  assert(l.size() == 3, "m1 contains 3 items");
  map<char, int> shorts = m1->shortcuts();

  GraphicComponents::Text * t1 = m1->validation();
  GraphicComponents::Text * t2 = m1->validation(2);
  GraphicComponents::Text * t3 = m1->itemSelected();
  GraphicComponents::Text * t4 = m2->validation(3);
  assert(t1 != nullptr, "Menu validation (no args)");
  assert(t2 != nullptr, "Menu second validation (number arg)");
  assert(t3 != nullptr, "Menu item selected");
  assert(t4, titem, "Menu third validation (address)");
}

void HMenuTests::execute () {
  const int MAIN = 0;
  list<string> lst0;
  list<string> lst;
  lst.push_back("item1");
  lst.push_back("item2");
  lst.push_back("item3");
  list<GraphicComponents::Text *> lst2;
  lst2.push_back(new GraphicComponents::Text(MAIN, 0, 0, "item1"));
  lst2.push_back(new GraphicComponents::Text(MAIN, 1, 0, "item2"));
  GraphicComponents::HMenu * m1 = new GraphicComponents::HMenu(MAIN, 0, 0, lst);
  GraphicComponents::HMenu * m2 = new GraphicComponents::HMenu(MAIN, 0, 0, lst, "my string list HMenu");
  GraphicComponents::HMenu * m3 = new GraphicComponents::HMenu(MAIN, 0, 0, lst2);
  GraphicComponents::HMenu * m4 = new GraphicComponents::HMenu(MAIN, 0, 0, lst2, "my Text* list HMenu");
  assert(m1 != nullptr, "HMenu constructor string list (4 args)");
  assert(m2 != nullptr, "HMenu constructor string list (5 args)");
  assert(m3 != nullptr, "HMenu constructor Text* list (4 args)");
  assert(m4 != nullptr, "HMenu constructor Text* list (5 args)");
}

void VMenuTests::execute () {
  const int MAIN = 0;
  list<string> lst0;
  list<string> lst;
  lst.push_back("item1");
  lst.push_back("item2");
  lst.push_back("item3");
  list<GraphicComponents::Text *> lst2;
  lst2.push_back(new GraphicComponents::Text(MAIN, 0, 0, "item1"));
  lst2.push_back(new GraphicComponents::Text(MAIN, 1, 0, "item2"));
  GraphicComponents::VMenu * m1 = new GraphicComponents::VMenu(MAIN, 0, 0, lst);
  GraphicComponents::VMenu * m2 = new GraphicComponents::VMenu(MAIN, 0, 0, lst, "my string list VMenu");
  GraphicComponents::VMenu * m3 = new GraphicComponents::VMenu(MAIN, 0, 0, lst2);
  GraphicComponents::VMenu * m4 = new GraphicComponents::VMenu(MAIN, 0, 0, lst2, "my Text* list VMenu");
  assert(m1 != nullptr, "VMenu constructor string list (4 args)");
  assert(m2 != nullptr, "VMenu constructor string list (5 args)");
  assert(m3 != nullptr, "VMenu constructor Text* list (4 args)");
  assert(m4 != nullptr, "VMenu constructor Text* list (5 args)");
}

void ButtonTests::execute () {
  const int MAIN = 0;
  //tests constructors
  GraphicComponents::Button * b1 = new GraphicComponents::Button(MAIN, 0, 0, "myButton");
  GraphicComponents::Button * b2 = new GraphicComponents::Button(MAIN, 0, 0, "myButton", "myButtonName");
  assert(b1 != nullptr, "Button constructor (4 args)");
  assert(b2 != nullptr, "Button constructor (5 args)");
  //tests value returned methods
  assert(b2->label().c_str(), "myButton", "b2 label is 'myButton'");
}

void ImageTests::execute () {

}

void CellTests::execute () {
  const int MAIN = 0;
  //tests constructors
  GraphicComponents::Cell * c1 = new GraphicComponents::Cell(MAIN, 0, 0, "my value");
  GraphicComponents::Cell * c2 = new GraphicComponents::Cell(MAIN, 0, 0, "my value", "c2");
  assert(c1 != nullptr, "Cell constructor (4 args)");
  assert(c2 != nullptr, "Cell constructor (5 args)");
  //tests with void returned methods
  c2->setWidth(20);
  c2->setHeight(3);
  c2->setValue("my new value");
  c2->select();
  //tests with valued returned methods
  assert(c2->isSelected(), true, "c2 is selected");
  assert(c2->value().c_str(), "my new value", "c2 value is 'my new value'");
}

void TableTests::execute () {
  const int MAIN = 0;
  //tests constructors
  GraphicComponents::Table * t1 = new GraphicComponents::Table(MAIN, 0, 0, 2, 3);
  GraphicComponents::Table * t2 = new GraphicComponents::Table(MAIN, 0, 0, 2, 3, "***");
  GraphicComponents::Table * t3 = new GraphicComponents::Table(MAIN, 0, 0, 2, 3, "***", "my table");
  assert(t1 != nullptr, "Table constructor (5 args)");
  assert(t2 != nullptr, "Table constructor (6 args)");
  assert(t3 != nullptr, "Table constructor (7 args)");

  //tests void returned methods
  t3->setValue(1, 1, "value of c(1,1)");
  string s = "value of c(1,2)";
  t3->setValue(1, 2, s);
  t3->updateLengths ();
  t3->select(2, 2);
  t3->setCursor(2, 3);
  //tests value returned methods
  GraphicComponents::Cell c1 = t3->getCell(1);
  GraphicComponents::Cell * c2 = t3->getCell(1, 1);
  assert(t3->getCell(1, 1) != nullptr, "t3 get cell (1, 1) is not nullptr");
  assert(c2 != nullptr, "c2 is not nullptr");
  assert(c2 == t3->getCell(1, 1), "c2 and t3 get cell (1, 1) returns the same memory address");
  GraphicComponents::tab tab1 = t3->getTab();
  //TODO: tester ensuite le contenu de tab
}

void CalendarTests::execute () {
  const int MAIN = 0;
  //tests constructors
  GraphicComponents::Calendar * c1 = new GraphicComponents::Calendar(MAIN, 0, 0);
  GraphicComponents::Calendar * c2 = new GraphicComponents::Calendar(MAIN, 0, 0, "my calendar");
  assert(c1 != nullptr, "Calendar constructor (3 args)");
  assert(c2 != nullptr, "Calendar constructor (4 args)");
  //tests valued returned methods
  GraphicComponents::Selector s1 = c2->getMonth();
  GraphicComponents::Selector s2 = c2->getYear();
  GraphicComponents::Table t = c2->getDaily();
}

void AgendaTests::execute () {
  const int MAIN = 0;
  //tests constructors
  GraphicComponents::Agenda * a1 = new GraphicComponents::Agenda(MAIN, 0, 0);
  GraphicComponents::Agenda * a2 = new GraphicComponents::Agenda(MAIN, 0, 0, "my agenda");
  assert(a1 != nullptr, "Agenda constructor (3 args)");
  assert(a2 != nullptr, "Agenda constructor (4 args)");
  //tests valued returned methods
  GraphicComponents::Selector s1 = a2->getDay();
  GraphicComponents::Selector s2 = a2->getMonth();
  GraphicComponents::Selector s3 = a2->getYear();
  GraphicComponents::Table t1 = a2->getHourly();
  GraphicComponents::Text text1 = a2->getName();
}

void NodeTests::execute () {
  const int MAIN = 0;
  //tests template methods
  GraphicComponents::Node * n = new GraphicComponents::Node("node1");
  Component * c = n->cast<Component*>(n);
  assert(c != nullptr, "cast operational (not nullptr)");
  list<GraphicComponents::Node*> lst;
  lst.push_back(n);
  list<Component*> lst_c = n->castList<Component*>(lst);
  list<GraphicComponents::Node*> lst_n = n->castList<GraphicComponents::Node*>(lst_c);
  assert(lst_n.size() > 0, "castList operational");

  //tests constructors
  GraphicComponents::Node * n1 = new GraphicComponents::Node("myNode1");
  GraphicComponents::Node * n2 = new GraphicComponents::Node(n1, "myNode2");
  assert(n1 != nullptr, "Node constructor (1 arg)");
  assert(n2 != nullptr, "Node constructor (2 args)");
  //tests void returned methods
  GraphicComponents::Node * n3 = new GraphicComponents::Node("myNode3");
  n2->add(n3);
  n2->add(new GraphicComponents::Node("myNode4"));
  n2->add(new GraphicComponents::Item("Item1"));
  n2->add(new GraphicComponents::GroupItem("Group1"));
  n2->erase(1); // erase node position 1
  GraphicComponents::GraphicComponent * gc = new GraphicComponents::GraphicComponent(MAIN, 0, 0, "my graphic component");
  n2->attach(gc);
  n2->detach();
  n1->clear();
  //tests valued returned methods
  list<GraphicComponents::Atom *> childs = n2->getChildren();
  assert(n2->getName().c_str(), "myNode2", "n2 name is 'myNode2'");
  GraphicComponents::Atom * parent = n2->getParent();
  GraphicComponents::Atom * group1 = n2->getNode("Group1");
  GraphicComponents::Atom * position2 = n2->getNode(2);
  assert(parent != nullptr, "n2 getParent() returns a non null pointer");
  assert(group1 != nullptr, "n2 getParent('Group1') returns a non null pointer");
  assert(position2 != nullptr, "n2 getParent(2) returns a non null pointer");
  assert(n2->getRank("Group1") == 2, "n2 node named 'Group1' rank is 2");
  assert(n2->getNameOffset("Group1"), (unsigned int)17, "n2 node named 'Group1' name offset is 17"); //[ASC]For HMenu
  assert(n2->validate(), "n2 is validate");
}

void ItemTests::execute () {
  //tests constructors
  GraphicComponents::Node * n1 = new GraphicComponents::Node("myNode1");
  GraphicComponents::Item * i1 = new GraphicComponents::Item("Item1");
  GraphicComponents::Item * i2 = new GraphicComponents::Item(n1, "Item1");
  assert(i1 != nullptr, "Item constructor (1 arg)");
  assert(i2 != nullptr, "Item constructor (2 args)");
  // tests void returned methods
  i1->select();
  assert(i1->isSelected(), "i1 is selected");
  i1->clear();
  assert(!i1->isSelected(), "i1 is not selected (cleared)");
  //tests value returned methods
  assert(!i2->isSelected(), "i2 is not selected");
  assert(i1->getName().c_str(), "Item1", "i1 name is 'Item1'");
  assert(i1->validate(), "i1 is validate()");
}

void GroupItemTests::execute () {
  //tests constructors
  GraphicComponents::Node * n1 = new GraphicComponents::Node("myNode1");
  GraphicComponents::GroupItem * gi1 = new GraphicComponents::GroupItem("GroupItem1");
  GraphicComponents::GroupItem * gi2 = new GraphicComponents::GroupItem(n1, "GroupItem1");
  assert(gi1 != nullptr, "GroupItem constructor (1 arg)");
  assert(gi2 != nullptr, "GroupItem constructor (2 args)");

  //tests void returned methods
  gi2->setDefault(1);
  gi2->setDefault(-1); //test negative bound
  gi2->display();
  gi2->selectItem(1);
  //tests valued returned methods
  gi2->add(new GraphicComponents::Item("Item1"));
  gi2->add(new GraphicComponents::Item("Item2"));
  gi2->add(new GraphicComponents::Item("Item3"));
  gi2->selectItem(2);
  GraphicComponents::Item * i1 = gi2->getSelectedItem();
  assert(i1 != nullptr, "gi2 getSelectedItem is not null pointer");
  assert(gi2->size(), 3, "gi2 size is 3");
}

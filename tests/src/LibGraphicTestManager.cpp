#include "LibGraphicTestManager.h"

//Dialogbox
void DialogboxTests::execute () {
  const int MAIN = 0;
  string titre = "DialogboxTitre";
  string message = "DialogboxMessage";
  GraphicComponents::DialogBox diag(MAIN, 20, 10, 8, 45, titre, message);
  list<GraphicComponents::GraphicComponent *> lst = diag.getGraphicComponents();
  assert((int)lst.size(), 2, "Verifie le nb de composants graphiques");
  list<GraphicComponents::GraphicComponent *>::iterator it = lst.begin();
  GraphicComponents::Button* b = dynamic_cast<GraphicComponents::Button*>(*it);
  assert(b != nullptr, "First object is Button component");
  assert(b->id(), 1, "First object id is 1");
  assert(b->label().c_str(), "OK", "First object is OK Button");
  assert(b->x(), 22, "OK Button X position");
  assert(b->y(), 6, "OK Button Y position");
  it++;
  GraphicComponents::Text* gc = dynamic_cast<GraphicComponents::Text*>(*it);
  assert(gc != nullptr, "Second object is Text component");
  assert(b->id(), 2, "Second object id is 2");

  GraphicComponents::DialogBox diag2(MAIN, 20, 10, 10, 66, titre, message, GraphicComponents::DialogBox::OK_CANCEL);
  lst = diag2.getGraphicComponents();
  assert((int)lst.size(), 3, "(2 boutons) Verifie le nb de composants graphiques");
  it = lst.begin();
  b = dynamic_cast<GraphicComponents::Button*>(*it);
  assert(b != nullptr, "(2 boutons) First object is Button component");
  assert(b->id(), 1, "(2 boutons) First object id is 1");
  assert(b->label().c_str(), "OK", "(2 boutons) First object is OK Button");
  assert(b->x(), 22, "(2 boutons) OK Button X position");
  assert(b->y(), 8, "(2 boutons) OK Button Y position");
  it++;

  b = dynamic_cast<GraphicComponents::Button*>(*it);
  assert(b != nullptr, "(2 boutons) Second object is Button component");
  assert(b->id(), 2, "(2 boutons) Second object id is 2");
  assert(b->label().c_str(), "Cancel", "(2 boutons) Second object is Cancel Button");
  assert(b->x(), 44, "(2 boutons) Cancel Button X position");
  assert(b->y(), 8, "(2 boutons) Cancel Button Y position");
  it++;

  gc = dynamic_cast<GraphicComponents::Text*>(*it);
  assert(gc != nullptr, "(2 boutons) Third object is Text component");
  assert(b->id(), 3, "(2 boutons) Third object id is 3");
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

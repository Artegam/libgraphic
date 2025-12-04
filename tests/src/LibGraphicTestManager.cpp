#include "LibGraphicTestManager.h"

//Dialogbox
DialogboxTests::DialogboxTests (string name) : testunit::TestManager(name) {}

void DialogboxTests::execute () {
  const int MAIN = 0;
  string titre = "DialogboxTitre";
  string message = "DialogboxMessage";
  GraphicComponents::DialogBox diag(MAIN, 20, 10, 8, 45, titre, message);
  list<GraphicComponents::GraphicComponent *> lst = diag.components();
  assert(lst.size() == 3, "Verifie le nb de composants graphiques");
}

int DialogboxTests::report () {
  return TestManager::report();
}

//Scrollbar
ScrollbarTests::ScrollbarTests (string name) : testunit::TestManager(name) {}

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

int ScrollbarTests::report () {
  return TestManager::report();
}

//LibGraphicTest
void LibGraphicTest::execute () {}
int LibGraphicTest::report () {return testunit::TestManager::report();}


// LibGraphicTestManager
LibGraphicTestManager::LibGraphicTestManager (string name) : testunit::TestManager(name) {}
void LibGraphicTestManager::execute () {}

int LibGraphicTestManager::report () {
  return TestManager::report();
}

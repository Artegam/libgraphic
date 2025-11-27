#include "ScrollbarTests.h"

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

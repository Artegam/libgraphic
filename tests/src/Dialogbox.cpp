#include "DialogboxTests.h"

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

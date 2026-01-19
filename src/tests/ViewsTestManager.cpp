#include <tests/ViewsTestManager.h>

//"Pugnare in Tenebris, Vincere in Luminis"

void ViewTests::execute () {
  //tests constructors
  Views::View * v = new Views::View();
  assert(v != nullptr, "View constructor (0 args)");
  //TODO: TO BE CONTINUED....
}

void NCursesTests::execute () {
  //tests constructors
  Views::NCurses * v = new Views::NCurses();
  assert(v != nullptr, "NCurses constructor (0 args)");
  delete v;
  //TODO: TO BE CONTINUED....
}

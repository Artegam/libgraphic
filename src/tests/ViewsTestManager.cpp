#include <tests/ViewsTestManager.h>

//"Pugnare in Tenebris, Vincere in Luminis"

void ViewTests::execute () {
  //tests constructors
  Views::View * view = new Views::View();
  assert(view != nullptr, "View constructor (0 args)");

  const unsigned char second_key = 'f';
  view->onShortcut(second_key);
  assert(view->selected() != nullptr, "A graphic component is selected in the view");
  //TODO: TO BE CONTINUED....
}

void NCursesTests::execute () {
  //tests constructors
  Views::NCurses * v = new Views::NCurses();
  assert(v != nullptr, "NCurses constructor (0 args)");
  delete v;
  //TODO: TO BE CONTINUED....
}

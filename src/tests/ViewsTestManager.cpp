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

void NCursesPaletteTests::execute () {
  map<unsigned short, pair<short,short>> colors;
  colors[0] = {COLOR_WHITE, COLOR_BLACK};
  colors[1] = {COLOR_BLACK, COLOR_WHITE};
  Views::NCursesPalette * p1 = new Views::NCursesPalette();
  assert(p1 != nullptr, "NCursesPalette constructor (0 args)");
  Views::NCursesPalette * p2 = new Views::NCursesPalette(colors);
  assert(p2 != nullptr, "NCursesPalette constructor (1 arg)");

  chtype t = p2->getColorPair(1);
  assert(t != 0, "NCursesPalette getColorPair");
  p1->add(1, COLOR_BLUE, COLOR_RED);
}

void NCursesTests::execute () {
  //tests constructors
  Views::NCurses * v = new Views::NCurses();
  assert(v != nullptr, "NCurses constructor (0 args)");
  delete v;
  //TODO: TO BE CONTINUED....
}

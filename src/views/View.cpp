#include "Views.h"

using namespace std;
using namespace Views;

View::View () {
}

void View::init (int height, int width) {
}

void View::loadPalette () {}

void View::end () {
  tobeClosed = true;
}

bool View::shouldClose () {
  return tobeClosed;
}

void View::close () {
}

void View::load (Screen screen) {
  _maxKeyboardx = screen.getSelectSize() - 1;
  screens.clear();
  screens.push_back(&screen);
}

void View::load (list<Screen*> lst) {
  screens.clear();
  screens = lst;
}

void View::display () {
}

void View::display (Component * c) {
  if (GraphicComposite * gc = dynamic_cast<GraphicComposite*>(c); gc != nullptr) {
    display(gc);
  } else if (GraphicLeaf * gl = dynamic_cast<GraphicLeaf*>(c); gl != nullptr) {
    display(gl);
  }
}

void View::display (GraphicComposite * gc) {
  if (DialogBox * db = dynamic_cast<DialogBox*>(gc); db != nullptr) {
    display(db);
  } else if (HMenu * menu = dynamic_cast<HMenu*>(gc); menu != nullptr) {
    display((*menu));
  } else if (VMenu * menu = dynamic_cast<VMenu*>(gc); menu != nullptr) {
    display((*menu));
  } else if (Menu * menu = dynamic_cast<Menu*>(gc); menu != nullptr) {
    display((*menu));
  } else if (Screen * scr = dynamic_cast<Screen*>(gc); scr != nullptr) {
    //display((*scr));
  }

  if(_active == NULL && gc->isSelected())
    _active = gc;
}

//[ASC] Du plus détaille au plus general (ordre important)
void View::display (GraphicLeaf * gl) {
  if (Input * input = dynamic_cast<Input*>(gl); input != nullptr) {
    display(input);
  }else if (Text * text = dynamic_cast<Text*>(gl); text != nullptr) {
    display((*text));
  }else if (Selector * sel = dynamic_cast<Selector*>(gl); sel != nullptr) {
    display((*sel));
  } else if (Button * button = dynamic_cast<Button*>(gl); button != nullptr) {
    display((*button));
  } else if (Cell * cell = dynamic_cast<Cell*>(gl); cell != nullptr) {
    display((*cell));
  } else if (Table * tab = dynamic_cast<Table*>(gl); tab != nullptr) {
    display((*tab));
  } else if (ScrollBar * scroll = dynamic_cast<ScrollBar*>(gl); scroll != nullptr) {
    display((*scroll));
  } else if (Calendar * cal = dynamic_cast<Calendar*>(gl); cal != nullptr) {
    display((*cal));
  } else if (Agenda * age = dynamic_cast<Agenda*>(gl); age != nullptr) {
    display((*age));
  }

  if(_active == NULL && gl->isSelected())
    _active = gl;
}

void View::display (DialogBox box) {}
void View::display (Menu menu) {}
void View::display (HMenu menu) {
  menu.select(submenuHCursor);
  _menu_shorcuts = menu.shortcuts();
  _active = menu.itemSelected();
}
void View::display (VMenu menu) {}
void View::display (Text text) {}
void View::display (Input * input) {}
void View::display (Selector selector) {}
void View::display (Calendar calendar) {}
void View::display (Agenda age) {}
void View::display (Table tab) {}
void View::display (Cell c) {}
void View::display (ScrollBar bar) {}
void View::display (Button button) {}

void View::mainMenu (int keybPosition) {
}

void View::options (int keybPosition) {
}

void View::languages (int keybPosition) {
}

void View::video (int keybPosition) {
}

void View::gameplay (int position, map<int, int> worldMap) {
}

int View::getChar () {
  return 0;
}

void View::initScreen () {
}

void View::clearScreen () {
}

void View::validateOption (int optionNumber) {
}

void View::createWindow (int position, int x, int y, int height, int width) {
}

const unsigned char View::keyboard () {
  return 0x00;
}

const int View::getKeyboardx () {
  return _keyboardx;
}

const int View::getKeyboardy () {
  return _keyboardy;
}

void View::setMaxKeyboardx (const int max) {
  _maxKeyboardx = max;
}

void View::setMaxKeyboardy (const int max) {
  _maxKeyboardy = max;
}

void View::setSubMenu (const bool active) {
  _submenu = active;
}

void View::resetKeyboard () {
  _keyboardx = 0;
  _keyboardy = 0;
}

bool View::isValid () {
  bool ret = _valid;
  _valid = false;
  return ret;
}

bool View::isSubMenu () {
  return _submenu;
}

size_win View::getScreenSize () {
  return screenSize;
}

void View::free () {
}

const unsigned int View::page () {
  return _page;
}

void View::setMaxPage (const unsigned int max) {
  if(max>0)
    _maxPage = max;
}

Component * View::validated () {
  if(_valid) {
    Component * gc = _validated;
    _validated = NULL;
    _submenu = false;
    _valid = false;
    return gc;
  } else
    return NULL;
}

Component * View::selected() {
  return _active;
}

void View::moveSubmenuVCursor (const bool inc) {
  if(inc)
    submenuVCursor++;
  else
    submenuVCursor--;
}

void View::moveSubmenuHCursor (const bool inc) {
  if(inc)
    submenuHCursor++;
  else
    submenuHCursor--;
}

const unsigned int View::getSubmenuVCursor () {
  return submenuVCursor;
}

const unsigned int View::getSubmenuHCursor () {
  return submenuHCursor;
}

pair<unsigned int, unsigned int> View::getCursorPosition () {
  return pair<unsigned int, unsigned int>(x, y);
}

void View::setCursorPosition (pair<unsigned int, unsigned int> p) {
  x = p.first;
  y = p.second;
}

void View::movePage(const bool next) {
  if(next && _page<_maxPage)
    _page++;
  else if(!next && _page>0)
    _page--;
}

void View::movePage(const unsigned int to_page) {
  _page = to_page;
}

void View::valid(const bool val) {
  _valid = val;
}

const bool View::isDialog () {
  return _dialog != NULL;
}

void View::onShortcut (const unsigned char shortcut) {
  submenuHCursor = _menu_shorcuts[shortcut];
  GraphicComposite * gc = nullptr;
  GraphicLeaf * gl = nullptr;

  if(_active != nullptr) {
    if (gc = dynamic_cast<GraphicComposite*>(_active); gc != nullptr) {
      gc->unselect();
    } else if (gl = dynamic_cast<GraphicLeaf*>(_active); gl != nullptr) {
      gl->unselect();
    }
  }

  _active = nullptr;
}

void View::setKeyboard (int screen) {}
InputDevices::Keyboard * View::getKeyboard () {return nullptr;}

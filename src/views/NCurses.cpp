#include "Views.h"

#include <ncurses.h>
#include <locale.h>

using namespace Views;

unsigned char Views::View::_first_key;
unsigned char Views::View::_second_key;
unsigned int Views::View::_page = 0;
unsigned int Views::View::_maxPage = 1;
unsigned int Views::View::_cursor_x = 0;
unsigned int Views::View::_cursor_y = 0;
bool Views::View::_isSubmenu = false;

Views::NCurses::NCurses () : View () {
  // Ncurses initialization
  setlocale(LC_ALL, "");
  initscr();
  cbreak();
  noecho();
  if(stack.size() == 0)  //[ASC] first screen is stdscr
    stack.push_back(stdscr);
  getmaxyx(stack.back(), screenSize.height, screenSize.width); //get height and width
  getyx(stack.back(), Views::View::_cursor_y, Views::View::_cursor_x); //get x and y start positions
  init(screenSize.height, screenSize.width);
  colorize();
}

Views::NCurses::~NCurses () {
  free();
  endwin();
}

void Views::NCurses::init (int height, int width) {
  this->worldHeight = height;
  this->worldWidth = width;

  // Creation of the stack
  stack[0] = subwin(stack.back(), screenSize.height, screenSize.width, Views::View::_cursor_y, Views::View::_cursor_x);

  if (has_colors() == FALSE) {
    endwin();
    printf("Your terminal does not support color\n");
    exit(1);
  }
}

void Views::NCurses::loadPalette () {
  //[ASC] init colors
  //init_pair(NAME, Text color, background color)
  if(_colorPalette != nullptr) {
    start_color();
    for(unsigned short i = 1; i <= _colorPalette->size(); i++)
      init_pair(i, _colorPalette->getPair(i).first, _colorPalette->getPair(i).second);
  }
}

void Views::NCurses::createWindow (int screen, int x, int y, int height, int width) {
  if(stack.size() < (unsigned long)(screen + 1)) 
    stack.resize(screen+1);
  stack.push_back(subwin(stack.back(), height, width, y, x));
}

void Views::NCurses::drawChar (WINDOW * win, int x, int y, char c, char color) {
  wattron(win, COLOR_PAIR(color));
  mvwaddch(win, y, x, c);
  wattroff(win, COLOR_PAIR(color));
}

void Views::NCurses::displayCursorPosition (int keybPosition) {
  mvprintw(25, 0, "POSITION: %d", keybPosition);
  refresh();
}

void Views::NCurses::validateOption (int optionNumber) {
  Screen scr = *screens.front();
  scr.select(optionNumber);
}

void Views::NCurses::clearScreen() {
  toClear = true;
}

void Views::NCurses::initScreen() {
  if (toClear) {
    Screen scr = *screens.front();
    wclear(stack.back());
    wclear(stack[scr.window()]);
    colorize();
    toClear = false;
  }
}

void Views::NCurses::end () {
  wclear(stack.back());
  mvwprintw(stack.back(), 14, 20, "******************");
  mvwprintw(stack.back(), 15, 20, "This is the end...");
  mvwprintw(stack.back(), 16, 20, "******************");
  refresh();
  getch();
  endwin();
}

void Views::NCurses::hello () {
  // pour tester
  initscr();
  printw("Hello World");
  refresh();
  getch();
  endwin();
}

void Views::NCurses::colorize () {
  wclear(stack[0]);
  start_color();
  wbkgd(stack[0], COLOR_PAIR(SCREEN));
}

void Views::NCurses::load (Screen screen) {
//[ASC] TODO: il y a un soucis ici... a creuser ou a refaire
  clear();
  View::load(screen);

  WINDOW * sub = subwin(stack.back(), screen.height(), screen.width(), screen.y(), screen.x());
  stack.push_back(sub);

  start_color();
  wbkgd(sub, COLOR_PAIR(SCREEN));
}

void Views::NCurses::display () {
  map<int, Component *> lst;
  wclear(stack[0]);

  //[ASC] default display
  if(screens.size() == 0) {
    Text * t = new Text(0, 0, screenSize.height/2, "libgraphic v1.0");
    t->align(Text::CENTER);
    display(t);
  }

  _dialog = NULL;
  for(list<Screen*>::reverse_iterator it=screens.rbegin(); it!=screens.rend(); it++) {
    list<Component *> m = (*it)->getGraphicComponents();
    for(list<Component *>::iterator imap = m.begin(); imap!= m.end(); imap++)
      lst[lst.size()] = *imap;
  }

  //mvwprintw(stack[0], 2, 50, "_keyboardx: %d", _keyboardx); //[ASC] Pour le debug
  mvwprintw(stack[0], 2, 40, "1st key pressed: %d", View::_first_key);
  mvwprintw(stack[0], 3, 40, "2nd key pressed: %d", View::_second_key);

  for(map<int, Component *>::iterator it = lst.begin(); it != lst.cend(); it++) {
    if (DialogBox * box = dynamic_cast<DialogBox*>(it->second); box != nullptr)
      _dialog = box;
    else
      display(it->second);
  }

  if(_dialog != NULL) { //[ASC] les dialogBox s affichent devant
    display((*_dialog));
    _dialog->selectNext();
    _active = _dialog->selectedComponent();
  }

  wmove(stack.back(), Views::View::_cursor_y, Views::View::_cursor_x); // repositione le curseur
  refresh();
  usleep(100000);
}

void Views::NCurses::display (DialogBox dialog) {
  list<Component *> lst;
  pair<unsigned int, unsigned int> position = dialog.position();
  if(!exists(position))
    windows[position] = subwin(stack[dialog.window()], dialog.height(), dialog.width(), dialog.y(), dialog.x());

  stack.push_back(windows[position]);
  wbkgd(windows[position], COLOR_PAIR(HMENU));
  wclear(windows[position]);
  box(windows[position], ACS_VLINE, ACS_HLINE);
  wrefresh(windows[position]);

  mvwprintw(windows[position], 0, 1, "%s", dialog.label().c_str());

  lst = dialog.getGraphicComponents();
  list<Component *>::iterator idx = lst.begin();
  advance(idx, dialog.selected());

  for(list<Component *>::iterator it = lst.begin(); it != lst.cend(); it++) {
    Input * input = dynamic_cast<Input*>(*it);
    if(input == nullptr && (*it) == (*idx))
      wattron(stack.back(), A_REVERSE);
    display(*it);
    if(input == nullptr && (*it) == (*idx))
      wattroff(stack.back(), A_REVERSE);
  }

  wrefresh(stack.back());
  stack.pop_back();
}

void Views::NCurses::display (Menu menu) {
  list<string>::iterator it;
  list<string> items = menu.items();
  unsigned int y = (menu.y() * screenSize.height) / 100;
  unsigned int x = (menu.x() * screenSize.width) / 100;

  unsigned int cursorPosition = 0;

  it = items.begin();
  advance(it, _keyboardx);
  Screen scr = *screens.front();
  mvwprintw(stack[scr.window()], 5, 50, "_maxKeyboardx: %d", _maxKeyboardx);

  //TODO: le 10 c'est la largeur, donc le calcul de la plus longue chaine de caracteres
  pair<unsigned int, unsigned int> position = menu.position();
  if(!exists(position))
    windows[position] = subwin(stack[menu.window()], items.size() + 2, 10,  y - 1, x - 1);
  box(windows[position], ACS_VLINE, ACS_HLINE);

  for(it = items.begin(); it != items.end(); it++) {
    if(cursorPosition == _keyboardx)
      wattron(windows[position], A_REVERSE);
    mvwprintw(windows[position], y, x, "%s", (*it).c_str());
    if(cursorPosition == _keyboardx)
      wattroff(windows[position], A_REVERSE);

    y++;
    cursorPosition++;
  }
}

void Views::NCurses::display (HMenu menu) {
  View::display (menu);

  list<string>::iterator it;
  list<string> items = menu.items();

  unsigned int cursorPosition = 0;
  unsigned int num = 0;

  submenuHCursor=submenuHCursor%items.size();

  pair<unsigned int, unsigned int> position = menu.position();
  if(!exists(position))
    windows[position] = subwin(stack[menu.window()], 1, screenSize.width, 0, 0);
  wbkgd(windows[position], COLOR_PAIR(menu.getColor()));

  for(it=items.begin(); it != items.end(); it++) {
    string str=(*it);
    string::iterator ptr=str.begin();

    mvwprintw(stack[0], 2, 3, "submenuHCursor: %d", submenuHCursor);
    mvwprintw(stack[0], 3, 3, "num : %d", num);
    mvwprintw(stack[0], 4, 3, "isSubmenu: %d", _isSubmenu);

    if(_isSubmenu && submenuHCursor == num)
      wattron(windows[position], COLOR_PAIR(HMENU_SELECTED));
    wattron(windows[position], A_BOLD | A_UNDERLINE);
    mvwprintw(windows[position], 0, cursorPosition, "%c", *ptr);
    cursorPosition++;
    wattroff(windows[position], A_BOLD | A_UNDERLINE);
    mvwprintw(windows[position], 0, cursorPosition, "%s", str.substr(1, str.size()-1).c_str());
    if(_isSubmenu && submenuHCursor == num)
      wattroff(windows[position], COLOR_PAIR(HMENU_SELECTED));
    cursorPosition+=(*it).size()+1;
    num++;
  }

  if(_isSubmenu) {
    unsigned int offset = 1;
    unsigned int num = 0;
    bool found = false;

    for(list<string>::iterator it = items.begin(); it!=items.end()||found; it++) {
      string s = *it;
      string::iterator s_it = s.begin();
      if(tolower(*s_it) == second_key) {
        submenuHCursor = num;
        menu.select(num);
        found = true;
        second_key=255;
        break;
      } else if (submenuHCursor == num) {
        menu.select(num);
        found = true;
        break;
      }
      offset+=(*it).size()+2;
      num++;
    }
  }
}

void Views::NCurses::display (VMenu menu) {
  list<string> lst = menu.items();
  if(lst.size()>0) {
    if(submenuVCursor>lst.size())
      submenuVCursor=lst.size()-1;
    submenuVCursor=submenuVCursor%lst.size();
    menu.select(submenuVCursor);
    _validated = menu.validation(submenuVCursor);

    pair<unsigned int, unsigned int> position = menu.position();
    if(!exists(position))
      windows[position] = subwin(stack[menu.window()], lst.size(), menu.width()+2,  menu.y(), menu.x());

    wbkgd(windows[position], COLOR_PAIR(HMENU));

    int line = 0;
    for(list<string>::iterator it=lst.begin(); it!=lst.end(); it++) {
      if(line == menu.selected())
        wattron(windows[position], A_REVERSE);
      mvwprintw(windows[position], line, 1, "%s", (*it).c_str());
      if(line == menu.selected())
        wattroff(windows[position], A_REVERSE);
      line++;
    }

  }
}

void Views::NCurses::display (Text text) {
  unsigned int x = 0;
  if(text.align() == Text::LEFT)
    x = text.x();
  else if(text.align() == Text::CENTER) {
    if(text.width()>0)
      x = text.x() + (text.width() - text.lenght())/2;
    else
      x = text.x() + (screenSize.width - text.lenght())/2;
  } else if(text.align() == Text::RIGHT) {
    if(text.width()>0)
      x = text.x() + (text.width() - text.lenght());
    else
      x = screenSize.width - text.lenght();
  }

  wattron(stack[text.window()], COLOR_PAIR(text.getColor()));
  mvwprintw(stack[text.window()], text.y(), x, "%s", text.label().c_str());
  wattroff(stack[text.window()], COLOR_PAIR(text.getColor()));
}

void Views::NCurses::display (Input * input) {
  display(*(dynamic_cast<Text*>(input)));
  unsigned int startx = input->x() + input->label().length();

  wattron(stack[input->window()], COLOR_PAIR(INPUT));
  mvwprintw(stack[input->window()], input->y(), startx, "%s", string(input->width(), ' ').c_str());
  mvwprintw(stack[input->window()], input->y(), startx, "%s", input->value().c_str());
  wattroff(stack[input->window()], COLOR_PAIR(INPUT));
  curs_set(1);
  wrefresh(stack[stack.size()-2]);
  wmove(stack[input->window()], input->y(), startx); // repositione le curseur

  if(input->isSelected()) {
    _active = input;
    unsigned char key = 0x00;
    while(input->isSelected() && key != 0x0a && key != 0x09) {
      wattron(stack[input->window()], COLOR_PAIR(INPUT));
      mvwprintw(stack[input->window()], input->y(), startx, "%s", string(input->width(), ' ').c_str());
      mvwprintw(stack[input->window()], input->y(), startx, "%s", input->value().c_str());
      wattroff(stack[input->window()], COLOR_PAIR(INPUT));

      key = wgetch(stack[input->window()]);
      long unsigned int w = 0;
      if(input->width()-1>=0)
        w = input->width()-1;
      if((input->value().size() < w) || key == 0x7F) // [ASC] Backspace
        input->setch(key);
    }
  }
  _validated = input;
  _valid = true;
}

void Views::NCurses::display (Selector selector) {
  WINDOW * win = stack[selector.window()];
  unsigned int y = (selector.y() * screenSize.height) / 100;
  unsigned int x = (selector.x() * screenSize.width) / 100;

  mvwprintw(win, y, x, "< %s >", selector.label().c_str());
}

void Views::NCurses::display (Table table) {
  basic b = table.getBasic();
  tab t = table.getTab();
  wmove(stack.back(), 0, 0);

  unsigned int x = (b.x * screenSize.width) / 100;
  unsigned int y = (b.y * screenSize.height) / 100;
  const unsigned int width = b.width;
  const unsigned int cols = t.cols;
  unsigned int maxrowsize = 1;

  if (width > 1) {
    unsigned int cpt = 0;
    list<unsigned int>::iterator rowit;
    list<unsigned int>::iterator colit;

    for(rowit = t.rowssizes.begin(); rowit != t.rowssizes.end(); rowit++) {
      x = (b.x * screenSize.width) / 100;
      if(cpt>0)
        y = y+maxrowsize+1;
      if(cpt==0)
        tablerow (table.getRow(0), t.colssizes, x, y, cols);
      else
        tablerow (table.getRow(cpt), t.colssizes, x, y, cols, nullptr, 1);
      cpt++;
    }
  }
}

void Views::NCurses::display (ScrollBar bar) {
  ScrollBarData data = bar.getScrollBar();

  mvwaddch(stack[bar.window()], bar.y(), bar.x(), ACS_UARROW);
  for(unsigned int i =bar.y()+1; i <= bar.y()+data.cursor; i++)
    mvwaddch(stack[bar.window()], i, bar.x(), ACS_CKBOARD);
  mvwaddch(stack[bar.window()], bar.y()+data.cursor+1, bar.x(), ACS_BLOCK);
  for(unsigned int i =bar.y()+data.cursor+2; i <= bar.y()+bar.height()-2; i++)
    mvwaddch(stack[bar.window()], i, bar.x(), ACS_CKBOARD);
  mvwaddch(stack[bar.window()], bar.y()+bar.height()-1, bar.x(), ACS_DARROW);
}

void Views::NCurses::display (Agenda age) {
  Text t = age.getName();
  display(t);
  Table tab = age.getHourly();
  display(tab);
}

void Views::NCurses::display (Calendar calendar) {
  Selector s = calendar.getMonth();
  display(s);
  Selector y = calendar.getYear();
  display(y);
  Table t = calendar.getDaily();
  display(t);
}

//Mode : type of row
// 0 - A simple row
// 1 - Last row of a table
void Views::NCurses::tablerow (list<Cell*> lst, list<unsigned int> colssizes, unsigned int x, unsigned int y, const unsigned int cols, Cell * cursor, unsigned int mode) {
  WINDOW * win = stack.back(); //ATTENTION ICI !!! On ne respecte pas la fenetre selectionnee dans les donnees
  unsigned int maxcolsize = 0;
  unsigned int maxrowsize = 1;
  unsigned int cpt = 0;
  list<unsigned int>::iterator rowit;
  list<unsigned int>::iterator colit;
  unsigned int col = 0;

  list<Cell*>::iterator it = lst.begin();

  //begin header
  wmove(win, y, x);
  if(mode==0)
    hline(ACS_ULCORNER, 1);
  else
    hline(ACS_LTEE, 1);
  // begin body
  wmove(win, y+maxrowsize, x);
  hline(ACS_VLINE, 1);
  // begin foot
  wmove(win, y+maxrowsize+1, x);
  hline(ACS_LLCORNER, 1);

  for(colit = colssizes.begin(); colit != colssizes.end(); colit++) {
    maxcolsize = *colit;
    col = cpt%cols;

    // length of header and junction tee
    wmove(win, y, x+col+1);
    hline(ACS_HLINE, maxcolsize);
    wmove(win, y, x+maxcolsize+col+1);
    if(mode==0)
      hline(ACS_TTEE, 1);
    else
      hline(ACS_PLUS, 1);

    // body
    wmove(win, y+maxrowsize, x+maxcolsize+col+1);
    hline(ACS_VLINE, 1);
    // Value
    Cell c = **it;

    if(c.isSelected())
      wattron(stack.back(), COLOR_PAIR(TABLE));

    mvwprintw(win, y+maxrowsize, x+col+1, "%s", c.value().c_str());
    if(c.isSelected())
      wattroff(stack.back(), COLOR_PAIR(TABLE));

    // length of foot and junction tee
    wmove(win, y+maxrowsize+1, x+col+1);
    hline(ACS_HLINE, maxcolsize);
    wmove(win, y+maxrowsize+1, x+maxcolsize+col+1);
    hline(ACS_BTEE, 1);

    cpt++;
    it++;
    if(cpt<cols)
      x+=maxcolsize;
  }
  //End of header
  wmove(win, y, x+maxcolsize+col+1);
  if(mode==0)
    hline(ACS_URCORNER, 1);
  else if(mode == 1)
    hline(ACS_RTEE, 1);
  // End of foot
  wmove(win, y+maxrowsize+1, x+maxcolsize+col+1);
  hline(ACS_LRCORNER, 1);
}

void Views::NCurses::display (Cell cell) {
  basic b = cell.getBasic();
  rect(b);

  mvwprintw(stack.back(), b.y+1, b.x+1, "%s", cell.value().c_str());
  wmove(stack.back(), 0, 0);
}

void Views::NCurses::display (Button button) {
  if(_valid)
    _validated = &button;

  if(button.isSelected())
    wattron(stack[button.window()], A_REVERSE);
  mvwprintw(stack[button.window()], button.y(), button.x()-1, "<%s>", button.label().c_str());
  if(button.isSelected())
    wattroff(stack[button.window()], A_REVERSE);
}

void Views::NCurses::rect(basic b) {
  WINDOW * win = stack.back();
  const unsigned int x = b.x;
  const unsigned int y = b.y;
  const unsigned int width = b.width;
  const unsigned int height = b.height;

  wmove(win, y, x);
  hline(ACS_ULCORNER, 1);
  wmove(win, y, x+1);
  hline(ACS_HLINE, width);
  wmove(win, y, x+width+1);
  hline(ACS_URCORNER, 1);
  wmove(win, y+1, x);
  vline(ACS_VLINE, height);
  wmove(win, y+height+1, x);
  hline(ACS_LLCORNER, 1);
  wmove(win, y+height+1, x+1);
  hline(ACS_HLINE, width);
  wmove(win, y+height+1, x+width+1);
  hline(ACS_LRCORNER, 1);
  wmove(win, y+1, x+width+1);
  vline(ACS_VLINE, height);
}

const unsigned char Views::NCurses::keyboard () {
  return _keyboard->listen();
}

void Views::NCurses::free () {
  endwin();
  echo();
}

void Views::NCurses::setSubMenu (const bool active) {
  Views::View::setSubMenu(active);
  if(active)
    curs_set(0);
  else
    curs_set(1);
}

void Views::NCurses::setKeyboard (int screen) {
  _keyboard = new InputDevices::NCursesKeyboard(stack[screen]);
  _keyboard->setOnKeyPressed(Views::NCurses::onKeyPressed);
}

InputDevices::Keyboard * Views::NCurses::getKeyboard () {return _keyboard;}

void Views::NCurses::onKeyPressed (unsigned char key) {
  View::_second_key = 0x00;
  View::_first_key = key;
  if(key == 27 || key == 53 || key == 54 || key == 49) View::_second_key = InputDevices::NCursesKeyboard::listenChar();
}

bool Views::NCurses::exists (pair<unsigned int, unsigned int> position) {
  vector<pair<unsigned int, unsigned int>> keys;
  for(map<pair<unsigned int, unsigned int>, WINDOW*>::iterator it = windows.begin(); it != windows.end(); it++)
    keys.push_back(it->first);
  return std::find(keys.begin(), keys.end(), position) != keys.end();
}

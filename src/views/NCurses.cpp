#include "Views.h"

#include <ncurses.h>
#include <locale.h>

using namespace Views;

#define EMPTY_PAIR     1
#define WATER_PAIR     2
#define PLAIN_PAIR     3
#define SHARK_PAIR     4
#define FISH_PAIR      5
#define SCREEN         6
#define HMENU          7
#define HMENU_SELECTED 8
#define INPUT          9

Views::NCurses::NCurses () : View () {
  // Ncurses initialization
  setlocale(LC_ALL, "");
  initscr();
  initColors();
  cbreak();
  noecho();
  if(stack.size() == 0)
    stack.push_back(stdscr);
  keypad(stack.back(), TRUE); //keypad of the keyboard
  nodelay(stack.back(), TRUE); // For the keyboard
  getmaxyx(stack.back(), screenSize.height, screenSize.width);
  getyx(stack.back(), y, x);
  colorize();
}

Views::NCurses::~NCurses () {
  free();
}

void Views::NCurses::init (int height, int width) {
  this->worldHeight = height;
  this->worldWidth = width;

  // Creation of the stack
  stack[0] = subwin(stack.back(), screenSize.height, screenSize.width, 0, 0);

  // Enable keyboard for first standart screen
  keypad(stack.back(), true);

  if (has_colors() == FALSE) {
    endwin();
    printf("Your terminal does not support color\n");
    exit(1);
  }

  start_color();
  init_pair(EMPTY_PAIR, COLOR_WHITE, COLOR_BLACK);
  init_pair(WATER_PAIR, COLOR_BLUE, COLOR_BLACK);
  init_pair(PLAIN_PAIR, COLOR_GREEN, COLOR_BLACK);
  init_pair(SHARK_PAIR, COLOR_RED, COLOR_BLACK);
  init_pair(FISH_PAIR, COLOR_CYAN, COLOR_BLACK);
}

void Views::NCurses::createWindow (int screen, int x, int y, int height, int width) {
  if(stack.size() < (unsigned long)(screen + 1)) 
    stack.resize(screen+1);
  stack.push_back(subwin(stack.back(), height, width, y, x));
  refresh();
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

int Views::NCurses::getChar () {
  return wgetch(stack.back());
}

void Views::NCurses::hello () {
  // pour tester
  initscr();
  printw("Hello World");
  refresh();
  getch();
  endwin();
}

/*
  NCurses colors indexes
  binary  decimal  Name
  000     0        Black
  001     1        Blue
  010     2        Green
  011     3        Cyan
  100     4        Red
  101     5        Magenta
  110     6        Yellow
  111     7        White

  (See intensifier bit in the documentation)
  1000    8        Bright Black
  1001    9        Bright Blue
  1010    10       Bright Green
  1011    11       Bright Cyan
  1100    12       Bright Red
  1101    13       Bright Magenta
  1110    14       Bright Yellow
  1111    15       Bright White
*/

void Views::NCurses::initColors () {
  start_color();
  init_pair(SCREEN, 7, 4);
  init_pair(HMENU, 0, 7);
  init_pair(HMENU_SELECTED, 0, 2);
  init_pair(INPUT, 2, 0);
}

void Views::NCurses::colorize () {
  wclear(stack[0]);
  wbkgd(stack[0], COLOR_PAIR(SCREEN));
}

void Views::NCurses::load (Screen screen) {
  clear();
  View::load(screen);
  WINDOW * sub = subwin(stack.back(), screen.height(), screen.width(), screen.y(), screen.x());
  stack.push_back(sub);
  wbkgd(stack.back(), COLOR_PAIR(SCREEN));
}

void Views::NCurses::display () {
  map<int, GraphicComponent *> lst;
  wclear(stack[0]);
  box(stack.back(), ACS_VLINE, ACS_HLINE);

  _dialog = NULL;
  for(list<Screen*>::iterator it=screens.begin(); it!=screens.end(); it++) {
    list<GraphicComponent *> m = (*it)->components();
    for(list<GraphicComponent *>::iterator imap = m.begin(); imap!= m.end(); imap++)
      lst[lst.size()] = *imap;
  }

  mvwprintw(stack[0], 2, 50, "_keyboardx: %d", _keyboardx);
  mvwprintw(stack[0], 2, 70, "page: %d / %d", _page, _maxPage);

  for(map<int, GraphicComponent *>::iterator it = lst.begin(); it != lst.cend(); it++) {
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

  wmove(stack.back(), y, x); // repositione le curseur
  refresh();
  wrefresh(stack.back());
  usleep(100000);
}

void Views::NCurses::display (GraphicComponent * gc) {
  View::display(gc);
}

void Views::NCurses::display (DialogBox dialog) {
  list<GraphicComponent *> lst;
  WINDOW * sub = subwin(stack.back(), dialog.height(), dialog.width(), dialog.y(), dialog.x());
  stack.push_back(sub);
  wbkgd(sub, COLOR_PAIR(HMENU));
  wclear(sub);
  box(sub, ACS_VLINE, ACS_HLINE);
  wrefresh(sub);

  mvwprintw(sub, 0, 1, "%s", dialog.label().c_str());

  lst = dialog.components();
  list<GraphicComponent *>::iterator idx = lst.begin();
  advance(idx, dialog.selected());

  for(list<GraphicComponent *>::iterator it = lst.begin(); it != lst.cend(); it++) {
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
  WINDOW * sub = subwin(stack[menu.window()], items.size() + 2, 10,  y - 1, x - 1);
  box(sub, ACS_VLINE, ACS_HLINE);

  for(it = items.begin(); it != items.end(); it++) {
    if(cursorPosition == _keyboardx)
      wattron(stack[menu.window()], A_REVERSE);
    mvwprintw(stack[menu.window()], y, x, "%s", (*it).c_str());
    if(cursorPosition == _keyboardx)
      wattroff(stack[menu.window()], A_REVERSE);

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

  WINDOW * sub = subwin(stack[menu.window()], 1, screenSize.width-2,  1, 1);
  wbkgd(sub, COLOR_PAIR(HMENU));
  _menu_shorcuts = menu.shortcuts();

  for(it=items.begin(); it != items.end(); it++) {
    string str=(*it);
    string::iterator ptr=str.begin();
    if(_submenu && submenuHCursor == num)
      wattron(sub, COLOR_PAIR(HMENU_SELECTED));
    wattron(sub, A_BOLD | A_UNDERLINE);
    mvwprintw(sub, 0, cursorPosition, "%c", *ptr);
    cursorPosition++;
    wattroff(sub, A_BOLD | A_UNDERLINE);
    mvwprintw(sub, 0, cursorPosition, "%s", str.substr(1, str.size()-1).c_str());
    if(_submenu && submenuHCursor == num)
      wattroff(sub, COLOR_PAIR(HMENU_SELECTED));
    cursorPosition+=(*it).size()+1;
    num++;
  }

  if(_submenu) {
    unsigned int offset = 1;
    unsigned int num = 0;
    list<string> lst = menu.items();
    bool found = false;
    if(submenuHCursor>lst.size())
      submenuHCursor=lst.size()-1;
    submenuHCursor=submenuHCursor%lst.size();
    for(list<string>::iterator it = lst.begin(); it!=lst.end()||found; it++) {
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
    WINDOW * sub = subwin(stack[menu.window()], lst.size(), 11,  menu.y(), menu.x());
    wbkgd(sub, COLOR_PAIR(HMENU));
    int line = 0;
    for(list<string>::iterator it=lst.begin(); it!=lst.end(); it++) {
      if(line == menu.selected())
        wattron(sub, A_REVERSE);
      mvwprintw(sub, line, 0, "%s", (*it).c_str());
      if(line == menu.selected())
        wattroff(sub, A_REVERSE);
      line++;
    }
  }
}

void Views::NCurses::display (Text text) {
  mvwprintw(stack.back(), text.y(), text.x(), "%s", text.label().c_str());
}

void Views::NCurses::display (Input * input) {
  display(*(dynamic_cast<Text*>(input)));
  unsigned int startx = input->x() + input->label().length();

  wattron(stack.back(), COLOR_PAIR(INPUT));
  mvwprintw(stack.back(), input->y(), startx, "%s", string(input->width(), ' ').c_str());
  mvwprintw(stack.back(), input->y(), startx, "%s", input->value().c_str());
  wattroff(stack.back(), COLOR_PAIR(INPUT));
  curs_set(1);
  wrefresh(stack[stack.size()-2]);
  wmove(stack.back(), input->y(), startx); // repositione le curseur

  if(input->isSelected()) {
    _active = input;
    unsigned char key = 0x00;
    while(input->isSelected() && key != 0x0a && key != 0x09) {
      wattron(stack.back(), COLOR_PAIR(INPUT));
      mvwprintw(stack.back(), input->y(), startx, "%s", string(input->width(), ' ').c_str());
      mvwprintw(stack.back(), input->y(), startx, "%s", input->value().c_str());
      wattroff(stack.back(), COLOR_PAIR(INPUT));

      key = wgetch(stack.back());
      if((input->value().size() < input->width()-1) || key == 0x7F) // [ASC] Backspace
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
  
  mvwprintw(stack[bar.window()], bar.y(), bar.x(), "-");
  mvwprintw(stack[bar.window()], bar.y()+data.cursor+1, bar.x(), "*");
  mvwprintw(stack[bar.window()], bar.y()+bar.height()-1, bar.x(), "+");
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
      wattron(stack.back(), COLOR_PAIR(WATER_PAIR));

    mvwprintw(win, y+maxrowsize, x+col+1, "%s", c.value().c_str());
    if(c.isSelected())
      wattroff(stack.back(), COLOR_PAIR(WATER_PAIR));

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
    wattron(stack.back(), A_REVERSE);
  mvwprintw(stack.back(), button.y(), button.x()-1, "<%s>", button.label().c_str());
  if(button.isSelected())
    wattroff(stack.back(), A_REVERSE);
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
  unsigned char key = 0x00;
  key = wgetch(stack[0]);
  return key;
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

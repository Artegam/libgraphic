#ifndef VIEWS_H
#define VIEWS_H

#include "GraphicComponents.h"
#include <ncurses.h>


#include <unistd.h>
#include <map>
#include <list>
#include <vector>
#include <string>
#include <cstring>
#include <thread>


#include <fstream>
#include <sstream>
#include <iostream>

#define V_QUIT 0x01

using namespace std;
using namespace GraphicComponents;

namespace Views {
  // Keyboard keys
  const int KEYB_DOWN     = 2;
  const int KEYB_UP       = 3;
  const int KEYB_LEFT     = 4;
  const int KEYB_RIGHT    = 5;
  const int KEYB_ENTER    = 10;
  const int KEYB_CR       = 13;
  const int KEYB_SPACE    = 32;
  const int KEYB_ESCAPE   = 27;
  const int KEYB_PAGEDOWN = 82;
  const int KEYB_PAGEUP   = 83;

  struct size_win {
    unsigned int height;
    unsigned int width;
  };

  // interface
  /// class View - 
  class View {
    protected:
      bool toClear = false;
      unsigned int _keyboardx = 0;
      unsigned int _keyboardy = 0;
      unsigned int _maxKeyboardx = 0;
      unsigned int _maxKeyboardy = 0;
      unsigned int _maxPage = 1;
      bool _valid = false;
      list<Screen*> screens;
      bool tobeClosed = false;
      size_win screenSize;
      unsigned int _page = 0;
      bool _submenu = false;
      Component * _active = nullptr;
      Component * _validated = nullptr;
      unsigned int submenuVCursor = 0;
      unsigned int submenuHCursor = 0;
      unsigned int x = 0, y = 0;
      DialogBox * _dialog = nullptr;
      map<char, int> _menu_shorcuts;

      // Operations
    public:
      View ();
      virtual ~View () {};
      virtual void init (int height, int width);
      void end ();
      bool shouldClose ();
      void close ();
      size_win getScreenSize ();
      virtual void free ();
      virtual Component * validated ();
      virtual Component * selected();
      void valid(const bool val = true);
      virtual int getChar ();
      virtual void initScreen();
      virtual void clearScreen ();
      virtual void validateOption (int optionNumber);
      virtual void createWindow (int position, int x, int y, int height, int width);
      //[ASC] Load emember functions
      virtual void load (Screen screen);
      virtual void load (list<Screen*> screens);
      //[ASC] Display member functions
      virtual void display ();
      virtual void display (Component * c);
      virtual void display (GraphicComposite * gc);
      virtual void display (GraphicLeaf * gl);
      virtual void display (DialogBox box);
      virtual void display (Menu menu);
      virtual void display (HMenu menu);
      virtual void display (VMenu menu);
      virtual void display (Text text);
      virtual void display (Input * input);
      virtual void display (Selector selector);
      virtual void display (Calendar calendar);
      virtual void display (Agenda age);
      virtual void display (Table tab);
      virtual void display (Cell c);
      virtual void display (ScrollBar bar);
      virtual void display (Button button);
      //[ASC] Old functions TO BE CLEAN
      virtual void mainMenu (int keybPosition = -1);
      virtual void options (int keybPosition = -1);
      virtual void languages (int keybPosition = -1);
      virtual void video (int keybPosition = -1);
      virtual void gameplay (int position, map<int, int> worldMap);
      //[ASC] Keyboard member functions
      virtual const unsigned char keyboard ();
      void resetKeyboard ();
      const int getKeyboardx ();
      const int getKeyboardy ();
      void setMaxKeyboardx (const int max = 0);
      void setMaxKeyboardy (const int max = 0);
      //[ASC] Menu member functions
      void setSubMenu (const bool active = true);
      const unsigned int getSubmenuVCursor ();
      const unsigned int getSubmenuHCursor ();
      void moveSubmenuVCursor (const bool inc = true);
      void moveSubmenuHCursor (const bool inc = true);
      //[ASC] Pages member functions
      virtual const unsigned int page ();
      virtual void setMaxPage (const unsigned int max = 1);
      void movePage(const bool next = true);
      void movePage(const unsigned int to_page);
      //[ASC] Cursor member functions
      pair<unsigned int, unsigned int> getCursorPosition ();
      void setCursorPosition (pair<unsigned int, unsigned int> p);
      //[ASC] isXX member functions
      const bool isDialog ();
      bool isValid ();
      bool isSubMenu ();
      // [ASC] Events
      void onShortcut (const unsigned char shortcut);
  };

  class NCursesPalette : public ColorPalette {
    protected:
#define EMPTY_PAIR     1
#define WATER_PAIR     2
#define PLAIN_PAIR     3
#define SHARK_PAIR     4
#define FISH_PAIR      5
#define SCREEN         6
#define HMENU          7
#define HMENU_SELECTED 8
#define INPUT          9

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

    public:
      NCursesPalette () {
        start_color();
        init_pair(SCREEN, 7, 4);
        init_pair(HMENU, 0, 7);
        init_pair(HMENU_SELECTED, 0, 2);
        init_pair(INPUT, 2, 0);

        init_pair(EMPTY_PAIR, COLOR_WHITE, COLOR_BLACK);
        init_pair(WATER_PAIR, COLOR_BLUE, COLOR_BLACK);
        init_pair(PLAIN_PAIR, COLOR_GREEN, COLOR_BLACK);
        init_pair(SHARK_PAIR, COLOR_RED, COLOR_BLACK);
        init_pair(FISH_PAIR, COLOR_CYAN, COLOR_BLACK);
      };
      chtype getColorPair (const int pair) {return COLOR_PAIR(pair);};
  };

  /// class NCursesView -
  class NCurses : public View {
    private:
      // Attributes
      //Logger * log = new Logger("NCurses.log"); //=> dependance
      int worldHeight = 1;
      int worldWidth = 1;
      int choice;
      int highlight = 0;
      void drawChar (WINDOW * win, int x, int y, char c, char color);
      const unsigned int bub_max = 15;
      unsigned int bub_nb = 15;
string test = "";
      char second_key = 255;
      vector<WINDOW*> stack; //LIFO
      NCursesPalette * _palette;

    protected:
      bool toClear = true;

      // Operations
    public:
      NCurses ();
      ~NCurses ();
      void init (int height, int width);
      void createWindow (int screen, int x, int y, int height = 2, int width = 10);
      void displayCursorPosition (int keybPosition);
      void end ();
      int getChar ();
      void hello (); // Pour tester l'affichage en cas de soucis
      void validateOption (int optionNumber);
      void clearScreen();
      void initScreen();
      void colorize ();
      void load (Screen screen);
      void display ();
      void display (Component * c) {View::display(c);};
      void display (GraphicComposite * gc) {View::display(gc);};
      void display (GraphicLeaf * gl) {View::display(gl);};
      void display (DialogBox box);
      void display (Menu menu);
      void display (HMenu menu);
      void display (VMenu menu);
      void display (Text text);
      void display (Input * input);
      void display (Selector selector);
      void display (Calendar calendar);
      void display (Agenda age);
      void display (Table tab);
      void display (Cell c);
      void display (ScrollBar bar);
      void display (Button button);
      const unsigned char keyboard ();
      void rect(basic b);
      void tablerow (list<Cell*> lst, list<unsigned int> colssizes, unsigned int x, unsigned int y, const unsigned int cols, Cell * cursor = nullptr, unsigned int mode = 0);
      void free ();
      void setSubMenu (const bool active = true);
  };

};

#endif

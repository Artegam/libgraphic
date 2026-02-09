#include "InputDevices.h"

#include <unistd.h>

using namespace InputDevices;

WINDOW * NCursesKeyboard::_window;
unsigned char NCursesKeyboard::_key;

NCursesKeyboard::NCursesKeyboard (WINDOW * window) {
  onKeyPressed=nullptr;
  _window = window;
  // Enable keyboard for first standart screen
  keypad(_window, true);
  noecho();
  timeout(0);
};

unsigned char NCursesKeyboard::listenChar () {
  return wgetch(_window);
}

unsigned char NCursesKeyboard::listen () { //[ASC] devrait être un pointeur sur fonction genre void* a exécuter...
//[ASC] TODO: Comment utiliser des évènements (pointeurs sur fonctions) ??
  _key = 0x00;
  _key = listenChar();
  execute();
  return _key;
}

void NCursesKeyboard::setEvent (unsigned char key, void (*fct)()) {
  switch(key) {
    case 83:
      onPageUp = fct;
      break;
    case 82:
      onPageDown = fct;
      break;
  }
};

void NCursesKeyboard::execute () {
  if(onKeyPressed != nullptr)
    onKeyPressed(_key);

  switch(_key) {
    case 83:
      onPageUp();
      break;
    case 82:
      onPageDown();
      break;
  }

/*
  switch(_key) {
    case KEYB_UP:
      onKeyboardUp(x, y);
      break;
    case KEYB_DOWN:
      onKeyboardDown(x, y);
      break;
    case KEYB_LEFT:
      onKeyboardLeft(x, y);
      break;
    case KEYB_RIGHT:
      onKeyboardRight(x, y);
      break;
    case KEYB_PAGEUP:
      onKeyboardPageUp(x, y);
      break;
    case KEYB_PAGEDOWN:
      onKeyboardPageDown(x, y);
      break;
    case KEYB_SPACE:
      break;
    case KEYB_ENTER:
      view->valid();
      if(view->isDialog()) {
        string flag = getFlag();
        if(flag == "Aller a..._OK") { // reflechir a comment l associer au composant graphique ?
          Screen * s = data->getScreen();
          GraphicParser p;
          GotoDialogBox * gc = (GotoDialogBox*)p.to_graphicComposite(s->selectedComponent());
          view->movePage(gc->to());
          data->updateScrollBar(view->page());
        } else if(flag == "Ouvrir fichier_Cancel") {
        } else if(flag == "Ouvrir fichier_OK") {
          //[ASC]Ici ouvrir le fichier proposé par la dialogBox
        } else if(flag == "A propos_OK") {
        }
        closeDialogBox();
      }
      break;
    case KEYB_ESCAPE:
      unsigned char second_key = view->keyboard();
      if(second_key >= 97 && second_key <= 122) { // Alt + a..z
        view->onShortcut(second_key);
        view->setSubMenu();
      } else {
        view->setSubMenu(false);
      }
      break;
  }
*/
}

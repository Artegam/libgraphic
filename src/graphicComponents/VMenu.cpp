#include "GraphicComponents.h"

using namespace GraphicComponents;


VMenu::VMenu (const int window, const int x, const int y, list<string> items, const string name) : Menu (window, x, y, items, name) {
}

VMenu::VMenu (const int window, const int x, const int y, list<Text *> items, const string name) : Menu (window, x, y, items, name) {
}

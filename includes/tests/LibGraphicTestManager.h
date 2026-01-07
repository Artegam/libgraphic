#ifndef LIBGRAPHICTESTMANAGER_H
#define LIBGRAPHICTESTMANAGER_H

#include <tests/TestUnit.h>
#include <../GraphicComponents.h>

class LibGraphicTest : public virtual testunit::TestManager {
  public:
    virtual void execute () {};
    virtual int report () {return TestManager::report();};
};

class GraphicComponentTests : public virtual LibGraphicTest {
  public:
    GraphicComponentTests (string name = "GraphicComponentTests") : testunit::TestManager(name) {};
    void execute ();
};

class ScreenTests : public virtual LibGraphicTest {
  public:
    ScreenTests (string name = "ScreenTests") : testunit::TestManager(name) {};
    void execute ();
};

class TextTests : public virtual LibGraphicTest {
  public:
    TextTests (string name = "TextTests") : testunit::TestManager(name) {};
    void execute ();
};

class InputTests : public virtual LibGraphicTest {
  public:
    InputTests (string name = "InputTests") : testunit::TestManager(name) {};
    void execute ();
};

class SelectorTests : public virtual LibGraphicTest {
  public:
    SelectorTests (string name = "SelectorTests") : testunit::TestManager(name) {};
    void execute ();
};

class ScrollbarTests : public virtual LibGraphicTest {
  public:
    ScrollbarTests (string name = "ScrollbarTests") : testunit::TestManager(name) {};
    void execute ();
};

class DialogboxTests : public virtual LibGraphicTest {
  public:
    DialogboxTests (string name = "DialogboxTests") : testunit::TestManager(name) {};
    void execute ();
};

class OpenDialogboxTests : public virtual LibGraphicTest {
  public:
    OpenDialogboxTests (string name = "OpenDialogboxTests") : testunit::TestManager(name) {};
    void execute ();
};

class GotoDialogboxTests : public virtual LibGraphicTest {
  public:
    GotoDialogboxTests (string name = "GotoDialogboxTests") : testunit::TestManager(name) {};
    void execute ();
};

class MenuTests : public virtual LibGraphicTest {
  public:
    MenuTests (string name = "MenuTests") : testunit::TestManager(name) {};
    void execute ();
};

class HMenuTests : public virtual LibGraphicTest {
  public:
    HMenuTests (string name = "HMenuTests") : testunit::TestManager(name) {};
    void execute ();
};

class VMenuTests : public virtual LibGraphicTest {
  public:
    VMenuTests (string name = "VMenuTests") : testunit::TestManager(name) {};
    void execute ();
};

class ButtonTests : public virtual LibGraphicTest {
  public:
    ButtonTests (string name = "ButtonTests") : testunit::TestManager(name) {};
    void execute ();
};

class ImageTests : public virtual LibGraphicTest {
  public:
    ImageTests (string name = "ImageTests") : testunit::TestManager(name) {};
    void execute ();
};

class CellTests : public virtual LibGraphicTest {
  public:
    CellTests (string name = "CellTests") : testunit::TestManager(name) {};
    void execute ();
};

class TableTests : public virtual LibGraphicTest {
  public:
    TableTests (string name = "TableTests") : testunit::TestManager(name) {};
    void execute ();
};

class CalendarTests : public virtual LibGraphicTest {
  public:
    CalendarTests (string name = "CalendarTests") : testunit::TestManager(name) {};
    void execute ();
};

class AgendaTests : public virtual LibGraphicTest {
  public:
    AgendaTests (string name = "AgendaTests") : testunit::TestManager(name) {};
    void execute ();
};

class NodeTests : public virtual LibGraphicTest {
  public:
    NodeTests (string name = "NodeTests") : testunit::TestManager(name) {};
    void execute ();
};

class ItemTests : public virtual LibGraphicTest {
  public:
    ItemTests (string name = "ItemTests") : testunit::TestManager(name) {};
    void execute ();
};

class GroupItemTests : public virtual LibGraphicTest {
  public:
    GroupItemTests (string name = "GroupItemTests") : testunit::TestManager(name) {};
    void execute ();
};

class LibGraphicTestManager : public virtual LibGraphicTest {
  public:
    LibGraphicTestManager (string name = "LibGraphicTestManager") : testunit::TestManager(name) {};
    void execute () {};
};

#endif

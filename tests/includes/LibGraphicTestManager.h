#ifndef LIBGRAPHICTESTMANAGER_H
#define LIBGRAPHICTESTMANAGER_H

#include "TestUnit.h"
#include "GraphicComponents.h"

class LibGraphicTest : public virtual testunit::TestManager {
  public:
    virtual void execute () {};
    virtual int report () {return TestManager::report();};
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

class LibGraphicTestManager : public virtual LibGraphicTest {
  public:
    LibGraphicTestManager (string name = "LibGraphicTestManager") : testunit::TestManager(name) {};
    void execute () {};
};

#endif

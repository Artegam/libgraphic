#ifndef LIBGRAPHICTESTMANAGER_H
#define LIBGRAPHICTESTMANAGER_H

#include "TestUnit.h"
#include "GraphicComponents.h"

class LibGraphicTest : public virtual testunit::TestManager {
  public:
    virtual void execute ();
    virtual int report ();
};

class ScrollbarTests : public virtual LibGraphicTest {
  public:
    ScrollbarTests (string name = "ScrollbarTests");
    void execute ();
    int report ();
};

class DialogboxTests : public virtual LibGraphicTest {
  public:
    DialogboxTests (string name = "DialogboxTests");
    void execute ();
    int report ();
};

class LibGraphicTestManager : public virtual testunit::TestManager {
  public:
    LibGraphicTestManager (string name = "LibGraphicTestManager");
    void execute ();
    int report ();
};

#endif

#ifndef VIEWSTESTMANAGER_H
#define VIEWSTESTMANAGER_H

#include <tests/TestUnit.h>
#include <../Views.h>

class ViewsTest : public virtual testunit::TestManager {
  public:
    virtual void execute () {};
    virtual int report () {return TestManager::report();};
};

class ViewTests : public virtual ViewsTest {
  public:
    ViewTests (string name = "ViewTests") : testunit::TestManager(name) {};
    void execute ();
};

class NCursesPaletteTests : public virtual ViewsTest {
  public:
    NCursesPaletteTests (string name = "NCursesPaletteTests") : testunit::TestManager(name) {};
    void execute ();
};

class NCursesTests : public virtual ViewsTest {
  public:
    NCursesTests (string name = "NCursesTests") : testunit::TestManager(name) {};
    void execute ();
};

#endif

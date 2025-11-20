#ifndef TESTUNIT_H
#define TESTUNIT_H

#include "Composite.h"

#include <string>
#include <list>

using namespace std;

namespace testunit {

  class TestComponent {
    public:
      void assert (bool test, string message);
  };

  class TestUnit : Leaf, TestComponent {
    private:
      unsigned int cpt = 0;
      unsigned int cptSuccess = 0;
      unsigned int cptFailures = 0;
      unsigned int cptUndef = 0;
      const string RED = "\033[1;31m";
      const string GREEN = "\033[1;32m";
      const string NOCOLOR = "\033[0m";
      const string failed = RED + "Failed" + NOCOLOR;
      const string passed = GREEN + "Passed" + NOCOLOR;

    public:
      void assert (bool test, string message);
      int report ();
  };

  class TestManager : Composite, TestComponent {
    private:
    public:
  };
}

#endif

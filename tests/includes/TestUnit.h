#ifndef TESTUNIT_H
#define TESTUNIT_H

#include "Composite.h"

#include <string>
#include <list>

using namespace std;

namespace testunit {

  const string RED = "\033[1;31m";
  const string GREEN = "\033[1;32m";
  const string YELLOW = "\033[1;33m";
  const string NOCOLOR = "\033[0m";
  const string failed = RED + "Failed" + NOCOLOR;
  const string passed = GREEN + "Passed" + NOCOLOR;
  const string undef  = YELLOW + "Undefined" + NOCOLOR;

  class TestComponent {
    public:
      void assert (bool test, string message);
  };

  class TestUnit : Leaf, TestComponent {
    private:
      int _result = -1;
      string _message;

    public:
      void assert (bool test, string message);
      int report ();
      int eval ();
  };

  class TestManager : Composite, TestComponent {
    private:
      unsigned int cpt = 0;
      unsigned int cptSuccess = 0;
      unsigned int cptFailures = 0;
      unsigned int cptUndef = 0;

      list <TestUnit> children;
      void eval ();
    public:
      void add (TestUnit c);
      void remove (TestUnit c);
      list<TestUnit> getChildren ();

      void assert (bool test, string message);
      void execute ();
      int report ();
  };
}

#endif

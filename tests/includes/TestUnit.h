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

  class TestUnit : public virtual Leaf {
    private:
      string _message;

    public:
      void assert (bool test, string message);
      int report ();
  };

  class TestManager : public virtual Composite {
    protected:
      unsigned int cpt = 0;
      unsigned int cptSuccess = 0;
      unsigned int cptFailures = 0;
      unsigned int cptUndef = 0;

      string _name;
    public:
      TestManager (string name = "TestManager");

      void assert (bool test, string message);
      void assert (TestManager* tm);
      virtual void execute ();
      virtual int eval ();
      int report ();
      string name ();
  };
}

#endif

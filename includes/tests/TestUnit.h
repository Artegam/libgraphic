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
      string _got      = "";
      string _expected = "";
      char address[19]; // [ASC] taille + 1 car '\0' est obligatoire en fin de chaine

      template <typename T>
      const char * addressToString(T* addr) {
        const unsigned int addr1 = (unsigned long)&addr;
        const unsigned int addr2 = ((unsigned long)&addr)>>32;
        sprintf(address, "0x%08x%08x", addr2, addr1);
        return address;
      };
      template <typename T>
      void saveParams(T test, T expected) {_got=to_string(test);_expected=to_string(expected);};
      template <typename T>
      void saveParams(T* test, T* expected) {
        _got=addressToString(test);
        _expected=addressToString(expected);
      };
    public:
      //Base expression
      void assert (bool test, const char * message = "");
      template <typename T>
      void assert (T test, T expected, const char * message = "") {
        saveParams(test, expected);
        if(std::is_array<T>::value)
          assert(_expected.compare(_got) == 0, message);
        else
          assert(_expected == _got, message);
      };
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

      void assert (TestManager* tm);
      virtual void execute ();
      virtual int eval ();
      int report ();
      string name ();

      //Base expression
      void assert (bool test, const char * message = "");
      template <typename T>
      void assert (T test, T expected, const char * message = "") {
        cpt++;
        TestUnit* tu = new TestUnit();
        printf("%.3d", cpt);
        tu->assert(test, expected, message);
        add(tu);
        tu = nullptr;
      };
  };
}

#endif

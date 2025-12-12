#include "TestUnit.h"

using namespace testunit;

//TestUnit
void TestUnit::assert (bool test, const char * message) {
  _message = message;
  _result = false;
  if(test)
    _result = true;
  report();
}

int TestUnit::report () {
  if(_message.size() > 40) {//[ASC] Ajouter '...' quand c est tronque
    _message = _message.substr(0, 40);
    _message += "...";
  }
  string firstpart = " - " + _message;
  int sizeRemaining = 50 - firstpart.size();
  string spacer = string(sizeRemaining, ' ');

  string resultString = undef;
  if(_result)
    resultString = passed;
  else if(!_result)
    resultString = failed;

  printf("%s\n", (firstpart+spacer+"["+resultString+"]").c_str());
  if(!_result && _expected != "") {
    printf("%s\n", (YELLOW+"\tgot: \'"+_got+"\'"+NOCOLOR).c_str());
    printf("%s\n", (YELLOW+"\texpected: \'"+_expected+"\'"+NOCOLOR).c_str());
  }
  return 0;
}

//TestManager
TestManager::TestManager (string name) {_name = name;}

void TestManager::assert (bool test, const char * message) {
  cpt++;
  TestUnit* tu = new TestUnit();
  printf("%.3d", cpt);
  tu->assert(test, message);
  add(tu);
  tu = nullptr;
}

void TestManager::assert (TestManager* tm) {
  tm->execute();
  tm->report();
  add(tm);
}

void TestManager::execute () {}

int TestManager::eval () {
  cptSuccess  = 0;
  cptFailures = 0;
  cptUndef    = 0;
  for(list<Component*>::iterator it = children.begin(); it != children.end(); it++)
    switch((*it)->eval()) {
      case true:
        cptSuccess++;
        break;
      case false:
        cptFailures++;
        break;
      default:
        cptUndef++;
    }
  for(list<Component*>::iterator it = children.begin(); it != children.end(); it++)
    if (TestManager* m = dynamic_cast<TestManager*>(*it); m != nullptr)
      assert(m->eval(), m->name().c_str());
  return cptSuccess == cpt;
}

int TestManager::report () {
  eval();
  double rate = ((double)cptSuccess/cpt*100);
  if(cptSuccess == 0 || cpt == 0)
    rate = 0.0;
  printf("**************************************************\n");
  printf("       %s\n", _name.c_str());
  printf("       TESTS REPORT\n\n");
  printf("  %s %d/%d\n", failed.c_str(), cptFailures, cpt);
  printf("  %s %d/%d\n", passed.c_str(), cptSuccess, cpt);
  printf("  Undefined %d/%d\n", cptUndef, cpt);
  printf("\n");
  printf("  TOTAL: %.2f%c\n", rate, '%');
  printf("**************************************************\n");
  _result = (rate == 100.0);
  if (_result)
    return 0;
  else
    return 1;
}

string TestManager::name () {return _name;}

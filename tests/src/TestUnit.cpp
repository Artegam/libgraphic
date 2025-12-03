#include "TestUnit.h"

using namespace testunit;

//TestUnit
void TestUnit::assert (bool test, string message) {
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
  return 0;
}

int TestUnit::eval () {
  return _result;
}

//TestManager - TODO: A ameliorer avec l instruction template ??
TestManager::TestManager (string name) {_name = name;}
void TestManager::execute () {}

void TestManager::assert (bool test, string message) {
  cpt++;
  TestUnit tu;
  printf("%.3d", cpt);
  tu.assert(test, message);
  add(&tu);
}

void TestManager::eval () {
  list<Component*> lst = getChildren();
  cpt = lst.size();
  for(list<Component*>::iterator it = lst.begin(); it != lst.end(); it++) {
    if (TestManager* m = dynamic_cast<TestManager*>(*it); m != nullptr) {
      m->execute();
      m->report();
    }
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
  }
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
  if(rate == 100.0)
    return 0; //Success
  return 1;
}


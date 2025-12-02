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
void TestManager::add (TestUnit c) {children.push_back(c);}
void TestManager::remove (TestUnit c){
  for(list<TestUnit>::iterator it = children.begin(); it != children.end(); it++)
    if(&(*it) == &c)
      children.erase(it);
}
list<TestUnit> TestManager::getChildren () {return children;}

void TestManager::assert (bool test, string message) {
  cpt++;
  TestUnit tu;
  printf("%.3d", cpt);
  tu.assert(test, message);
  add(tu);
}

void TestManager::eval () {
  for(list<TestUnit>::iterator it = children.begin(); it != children.end(); it++) {
    switch(it->eval()) {
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
  printf("**************************************************\n");
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


#include "TestUnit.h"

using namespace testunit;

//TestComponent
void TestComponent::assert (bool test, string message) {}

//TestUnit
void TestUnit::assert (bool test, string message) {
  if(message.size() > 40) {
    message = message.substr(0, 40); //[ASC] Ajouter '...' quand c est tronque ???
    message += "...";
  }
  string result = failed;
  if(test) {
    result = passed;
    cptSuccess++;
  } else if(!test) {
    cptFailures++;
  } else {
    cptUndef++;
  }
  string firstpart = " " + to_string(cpt+1) + " - " + message.c_str(); 
  int sizeRemaining = 50 - firstpart.size();
  string spacer = string(sizeRemaining, ' ');
  printf("%s\n", (firstpart+spacer+"["+result+"]").c_str());
  cpt++;
}

int TestUnit::report () {
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

//TestManager

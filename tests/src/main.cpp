#include <string>
#include <list>

#include <iostream>
#include <unistd.h>

#include "GraphicComponents.h"

using namespace std;

static unsigned int cpt = 0;
static unsigned int cptSuccess = 0;
static unsigned int cptFailures = 0;
static unsigned int cptUndef = 0;
const string RED = "\033[1;31m";
const string GREEN = "\033[1;32m";
const string NOCOLOR = "\033[0m";
const string failed = RED + "Failed" + NOCOLOR;
const string passed = GREEN + "Passed" + NOCOLOR;

void title() {
  cout << "hexdump v1.0 Schricke Anthony (c) 2025" << endl;
}

void error(const char *msg) {
  perror(msg);
  exit(0);
}

/*
void argumentCheck(int argc, char** argv) {
  string prototype = "hexdump [-c|--colors] [-b|--block n] filename";
  if (argc < 2) {
    fprintf(stderr,"ERROR: syntax is\n\t %s\n", prototype.c_str());
    exit(0);
  } else if(argc == 2 && argv[1][0] == '-') {
    fprintf(stderr,"ERROR: syntax is\n\t %s\n", prototype.c_str());
    exit(0);
  } else if(argc >= 3 && argv[1][0] == '-') {
    for(int i = 1; i<(argc-1); i++) {
      string opt = argv[i];
      if(opt == "-c" || opt == "--colors")
        pres.appParam(APP_PARAMS_COLORS, true);
      if(opt == "-a" || opt == "--ascii")
        pres.appParam(APP_PARAMS_ASCII, true);
      if(opt == "-f" || opt == "--find") {
        pres.appParam(APP_PARAMS_RESEARCH, true);
        pres.appParam(APP_PARAMS_TOFIND, argv[i+1]);
        //inv = new Investigator(params.to_find);
        i++;
      }
      if(opt == "-b" || opt == "--block") {
        pres.appParam(APP_PARAMS_BLOCKSIZE, atoi(argv[i+1]));
        i++;
      }
    }
    pres.appParam(APP_PARAMS_FILEPATH, string(argv[argc-1]));
  } else {
    pres.appParam(APP_PARAMS_FILEPATH, string(argv[1]));
  }
}
*/

void assert (bool test, string message) {
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

void report () {
  printf("**************************************************\n");
  printf("       TESTS REPORT\n\n");
  printf("  %s %d/%d\n", failed.c_str(), cptFailures, cpt);
  printf("  %s %d/%d\n", passed.c_str(), cptSuccess, cpt);
  printf("  Undefined %d/%d\n", cptUndef, cpt);
  printf("\n");
  printf("  TOTAL: %.2f%c\n", ((double)cptSuccess/cpt*100), '%');
  printf("**************************************************\n");
}

int main(int argc, char** argv) {
  GraphicComponents::ScrollBar b(0, 8, 5); //screen, position
  GraphicComponents::ScrollBarData data = b.getScrollBar(); // recupere les donnees
  assert(data.unit == 1.0, "Valeur par defaut de unit");
  assert(data.cursor == 1, "Valeur par defaut de cursor");
  assert(data.max == 10, "Valeur par defaut de max");
  b.resize(16, 1, 1760); // hauteur, largeur, nombre de blocks
  b.update(5); // aller au block numero 5
  data = b.getScrollBar(); // recupere les donnees
  assert(data.max == 14, "Calcul de la valeur max");
  assert(data.unit == (double)1/1760, "Calcul de la valeur d'une unite");
  report();
  return 0;
}

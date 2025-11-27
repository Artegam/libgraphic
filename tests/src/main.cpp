#include <string>
#include <list>

#include <iostream>
#include <unistd.h>

#include "ScrollbarTests.h"
#include "DialogboxTests.h"

using namespace std;

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


void scrollbar_tests () {
}

int main(int argc, char** argv) {
  ScrollbarTests tests; //TODO - améliorer ca avec des chapitres
  tests.execute();
  tests.report();
  DialogboxTests tests2;
  tests2.execute();
  tests2.report();
  return tests2.report();
}

CXX := g++
PROJECT := libgraphic.so
TESTS = tests/
INC = includes/
SRC = src/
OUT = o/
BIN = bin/
LIB = lib/
INSTALL_DIR = /lib/x86_64-linux-gnu/
HEADERS_DIR = /usr/include/
TEST_DIR = $(SRC)$(TESTS)

PROJECT_DIRS = $(SRC) $(INC) $(LIB) $(OUT) $(BIN) $(TEST_DIR)

INCLUDES = -I $(INC) # -I $(INC_RENDER) -I $(TESTS)

LIBS = -lncurses
OPT = -Wall -O -g -shared -fPIC
TESTS_OPT = -Wall
OPT_THREAD = -std=c++0x -pthread


SRC_FILES = $(shell if [ -d src/ ]; then find src/ -type f -name '*.cpp' | grep --invert-match tests/; fi)
OBJ_FILES = $(patsubst src/%.cpp, o/%.o, $(SRC_FILES))
TEST_SRC_FILES = $(shell if [ -d src/ ]; then find src/ -type f -name '*.cpp'; fi)
TEST_OBJ_FILES = $(patsubst src/%.cpp, o/%.o, $(TEST_SRC_FILES))

## Pour declarer des targets qui ne sont pas des fichiers
.PHONY: project clean install uninstall install-tools uninstall-tools tests
.SILENT: install uninstall

all: $(PROJECT)

project:
	mkdir --parents $(PROJECT_DIRS)

tests: $(TEST_OBJ_FILES)
	g++ $(TESTS_OPT) $(INCLUDES) $(OPT_THREAD) $^ -o $(BIN)$@ $(LIBS)
	$(BIN)$@ || (echo " Some tests have failed. Compilation exiting.")

$(PROJECT): $(OBJ_FILES)
	g++ $(OPT) $(INCLUDES) $(OPT_THREAD) $^ -o $(LIB)$@ $(LIBS)

o/%.o: src/%.cpp
	@mkdir -p "$(@D)"
	$(CXX) $(OPT) -c $(INCLUDES) $? -o $@

clean:
	rm -r o/;find . -name "*~" | xargs rm -f

install:
	sudo cp $(LIB)$(PROJECT) $(INSTALL_DIR)
	sudo cp $(INC)*.h $(HEADERS_DIR)
	echo "$(PROJECT) installed successfully !"

install-tools:
	sudo apt-get install g++ vim dia dia2code doxygen

uninstall:
	sudo rm -f $(INSTALL_DIR)$(PROJECT)

uninstall-tools:
	sudo apt-get remove g++ vim dia dia2code doxygen
	rm -r o/

include $(DEP_FILES)

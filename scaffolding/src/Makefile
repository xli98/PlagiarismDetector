###################################################
# Makefile for HW8
# Coco Li
# 2016-11-12
#
# files are split between multiple directories.
# Also uses generic rules and more advanced substitutions,
# as well as automatic dependency calculation
#
###################################################

###############################
# path variables
###############################
# where to look for .h files
INC_DIRS = ../include
# where to put .o files
OBJ_DIR = ./obj
# where to put executables
BIN_DIR = ../bin

$(shell mkdir -p $(OBJ_DIR))
$(shell mkdir -p $(BIN_DIR))
###############################
# targets
###############################


$(BIN_DIR)/a8: $(OBJ_DIR)/a8.o $(OBJ_DIR)/NgramCollection.o $(OBJ_DIR)/LanguageModel.o 
	g++ -g -lm $(OBJ_DIR)/a8.o $(OBJ_DIR)/NgramCollection.o $(OBJ_DIR)/LanguageModel.o  -o $(BIN_DIR)/a8

#for unit tests of NgramCollection
$(BIN_DIR)/unitTestNgramCollection: $(OBJ_DIR)/NgramCollection.o $(OBJ_DIR)/unitTests-NgramCollection.o $(OBJ_DIR)/unitTestDriver.o
	 g++ -g -lm $(OBJ_DIR)/unitTests-NgramCollection.o $(OBJ_DIR)/NgramCollection.o $(OBJ_DIR)/unitTestDriver.o  -o $(BIN_DIR)/unitTestNgramCollection

#for unit tests of LanguageModel
$(BIN_DIR)/unitTestLanguageModel: $(OBJ_DIR)/LanguageModel.o $(OBJ_DIR)/unitTests-LanguageModel.o $(OBJ_DIR)/unitTestDriver.o
	 g++ -g -lm $(OBJ_DIR)/unitTests-LanguageModel.o $(OBJ_DIR)/LanguageModel.o $(OBJ_DIR)/unitTestDriver.o  -o $(BIN_DIR)/unitTestLanguageModel

$(OBJ_DIR)/a8.o: a8.cpp
	g++ -std=c++11 -Wall -Wextra -pedantic -g -I../include/ -c a8.cpp -o $(OBJ_DIR)/a8.o

$(OBJ_DIR)/unitTestDriver.o: unitTestDriver.cpp
	g++ -std=c++11 -Wall -Wextra -pedantic -g -I../include/ -c unitTestDriver.cpp -o $(OBJ_DIR)/unitTestDriver.o

$(OBJ_DIR)/NgramCollection.o: NgramCollection.cpp $(INC_DIRS)/NgramCollection.hpp $(INC_DIRS)/LanguageModel.hpp
	g++ -std=c++11 -Wall -Wextra -pedantic -g -I../include/ -c NgramCollection.cpp -o $(OBJ_DIR)/NgramCollection.o

$(OBJ_DIR)/LanguageModel.o: LanguageModel.cpp $(INC_DIRS)/LanguageModel.hpp
	g++ -std=c++11 -Wall -Wextra -pedantic -g -lm -I../include/ -c LanguageModel.cpp -o $(OBJ_DIR)/LanguageModel.o

$(OBJ_DIR)/unitTests-NgramCollection.o: unitTests-NgramCollection.cpp $(INC_DIRS)/catch.hpp $(INC_DIRS)/NgramCollection.hpp
	g++ -std=c++11 -Wall -Wextra -pedantic -g -I../include/ -c unitTests-NgramCollection.cpp -o $(OBJ_DIR)/unitTests-NgramCollection.o

$(OBJ_DIR)/unitTests-LanguageModel.o: unitTests-LanguageModel.cpp $(INC_DIRS)/catch.hpp $(INC_DIRS)/LanguageModel.hpp
	g++ -std=c++11 -Wall -Wextra -pedantic -g -I../include/ -c unitTests-LanguageModel.cpp -o $(OBJ_DIR)/unitTests-LanguageModel.o

$(OBJ_DIR):

###############################
# "utility" rules
###############################
# the .PHONY line says these targets aren't expected to generate files named after the target

.PHONY: clean a8

# "shortcut" target (so we don't have to type the bin dir before our target name)
a8: $(BIN_DIR)/a8
N: $(BIN_DIR)/unitTestNgramCollection
L: $(BIN_DIR)/unitTestLanguageModel

# clean up generated files
clean:
	@echo removing generated files...
	@rm -f $(OBJ_DIR)/*.o

# Compiler options
CC=g++
CFLAGS=-Wall -Werror -ansi -pedantic
LDFLAGS=
SRC_DIR=src
SOURCES=$(SRC_DIR)/token.cpp $(SRC_DIR)/parser.cpp $(SRC_DIR)/tokencomposite.cpp $(SRC_DIR)/main.cpp
DEPS=$(SRC_DIR)/baseshell.h $(SRC_DIR)/parser.h $(SRC_DIR)/token.h $(SRC_DIR)/tokencomposite.h
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=rshell

all: $(OBJECTS)
	mkdir bin
	$(CC) $(OBJECTS) -o bin/$(EXECUTABLE)

.cpp.o: $(DEPS)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf bin
	rm $(SRC_DIR)/*.o
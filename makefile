
TARGET := main
SOURCES := $(wildcard src/*.c) $(wildcard src/DataType/*.c)
OBJECTS := $(subst /src,,$(SOURCES:%.c=build/%.o))

INCLUDE := -Iinclude
LIBPATH :=
LIBS :=

FLAGS := -Wall
CCFLAGS := $(FLAGS) -std=c99
CXXFLAGS := $(FLAGS)

CC := gcc
Cxx := g++

all: createBuild $(OBJECTS)
	$(CC) $(CCFLAGS) $(INCLUDE) $(OBJECTS) -o $(TARGET) $(LIBPATH) $(LIBS)

build/%.o: src/%.c
	$(CC) $(CCFLAGS) $(INCLUDE) -c $< -o $@

.PHONY: clean help

clean:
	rm -fr build
	rm -f $(TARGET)

createBuild:
	mkdir -p build/DataType
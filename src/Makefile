# Makefile for test IMPEDANCE TRANSFORM AND MATCHING BY SMITH CHART	program
PROGRAM = impedance-transform
SOURCES = main.cpp menu.cpp stuble.cpp

# C compiler: gcc
CC = gcc

# Compiler flags
CFLAGS = -Wall -Wextra -Wno-write-strings -std=c++98 -Wpedantic -O2

# Libraries to link
LIBS = -lSDL_bgi -lSDL2 -lm

all: $(PROGRAM)

$(PROGRAM): $(SOURCES)
	$(CC) $(CFLAGS) $(SOURCES) -o $(PROGRAM) $(LIBS)

clean:
	rm -f impedance-transform *.o

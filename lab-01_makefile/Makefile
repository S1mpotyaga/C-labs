.PHONY: all prepare compile link clean

CC=gcc
CFLAGS=-c -Wall -Werror -Wextra
INCLUDES=-Iinclude
EXECUTABLE=lab-01_makefile


CSOURCES=algorithm.c io.c util.c main.c
 

all: prepare compile link

prepare:
	if [ ! -d "obj" ]; then mkdir obj; fi

compile: $(CSOURCES)

$(CSOURCES):
	$(CC) $(CFLAGS) $(INCLUDES) src/$@ -o obj/$@.o

link:
	$(CC) obj/*.o -o $(EXECUTABLE)

clean:
	rm -rf obj/*.o $(EXECUTABLE)

.PHONY: all prepare compile link clean

CC=gcc
CFLAGS=-c -Wall -Werror -Wextra
INCLUDES=-Iinclude
EXECUTABLE=lab-01_makefile
 

all: prepare compile link

prepare:
	if [ ! -d "obj" ]; then mkdir obj; fi

compile: obj/main.o obj/util.o obj/io.o obj/algorithm.o

obj/main.o: src/main.c
	$(CC) $(CFLAGS) $(INCLUDES) src/main.c -o obj/main.o

obj/util.o: src/util.c
	$(CC) $(CFLAGS) $(INCLUDES) src/util.c -o obj/util.o

obj/io.o: src/io.c
	$(CC) $(CFLAGS) $(INCLUDES) src/io.c -o obj/io.o

obj/algorithm.o: src/algorithm.c
	$(CC) $(CFLAGS) $(INCLUDES) src/algorithm.c -o obj/algorithm.o

link:
	$(CC) obj/*.o -o $(EXECUTABLE)

clean:
	rm -rf obj/*.o $(EXECUTABLE)

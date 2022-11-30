.PHONY: all prepare compile link clean

CC = gcc
INCLUDES =-Iinclude
C_FLAGS =-c -Wall -Werror -Wextra 
EXECUTABLE=lab-03_mergesort

all: prepare compile link

prepare:
	if [ ! -d "obj" ]; then mkdir obj; fi

compile: obj/main.o obj/mergesort.o

obj/main.o: src/main.c
	$(CC) $(C_FLAGS) $(INCLUDES) src/main.c -o obj/main.o

obj/mergesort.o: src/mergesort.c
	$(CC) $(C_FLAGS) $(INCLUDES) src/mergesort.c -o obj/mergesort.o
link: $(EXECUTABLE)

$(EXECUTABLE): obj/main.o obj/mergesort.o
	$(CC) obj/*o -o $(EXECUTABLE)

clean:
	rm -rf obj/*.o $(EXECUTABLE)
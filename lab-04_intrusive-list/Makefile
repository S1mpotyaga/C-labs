.PHONY: all prepare compile link clean

CC = gcc
INCLUDES =-Iinclude
C_FLAGS =-c -Wall -Werror -Wextra 
EXECUTABLE=lab-04_intrusive-list

all: prepare compile link

prepare:
	if [ ! -d "obj" ]; then mkdir obj; fi

compile: obj/clist.o obj/main.o

obj/clist.o: src/clist.c
	$(CC) $(C_FLAGS) $(INCLUDES) src/clist.c -o obj/clist.o

obj/main.o: src/main.c
	$(CC) $(C_FLAGS) $(INCLUDES) src/main.c -o obj/main.o

link: $(EXECUTABLE)

$(EXECUTABLE): obj/clist.o obj/main.o
	$(CC) obj/*o -o $(EXECUTABLE)

clean:
	rm -rf obj/*.o $(EXECUTABLE)
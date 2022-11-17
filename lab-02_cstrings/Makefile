.PHONY: all prepare compile link clean

CC = gcc
INCLUDES =-Iinclude
C_FLAGS =-c -Wall -Werror -Wextra 
EXECUTABLE=lab-02_cstrings

all: prepare compile link

prepare:
	if [ ! -d "obj" ]; then mkdir obj; fi

compile: obj/str.o obj/test_str.o obj/test.o

obj/str.o: src/str.c
	$(CC) $(C_FLAGS) $(INCLUDES) src/str.c -o obj/str.o

obj/test_str.o: src/test_str.c
	$(CC) $(C_FLAGS) $(INCLUDES) src/test_str.c -o obj/test_str.o

obj/test.o: src/test.c
	$(CC) $(C_FLAGS) $(INCLUDES) src/test.c -o obj/test.o

link: $(EXECUTABLE)

$(EXECUTABLE): obj/str.o obj/test_str.o obj/test.o
	$(CC) obj/*o -o $(EXECUTABLE)

clean:
	rm -rf obj/*.o $(EXECUTABLE)
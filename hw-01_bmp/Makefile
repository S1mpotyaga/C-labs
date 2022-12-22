.PHONY: all prepare compile link clean

CC = gcc
INCLUDES =-Iinclude
C_FLAGS =-c -Wall -Werror -Wextra 
EXECUTABLE=hw-01_bmp

all: prepare compile link

prepare:
	if [ ! -d "obj" ]; then mkdir obj; fi

compile: obj/bmp.o obj/main.o obj/stego.o

obj/bmp.o: src/bmp.c
	$(CC) $(C_FLAGS) $(INCLUDES) src/bmp.c -o obj/bmp.o

obj/main.o: src/main.c
	$(CC) $(C_FLAGS) $(INCLUDES) src/main.c -o obj/main.o

obj/stego.o: src/stego.c
	$(CC) $(C_FLAGS) $(INCLUDES) src/stego.c -o obj/stego.o

link: $(EXECUTABLE)

$(EXECUTABLE): obj/bmp.o obj/main.o obj/stego.o
	$(CC) obj/*.o -o $(EXECUTABLE)

clean:
	rm -rf obj/*.o $(EXECUTABLE)


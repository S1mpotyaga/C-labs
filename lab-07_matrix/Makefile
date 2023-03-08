.PHONY: all prepare compile link clean

CC = g++ 
INCLUDES =-Iinclude
C_FLAGS =-c -std=gnu++17 -Wall -Werror -Wextra 
EXECUTABLE=lab-07_matrix

all: prepare compile link

prepare:
	if [ ! -d "obj" ]; then mkdir obj; fi

compile: obj/matrix.o obj/main.o

obj/matrix.o: src/matrix.cpp include/matrix.h
	$(CC) $(C_FLAGS) $(INCLUDES) src/matrix.cpp -o obj/matrix.o

obj/main.o: src/main.cpp include/matrix.h
	$(CC) $(C_FLAGS) $(INCLUDES) src/main.cpp -o obj/main.o

link: $(EXECUTABLE)

$(EXECUTABLE): obj/matrix.o obj/main.o
	$(CC) obj/*.o -o $(EXECUTABLE)

clean:
	rm -rf obj/*.o $(EXECUTABLE)
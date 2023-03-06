.PHONY: all prepare compile link clean

CC = g++ 
INCLUDES =-Iinclude
C_FLAGS =-c -std=gnu++17 -Wall -Werror -Wextra 
EXECUTABLE=lab-06_int-vector

all: prepare compile link

prepare:
	if [ ! -d "obj" ]; then mkdir obj; fi

compile: obj/my_vector.o

obj/my_vector.o: src/my_vector.cpp
	$(CC) $(C_FLAGS) $(INCLUDES) src/my_vector.cpp -o obj/my_vector.o

obj/main.o: src/main.cpp
	$(CC) $(C_FLAGS) $(INCLUDES) src/main.cpp -o obj/main.o

link: $(EXECUTABLE)

$(EXECUTABLE): obj/my_vector.o obj/main.o
	$(CC) obj/*.o -o $(EXECUTABLE)

clean:
	rm -rf obj/*.o $(EXECUTABLE)


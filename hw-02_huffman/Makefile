.PHONY: all clean
 
CC=g++
CFLAGS=-std=gnu++17 -c -Wall -Wextra -Werror
INCDIRS=-Iinclude
EXECUTABLE=hw-02_huffman
 
INCS=$(wildcard include/*.h)
SRCS=$(wildcard src/*.cpp)
OBJS=$(patsubst src/%.cpp, obj/%.o, $(SRCS))
 
all: $(EXECUTABLE)
 
obj:
	mkdir obj

obj/%.o: src/%.cpp $(INCS) | obj
	$(CC) $(CFLAGS) $(INCDIRS) $< -o $@

$(EXECUTABLE): $(OBJS)
	$(CC) $(OBJS) -o $(EXECUTABLE)

clean:
	rm -rf obj
	rm $(EXECUTABLE)
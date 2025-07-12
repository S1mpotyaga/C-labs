CC=gcc
INCLUDES=-Iinclude
FLAGS=-c -Wall -Wextra -Werror
BUILD_DIR=obj
SRC_DIR=src
EXECUTABLE=lab-03_mergesort

build: compile
	$(CC) $(BUILD_DIR)/*.o -o $(EXECUTABLE)

compile: $(BUILD_DIR)/mergesort.o $(BUILD_DIR)/main.o

$(BUILD_DIR)/mergesort.o:
	$(CC) $(FLAGS) $(INCLUDES) $(SRC_DIR)/mergesort.c -o $(BUILD_DIR)/mergesort.o

$(BUILD_DIR)/main.o:
	$(CC) $(FLAGS) $(INCLUDES) $(SRC_DIR)/main.c -o $(BUILD_DIR)/main.o

clean:
	rm -rf $(BUILD_DIR)/*.o $(EXECUTABLE)
CC=gcc
BUILD_DIR=obj
SRC_DIR=src
CCFLAGS=-c -Wall -Wextra -Werror
INCLUDES=-Iinclude
EXECUTABLE=lab-01_makefile

build: compile
	$(CC) $(BUILD_DIR)/*.o -o $(EXECUTABLE)

compile: $(BUILD_DIR)/main.o $(BUILD_DIR)/util.o $(BUILD_DIR)/algorithm.o $(BUILD_DIR)/io.o

$(BUILD_DIR)/main.o:
	$(CC) $(CCFLAGS) $(INCLUDES) $(SRC_DIR)/main.c -o $(BUILD_DIR)/main.o

$(BUILD_DIR)/util.o:
	$(CC) $(CCFLAGS) $(INCLUDES) $(SRC_DIR)/util.c -o $(BUILD_DIR)/util.o

$(BUILD_DIR)/algorithm.o:
	$(CC) $(CCFLAGS) $(INCLUDES) $(SRC_DIR)/algorithm.c -o $(BUILD_DIR)/algorithm.o

$(BUILD_DIR)/io.o:
	$(CC) $(CCFLAGS) $(INCLUDES) $(SRC_DIR)/io.c -o $(BUILD_DIR)/io.o

clean: 
	rm -rf $(BUILD_DIR)/*.o $(EXECUTABLE)
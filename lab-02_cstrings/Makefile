CC=gcc
INCLUDES=-Iinclude
FLAGS=-c -Wall -Wextra -Werror
BUILD_DIR=obj
SRC_DIR=src
EXECUTABLE=lab-02_cstrings

build: clean compile
	$(CC) $(BUILD_DIR)/*.o -o $(EXECUTABLE)

compile: $(BUILD_DIR)/test_str.o $(BUILD_DIR)/str.o $(BUILD_DIR)/test.o

$(BUILD_DIR)/test_str.o:
	$(CC) $(FLAGS) $(INCLUDES) $(SRC_DIR)/test_str.c -o $(BUILD_DIR)/test_str.o

$(BUILD_DIR)/str.o:
	$(CC) $(FLAGS) $(INCLUDES) $(SRC_DIR)/str.c -o $(BUILD_DIR)/str.o

$(BUILD_DIR)/test.o:
	$(CC) $(FLAGS) $(INCLUDES) $(SRC_DIR)/test.c -o $(BUILD_DIR)/test.o

clean:
	rm -rf $(BUILD_DIR)/*.o $(EXECUTABLE)
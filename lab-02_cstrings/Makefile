CC=gcc
INCLUDES=-Iinclude
FLAGS=-c -Wall -Wextra -Werror
BUILD_DIR=obj
BUILD_SRC=src
EXECUTABLE=lab-02_cstrings

build: compile
	$(CC) $(BUILD_DIR)/*.o -o $(EXECUTABLE)

compile: $(BUILD_DIR)/*.o

$(BUILD_DIR)/test_str.o:
	$(CC) $(INCLUDES) $(FLAGS) $(BUILD_SRC)/test_str.c -o $(BUILD_DIR)/test_str.o

$(BUILD_DIR)/str.o:
	$(CC) $(INCLUDES) $(FLAGS) $(BUILD_SRC)/str.c -o $(BUILD_DIR)/str.o

$(BUILD_DIR)/test.o:
	$(CC) $(INCLUDES) $(FLAGS) $(BUILD_SRC)/test.c -o $(BUILD_DIR)/test.o

clean:
	rm -rf $(BUILD_DIR)/*.o $(EXECUTABLE)
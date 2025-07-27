.PHONY: all prepare link compile clean

CC = gcc
INCLUDES = -Iinclude
FLAGS = -c -Wall -Wextra -Werror
BUILD_DIR = obj
SRC_DIR = src
EXECUTABLE = lab-05_c-io

all: clean prepare link

prepare:
	@if [ ! -d "obj" ]; then \
		mkdir obj; \
	fi

link: compile
	$(CC) $(BUILD_DIR)/*.o -o $(EXECUTABLE)

compile: $(BUILD_DIR)/clist.o $(BUILD_DIR)/point_list.o $(BUILD_DIR)/main.o

$(BUILD_DIR)/point_list.o:
	$(CC) $(FLAGS) $(INCLUDES) $(SRC_DIR)/point_list.c -o $(BUILD_DIR)/point_list.o

$(BUILD_DIR)/clist.o:
	$(CC) $(FLAGS) $(INCLUDES) $(SRC_DIR)/clist.c -o $(BUILD_DIR)/clist.o

$(BUILD_DIR)/main.o:
	$(CC) $(FLAGS) $(INCLUDES) $(SRC_DIR)/main.c -o $(BUILD_DIR)/main.o

clean:
	rm -rf $(BUILD_DIR)/*.o $(EXECUTABLE)
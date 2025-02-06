CC=gcc
BUILD_DIR=obj
SRC_DIR=src

all: $(BUILD_DIR)/main.o $(BUILD_DIR)/util.o $(BUILD_DIR)/algorithm.o $(BUILD_DIR)/io.o

$(BUILD_DIR)/main.o:
	$(CC) $(SRC_DIR)/main.c -o $(BUILD_DIR)/main.o

$(BUILD_DIR)/util.o:
	$(CC) $(SRC_DIR)/util.c -o $(BUILD_DIR)/util.o

$(BUILD_DIR)/algorithm.o:
	$(CC) $(SRC_DIR)/algorithm.c -o $(BUILD_DIR)/algorithm.o

$(BUILD_DIR)/io.o:
	$(CC) $(SRC_DIR)/io.c -o $(BUILD_DIR)/io.o

clean: 
	rm $(BUILD_DIR)/*.o 
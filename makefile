CC := g++

SRC_DIR := src
BUILD_DIR := build
TARGET_FILE := bin/main

SRC_FILES := $(wildcard $(SRC_DIR)/*.cpp)
OBJ_FILES := $(patsubst $(SRC_DIR)/%.cpp, $(BUILD_DIR)/%.o, $(SRC_FILES))


$(TARGET_FILE): $(OBJ_FILES)
	$(CC) -o $@ $^ $(CFLAGS)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CC) -c $< -o $@

clean:
	rm -f $(OBJ_FILES) $(TARGET_FILE)

.PHONY:
	clean

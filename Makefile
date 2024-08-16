# Compiler
CC = g++

# Source files directory
SRC_DIR = code

# Source files
SRC = $(SRC_DIR)/main.cpp

# Header files directory
INC_DIR = $(SRC_DIR)

# Build directory
BUILD_DIR = build

# Output executable
OUT = $(BUILD_DIR)/stl

# Test source files
TEST_SRC = $(SRC_DIR)/vector_test.cpp  # Replace with your actual test file

# Test output executable
TEST_OUT = $(BUILD_DIR)/vector_test

# Compiler flags
CFLAGS = -I$(INC_DIR) -g

# Default target, this compiles the program
all: $(OUT)

# Compile the program
$(OUT): $(SRC) | $(BUILD_DIR)
	$(CC) $(CFLAGS) $(SRC) -o $(OUT)

# Compile the test suite
$(TEST_OUT): $(TEST_SRC) | $(BUILD_DIR)
	$(CC) $(CFLAGS) $(TEST_SRC) -lgtest -lgtest_main -pthread -o $(TEST_OUT)

# Ensure build directory exists
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# Custom run command
run: $(OUT)
	./$(OUT)

# Run tests
test: $(TEST_OUT)
	./$(TEST_OUT)

# Clean up generated files
clean:
	rm -f $(OUT) $(TEST_OUT)

# Phony targets
.PHONY: all run test clean

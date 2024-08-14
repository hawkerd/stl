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

# Compiler flags (optional)
CFLAGS = -I$(INC_DIR)

# Default target, this compiles the program
all: $(OUT)

# Compile the program
$(OUT): $(SRC) | $(BUILD_DIR)
	$(CC) $(CFLAGS) $(SRC) -o $(OUT)

# Ensure build directory exists
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# Custom run command
run: $(OUT)
	./$(OUT)

# Clean up generated files
clean:
	rm -f $(OUT)

# Phony targets
.PHONY: all run clean

CC := clang
TARGET := atlas

SRC_DIR := src
INC_DIR := include
BUILD_DIR := build
BIN_DIR := bin

CFLAGS := -std=c18 -Wall -Wextra -Wpedantic -I$(INC_DIR)
LDFLAGS :=

# Debug/Release toggle: `make MODE=release`
MODE ?= debug
ifeq ($(MODE),release)
	CFLAGS += -O2 -DNDEBUG
else
	CFLAGS += -g -O0 -DDEBUG
endif

SRCS := $(wildcard $(SRC_DIR)/*.c)
OBJS := $(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/%.o,$(SRCS))
DEPS := $(OBJS:.o=.d)

.PHONY: all clean run compiledb rebuild

all: $(BIN_DIR)/$(TARGET)

$(BIN_DIR)/$(TARGET): $(OBJS) | $(BIN_DIR)
	$(CC) $(OBJS) -o $@ $(LDFLAGS)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -MMD -MP -c $< -o $@

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(BIN_DIR):
	mkdir -p $(BIN_DIR)

-include $(DEPS)

run: all
	./$(BIN_DIR)/$(TARGET)

rebuild: clean all

clean:
	rm -rf $(BUILD_DIR) $(BIN_DIR)

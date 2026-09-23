CC := clang
TARGET := atlas

SRC_DIR := src
INC_DIR := include
BUILD_DIR := build
BIN_DIR := bin

CFLAGS := -std=c2y -Wall -Wextra -Wpedantic -I$(INC_DIR)
LDFLAGS :=

# Debug/Release toggle: `make MODE=release`
MODE ?= debug
ifeq ($(MODE),release)
	CFLAGS += -O2 -DNDEBUG
else
	CFLAGS += -g -O0 -DDEBUG
endif

# Recursive wildcard: finds files matching $2 under $1, including subdirs
rwildcard = $(foreach d,$(wildcard $1*),$(call rwildcard,$d/,$2) $(filter $(subst *,%,$2),$d))

SRCS := $(call rwildcard,$(SRC_DIR)/,*.c)
OBJS := $(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/%.o,$(SRCS))
DEPS := $(OBJS:.o=.d)

.PHONY: all clean run compiledb rebuild

all: $(BIN_DIR)/$(TARGET)

$(BIN_DIR)/$(TARGET): $(OBJS) | $(BIN_DIR)
	$(CC) $(OBJS) -o $@ $(LDFLAGS)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c | $(BUILD_DIR)
	@mkdir -p $(dir $@)
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

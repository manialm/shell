TARGET=shell

CC = gcc

BUILD_DIR := ./build
SRC_DIRS := ./src

SRCS := $(shell find $(SRC_DIRS) -name '*.c')
OBJS := $(SRCS:%=$(BUILD_DIR)/%.o)

INCLUDE_DIR := include/
INCLUDES := -I $(INCLUDE_DIR)
WARNINGS := -Werror -Wall -Wpedantic

FLAGS := $(INCLUDES)
FLAGS += $(WARNINGS)

all: $(BUILD_DIR)/$(TARGET)
	@$(BUILD_DIR)/$(TARGET)

$(BUILD_DIR)/$(TARGET): $(OBJS)
	@$(CC) $(OBJS) -o $@

$(BUILD_DIR)/%.c.o: %.c
	@mkdir -p $(dir $@)
	@$(CC) $(FLAGS) -c $< -o $@

.PHONY: clean
clean:
	/bin/rm -r $(BUILD_DIR)
TARGET = shell

CC = gcc

SUBDIRS := parser
BUILD_DIR := build
SOURCE_DIR := src

SRCS = $(shell find $(SOURCE_DIR)/ -type f -name '*.c')
OBJS = $(SRCS:$(SOURCE_DIR)/%=$(BUILD_DIR)/%.o)

INCLUDE_DIR := include
INCLUDES := -I $(INCLUDE_DIR)
WARNINGS := -Werror -Wall -Wpedantic

CFLAGS := $(INCLUDES)
CFLAGS += $(WARNINGS)
CFLAGS += -g

all: $(BUILD_DIR)/$(TARGET)
	@$(BUILD_DIR)/$(TARGET)

$(BUILD_DIR)/$(TARGET): $(SUBDIRS) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $@

.PHONY: parser
parser:
	$(MAKE) -C $(SOURCE_DIR)/parser

$(BUILD_DIR)/%.c.o: $(SOURCE_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: clean
clean: clean-subdirs
	rm -r $(BUILD_DIR)

clean-subdirs:
	make -C $(SOURCE_DIR)/parser clean


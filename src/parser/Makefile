CC = gcc

BUILD_DIR := ../../build/parser
INCLUDE_DIR := ../../include

SRCS := $(wildcard *.c)
OBJS := $(SRCS:%=$(BUILD_DIR)/%.o)

INCLUDES := -I $(INCLUDE_DIR)
CFLAGS := $(INCLUDES)
CFLAGS += -g

LEXER_TARGETS := $(INCLUDE_DIR)/parser/Lexer.h Lexer.c
PARSER_TARGETS := $(INCLUDE_DIR)/parser/Parser.h Parser.c

all: Lexer.c Parser.c $(OBJS)

Lexer.c: Lexer.l
	@flex --header-file=$(INCLUDE_DIR)/parser/Lexer.h -o Lexer.c Lexer.l

Parser.c: Parser.y Lexer.c
	@bison --header=$(INCLUDE_DIR)/parser/Parser.h -o Parser.c Parser.y

$(BUILD_DIR)/%.c.o: %.c
	@mkdir -p $(dir $@)
	@$(CC) -c $(CFLAGS) $< -o $@

clean:
	@rm -rf $(LEXER_TARGETS) $(PARSER_TARGETS) $(BUILD_DIR)
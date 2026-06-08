CC = gcc
AR = ar

CFLAGS = -Wall -Wextra -g -Iinclude

BUILD_DIR = build

LIB_NAME = parser
LIB_FILE = $(BUILD_DIR)/lib$(LIB_NAME).a

SRC = src/parser.c
OBJ = $(BUILD_DIR)/parser.o

all: lib

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(OBJ): $(SRC) include/parser.h | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $(SRC) -o $(OBJ)

lib: $(LIB_FILE)

$(LIB_FILE): $(OBJ)
	$(AR) rcs $(LIB_FILE) $(OBJ)

ifneq ($(filter example run,$(MAKECMDGOALS)),)
ifndef EXAMPLE
$(error Missing EXAMPLE. Use: make example EXAMPLE=hello)
endif
endif

EXAMPLE_SRC = examples/$(EXAMPLE).c
EXAMPLE_BIN = $(BUILD_DIR)/examples/$(EXAMPLE)

example: $(EXAMPLE_BIN)

$(EXAMPLE_BIN): $(EXAMPLE_SRC) $(LIB_FILE) | $(BUILD_DIR)
	mkdir -p $(BUILD_DIR)/examples
	$(CC) $(CFLAGS) $(EXAMPLE_SRC) -L$(BUILD_DIR) -l$(LIB_NAME) -o $(EXAMPLE_BIN)

run: $(EXAMPLE_BIN)
	./$(EXAMPLE_BIN)

clean:
	rm -rf $(BUILD_DIR)


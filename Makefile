CC = gcc
CFLAGS = -Iinclude
LIBS = -lncurses
SRC_DIR = src
OBJ_DIR = build
DEPS = include/snake.h include/food.h include/game_screen.h include/pos.h
SRC = $(wildcard $(SRC_DIR)/*.c)
OBJ = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC))

# Pattern rule for compiling .o files from .c files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

# Rule to link the object files into the final executable
snake: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

# Clean rule to remove compiled files
.PHONY: clean
clean:
	rm -f $(OBJ_DIR)/*.o snake && rm -rf $(OBJ_DIR)

# Ensure OBJ_DIR exists
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)
# Build all object files
all: $(OBJ_DIR) $(OBJ) snake


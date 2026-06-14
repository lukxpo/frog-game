CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -Iinclude
LDFLAGS = -lraylib -lm -ldl -lpthread -lrt -lX11

SRC = $(wildcard src/*.c)
OBJ = $(SRC:.c=.o)

TARGET = build/game

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(OBJ) -o $(TARGET) $(LDFLAGS)

src/%.o: src/%.c
	$(CC) $(CFLAGS) -c $< -o $@

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f src/*.o $(TARGET)

.PHONY: all run clean
CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -Iinclude
LDFLAGS = -lraylib -lm -ldl -lpthread -lrt -lX11

SRC = $(wildcard src/*.c)
OBJ = $(SRC:.c=.o)

TARGET = build/game

# --- Emscripten Configuration for Web ---
EMSCRIPTEN_PATH = /home/lucas/emsdk
RAYLIB_WEB_PATH = /home/lucas/raylib/src
EMCC = emcc
EMFLAGS = -s USE_GLFW=3 \
          -s ASYNCIFY \
          --shell-file shell.html \
          --preload-file assets \
          -DPLATFORM_WEB \
          -Os -Wall \
          -I$(RAYLIB_WEB_PATH) \
          -I./src

# Default target (Linux desktop)
all: $(TARGET)

# Standard desktop compilation
$(TARGET): $(OBJ)
	$(CC) $(OBJ) -o $(TARGET) $(LDFLAGS)

src/%.o: src/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# Native quick testing
run: $(TARGET)
	./$(TARGET)

# --- New Web Build Target ---
web:
	@echo "Building for the Web..."
	mkdir -p build
	$(EMCC) -o build/index.html $(SRC) $(RAYLIB_WEB_PATH)/libraylib.web.a $(EMFLAGS)
	@echo "Packaging for itch.io..."
	# Move into the build folder, zip everything EXCEPT the desktop binary and other zips
	cd build && zip -r frog-web-build.zip . -x "game" "*.zip"
	@echo "Web build finished! Complete package is at build/frog-web-build.zip"

# Cleanup everything
clean:
	rm -f src/*.o $(TARGET)
	rm -f build/index.html build/game.js build/game.wasm build/game.data build/frog-web-build.zip

.PHONY: all run clean web
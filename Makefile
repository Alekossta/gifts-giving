# Compiler and flags
CXX = g++
EMCC = emcc
CXXFLAGS = -std=c++17 -Wall -Iinclude

# Libraries
LIBS = -lSDL2 -lSDL2_image -lSDL2_ttf -lm
EMCC_LIBS = -s USE_SDL=2 -s USE_SDL_IMAGE=2 -s SDL2_IMAGE_FORMATS='["png"]' -s USE_SDL_TTF=2 --preload-file assets -s WASM=1

# Folders
SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin

# Source files and object files
SRCS = $(wildcard $(SRC_DIR)/**/*.cpp) $(wildcard $(SRC_DIR)/*.cpp)
OBJS = $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SRCS))

# Output binaries
NATIVE_TARGET = $(BIN_DIR)/main
WEB_TARGET = $(BIN_DIR)/main.html

# Default rule
all: local

# Local native build
local: $(NATIVE_TARGET)

$(NATIVE_TARGET): $(OBJS)
	@mkdir -p $(BIN_DIR)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LIBS)

# Compile source files to object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Web build
web: $(WEB_TARGET)

$(WEB_TARGET): $(SRCS)
	@mkdir -p $(BIN_DIR)
	$(EMCC) $(CXXFLAGS) $(EMCC_LIBS) $^ -o $(BIN_DIR)/main.html
	@mv $(BIN_DIR)/main.html $(BIN_DIR)/index.html

# Clean up
clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)

# Phony targets
.PHONY: all clean local web run

# Run locally
run: local
	@echo "Running program..."
	@$(NATIVE_TARGET)

# Run web build on a local server
run-web: web
	@echo "Starting Python HTTP server..."
	@python3 -m http.server --directory $(BIN_DIR) 8080
# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++11 -I../inc -Wall -Wextra -O2 -DTEST_MODE

# SFML, Boost, and tinyxml2 settings
SFML_LIBS = -lsfml-graphics -lsfml-window -lsfml-system
BOOST_LIBS = -lboost_filesystem -lboost_system
TINYXML2_LIBS = -ltinyxml2

# Directories
SRC_DIR = ../src
INC_DIR = ../inc
OBJ_DIR = ./obj
BUILD_DIR = ./build
TEST_DIR = .

# Source files
MAP_SRC = $(SRC_DIR)/Map.cpp
STATE_SRC = $(SRC_DIR)/State.cpp
TEXTURE_ATLAS_SRC = $(TEST_DIR)/TextureAtlasParser.cpp
CHARACTER_TEXTURE_SRC = $(TEST_DIR)/TestCharacterTexture.cpp
SPRITE_LOADER_SRC = $(SRC_DIR)/SpriteLoader.cpp
SPRITE_LOADER_TEST_SRC = $(TEST_DIR)/SpriteLoaderTest.cpp

# Object files (store in OBJ_DIR)
MAP_OBJ = $(OBJ_DIR)/Map.o
STATE_OBJ = $(OBJ_DIR)/State.o
TEXTURE_ATLAS_OBJ = $(OBJ_DIR)/TextureAtlasParser.o
CHARACTER_TEXTURE_OBJ = $(OBJ_DIR)/TestCharacterTexture.o
SPRITE_LOADER_OBJ = $(OBJ_DIR)/SpriteLoader.o
SPRITE_LOADER_TEST_OBJ = $(OBJ_DIR)/SpriteLoaderTest.o

# Test source files
TEST_MAP_SRC = $(TEST_DIR)/TestMap.cpp
TEST_TEXTURE_ATLAS_SRC = $(TEST_DIR)/TestTextureAtlasParser.cpp

# Test object files (store in OBJ_DIR)
TEST_MAP_OBJ = $(OBJ_DIR)/TestMap.o
TEST_TEXTURE_ATLAS_OBJ = $(OBJ_DIR)/TestTextureAtlasParser.o

# Executables (store in BUILD_DIR)
EXEC_MAP = $(BUILD_DIR)/TestMap
EXEC_TEXTURE_ATLAS = $(BUILD_DIR)/TestTextureAtlasParser
EXEC_CHARACTER_TEXTURE = $(BUILD_DIR)/TestCharacterTexture
EXEC_SPRITE_LOADER_TEST = $(BUILD_DIR)/SpriteLoaderTest

# Targets
all: $(EXEC_MAP) $(EXEC_TEXTURE_ATLAS) $(EXEC_CHARACTER_TEXTURE) $(EXEC_SPRITE_LOADER_TEST)
	@echo "All targets have been compiled."

map: $(EXEC_MAP)
	@echo "Map test executable has been compiled."

texture-atlas: $(EXEC_TEXTURE_ATLAS)
	@echo "TextureAtlas test executable has been compiled."

character-texture: $(EXEC_CHARACTER_TEXTURE)
	@echo "TestCharacterTexture test executable has been compiled."

sprite-loader-test: $(EXEC_SPRITE_LOADER_TEST)
	@echo "SpriteLoaderTest executable has been compiled."

# Rule to build Map and State object files
$(MAP_OBJ): $(MAP_SRC) $(INC_DIR)/Map.h $(INC_DIR)/State.h | $(OBJ_DIR)
	@echo "Compiling Map..."
	$(CXX) $(CXXFLAGS) -c $(MAP_SRC) -o $(MAP_OBJ)

$(STATE_OBJ): $(STATE_SRC) $(INC_DIR)/State.h | $(OBJ_DIR)
	@echo "Compiling State..."
	$(CXX) $(CXXFLAGS) -c $(STATE_SRC) -o $(STATE_OBJ)

# Rule to build TextureAtlasParser object file
$(TEXTURE_ATLAS_OBJ): $(TEXTURE_ATLAS_SRC) $(INC_DIR)/TextureAtlasParser.h | $(OBJ_DIR)
	@echo "Compiling TextureAtlasParser..."
	$(CXX) $(CXXFLAGS) -c $(TEXTURE_ATLAS_SRC) -o $(TEXTURE_ATLAS_OBJ)

# Rule to build TestCharacterTexture object file
$(CHARACTER_TEXTURE_OBJ): $(CHARACTER_TEXTURE_SRC) | $(OBJ_DIR)
	@echo "Compiling TestCharacterTexture..."
	$(CXX) $(CXXFLAGS) -c $(CHARACTER_TEXTURE_SRC) -o $(CHARACTER_TEXTURE_OBJ)

# Rule to build SpriteLoader object file
$(SPRITE_LOADER_OBJ): $(SPRITE_LOADER_SRC) $(INC_DIR)/SpriteLoader.h | $(OBJ_DIR)
	@echo "Compiling SpriteLoader..."
	$(CXX) $(CXXFLAGS) -c $(SPRITE_LOADER_SRC) -o $(SPRITE_LOADER_OBJ)

# Rule to build SpriteLoaderTest object file
$(SPRITE_LOADER_TEST_OBJ): $(SPRITE_LOADER_TEST_SRC) | $(OBJ_DIR)
	@echo "Compiling SpriteLoaderTest..."
	$(CXX) $(CXXFLAGS) -c $(SPRITE_LOADER_TEST_SRC) -o $(SPRITE_LOADER_TEST_OBJ)

# Rule to build Map test executable
$(EXEC_MAP): $(TEST_MAP_OBJ) $(MAP_OBJ) $(STATE_OBJ) $(SPRITE_LOADER_OBJ) | $(BUILD_DIR)
	@echo "Linking Map test executable..."
	$(CXX) $(CXXFLAGS) -o $@ $(TEST_MAP_OBJ) $(MAP_OBJ) $(STATE_OBJ) $(SPRITE_LOADER_OBJ) $(SFML_LIBS) $(BOOST_LIBS) $(TINYXML2_LIBS)

# Rule to build TextureAtlas test executable
$(EXEC_TEXTURE_ATLAS): $(TEST_TEXTURE_ATLAS_OBJ) $(TEXTURE_ATLAS_OBJ) | $(BUILD_DIR)
	@echo "Linking TextureAtlas test executable..."
	$(CXX) $(CXXFLAGS) -o $@ $(TEST_TEXTURE_ATLAS_OBJ) $(TEXTURE_ATLAS_OBJ) $(SFML_LIBS) $(BOOST_LIBS) $(TINYXML2_LIBS)

# Rule to build TestCharacterTexture test executable
$(EXEC_CHARACTER_TEXTURE): $(TEST_CHARACTER_TEXTURE_OBJ) $(CHARACTER_TEXTURE_OBJ) $(MAP_OBJ) $(STATE_OBJ) $(TEXTURE_ATLAS_OBJ) $(SPRITE_LOADER_OBJ) | $(BUILD_DIR)
	@echo "Linking TestCharacterTexture test executable..."
	$(CXX) $(CXXFLAGS) -o $@ $(TEST_CHARACTER_TEXTURE_OBJ) $(CHARACTER_TEXTURE_OBJ) $(MAP_OBJ) $(STATE_OBJ) $(TEXTURE_ATLAS_OBJ) $(SPRITE_LOADER_OBJ) $(SFML_LIBS) $(BOOST_LIBS) $(TINYXML2_LIBS)

# Rule to build SpriteLoaderTest executable
$(EXEC_SPRITE_LOADER_TEST): $(SPRITE_LOADER_TEST_OBJ) $(SPRITE_LOADER_OBJ) | $(BUILD_DIR)
	@echo "Linking SpriteLoaderTest executable..."
	$(CXX) $(CXXFLAGS) -o $@ $(SPRITE_LOADER_TEST_OBJ) $(SPRITE_LOADER_OBJ) $(SFML_LIBS) $(BOOST_LIBS) $(TINYXML2_LIBS)

# Rule to build TestMap object file
$(TEST_MAP_OBJ): $(TEST_MAP_SRC) $(INC_DIR)/Map.h $(INC_DIR)/State.h | $(OBJ_DIR)
	@echo "Compiling TestMap..."
	$(CXX) $(CXXFLAGS) -c $(TEST_MAP_SRC) -o $(TEST_MAP_OBJ)

# Rule to build TestTextureAtlasParser object file
$(TEST_TEXTURE_ATLAS_OBJ): $(TEST_TEXTURE_ATLAS_SRC) $(INC_DIR)/TextureAtlasParser.h | $(OBJ_DIR)
	@echo "Compiling TestTextureAtlasParser..."
	$(CXX) $(CXXFLAGS) -c $(TEST_TEXTURE_ATLAS_SRC) -o $(TEST_TEXTURE_ATLAS_OBJ)

# Create obj and build directories if they don't exist
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# Clean up generated files
clean:
	@echo "Cleaning up generated files..."
	rm -f $(BUILD_DIR)/* $(OBJ_DIR)/*.o

# Run the Map test executable
run-map: $(EXEC_MAP)
	@echo "Running Map test executable..."
	./$(EXEC_MAP)

# Run the TextureAtlas test executable
run-texture-atlas: $(EXEC_TEXTURE_ATLAS)
	@echo "Running TextureAtlas test executable..."
	./$(EXEC_TEXTURE_ATLAS)

# Run the TestCharacterTexture test executable
run-character-texture: $(EXEC_CHARACTER_TEXTURE)
	@echo "Running TestCharacterTexture test executable..."
	./$(EXEC_CHARACTER_TEXTURE)

# Run the SpriteLoaderTest executable
run-sprite-loader-test: $(EXEC_SPRITE_LOADER_TEST)
	@echo "Running SpriteLoaderTest executable..."
	./$(EXEC_SPRITE_LOADER_TEST)

.PHONY: all map texture-atlas character-texture sprite-loader-test clean run-map run-texture-atlas run-character-texture run-sprite-loader-test

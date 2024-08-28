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
GENERATE_LEVEL_SRC = $(SRC_DIR)/GenerateLevel.cpp
TEST_GENERATE_LEVEL_SRC = $(TEST_DIR)/TestGenerateLevel.cpp

# Object files (store in OBJ_DIR)
MAP_OBJ = $(OBJ_DIR)/Map.o
STATE_OBJ = $(OBJ_DIR)/State.o
TEXTURE_ATLAS_OBJ = $(OBJ_DIR)/TextureAtlasParser.o
CHARACTER_TEXTURE_OBJ = $(OBJ_DIR)/TestCharacterTexture.o
SPRITE_LOADER_OBJ = $(OBJ_DIR)/SpriteLoader.o
GENERATE_LEVEL_OBJ = $(OBJ_DIR)/GenerateLevel.o
TEST_GENERATE_LEVEL_OBJ = $(OBJ_DIR)/TestGenerateLevel.o

# Executables (store in BUILD_DIR)
EXEC_MAP = $(BUILD_DIR)/TestMap
EXEC_TEXTURE_ATLAS = $(BUILD_DIR)/TestTextureAtlasParser
EXEC_CHARACTER_TEXTURE = $(BUILD_DIR)/TestCharacterTexture
EXEC_SPRITE_LOADER_TEST = $(BUILD_DIR)/SpriteLoaderTest
EXEC_GENERATE_LEVEL = $(BUILD_DIR)/TestGenerateLevel

# Targets
all: $(EXEC_MAP) $(EXEC_TEXTURE_ATLAS) $(EXEC_CHARACTER_TEXTURE) $(EXEC_SPRITE_LOADER_TEST) $(EXEC_GENERATE_LEVEL)
	@echo "All targets have been compiled."

map: $(EXEC_MAP)
	@echo "Map test executable has been compiled."

texture-atlas: $(EXEC_TEXTURE_ATLAS)
	@echo "TextureAtlas test executable has been compiled."

character-texture: $(EXEC_CHARACTER_TEXTURE)
	@echo "TestCharacterTexture test executable has been compiled."

sprite-loader-test: $(EXEC_SPRITE_LOADER_TEST)
	@echo "SpriteLoaderTest executable has been compiled."

generate-level: $(EXEC_GENERATE_LEVEL)
	@echo "TestGenerateLevel executable has been compiled."

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

# Rule to build GenerateLevel object file
$(GENERATE_LEVEL_OBJ): $(GENERATE_LEVEL_SRC) $(INC_DIR)/GenerateLevel.h | $(OBJ_DIR)
	@echo "Compiling GenerateLevel..."
	$(CXX) $(CXXFLAGS) -c $(GENERATE_LEVEL_SRC) -o $(GENERATE_LEVEL_OBJ)

# Rule to build TestGenerateLevel object file
$(TEST_GENERATE_LEVEL_OBJ): $(TEST_GENERATE_LEVEL_SRC) | $(OBJ_DIR)
	@echo "Compiling TestGenerateLevel..."
	$(CXX) $(CXXFLAGS) -c $(TEST_GENERATE_LEVEL_SRC) -o $(TEST_GENERATE_LEVEL_OBJ)

# Rule to build Map test executable
$(EXEC_MAP): $(OBJ_DIR)/TestMap.o $(MAP_OBJ) $(STATE_OBJ) $(SPRITE_LOADER_OBJ) | $(BUILD_DIR)
	@echo "Linking Map test executable..."
	$(CXX) $(CXXFLAGS) -o $@ $^ $(SFML_LIBS) $(BOOST_LIBS) $(TINYXML2_LIBS)

# Rule to build TextureAtlas test executable
$(EXEC_TEXTURE_ATLAS): $(OBJ_DIR)/TestTextureAtlasParser.o $(TEXTURE_ATLAS_OBJ) | $(BUILD_DIR)
	@echo "Linking TextureAtlas test executable..."
	$(CXX) $(CXXFLAGS) -o $@ $^ $(SFML_LIBS) $(BOOST_LIBS) $(TINYXML2_LIBS)

# Rule to build TestCharacterTexture test executable
$(EXEC_CHARACTER_TEXTURE): $(OBJ_DIR)/TestCharacterTexture.o $(CHARACTER_TEXTURE_OBJ) $(MAP_OBJ) $(STATE_OBJ) $(TEXTURE_ATLAS_OBJ) $(SPRITE_LOADER_OBJ) | $(BUILD_DIR)
	@echo "Linking TestCharacterTexture test executable..."
	$(CXX) $(CXXFLAGS) -o $@ $^ $(SFML_LIBS) $(BOOST_LIBS) $(TINYXML2_LIBS)

# Rule to build SpriteLoaderTest executable
$(EXEC_SPRITE_LOADER_TEST): $(OBJ_DIR)/SpriteLoaderTest.o $(SPRITE_LOADER_OBJ) | $(BUILD_DIR)
	@echo "Linking SpriteLoaderTest executable..."
	$(CXX) $(CXXFLAGS) -o $@ $^ $(SFML_LIBS) $(BOOST_LIBS) $(TINYXML2_LIBS)

# Rule to build TestGenerateLevel executable
$(EXEC_GENERATE_LEVEL): $(TEST_GENERATE_LEVEL_OBJ) $(GENERATE_LEVEL_OBJ) | $(BUILD_DIR)
	@echo "Linking TestGenerateLevel executable..."
	$(CXX) $(CXXFLAGS) -o $@ $^ $(SFML_LIBS) $(BOOST_LIBS) $(TINYXML2_LIBS)

# Rule to build TestMap object file
$(OBJ_DIR)/TestMap.o: $(TEST_DIR)/TestMap.cpp $(INC_DIR)/Map.h $(INC_DIR)/State.h | $(OBJ_DIR)
	@echo "Compiling TestMap..."
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Rule to build TestTextureAtlasParser object file
$(OBJ_DIR)/TestTextureAtlasParser.o: $(TEST_DIR)/TestTextureAtlasParser.cpp $(INC_DIR)/TextureAtlasParser.h | $(OBJ_DIR)
	@echo "Compiling TestTextureAtlasParser..."
	$(CXX) $(CXXFLAGS) -c $< -o $@

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

# Run the TestGenerateLevel executable
run-generate-level: $(EXEC_GENERATE_LEVEL)
	@echo "Running TestGenerateLevel executable..."
	./$(EXEC_GENERATE_LEVEL)

.PHONY: all map texture-atlas character-texture sprite-loader-test generate-level clean run-map run-texture-atlas run-character-texture run-sprite-loader-test run-generate-level

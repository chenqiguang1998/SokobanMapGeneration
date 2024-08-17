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
TEST_DIR = .

# Source files
MAP_SRC = $(SRC_DIR)/Map.cpp
STATE_SRC = $(SRC_DIR)/State.cpp
TEXTURE_ATLAS_SRC = $(SRC_DIR)/TextureAtlasParser.cpp

# Object files
MAP_OBJ = $(MAP_SRC:.cpp=.o)
STATE_OBJ = $(STATE_SRC:.cpp=.o)
TEXTURE_ATLAS_OBJ = $(TEXTURE_ATLAS_SRC:.cpp=.o)

# Test source files
TEST_MAP_SRC = $(TEST_DIR)/TestMap.cpp
TEST_TEXTURE_ATLAS_SRC = $(TEST_DIR)/TestTextureAtlasParser.cpp

# Test object files
TEST_MAP_OBJ = $(TEST_MAP_SRC:.cpp=.o)
TEST_TEXTURE_ATLAS_OBJ = $(TEST_TEXTURE_ATLAS_SRC:.cpp=.o)

# Executables
EXEC_MAP = TestMap
EXEC_TEXTURE_ATLAS = TestTextureAtlasParser

# Targets
all: $(EXEC_MAP) $(EXEC_TEXTURE_ATLAS)
	@echo "All targets have been compiled."

map: $(EXEC_MAP)
	@echo "Map test executable has been compiled."

texture-atlas: $(EXEC_TEXTURE_ATLAS)
	@echo "TextureAtlas test executable has been compiled."

# Rule to build Map and State object files
$(MAP_OBJ): $(MAP_SRC) $(INC_DIR)/Map.h $(INC_DIR)/State.h
	@echo "Compiling Map..."
	$(CXX) $(CXXFLAGS) -c $(MAP_SRC) -o $(MAP_OBJ)

$(STATE_OBJ): $(STATE_SRC) $(INC_DIR)/State.h
	@echo "Compiling State..."
	$(CXX) $(CXXFLAGS) -c $(STATE_SRC) -o $(STATE_OBJ)

# Rule to build TextureAtlasParser object file
$(TEXTURE_ATLAS_OBJ): $(TEXTURE_ATLAS_SRC) $(INC_DIR)/TextureAtlasParser.h
	@echo "Compiling TextureAtlasParser..."
	$(CXX) $(CXXFLAGS) -c $(TEXTURE_ATLAS_SRC) -o $(TEXTURE_ATLAS_OBJ)

# Rule to build Map test executable
$(EXEC_MAP): $(TEST_MAP_OBJ) $(MAP_OBJ) $(STATE_OBJ)
	@echo "Linking Map test executable..."
	$(CXX) $(CXXFLAGS) -o $@ $(TEST_MAP_OBJ) $(MAP_OBJ) $(STATE_OBJ) $(SFML_LIBS) $(BOOST_LIBS) $(TINYXML2_LIBS)

# Rule to build TextureAtlas test executable
$(EXEC_TEXTURE_ATLAS): $(TEST_TEXTURE_ATLAS_OBJ) $(TEXTURE_ATLAS_OBJ)
	@echo "Linking TextureAtlas test executable..."
	$(CXX) $(CXXFLAGS) -o $@ $(TEST_TEXTURE_ATLAS_OBJ) $(TEXTURE_ATLAS_OBJ) $(SFML_LIBS) $(BOOST_LIBS) $(TINYXML2_LIBS)

# Rule to build TestMap object file
$(TEST_MAP_OBJ): $(TEST_MAP_SRC) $(INC_DIR)/Map.h $(INC_DIR)/State.h
	@echo "Compiling TestMap..."
	$(CXX) $(CXXFLAGS) -c $(TEST_MAP_SRC) -o $(TEST_MAP_OBJ)

# Rule to build TestTextureAtlasParser object file
$(TEST_TEXTURE_ATLAS_OBJ): $(TEST_TEXTURE_ATLAS_SRC) $(INC_DIR)/TextureAtlasParser.h
	@echo "Compiling TestTextureAtlasParser..."
	$(CXX) $(CXXFLAGS) -c $(TEST_TEXTURE_ATLAS_SRC) -o $(TEST_TEXTURE_ATLAS_OBJ)

# Clean up generated files
clean:
	@echo "Cleaning up generated files..."
	rm -f $(EXEC_MAP) $(EXEC_TEXTURE_ATLAS) $(TEST_MAP_OBJ) $(TEST_TEXTURE_ATLAS_OBJ) $(MAP_OBJ) $(STATE_OBJ) $(TEXTURE_ATLAS_OBJ) $(SRC_DIR)/*.o

# Run the Map test executable
run-map: $(EXEC_MAP)
	@echo "Running Map test executable..."
	./$(EXEC_MAP)

# Run the TextureAtlas test executable
run-texture-atlas: $(EXEC_TEXTURE_ATLAS)
	@echo "Running TextureAtlas test executable..."
	./$(EXEC_TEXTURE_ATLAS)

.PHONY: all map texture-atlas clean run-map run-texture-atlas

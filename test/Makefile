# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++11 -I../inc -Wall -Wextra -O2  -DTEST_MODE

# SFML, Boost, and tinyxml2 settings
SFML_LIBS = -lsfml-graphics -lsfml-window -lsfml-system
BOOST_LIBS = -lboost_filesystem -lboost_system
TINYXML2_LIBS = -ltinyxml2

# Directories
SRC_DIR = ../src
INC_DIR = ../inc
TEST_DIR = .

# Files
ATLAS_SRC = $(SRC_DIR)/TextureAtlasParser.cpp
ATLAS_OBJ = $(ATLAS_SRC:.cpp=.o)

TEST_SRC = $(TEST_DIR)/TestTextureAtlasParser.cpp
TEST_OBJ = $(TEST_SRC:.cpp=.o)
EXEC = TestTextureAtlasParser

# Targets
all: $(EXEC)

# Rule to build TextureAtlasParser object
$(ATLAS_OBJ): $(ATLAS_SRC) $(INC_DIR)/TextureAtlasParser.h
	$(CXX) $(CXXFLAGS) -c $(ATLAS_SRC) -o $(ATLAS_OBJ)

# Rule to build the final executable
$(EXEC): $(TEST_OBJ) $(ATLAS_OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $(TEST_OBJ) $(ATLAS_OBJ) $(SFML_LIBS) $(BOOST_LIBS) $(TINYXML2_LIBS)

# Rule to build TestTextureAtlasParser object
$(TEST_OBJ): $(TEST_SRC) $(INC_DIR)/TextureAtlasParser.h
	$(CXX) $(CXXFLAGS) -c $(TEST_SRC) -o $(TEST_OBJ)

# Clean up generated files
clean:
	rm -f $(EXEC) $(TEST_OBJ) $(ATLAS_OBJ)

# Run the executable
run: $(EXEC)
	./$(EXEC)

.PHONY: all clean run

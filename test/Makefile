# 编译器及其标志
CXX = g++ -g3 -ggdb
CXXFLAGS = -std=c++11 -I../inc -Wall -Wextra -O2 -DTEST_MODE

# SFML, Boost 和 tinyxml2 设置
SFML_LIBS = -lsfml-graphics -lsfml-window -lsfml-system
BOOST_LIBS = -lboost_filesystem -lboost_system
TINYXML2_LIBS = -ltinyxml2

# 目录
SRC_DIR = ../src
INC_DIR = ../inc
OBJ_DIR = ./obj
BUILD_DIR = ./build
TEST_DIR = .

# 源文件
SRC_FILES = $(wildcard $(SRC_DIR)/*.cpp)  # src 目录下的所有源文件
TEST_SRC_FILES = $(wildcard $(TEST_DIR)/*.cpp)  # test 目录下的所有源文件
ALL_SRC_FILES = $(SRC_FILES) $(TEST_SRC_FILES)  # 所有源文件

# 对象文件
OBJ_FILES = $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRC_FILES))  # src 目录下源文件对应的对象文件
OBJ_FILES += $(patsubst $(TEST_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(TEST_SRC_FILES))  # test 目录下源文件对应的对象文件

# 可执行文件
EXEC_MAP = $(BUILD_DIR)/TestMap
EXEC_TEXTURE_ATLAS = $(BUILD_DIR)/TestTextureAtlasParser
EXEC_CHARACTER_TEXTURE = $(BUILD_DIR)/TestCharacterTexture
EXEC_SPRITE_LOADER_TEST = $(BUILD_DIR)/SpriteLoaderTest
EXEC_GENERATE_LEVEL = $(BUILD_DIR)/TestGenerateLevel
EXEC_SOLVER_TEST = $(BUILD_DIR)/TestSolver

# 默认目标
all: $(EXEC_MAP) $(EXEC_TEXTURE_ATLAS) $(EXEC_CHARACTER_TEXTURE) $(EXEC_SPRITE_LOADER_TEST) $(EXEC_GENERATE_LEVEL) $(EXEC_SOLVER_TEST)
	@echo "所有目标已编译完成。"

# 创建 obj 和 build 目录（如果不存在的话）
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# 编译对象文件的规则
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR)
	@echo "编译 $<..."
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJ_DIR)/%.o: $(TEST_DIR)/%.cpp | $(OBJ_DIR)
	@echo "编译 $<..."
	$(CXX) $(CXXFLAGS) -c $< -o $@

# 链接生成可执行文件的规则
$(EXEC_MAP): $(OBJ_DIR)/TestMap.o $(OBJ_DIR)/Map.o $(OBJ_DIR)/State.o $(OBJ_DIR)/SpriteLoader.o | $(BUILD_DIR)
	@echo "链接 $@..."
	$(CXX) $(CXXFLAGS) -o $@ $^ $(SFML_LIBS) $(BOOST_LIBS) $(TINYXML2_LIBS)

$(EXEC_TEXTURE_ATLAS): $(OBJ_DIR)/TestTextureAtlasParser.o $(OBJ_DIR)/TextureAtlasParser.o | $(BUILD_DIR)
	@echo "链接 $@..."
	$(CXX) $(CXXFLAGS) -o $@ $^ $(SFML_LIBS) $(BOOST_LIBS) $(TINYXML2_LIBS)

$(EXEC_CHARACTER_TEXTURE): $(OBJ_DIR)/TestCharacterTexture.o $(OBJ_DIR)/TestCharacterTexture.o $(OBJ_DIR)/Map.o $(OBJ_DIR)/State.o $(OBJ_DIR)/TextureAtlasParser.o $(OBJ_DIR)/SpriteLoader.o | $(BUILD_DIR)
	@echo "链接 $@..."
	$(CXX) $(CXXFLAGS) -o $@ $^ $(SFML_LIBS) $(BOOST_LIBS) $(TINYXML2_LIBS)

$(EXEC_SPRITE_LOADER_TEST): $(OBJ_DIR)/SpriteLoaderTest.o $(OBJ_DIR)/SpriteLoader.o | $(BUILD_DIR)
	@echo "链接 $@..."
	$(CXX) $(CXXFLAGS) -o $@ $^ $(SFML_LIBS) $(BOOST_LIBS) $(TINYXML2_LIBS)

$(EXEC_GENERATE_LEVEL): $(OBJ_DIR)/TestGenerateLevel.o $(OBJ_DIR)/GenerateLevel.o $(OBJ_DIR)/State.o $(OBJ_DIR)/Map.o $(OBJ_DIR)/SpriteLoader.o | $(BUILD_DIR)
	@echo "链接 $@..."
	$(CXX) $(CXXFLAGS) -o $@ $^ $(SFML_LIBS) $(BOOST_LIBS) $(TINYXML2_LIBS)

$(EXEC_SOLVER_TEST): $(OBJ_DIR)/TestSolver.o $(OBJ_DIR)/Solver.o $(OBJ_DIR)/State.o $(OBJ_DIR)/Map.o $(OBJ_DIR)/StateNode.o $(OBJ_DIR)/SpriteLoader.o | $(BUILD_DIR)
	@echo "链接 $@..."
	$(CXX) $(CXXFLAGS) -o $@ $^ $(SFML_LIBS) $(BOOST_LIBS) $(TINYXML2_LIBS)

# 清理生成的文件
clean:
	@echo "清理生成的文件..."
	rm -f $(BUILD_DIR)/* $(OBJ_DIR)/*.o

# 运行可执行文件的规则
run-map: $(EXEC_MAP)
	@echo "运行 $<..."
	./$<

run-texture-atlas: $(EXEC_TEXTURE_ATLAS)
	@echo "运行 $<..."
	./$<

run-character-texture: $(EXEC_CHARACTER_TEXTURE)
	@echo "运行 $<..."
	./$<

run-sprite-loader-test: $(EXEC_SPRITE_LOADER_TEST)
	@echo "运行 $<..."
	./$<

run-generate-level: $(EXEC_GENERATE_LEVEL)
	@echo "运行 $<..."
	./$<

run-solver-test: $(EXEC_SOLVER_TEST)
	@echo "运行 $<..."
	./$<

.PHONY: all clean run-map run-texture-atlas run-character-texture run-sprite-loader-test run-generate-level run-solver-test

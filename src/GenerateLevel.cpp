#include "GenerateLevel.h"
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <iomanip>

// TileType 到字符串的映射函数
const char* tileTypeToString(TileType type) {
    switch (type) {
        case Wall:      return "Wall";
        case Floor:     return "Floor";
        case Character: return "Chara";
        case Box:       return "Box";
        case Aid:       return "Aid";
        default:        return "Unknown";
    }
}


// TileType 到数字的映射函数
int tileTypeToNumber(TileType type) {
    switch (type) {
        case Wall:      return 1;
        case Floor:     return 0;
        case Character: return 2;
        case Box:       return 3;
        case Aid:       return 4;
        default:        return -1; // Unknown type
    }
}

// ANSI 颜色转义码
const char* colorForTileType(TileType type) {
    switch (type) {
        case Wall:      return "\033[38;5;208m"; // 橙色
        case Floor:     return "\033[38;5;28m";  // 绿色
        case Character: return "\033[97m";       // 白色
        case Box:       return "\033[38;5;196m"; // 红色
        case Aid:       return "\033[38;5;206m"; // 粉色
        default:        return "\033[0m";         // 默认颜色
    }
}

// 构造函数
GenerateLevel::GenerateLevel(int w, int h) : width(w), height(h) {
    tiles = new TileType[width * height];
    savedtiles = new TileType[width * height];
    initializeTiles();
    srand(static_cast<unsigned>(time(nullptr))); // 只设置一次随机数种子
    save(false);
}

// 析构函数
GenerateLevel::~GenerateLevel() {
    delete[] tiles;
    delete[] savedtiles;
}

// 获取瓷砖类型
TileType GenerateLevel::getTiles(int x, int y) const {
    if (x < 0 || x >= width || y < 0 || y >= height) {
        throw std::out_of_range("Tile coordinates are out of bounds");
    }
    return tiles[y * width + x];
}

// 初始化瓷砖
void GenerateLevel::initializeTiles() {
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (i == 0 || i == height - 1 || j == 0 || j == width - 1) {
                tiles[i * width + j] = Wall;
            } else {
                tiles[i * width + j] = Floor;
            }
        }
    }
}

// 生成角色
bool GenerateLevel::generateChar() {
    for (int attempt = 0; attempt < MAX_ATTEMPTS; ++attempt) {
        int randi = rand() % height;
        int randj = rand() % width;
        if (tiles[randi * width + randj] == Floor) {
            tiles[randi * width + randj] = Character;
            return true;
        }
    }
    return false;
}

// 生成箱子
bool GenerateLevel::generateBox() {
    for (int attempt = 0; attempt < MAX_ATTEMPTS; ++attempt) {
        int randi = rand() % height;
        int randj = rand() % width;
        if (tiles[randi * width + randj] == Floor) {
            tiles[randi * width + randj] = Box;
            return true;
        }
    }
    return false;
}

// 生成墙
bool GenerateLevel::generateWall() {
    for (int attempt = 0; attempt < MAX_ATTEMPTS; ++attempt) {
        int randi = rand() % height;
        int randj = rand() % width;
        if (tiles[randi * width + randj] == Floor) {
            tiles[randi * width + randj] = Wall;
            return true;
        }
    }
    return false;
}

// 生成辅助道具
bool GenerateLevel::generateAid() {
    for (int attempt = 0; attempt < MAX_ATTEMPTS; ++attempt) {
        int randi = rand() % height;
        int randj = rand() % width;
        TileType currentTile = tiles[randi * width + randj];
        
        // 只要不是人物或箱子的位置，都可以生成辅助道具
        if (currentTile != Character && currentTile != Box) {
            tiles[randi * width + randj] = Aid;
            return true;
        }
    }
    return false;
}

// 保存瓷砖状态，并打印地图的矩阵图，使用制表符对齐
// void GenerateLevel::save(bool printNumeric) const {
//     const int fieldWidth = 5; // 每个字段宽度，包括制表符
//     for (int i = 0; i < height; i++) {
//         for (int j = 0; j < width; j++) {
//             TileType tile = tiles[i * width + j];
//             if (printNumeric) {
//                 // 打印数字矩阵
//                 std::cout << std::setw(fieldWidth) << tileTypeToNumber(tile) << '\t';
//             } else {
//                 // 打印文字矩阵并上色
//                 std::cout << colorForTileType(tile) << std::setw(fieldWidth) << tileTypeToString(tile) << '\033[0m' << '\t';
//             }
//             savedtiles[i * width + j] = tile; // 保存瓷砖状态
//         }
//         std::cout << std::endl; // 换行
//     }
//     std::cout << std::endl; // 空行，方便区分不同的地图状态
// }
void GenerateLevel::save(bool printNumeric) const {
    const int fieldWidth = 5; // 每个字段宽度，包括制表符
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            TileType tile = tiles[i * width + j];
            if (printNumeric) {
                // 打印数字矩阵
                std::cout << std::setw(fieldWidth) << tileTypeToNumber(tile) << '\t';
            } else {
                // 打印文字矩阵并上色
                std::cout << colorForTileType(tile) << std::setw(fieldWidth) << tileTypeToString(tile) << '\t';// '\033[0m' << '\t';
            }
            savedtiles[i * width + j] = tile; // 保存瓷砖状态
        }
        std::cout << std::endl; // 换行
    }
    std::cout << std::endl; // 空行，方便区分不同的地图状态
}


// 加载瓷砖状态
void GenerateLevel::load() {
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            tiles[i * width + j] = savedtiles[i * width + j];
        }
    }
}

// 获取当前的瓷砖状态
TileType GenerateLevel::getCurrentTile(int x, int y) const {
    if (x < 0 || x >= width || y < 0 || y >= height) {
        throw std::out_of_range("Tile coordinates are out of bounds");
    }
    return tiles[y * width + x];
}

// 获取保存的瓷砖状态
TileType GenerateLevel::getSavedTile(int x, int y) const {
    if (x < 0 || x >= width || y < 0 || y >= height) {
        throw std::out_of_range("Tile coordinates are out of bounds");
    }
    return savedtiles[y * width + x];
}

// 设置新瓷砖数组
void GenerateLevel::setTiles(TileType* t) {
    delete[] tiles;
    tiles = t;
    // Optionally, you may want to reset savedtiles if necessary
}

// 设置宽度和高度，并重新初始化瓷砖
void GenerateLevel::setWidget(int w, int h) {
    delete[] tiles;
    delete[] savedtiles;
    width = w;
    height = h;
    tiles = new TileType[width * height];
    savedtiles = new TileType[width * height];
    initializeTiles();
}

// 重置瓷砖到保存状态
void GenerateLevel::resetTiles() {
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            tiles[i * width + j] = savedtiles[i * width + j];
        }
    }
}

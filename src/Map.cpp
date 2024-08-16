#include "pch.h"
#include "Map.h"
#include <iostream>
#include <fstream>
#include <unordered_map>

// Constructor
Map::Map() {
    // Initialization code if needed
}

// Destructor
Map::~Map() {
    // Cleanup code if needed
}

// Function to draw the map based on the state
void Map::drawMap(const State* state) const {
    validateMapDimensions(state->width, state->height); // Validate dimensions

    for (int i = 0; i < state->height; ++i) {
        for (int j = 0; j < state->width; ++j) {
            drawTile(state->tiles[i * state->width + j]);
        }
        std::cout << "\n";
    }
}

// Function to draw a single tile based on its type
void Map::drawTile(TileType type) const {
    static const std::unordered_map<TileType, std::string> tileMap = {
        { Wall, "\033[31m▓\033[0m" },
        { Aid, "\033[41;37m⿴\033[0m" },
        { Box, "\033[42;31m■\033[0m" },
        { BoxinAid, "\033[43;31m❐\033[0m" },
        { Character, "\033[44;33m☺\033[0m" },
        { CharacterinAid, "\033[45;32m☺a\033[0m" }
    };

    auto it = tileMap.find(type);
    if (it != tileMap.end()) {
        std::cout << it->second;
    } else {
        std::cout << "  "; // Default space for unknown types
    }
}

// Function to save the map to a file
void Map::saveMapToFile(const std::string& filename, const State* state) const {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cerr << "无法打开文件进行保存。\n";
        return;
    }

    file << state->height << " " << state->width << "\n";
    for (int i = 0; i < state->height; ++i) {
        for (int j = 0; j < state->width; ++j) {
            file << static_cast<int>(state->tiles[i * state->width + j]) << " ";
        }
        file << "\n";
    }

    file.close();
}

// Function to load the map from a file
State* Map::loadMapFromFile(const std::string& filename) const {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "无法打开文件进行加载。\n";
        return nullptr;
    }

    int height, width;
    file >> height >> width;

    State* state = new State(width, height);
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            int tileType;
            file >> tileType;
            state->tiles[i * width + j] = static_cast<TileType>(tileType);
        }
    }

    file.close();
    return state;
}

// Function to validate map dimensions
void Map::validateMapDimensions(int width, int height) const {
    if (width <= 0 || height <= 0) {
        std::cerr << "无效的地图尺寸。\n";
        exit(1);
    }
}

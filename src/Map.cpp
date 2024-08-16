#include "pch.h"
#include "Map.h"
#include <iostream>
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

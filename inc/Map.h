#pragma once
#include "TileType.h"
#include "State.h"
#include <string>

class Map {
public:
    Map();
    ~Map();
    void drawMap(const State* state) const; // Mark as const since it doesn't modify the object
    void saveMapToFile(const std::string& filename, const State* state) const;
    State* loadMapFromFile(const std::string& filename) const;

private:
    void drawTile(TileType type) const; // Mark as const since it doesn't modify the object
    void validateMapDimensions(int width, int height) const;
};

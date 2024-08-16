#pragma once
#include "TileType.h"
#include "State.h"

class Map {
public:
    Map();
    ~Map();
    void drawMap(const State* state) const; // Mark as const since it doesn't modify the object

private:
    void drawTile(TileType type) const; // Mark as const since it doesn't modify the object
};

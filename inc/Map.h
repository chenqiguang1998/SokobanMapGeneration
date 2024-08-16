#pragma once
#include "TileType.h"
#include "State.h"

class Map {
public:
    Map();
    ~Map();
    void drawMap(State * state);
private:
    int width;
    int height;
    int ** MapArray;
    void drawTile(TileType type);
};

#pragma once
#include "TileType.h"

class GenerateLevel {
public:
    int width;
    int height;
    TileType* tiles;
    TileType* savedtiles;

    GenerateLevel(int w, int h);
    ~GenerateLevel(); // Destructor to release allocated memory

    bool generateChar();
    bool generateBox();
    bool generateWall();
    bool generateAid();

    void save();
    void load();

private:
    static const int MAX_ATTEMPTS = 1000; // Max attempts for placement
    void initializeTiles(); // Initialize tiles with walls and floors
};

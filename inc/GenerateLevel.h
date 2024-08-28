#pragma once
#include "TileType.h"
#include <stdexcept>

class GenerateLevel {
public:
    GenerateLevel(int w, int h); // Constructor to initialize the level with width and height
    ~GenerateLevel(); // Destructor to release allocated memory

    bool generateChar(); // Generate a character in the level
    bool generateBox(); // Generate a box in the level
    bool generateWall(); // Generate a wall in the level
    bool generateAid(); // Generate an aid item in the level

    void save(bool printNumeric)const; // Save the current state of the level
    void load(); // Load the previously saved state

    int getWidth() const { return width; } // Get the width of the level
    int getHeight() const { return height; } // Get the height of the level

    TileType* getTiles() { return tiles; } // Get the pointer to the tiles array
    void setWidget(int w, int h); // Set the width and height, and reinitialize tiles
    void resetTiles(); // Reset tiles to their saved state
    void setTiles(TileType* t); // Set tiles to a new array and update savedtiles

    TileType getTiles(int x, int y) const; // Get the tile type at (x, y)
    void reinitializeTiles() { initializeTiles(); } // Reinitialize tiles

    TileType getSavedTile(int x, int y) const; // Get the saved tile type at (x, y)
    TileType getCurrentTile(int x, int y) const; // Get the current tile type at (x, y)

private:
    static const int MAX_ATTEMPTS = 1000; // Max attempts for placement
    void initializeTiles(); // Initialize tiles with walls and floors

    int width; // Width of the level
    int height; // Height of the level
    TileType* tiles; // Pointer to the current tiles array
    TileType* savedtiles; // Pointer to the saved tiles array
};

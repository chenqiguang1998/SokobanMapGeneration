#include "pch.h"
#include "GenerateLevel.h"
#include <cstdlib>
#include <ctime>
#include <iostream>

GenerateLevel::GenerateLevel(int w, int h) : width(w), height(h) {
    tiles = new TileType[width * height];
    savedtiles = new TileType[width * height];
    initializeTiles();
    if (!generateChar()) {
        std::cerr << "生成角色失败\n";
    }
    save();
}

GenerateLevel::~GenerateLevel() {
    delete[] tiles;
    delete[] savedtiles;
}

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

bool GenerateLevel::generateChar() {
    srand(static_cast<unsigned>(time(nullptr)));
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

bool GenerateLevel::generateBox() {
    srand(static_cast<unsigned>(time(nullptr)));
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

bool GenerateLevel::generateWall() {
    srand(static_cast<unsigned>(time(nullptr)));
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

bool GenerateLevel::generateAid() {
    srand(static_cast<unsigned>(time(nullptr)));
    for (int attempt = 0; attempt < MAX_ATTEMPTS; ++attempt) {
        int randi = rand() % height;
        int randj = rand() % width;
        if (tiles[randi * width + randj] == Floor) {
            tiles[randi * width + randj] = Aid;
            return true;
        }
    }
    return false;
}

void GenerateLevel::save() {
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            savedtiles[i * width + j] = tiles[i * width + j];
        }
    }
}

void GenerateLevel::load() {
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            tiles[i * width + j] = savedtiles[i * width + j];
        }
    }
}

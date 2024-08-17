#include "pch.h"
#include "Map.h"
#include <iostream>
#include <fstream>
#include <unordered_map>

// Constructor
Map::Map() : tileWidth(64), tileHeight(64) {
    // Initialization code if needed
}

// Destructor
Map::~Map() {
    // Cleanup code if needed
}

// Draw map on console
void Map::drawMap(const State* state) const {
    validateMapDimensions(state->width, state->height);

    for (int i = 0; i < state->height; ++i) {
        for (int j = 0; j < state->width; ++j) {
            drawTile(state->tiles[i * state->width + j]);
        }
        std::cout << "\n";
    }
}

// Draw map with texture
void Map::drawMapWithTexture(const State* state, const sf::Texture& texture, bool columnMajor) const {
    int mapWidth = state->width * tileWidth;
    int mapHeight = state->height * tileHeight;

    sf::RenderTexture renderTexture;
    renderTexture.create(mapWidth, mapHeight);
    renderTexture.clear(sf::Color::White); // Set background color or use a background texture

    // Calculate the offset to center the map
    int offsetX = (renderTexture.getSize().x - mapWidth) / 2;
    int offsetY = (renderTexture.getSize().y - mapHeight) / 2;

    // Draw tiles
    for (int i = 0; i < state->height; ++i) {
        for (int j = 0; j < state->width; ++j) {
            drawTile(state->tiles[i * state->width + j], renderTexture, texture, j, i, columnMajor);
        }
    }

    renderTexture.display();
    sf::Texture finalTexture = renderTexture.getTexture();
    // Use finalTexture as needed (e.g., display it in a window)
}

// Draw a single tile with texture
void Map::drawTileWithTexture(sf::RenderTexture& renderTexture, TileType type, int tileX, int tileY, const sf::Texture& texture) const {
    sf::Sprite sprite(texture);
    sprite.setTextureRect(sf::IntRect(type * tileWidth, 0, tileWidth, tileHeight)); // Adjust based on tile index
    sprite.setPosition(tileX, tileY);
    renderTexture.draw(sprite);
}

// Save map to a file
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

// Load map from a file
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

// Validate map dimensions
void Map::validateMapDimensions(int width, int height) const {
    if (width <= 0 || height <= 0) {
        std::cerr << "无效的地图尺寸。\n";
        exit(1);
    }
}

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

// Function to draw the map with texture and render to a RenderTexture
void Map::drawMapWithTexture(sf::RenderTexture& renderTexture, const State* state, const sf::Texture& texture, bool columnMajor) const {
    validateMapDimensions(state->width, state->height);

    int mapWidth = state->width * tileWidth;
    int mapHeight = state->height * tileHeight;

    // Create a render texture for drawing
    renderTexture.create(mapWidth, mapHeight);
    renderTexture.clear(sf::Color::White);

    // Calculate the offset to center the map
    int offsetX = (renderTexture.getSize().x - mapWidth) / 2;
    int offsetY = (renderTexture.getSize().y - mapHeight) / 2;

    // Draw tiles
    for (int i = 0; i < state->height; ++i) {
        for (int j = 0; j < state->width; ++j) {
            drawTile(state->tiles[i * state->width + j], renderTexture, texture, j * tileWidth + offsetX, i * tileHeight + offsetY, columnMajor);
        }
    }

    renderTexture.display();
}

// Function to draw a single tile with texture
void Map::drawTile(TileType type, sf::RenderTexture& renderTexture, const sf::Texture& texture, int x, int y, bool columnMajor) const {
    sf::Sprite sprite(texture);

    int tileIndex = static_cast<int>(type); // Use the TileType enum value as the tile index
    int tilesPerRow = texture.getSize().x / tileWidth;

    int tileX = (columnMajor ? x : y);
    int tileY = (columnMajor ? y : x);

    sprite.setTextureRect(sf::IntRect(tileIndex % tilesPerRow * tileWidth, tileIndex / tilesPerRow * tileHeight, tileWidth, tileHeight));
    sprite.setPosition(tileX, tileY);

    renderTexture.draw(sprite);
}

void Map::setWindowAndRenderTexture(sf::RenderWindow& window, sf::RenderTexture& renderTexture, const State* state, const std::string& title) const {
    // 计算窗口和渲染纹理的尺寸
    int width = state->width * tileWidth;
    int height = state->height * tileHeight;

    // 设置窗口大小和标题
    window.create(sf::VideoMode(width, height), title);

    // 设置渲染纹理大小
    renderTexture.create(width, height);
    renderTexture.clear(sf::Color::White);
}


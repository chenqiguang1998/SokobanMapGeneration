#pragma once
#include "TileType.h"
#include "State.h"
#include <string>
#include <SFML/Graphics.hpp>

class Map {
public:
    Map();
    ~Map();
    void drawMap(const State* state) const;
    void saveMapToFile(const std::string& filename, const State* state) const;
    State* loadMapFromFile(const std::string& filename) const;

    // 新增：使用素材绘制地图
    void drawMapWithTexture(const State* state, const sf::Texture& texture, bool columnMajor = true) const;
    void drawMapWithTexture(sf::RenderTexture& renderTexture, const State* state, const sf::Texture& texture, bool columnMajor = true) const;

    void setWindowAndRenderTexture(sf::RenderWindow& window, sf::RenderTexture& renderTexture, const State* state, const std::string& title) const;
private:
    void drawTile(TileType type) const;
    void drawTile(TileType type, sf::RenderTexture& renderTexture, const sf::Texture& texture, int x, int y, bool columnMajor) const; // Texture drawing
    void validateMapDimensions(int width, int height) const;
    void drawTileWithTexture(sf::RenderTexture& renderTexture, TileType type, int tileX, int tileY, const sf::Texture& texture) const;

    int tileWidth;  // Tile width in pixels
    int tileHeight; // Tile height in pixels
};

#ifndef MAP_H
#define MAP_H

#include "State.h"
#include <SFML/Graphics.hpp>
#define TILE_SIZE 64
class Map {
public:
    Map();
    ~Map();

    // 绘制地图，控制台模式
    void drawMap(const State* state) const;

    // 绘制带纹理的地图 - 使用渲染纹理
    void drawMapWithTexture(sf::RenderTexture& renderTexture, const State* state, const sf::Texture& texture, bool columnMajor) const;
    
    // 绘制带纹理的地图 - 不使用渲染纹理
    void drawMapWithTexture(const State* state, const sf::Texture& texture, bool columnMajor) const;

    // 保存地图到文件
    void saveMapToFile(const std::string& filename, const State* state) const;

    // 从文件加载地图
    State* loadMapFromFile(const std::string& filename) const;
    void drawMapArea(const State& state, sf::RenderWindow& window, const sf::IntRect& rect) const;
    void drawTile(sf::RenderWindow& window, TileType tileType, int x, int y) const;
    // 设置窗口和渲染纹理
    void setWindowAndRenderTexture(sf::RenderWindow& window, sf::RenderTexture& renderTexture, const State* state, const std::string& title) const;

private:
    // 绘制单个瓦片 - 使用纹理
    void drawTile(TileType type, sf::RenderTexture& renderTexture, const sf::Texture& texture, int x, int y, bool columnMajor) const;
    
    // 绘制单个瓦片 - 控制台模式
    void drawTile(TileType type) const;

    // 绘制角色 - 使用纹理
    void drawCharacter(sf::RenderTexture& renderTexture, const State* state, const sf::Texture& texture) const;

    // 验证地图尺寸
    void validateMapDimensions(int width, int height) const;

    int tileWidth;
    int tileHeight;
};

#endif // MAP_H

#include "Map.h"
#include "SpriteLoader.h"
#include "State.h"
#include <iostream>
#include <fstream>
#include <unordered_map>
#include <SFML/Graphics.hpp>
#include <chrono>

// 构造函数
Map::Map() : tileWidth(64), tileHeight(64) {}

// 析构函数
Map::~Map() {}

// 绘制控制台上的地图
void Map::drawMap(const State* state) const {
    validateMapDimensions(state->width, state->height);

    for (int i = 0; i < state->height; ++i) {
        for (int j = 0; j < state->width; ++j) {
            drawTile(state->tiles[i * state->width + j]);
        }
        std::cout << "\n";
    }
}

// 绘制带纹理的地图 - 使用渲染纹理
void Map::drawMapWithTexture(sf::RenderTexture& renderTexture, const State* state, const sf::Texture& texture, bool columnMajor) const {
    int mapWidth = state->width * tileWidth;
    int mapHeight = state->height * tileHeight;

    // 创建和清除渲染纹理
    renderTexture.create(mapWidth, mapHeight);
    renderTexture.clear(sf::Color::White);

    // 计算偏移量以使地图居中
    int offsetX = (renderTexture.getSize().x - mapWidth) / 2;
    int offsetY = (renderTexture.getSize().y - mapHeight) / 2;

    // 绘制瓦片
    for (int i = 0; i < state->height; ++i) {
        for (int j = 0; j < state->width; ++j) {
            drawTile(state->tiles[i * state->width + j], renderTexture, texture, j * tileWidth + offsetX, i * tileHeight + offsetY, columnMajor);
        }
    }

    // 绘制角色
    drawCharacter(renderTexture, state, texture);

    // 显示渲染纹理
    renderTexture.display();
}

// 绘制带纹理的地图 - 不使用渲染纹理
void Map::drawMapWithTexture(const State* state, const sf::Texture& texture, bool columnMajor) const {
    sf::RenderTexture renderTexture;
    drawMapWithTexture(renderTexture, state, texture, columnMajor);
}

// 绘制单个瓦片 - 使用纹理
void Map::drawTile(TileType type, sf::RenderTexture& renderTexture, const sf::Texture& texture, int x, int y, bool columnMajor) const {
    sf::Sprite sprite(texture);

    int tileIndex = static_cast<int>(type);
    int tilesPerRow = texture.getSize().x / tileWidth;

    int tileX = (columnMajor ? x : y);
    int tileY = (columnMajor ? y : x);

    sprite.setTextureRect(sf::IntRect(tileIndex % tilesPerRow * tileWidth, tileIndex / tilesPerRow * tileHeight, tileWidth, tileHeight));
    sprite.setPosition(tileX, tileY);

    renderTexture.draw(sprite);
}

// 绘制角色 - 使用纹理
void Map::drawCharacter(sf::RenderTexture& renderTexture, const State* state, const sf::Texture& texture) const {
    SpriteLoader spriteLoader("", ""); // 创建一个 SpriteLoader 对象
    int characterBaseIndex = LEFT_STOP; // 角色纹理的起始索引

    // 获取角色状态
    const State::CharacterState &charState = state->getCharacterState();
    int charDir = static_cast<int>(charState.dir);
    int charFrame = 0;

    // 计算当前时间与上次输入时间的时间差
    static auto lastInputTime = std::chrono::steady_clock::now();
    auto now = std::chrono::steady_clock::now();
    std::chrono::duration<double> elapsed = now - lastInputTime;

    if (charState.isMoving) {
        charFrame = (charState.stepsMoved % 2); // 0或1
        lastInputTime = now;
    } else if (elapsed.count() >= 0.5) {
        charFrame = 0; // 静止状态帧
    }

    int tileIndex;
    if (charDir == static_cast<int>(Direction::D_LEFT) || charDir == static_cast<int>(Direction::D_RIGHT)) {
        tileIndex = characterBaseIndex + charDir * 2 + (charState.isMoving ? 1 : 0);
    } else {
        tileIndex = characterBaseIndex + charDir * 2 + charFrame;
    }

    std::string textureName = spriteLoader.getTextureName(static_cast<TextureType>(tileIndex));
    std::cout << "Character texture: " << textureName << std::endl;

    sf::Sprite sprite(texture);
    sprite.setTextureRect(sf::IntRect(tileIndex * tileWidth, 0, tileWidth, tileHeight));
    sprite.setPosition(state->cx * tileWidth, state->cy * tileHeight);

    renderTexture.draw(sprite);
}

// 保存地图到文件
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

// 从文件加载地图
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

// 验证地图尺寸
void Map::validateMapDimensions(int width, int height) const {
    if (width <= 0 || height <= 0) {
        std::cerr << "无效的地图尺寸。\n";
        exit(1);
    }
}

// 绘制单个瓦片 - 控制台模式
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
        std::cout << "  "; // 默认的未知类型
    }
}

// 设置窗口和渲染纹理
void Map::setWindowAndRenderTexture(sf::RenderWindow& window, sf::RenderTexture& renderTexture, const State* state, const std::string& title) const {
    int width = state->width * tileWidth;
    int height = state->height * tileHeight;

    window.create(sf::VideoMode(width, height), title);
    renderTexture.create(width, height);
    renderTexture.clear(sf::Color::White);
}

void Map::drawMapArea(const State& state, sf::RenderWindow& window, const sf::IntRect& rect) const {
    int startX = rect.left;
    int startY = rect.top;
    int endX = rect.left + rect.width;
    int endY = rect.top + rect.height;

    // 遍历矩形区域内的每个瓦片
    for (int y = startY; y < endY; ++y) {
        for (int x = startX; x < endX; ++x) {
            // 确保 x 和 y 在有效范围内
            if (x >= 0 && x < state.getWidth() && y >= 0 && y < state.getHeight()) {
                TileType tileType = state.getTile(x, y);
                drawTile(window, tileType, x, y);
            }
        }
    }
}

void Map::drawTile(sf::RenderWindow& window, TileType tileType, int x, int y) const {
    // 根据瓦片类型绘制相应的图像或图形
    // 这里的实现是示例，你需要根据实际的 TileType 和绘制逻辑来实现
    sf::RectangleShape tileShape(sf::Vector2f(tileWidth, tileHeight)); // 假设每个瓦片大小为 32x32 像素
    tileShape.setPosition(x * tileWidth, y * tileHeight); // 设置位置
    
    switch (tileType) {
        case Floor:
            tileShape.setFillColor(sf::Color::White); // 白色表示地板
            break;
        case Wall:
            tileShape.setFillColor(sf::Color::Black); // 黑色表示墙壁
            break;
        case Box:
            tileShape.setFillColor(sf::Color::Red); // 红色表示箱子
            break;
        // 添加其他瓦片类型的处理逻辑
        default:
            tileShape.setFillColor(sf::Color::Green); // 默认颜色
            break;
    }
    
    window.draw(tileShape); // 绘制瓦片
}

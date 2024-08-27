#ifndef SPRITE_LOADER_H
#define SPRITE_LOADER_H

#include <SFML/Graphics.hpp>
#include <string>
#include <map>

// 定义纹理类型
enum class TextureType {
    // 角色
    CHARACTER1, // 左停
    CHARACTER10, // 左动
    CHARACTER2, // 右停
    CHARACTER3, // 右动
    CHARACTER4, // 后停
    CHARACTER5, // 后动2
    CHARACTER6, // 后动1
    CHARACTER7, // 前停
    CHARACTER8, // 前动2
    CHARACTER9, // 前动1
    
    // 黑暗箱子
    CRATE_DARK_BEIGE,
    CRATE_DARK_BLACK,
    CRATE_DARK_BLUE,
    CRATE_DARK_BROWN,
    CRATE_DARK_GRAY,
    CRATE_DARK_PURPLE,
    CRATE_DARK_RED,
    CRATE_DARK_YELLOW,
    
    // 普通箱子
    CRATE_BEIGE,
    CRATE_BLACK,
    CRATE_BLUE,
    CRATE_BROWN,
    CRATE_GRAY,
    CRATE_PURPLE,
    CRATE_RED,
    CRATE_YELLOW,
    
    // 终点
    ENDPOINT_BEIGE,
    ENDPOINT_BLACK,
    ENDPOINT_BLUE,
    ENDPOINT_BROWN,
    ENDPOINT_GRAY,
    ENDPOINT_PURPLE,
    ENDPOINT_RED,
    ENDPOINT_YELLOW,
    
    // 地面
    GROUND_GRAVEL_CONCRETE,
    GROUND_GRAVEL_DIRT,
    GROUND_GRAVEL_GRASS,
    GROUND_GRAVEL_SAND,
    GROUND_CONCRETE,
    GROUND_DIRT,
    GROUND_GRASS,
    GROUND_SAND,
    
    // 墙壁
    WALL_ROUND_BEIGE,
    WALL_ROUND_BLACK,
    WALL_ROUND_BROWN,
    WALL_ROUND_GRAY,
    WALL_BEIGE,
    WALL_BLACK,
    WALL_BROWN,
    WALL_GRAY
};

// Assuming TextureType is an enum class, but integer values are needed
#define LEFT_STOP    static_cast<int>(TextureType::CHARACTER1)  // 左停
#define LEFT_MOVE    static_cast<int>(TextureType::CHARACTER10) // 左动
#define RIGHT_STOP   static_cast<int>(TextureType::CHARACTER2)  // 右停
#define RIGHT_MOVE   static_cast<int>(TextureType::CHARACTER3)  // 右动
#define BACK_STOP    static_cast<int>(TextureType::CHARACTER4)  // 后停
#define BACK_MOVE1   static_cast<int>(TextureType::CHARACTER6)  // 后动1
#define BACK_MOVE2   static_cast<int>(TextureType::CHARACTER5)  // 后动2
#define FRONT_STOP   static_cast<int>(TextureType::CHARACTER7)  // 前停
#define FRONT_MOVE1  static_cast<int>(TextureType::CHARACTER9)  // 前动1
#define FRONT_MOVE2  static_cast<int>(TextureType::CHARACTER8)  // 前动2


class SpriteLoader {
public:
    SpriteLoader(const std::string& xmlPath, const std::string& imagePath);
    bool load();
    
    void drawSprite(TextureType type, sf::RenderWindow& window, const sf::Vector2f& position);
    void drawAllSprites(sf::RenderWindow& window); // 绘制所有精灵
    void drawSpritesInRegion(sf::RenderWindow& window, const sf::FloatRect& region); // 在特定区域内绘制精灵
    
    std::string getTextureName(TextureType type) const;

private:
    bool loadSprites(const std::string& xmlPath);
    std::string textureTypeToString(TextureType type) const;

    std::string xmlPath;
    std::string imagePath;
    sf::Texture texture;
    std::map<std::string, sf::Sprite> sprites;
};

#endif // SPRITE_LOADER_H

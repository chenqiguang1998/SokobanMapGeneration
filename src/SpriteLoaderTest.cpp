#include <SFML/Graphics.hpp>
#include "SpriteLoader.h"
#include <iostream>

int main() {
    // 创建 SFML 窗口
    sf::RenderWindow window(sf::VideoMode(800, 600), "Sprite Loader Test");

    // 创建 SpriteLoader 实例，指定 XML 和图片路径
    SpriteLoader loader("res/sprites.xml", "res/sprites.png");
    if (!loader.load()) {
        std::cerr << "Failed to load sprites" << std::endl;
        return -1;
    }

    // 测试绘制
    bool displayAllSprites = true;  // 控制是否展示所有素材
    sf::Clock clock;  // 用于控制每秒绘制一次
    std::map<std::string, sf::Sprite> sprites = loader.getSprites(); // 从 SpriteLoader 获取所有的 sprites
    auto it = sprites.begin(); // 迭代器，用于切换 sprite

    while (window.isOpen()) {
        sf::Time deltaTime = clock.restart();  // 获取时间间隔

        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        window.clear(sf::Color::White);  // 清空窗口

        if (displayAllSprites) {
            // 绘制所有的 sprites
            for (const auto& pair : sprites) {
                loader.drawSprite(pair.first, window, sf::Vector2f(100.0f, 100.0f)); // 位置可以调整
            }
        } else {
            // 绘制当前 sprite（通过迭代器切换）
            if (it != sprites.end()) {
                loader.drawSprite(it->first, window, sf::Vector2f(400.0f, 300.0f)); // 位置可以调整
                ++it;
                if (it == sprites.end()) {
                    it = sprites.begin();
                }
            }
        }

        window.display();  // 显示绘制内容

        // 每隔 2 秒切换绘制模式（展示所有素材或单一素材）
        if (deltaTime.asSeconds() > 2.0f) {
            displayAllSprites = !displayAllSprites;
            clock.restart();  // 重置时钟
        }
    }

    return 0;
}

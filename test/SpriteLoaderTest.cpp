#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <iostream>
#include <map>
#include <string>
#include <thread>
#include <chrono>
#include "SpriteLoader.h"

// 函数声明
void handleEvents(sf::RenderWindow& window, std::map<TextureType, std::string>& textures, 
                   std::map<TextureType, std::string>::iterator& currentTextureIt);
void drawCurrentTexture(SpriteLoader& loader, sf::RenderWindow& window, 
                        std::map<TextureType, std::string>::iterator currentTextureIt, 
                        sf::Text& textureNameText, std::map<TextureType, std::string>& textures);
void controlFrameRate();

// 主函数
int main() {
    // 创建 SFML 窗口
    sf::RenderWindow window(sf::VideoMode(800, 600), "Sprite Loader Test");

    // 创建字体
    sf::Font font;
    if (!font.loadFromFile("../res/fonts/Kenarose.ttf")) {
        std::cerr << "Failed to load font" << std::endl;
        return -1;
    }

    sf::Text textureNameText;
    textureNameText.setFont(font);
    textureNameText.setCharacterSize(24);
    textureNameText.setFillColor(sf::Color::Black);

    // 创建 SpriteLoader 实例
    SpriteLoader loader("../res/sprites.xml", "../res/sprites.png");
    if (!loader.load()) {
        std::cerr << "Failed to load sprites" << std::endl;
        return -1;
    }

    // 纹理类型映射到名称
    std::map<TextureType, std::string> textures = {
        {TextureType::CHARACTER1, "CHARACTER1"},
        {TextureType::CHARACTER10, "CHARACTER10"},
        {TextureType::CHARACTER2, "CHARACTER2"},
        {TextureType::CHARACTER3, "CHARACTER3"},
        {TextureType::CHARACTER4, "CHARACTER4"},
        {TextureType::CHARACTER5, "CHARACTER5"},
        {TextureType::CHARACTER6, "CHARACTER6"},
        {TextureType::CHARACTER7, "CHARACTER7"},
        {TextureType::CHARACTER8, "CHARACTER8"},
        {TextureType::CHARACTER9, "CHARACTER9"}
    };
    
    auto currentTextureIt = textures.begin();
    sf::Clock clock;

    while (window.isOpen()) {
        sf::Time deltaTime = clock.restart();  // 获取时间间隔

        handleEvents(window, textures, currentTextureIt);

        window.clear(sf::Color::White);  // 清空窗口

        drawCurrentTexture(loader, window, currentTextureIt, textureNameText, textures);

        window.display();  // 显示绘制内容

        controlFrameRate();  // 控制帧率
    }

    return 0;
}

// 处理窗口事件
void handleEvents(sf::RenderWindow& window, std::map<TextureType, std::string>& textures, 
                   std::map<TextureType, std::string>::iterator& currentTextureIt) {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
        } else if (event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::Left) {
                // 显示上一个纹理
                if (currentTextureIt != textures.begin()) {
                    --currentTextureIt;
                } else {
                    currentTextureIt = textures.end();
                    --currentTextureIt;
                }
            } else if (event.key.code == sf::Keyboard::Right) {
                // 显示下一个纹理
                ++currentTextureIt;
                if (currentTextureIt == textures.end()) {
                    currentTextureIt = textures.begin();
                }
            }
        }
    }
}

// 绘制当前纹理
void drawCurrentTexture(SpriteLoader& loader, sf::RenderWindow& window, 
                        std::map<TextureType, std::string>::iterator currentTextureIt, 
                        sf::Text& textureNameText, std::map<TextureType, std::string>& textures) {
    if (currentTextureIt != textures.end()) {
        loader.drawSprite(currentTextureIt->first, window, sf::Vector2f(400.0f, 300.0f)); // 位置可以调整

        // 显示纹理名称
        textureNameText.setString(currentTextureIt->second);
        window.draw(textureNameText);
    }
}

// 控制帧率
void controlFrameRate() {
    std::this_thread::sleep_for(std::chrono::milliseconds(16));  // 约60FPS
}

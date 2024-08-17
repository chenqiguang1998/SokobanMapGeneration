#include "TextureAtlasParser.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

int main() {
    // 创建 TextureAtlas 实例并加载 XML 文件
    TextureAtlas atlas;
    if (!atlas.load()) {
        std::cerr << "Failed to load texture atlas." << std::endl;
        return 1;
    }

    sf::RenderWindow window(sf::VideoMode(800, 600), "Texture Atlas Viewer");

    // 获取所有纹理名称
    const auto& subTextures = atlas.getSubTextures();
    std::vector<std::string> textureNames;
    for (const auto& entry : subTextures) {
        textureNames.push_back(entry.first);
    }

    // 确保有纹理可以显示
    if (textureNames.empty()) {
        std::cerr << "No textures available." << std::endl;
        return 1;
    }

    // 当前纹理的索引
    auto it = textureNames.begin();
    sf::Sprite sprite;
    sprite.setTexture(*(atlas.getTexture(*it)));
    sprite.setPosition(0, 0);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            else if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Right) {
                    // 切换到下一个纹理
                    ++it;
                    if (it == textureNames.end()) it = textureNames.begin();
                    sprite.setTexture(*(atlas.getTexture(*it)));
                } else if (event.key.code == sf::Keyboard::Left) {
                    // 切换到上一个纹理
                    if (it == textureNames.begin()) it = textureNames.end();
                    --it;
                    sprite.setTexture(*(atlas.getTexture(*it)));
                }
            }
        }

        window.clear();
        window.draw(sprite);
        window.display();
    }

    return 0;
}

#ifndef SPRITE_LOADER_H
#define SPRITE_LOADER_H

#include <SFML/Graphics.hpp>
#include <string>
#include <map>

class SpriteLoader {
public:
    SpriteLoader(const std::string& xmlPath, const std::string& imagePath);
    bool load();
    void drawSprite(const std::string& name, sf::RenderWindow& window, const sf::Vector2f& position);

private:
    bool loadSprites(const std::string& xmlPath);

    std::string xmlPath;
    std::string imagePath;
    sf::Texture texture;
    std::map<std::string, sf::Sprite> sprites;
};

#endif // SPRITE_LOADER_H

#pragma once

#include <SFML/Graphics.hpp>
#include <tinyxml2.h>
#include <unordered_map>
#include <string>

struct SubTexture {
    std::string name;
    int x, y, width, height;
};

class TextureAtlas {
public:
    TextureAtlas();
    ~TextureAtlas();

    bool load();
    sf::Texture* getTexture(const std::string& name);

    // Public method to access subTextures
    const std::unordered_map<std::string, sf::IntRect>& getSubTextures() const;

private:
    std::string imagePath;
    std::string atlasPath;
    sf::Texture texture;
    std::unordered_map<std::string, sf::IntRect> subTextures;

    bool parseAtlas();
    std::string toAbsolutePath(const std::string& relativePath) const;
};

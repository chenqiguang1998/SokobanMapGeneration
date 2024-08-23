#include "SpriteLoader.h"
#include <tinyxml2.h>
#include <iostream>
#include <unistd.h> // For getcwd
#include <cstring>  // For strlen

SpriteLoader::SpriteLoader(const std::string& xmlPath, const std::string& imagePath)
    : xmlPath(xmlPath), imagePath(imagePath) {}

bool SpriteLoader::load() {
    // 获取当前工作目录
    char buffer[1024];
    if (getcwd(buffer, sizeof(buffer)) != nullptr) {
        std::string currentDir(buffer);

        // 拼接文件路径
        std::string absoluteXmlPath = currentDir + "/" + xmlPath;
        std::string absoluteImagePath = currentDir + "/" + imagePath;

        // 加载纹理
        if (!texture.loadFromFile(absoluteImagePath)) {
            std::cerr << "Failed to load texture from " << absoluteImagePath << std::endl;
            return false;
        }

        // 加载sprites
        if (!loadSprites(absoluteXmlPath)) {
            std::cerr << "Failed to load sprites from " << absoluteXmlPath << std::endl;
            return false;
        }

        return true;
    } else {
        std::cerr << "Failed to get current working directory" << std::endl;
        return false;
    }
}

bool SpriteLoader::loadSprites(const std::string& xmlPath) {
    using namespace tinyxml2;

    XMLDocument doc;
    if (doc.LoadFile(xmlPath.c_str()) != XML_SUCCESS) {
        std::cerr << "Failed to load XML file: " << xmlPath << std::endl;
        return false;
    }

    XMLElement* root = doc.FirstChildElement("TextureAtlas");
    if (!root) {
        std::cerr << "Invalid XML format: Missing TextureAtlas element" << std::endl;
        return false;
    }

    for (XMLElement* element = root->FirstChildElement("SubTexture"); element != nullptr; element = element->NextSiblingElement("SubTexture")) {
        const char* name = element->Attribute("name");
        int x, y, width, height;

        if (element->QueryIntAttribute("x", &x) != XML_SUCCESS ||
            element->QueryIntAttribute("y", &y) != XML_SUCCESS ||
            element->QueryIntAttribute("width", &width) != XML_SUCCESS ||
            element->QueryIntAttribute("height", &height) != XML_SUCCESS) {
            std::cerr << "Failed to parse SubTexture attributes for element" << std::endl;
            continue;
        }

        sf::Sprite sprite;
        sprite.setTexture(texture);
        sprite.setTextureRect(sf::IntRect(x, y, width, height));

        if (name) {
            sprites[name] = sprite;
        } else {
            std::cerr << "SubTexture missing 'name' attribute" << std::endl;
        }
    }

    return true;
}

void SpriteLoader::drawSprite(const std::string& name, sf::RenderWindow& window, const sf::Vector2f& position) {
    std::map<std::string, sf::Sprite>::const_iterator it = sprites.find(name);
    if (it != sprites.end()) {
        sf::Sprite sprite(it->second);
        sprite.setPosition(position);
        window.draw(sprite);
    } else {
        std::cerr << "Sprite " << name << " not found" << std::endl;
    }
}

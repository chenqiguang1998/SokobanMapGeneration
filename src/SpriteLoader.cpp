#include "SpriteLoader.h"
#include "tinyxml2.h"
#include <iostream>
#include <unistd.h> // For getcwd

// 将纹理类型映射到字符串
std::string SpriteLoader::textureTypeToString(TextureType type) const {
    switch (type) {
        case TextureType::CHARACTER1: return "Character1.png";
        case TextureType::CHARACTER10: return "Character10.png";
        case TextureType::CHARACTER2: return "Character2.png";
        case TextureType::CHARACTER3: return "Character3.png";
        case TextureType::CHARACTER4: return "Character4.png";
        case TextureType::CHARACTER5: return "Character5.png";
        case TextureType::CHARACTER6: return "Character6.png";
        case TextureType::CHARACTER7: return "Character7.png";
        case TextureType::CHARACTER8: return "Character8.png";
        case TextureType::CHARACTER9: return "Character9.png";

        case TextureType::CRATE_DARK_BEIGE: return "CrateDark_Beige.png";
        case TextureType::CRATE_DARK_BLACK: return "CrateDark_Black.png";
        case TextureType::CRATE_DARK_BLUE: return "CrateDark_Blue.png";
        case TextureType::CRATE_DARK_BROWN: return "CrateDark_Brown.png";
        case TextureType::CRATE_DARK_GRAY: return "CrateDark_Gray.png";
        case TextureType::CRATE_DARK_PURPLE: return "CrateDark_Purple.png";
        case TextureType::CRATE_DARK_RED: return "CrateDark_Red.png";
        case TextureType::CRATE_DARK_YELLOW: return "CrateDark_Yellow.png";

        case TextureType::CRATE_BEIGE: return "Crate_Beige.png";
        case TextureType::CRATE_BLACK: return "Crate_Black.png";
        case TextureType::CRATE_BLUE: return "Crate_Blue.png";
        case TextureType::CRATE_BROWN: return "Crate_Brown.png";
        case TextureType::CRATE_GRAY: return "Crate_Gray.png";
        case TextureType::CRATE_PURPLE: return "Crate_Purple.png";
        case TextureType::CRATE_RED: return "Crate_Red.png";
        case TextureType::CRATE_YELLOW: return "Crate_Yellow.png";

        case TextureType::ENDPOINT_BEIGE: return "EndPoint_Beige.png";
        case TextureType::ENDPOINT_BLACK: return "EndPoint_Black.png";
        case TextureType::ENDPOINT_BLUE: return "EndPoint_Blue.png";
        case TextureType::ENDPOINT_BROWN: return "EndPoint_Brown.png";
        case TextureType::ENDPOINT_GRAY: return "EndPoint_Gray.png";
        case TextureType::ENDPOINT_PURPLE: return "EndPoint_Purple.png";
        case TextureType::ENDPOINT_RED: return "EndPoint_Red.png";
        case TextureType::ENDPOINT_YELLOW: return "EndPoint_Yellow.png";

        case TextureType::GROUND_GRAVEL_CONCRETE: return "GroundGravel_Concrete.png";
        case TextureType::GROUND_GRAVEL_DIRT: return "GroundGravel_Dirt.png";
        case TextureType::GROUND_GRAVEL_GRASS: return "GroundGravel_Grass.png";
        case TextureType::GROUND_GRAVEL_SAND: return "GroundGravel_Sand.png";
        case TextureType::GROUND_CONCRETE: return "Ground_Concrete.png";
        case TextureType::GROUND_DIRT: return "Ground_Dirt.png";
        case TextureType::GROUND_GRASS: return "Ground_Grass.png";
        case TextureType::GROUND_SAND: return "Ground_Sand.png";

        case TextureType::WALL_ROUND_BEIGE: return "WallRound_Beige.png";
        case TextureType::WALL_ROUND_BLACK: return "WallRound_Black.png";
        case TextureType::WALL_ROUND_BROWN: return "WallRound_Brown.png";
        case TextureType::WALL_ROUND_GRAY: return "WallRound_Gray.png";
        case TextureType::WALL_BEIGE: return "Wall_Beige.png";
        case TextureType::WALL_BLACK: return "Wall_Black.png";
        case TextureType::WALL_BROWN: return "Wall_Brown.png";
        case TextureType::WALL_GRAY: return "Wall_Gray.png";

        default: return "Unknown.png";
    }
}

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

void SpriteLoader::drawSprite(TextureType type, sf::RenderWindow& window, const sf::Vector2f& position) {
    std::string textureName = textureTypeToString(type);
    auto it = sprites.find(textureName);
    if (it != sprites.end()) {
        sf::Sprite sprite(it->second);
        sprite.setPosition(position);
        window.draw(sprite);
    } else {
        std::cerr << "Sprite " << textureName << " not found" << std::endl;
    }
}

void SpriteLoader::drawAllSprites(sf::RenderWindow& window) {
    for (const auto& pair : sprites) {
        sf::Sprite sprite = pair.second;
        window.draw(sprite);
    }
}

void SpriteLoader::drawSpritesInRegion(sf::RenderWindow& window, const sf::FloatRect& region) {
    for (const auto& pair : sprites) {
        sf::Sprite sprite = pair.second;
        sf::FloatRect spriteBounds = sprite.getGlobalBounds();

        if (region.intersects(spriteBounds)) {
            window.draw(sprite);
        }
    }
}

std::string SpriteLoader::getTextureName(TextureType type) const {
    return textureTypeToString(type);
}


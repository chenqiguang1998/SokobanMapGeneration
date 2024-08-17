#include "TextureAtlasParser.h"
#include <boost/filesystem.hpp>
#include <iostream>
#ifdef TEST_MODE
TextureAtlas::TextureAtlas()
    : imagePath("../res/sprites.png"), atlasPath("../res/sprites.xml") {
        printf("test mode!\n");
#else
        TextureAtlas::TextureAtlas()
    : imagePath("sprites.png"), atlasPath("sprites.xml") {
#endif
    // Convert relative paths to absolute paths
    imagePath = toAbsolutePath(imagePath);
    atlasPath = toAbsolutePath(atlasPath);
}

TextureAtlas::~TextureAtlas() {}

bool TextureAtlas::load() {
    if (!texture.loadFromFile(imagePath)) {
        std::cerr << "Error loading spritesheet" << std::endl;
        return false;
    }
    return parseAtlas();
}

bool TextureAtlas::parseAtlas() {
    tinyxml2::XMLDocument doc;
    if (doc.LoadFile(atlasPath.c_str()) != tinyxml2::XML_SUCCESS) {
        std::cerr << "Error loading XML file" << std::endl;
        return false;
    }

    tinyxml2::XMLElement* root = doc.FirstChildElement("TextureAtlas");
    if (!root) {
        std::cerr << "No TextureAtlas found in XML" << std::endl;
        return false;
    }

    tinyxml2::XMLElement* subTexture = root->FirstChildElement("SubTexture");
    while (subTexture) {
        SubTexture subTex;
        subTex.name = subTexture->Attribute("name");
        subTexture->QueryIntAttribute("x", &subTex.x);
        subTexture->QueryIntAttribute("y", &subTex.y);
        subTexture->QueryIntAttribute("width", &subTex.width);
        subTexture->QueryIntAttribute("height", &subTex.height);

        subTextures[subTex.name] = sf::IntRect(subTex.x, subTex.y, subTex.width, subTex.height);

        subTexture = subTexture->NextSiblingElement("SubTexture");
    }

    return true;
}

sf::Texture* TextureAtlas::getTexture(const std::string& name) {
    if (subTextures.find(name) == subTextures.end()) {
        return nullptr;
    }
    sf::Texture* subTexture = new sf::Texture();
    sf::Image image = texture.copyToImage();
    subTexture->loadFromImage(image, subTextures[name]);
    return subTexture;
}

const std::unordered_map<std::string, sf::IntRect>& TextureAtlas::getSubTextures() const {
    return subTextures;
}

std::string TextureAtlas::toAbsolutePath(const std::string& relativePath) const {
    boost::filesystem::path relPath(relativePath);
    boost::filesystem::path absPath = boost::filesystem::absolute(relPath);
    return absPath.string();
}

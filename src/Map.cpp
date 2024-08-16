#include "pch.h"
#include "Map.h"
#include <iostream>
using namespace std;

Map::Map() {
    // Linux 下不需要 _setmode 和 _O_U16TEXT 设置
}

Map::~Map() {
}

void Map::drawMap(State * state) {
    for (int i = 0; i < state->height; i++) {
        for (int j = 0; j < state->width; j++) {
            this->drawTile(*(state->tiles + i * state->width + j));
        }
        std::cout << "\n";
    }
}

void Map::drawTile(TileType type) {
    switch (type) {
    case Wall:
        std::cout << "\033[31m▓\033[0m"; // 红色文字
        break;
    case Aid:
        std::cout << "\033[41;37m⿴\033[0m"; // 背景红，前景白
        break;
    case Box:
        std::cout << "\033[42;31m■\033[0m"; // 背景绿，前景红
        break;
    case BoxinAid:
        std::cout << "\033[43;31m❐\033[0m"; // 背景黄，前景红
        break;
    case Character:
        std::cout << "\033[44;33m☺\033[0m"; // 背景蓝，前景黄
        break;
    case CharacterinAid:
        std::cout << "\033[45;32m☺a\033[0m"; // 背景紫，前景绿
        break;
    default:
        std::cout << "  "; // 默认空格
        break;
    }
}

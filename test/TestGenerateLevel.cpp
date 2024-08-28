#include "pch.h"
#include "GenerateLevel.h"
#include <cassert>
#include <iostream>

void printMap(const GenerateLevel& level) {
    level.save(false); // 打印当前地图状态
}

void testGenerateLevel() {
    // 创建一个 10x10 的生成关卡对象
    GenerateLevel level(10, 10);

    // 检查初始化瓷砖状态
    for (int i = 0; i < 10; ++i) {
        for (int j = 0; j < 10; ++j) {
            if (i == 0 || i == 9 || j == 0 || j == 9) {
                assert(level.getCurrentTile(j, i) == Wall);
            } else {
                assert(level.getCurrentTile(j, i) == Floor);
            }
        }
    }

    // 生成角色并检查
    if (!level.generateChar()) {
        std::cerr << "生成角色失败\n";
    }
    bool charGenerated = false;
    for (int i = 0; i < level.getHeight(); ++i) {
        for (int j = 0; j < level.getWidth(); ++j) {
            if (level.getCurrentTile(j, i) == Character) {
                charGenerated = true;
                break;
            }
        }
        if (charGenerated) break;
    }
    assert(charGenerated);
    printMap(level); // 打印生成角色后的地图

    // 生成箱子并检查
    if (!level.generateBox()) {
        std::cerr << "生成箱子失败\n";
    }
    bool boxGenerated = false;
    for (int i = 0; i < level.getHeight(); ++i) {
        for (int j = 0; j < level.getWidth(); ++j) {
            if (level.getCurrentTile(j, i) == Box) {
                boxGenerated = true;
                break;
            }
        }
        if (boxGenerated) break;
    }
    assert(boxGenerated);
    printMap(level); // 打印生成箱子后的地图

    // 生成墙并检查
    if (!level.generateWall()) {
        std::cerr << "生成墙失败\n";
    }
    bool wallGenerated = false;
    for (int i = 0; i < level.getHeight(); ++i) {
        for (int j = 0; j < level.getWidth(); ++j) {
            if (level.getCurrentTile(j, i) == Wall) {
                wallGenerated = true;
                break;
            }
        }
        if (wallGenerated) break;
    }
    assert(wallGenerated);
    printMap(level); // 打印生成墙后的地图

    // 生成辅助道具并检查
    if (!level.generateAid()) {
        std::cerr << "生成辅助道具失败\n";
    }
    bool aidGenerated = false;
    for (int i = 0; i < level.getHeight(); ++i) {
        for (int j = 0; j < level.getWidth(); ++j) {
            if (level.getCurrentTile(j, i) == Aid) {
                aidGenerated = true;
                break;
            }
        }
        if (aidGenerated) break;
    }
    assert(aidGenerated);
    printMap(level); // 打印生成辅助道具后的地图

    std::cout << "所有测试通过！\n";
}

int main() {
    testGenerateLevel();
    return 0;
}

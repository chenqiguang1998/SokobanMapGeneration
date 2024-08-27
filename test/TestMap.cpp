#include <SFML/Graphics.hpp>
#include "Map.h"
#include "State.h"
#include <iostream>
#include <string>

// 示例地图瓦片
TileType tilesample[49] = {
    Wall, Wall, Wall, Wall, Wall, Wall, Wall,
    Wall, Aid, Floor, Aid, Floor, Aid, Wall,
    Wall, Floor, Box, Box, Box, Floor, Wall,
    Wall, Aid, Box, Character, Box, Aid, Wall,
    Wall, Floor, Box, Box, Box, Floor, Wall,
    Wall, Aid, Floor, Aid, Floor, Aid, Wall,
    Wall, Wall, Wall, Wall, Wall, Wall, Wall,
};

// 创建一个包含示例瓦片的 State 对象
State* createSampleState(int width, int height) {
    State* state = new State(width, height);
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            state->setTile(x, y, tilesample[y * width + x]);
        }
    }
    return state;
}

// 测试绘制地图的函数
void testMap() {
    int width = 7;
    int height = 7;
    State* state = createSampleState(width, height);

    std::cout << "请选择功能：" << std::endl;
    std::cout << "1. 控制台模式 - 在控制台中绘制地图" << std::endl;
    std::cout << "2. 纹理模式 - 使用 SFML 纹理绘制地图" << std::endl;
    std::cout << "3. 退出" << std::endl;
    std::cout << "请输入您的选择（1/2/3）: ";

    int choice;
    std::cin >> choice;

    Map map;

    if (choice == 1) {
        map.drawMap(state);
    } else if (choice == 2) {
        sf::RenderWindow window;
        sf::RenderTexture renderTexture;

        // 设置窗口和渲染纹理的标题
        std::string windowTitle = "Map Test - " + std::to_string(width) + "x" + std::to_string(height);
        map.setWindowAndRenderTexture(window, renderTexture, state, windowTitle);

        sf::Texture texture;
        if (!texture.loadFromFile("../res/sprites.png")) {
            std::cerr << "加载纹理失败" << std::endl;
            return;
        }

        // 使用 columnMajor 参数调用 drawMapWithTexture
        map.drawMapWithTexture(renderTexture, state, texture, true);

        sf::Sprite sprite(renderTexture.getTexture());
        window.clear();
        window.draw(sprite);
        window.display();

        while (window.isOpen()) {
            sf::Event event;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    window.close();
                }
            }
        }
    } else if (choice == 3) {
        delete state;
        exit(0); // Exit the program
    } else {
        std::cerr << "无效选择，请输入1、2或3。" << std::endl;
    }

    delete state; // Clean up the allocated State object
}

int main() {
    std::cout << "欢迎使用地图测试程序！" << std::endl;
    testMap();
    return 0;
}

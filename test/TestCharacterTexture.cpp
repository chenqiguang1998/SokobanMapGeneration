#include <SFML/Graphics.hpp>
#include "Map.h"
#include "State.h"
#include <iostream>

// 设置初始人物状态
State::CharacterState initCharacterState() {
    State::CharacterState characterState;
    characterState.dir = Direction::D_RIGHT;  // 初始方向为右
    characterState.isMoving = false;        // 初始状态为静止
    characterState.stepsMoved = 0;          // 初始步数为0
    return characterState;
}

// 打印角色状态信息
void printCharacterState(const State::CharacterState& characterState) {
    std::string direction;
    switch (characterState.dir) {
        case Direction::D_LEFT: direction = "左"; break;
        case Direction::D_RIGHT: direction = "右"; break;
        case Direction::D_UP: direction = "上"; break;
        case Direction::D_DOWN: direction = "下"; break;
    }
    std::cout << "角色状态: 方向: " << direction
              << ", 移动状态: " << (characterState.isMoving ? "移动中" : "静止")
              << ", 步数: " << characterState.stepsMoved << std::endl;
}

int main() {
    // 创建窗口
    sf::RenderWindow window(sf::VideoMode(800, 600), "角色控制测试");

    // 加载纹理
    sf::Texture texture;
    if (!texture.loadFromFile("../res/sprites.png")) {
        std::cerr << "无法加载纹理文件！" << std::endl;
        return -1;
    }

    // 初始化地图和状态
    Map map;
    State state(10, 10);  // 创建一个10x10的地图
    state.setLocation(5, 5);  // 设置角色的初始位置
    state.setCharacterState(initCharacterState());

    // 游戏主循环
    while (window.isOpen()) {
        // 处理事件
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        // 获取角色状态
        State::CharacterState characterState = state.getCharacterState();

        // 处理按键
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            characterState.dir = Direction::D_LEFT;
            characterState.isMoving = true;
        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            characterState.dir = Direction::D_RIGHT;
            characterState.isMoving = true;
        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
            characterState.dir = Direction::D_UP;
            characterState.isMoving = true;
        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
            characterState.dir = Direction::D_DOWN;
            characterState.isMoving = true;
        } else {
            characterState.isMoving = false;
        }

        // 更新步数
        if (characterState.isMoving) {
            characterState.stepsMoved++;
        }

        // 更新角色位置
        // 假设角色每移动一步，向当前方向移动一个单位
        if (characterState.isMoving) {
            switch (characterState.dir) {
                case Direction::D_LEFT:
                    state.moveCharacter(-1, 0); // 自定义 moveCharacter 函数
                    break;
                case Direction::D_RIGHT:
                    state.moveCharacter(1, 0);
                    break;
                case Direction::D_UP:
                    state.moveCharacter(0, -1);
                    break;
                case Direction::D_DOWN:
                    state.moveCharacter(0, 1);
                    break;
            }
        }

        // 打印角色状态信息
        printCharacterState(characterState);

        // 清除窗口
        window.clear();

        // 绘制地图和角色
        sf::RenderTexture renderTexture;
        renderTexture.create(800, 600);  // 设置合适的尺寸
        map.setWindowAndRenderTexture(window, renderTexture, &state, "角色控制测试");
        map.drawMapWithTexture(renderTexture, &state, texture, false);

        // 显示绘制内容
        sf::Sprite sprite(renderTexture.getTexture());
        window.draw(sprite);
        window.display();
    }

    return 0;
}

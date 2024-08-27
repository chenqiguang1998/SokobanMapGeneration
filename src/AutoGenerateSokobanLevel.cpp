#include "pch.h"
#include <iostream>
#include "State.h"
#include "Map.h"
#include "Solver.h"
#include "GenerateLevel.h"
#include <ctime>
#include <unistd.h> // 用于sleep函数
#include <vector>
#include <SFML/Graphics.hpp>

// #define DEBUG_MODE

TileType tilesample[49] = {
    Wall, Wall, Wall, Wall, Wall, Wall, Wall,
    Wall, Aid, Floor, Aid, Floor, Aid, Wall,
    Wall, Floor, Box, Box, Box, Floor, Wall,
    Wall, Aid, Box, Character, Box, Aid, Wall,
    Wall, Floor, Box, Box, Box, Floor, Wall,
    Wall, Aid, Floor, Aid, Floor, Aid, Wall,
    Wall, Wall, Wall, Wall, Wall, Wall, Wall,
};

State* createSampleState(int width, int height) {
    State* state = new State(width, height);
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            state->setTile(x, y, tilesample[y * width + x]);
        }
    }
    return state;
}

void drawMapConsole(Map& map, State* state) {
    std::cout << "在控制台中绘制地图：" << std::endl;
    map.drawMap(state);
}

void drawMapWindow(sf::RenderWindow& window, Map& map, State* state) {
    sf::RenderTexture renderTexture;
    if (!renderTexture.create(window.getSize().x, window.getSize().y)) {
        std::cerr << "创建渲染纹理失败" << std::endl;
        return;
    }

    sf::Texture texture;
    if (!texture.loadFromFile("../res/sprites.png")) {
        std::cerr << "加载纹理失败" << std::endl;
        return;
    }

    map.drawMapWithTexture(state, texture, true);
    sf::Sprite sprite(renderTexture.getTexture());

    window.clear();
    window.draw(sprite);
    window.display();
}

void initAndDrawMap(int width, int height, int mode) {
    State* state = createSampleState(width, height);
    Map map;

    if (mode == 1 || mode == 3) {
        drawMapConsole(map, state);
    }

    if (mode == 2 || mode == 3) {
        sf::RenderWindow window(sf::VideoMode(800, 600), "Map Test");
        drawMapWindow(window, map, state);

        while (window.isOpen()) {
            sf::Event event;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    window.close();
                }
            }
        }
    }

    delete state;
}

void solvePuzzle() {
    State* state = createSampleState(7, 7);
    Map* map = new Map();
    Solver solver(state);

    #ifdef DEBUG_MODE
        initAndDrawMap(7, 7, 3);
    #else
        map->drawMap(state);
    #endif

    int res = solver.run();
    if (res == -1) {
        std::cerr << "\033[31m该关卡无解！！！\033[0m\n";
    }
    else if (res == 1) {
        map->drawMap(state);
        int stepnum = solver.getStepList().size();
        solver.drawStep();
        std::cout << "\033[31m总共的迭代次数\033[0m" << solver.getIterNum() << "\n";
        std::cout << "\033[31m最短完成步数\033[0m" << stepnum << "\n";
    }

    delete state;
    delete map;
}

void generateLevel() {
    GenerateLevel gl(7, 7);
    TileType* tiles = gl.tiles;

    State* state = new State(7, 7);
    state->setLevel((TileType*)tiles);
    Map* map = new Map();
    Solver solver(state);

    #ifdef DEBUG_MODE
        initAndDrawMap(7, 7, 3);
    #else
        map->drawMap(state);
    #endif

    srand(static_cast<unsigned>(time(NULL)) * 10);
    int gtime = 0;
    int trytime = 100;
    while (trytime--) {
        usleep(50000); // 50 毫秒
        gtime++;
        if (rand() % 2) {
            gl.generateBox();
            gl.generateAid();
        }
        else {
            gl.generateWall();
        }
        state->setLevel((TileType*)tiles);
        Solver solver(state);
        std::cout << "\033[31m迭代第" << gtime << "次生成的关卡\033[0m\n";

        int res = solver.run();
        if (res == -1) {
            std::cerr << "\033[31m该关卡无解！！！\033[0m\n";
            gl.load();
        }
        else if (res == 1) {
            map->drawMap(state);
            trytime = 100;
            int stepnum = solver.getStepList().size();
            std::cout << "\033[31m总共的迭代次数\033[0m" << solver.getIterNum() << "\n";
            std::cout << "\033[31m最短完成步数\033[0m" << stepnum << "\n";
            gl.save();
        }
    }
    solver.drawStep();
    getchar();

    delete state;
    delete map;
}

void playGame() {
    State* state = createSampleState(7, 7);
    Map* map = new Map();

    while (!state->ifWin()) {
        #ifdef DEBUG_MODE
            initAndDrawMap(7, 7, 3);
        #else
            map->drawMap(state);
        #endif

        std::cout << "\033[1m请输入操作：w向上，s向下，a向左，d向右\033[0m\n";
        char c = getchar();
        getchar(); // 处理换行符
        if (c == 'w') {
            state->up();
        }
        else if (c == 's') {
            state->down();
        }
        else if (c == 'a') {
            state->left();
        }
        else if (c == 'd') {
            state->right();
        }
    }
    map->drawMap(state);
    std::cout << "\033[31m恭喜胜利！！！\033[0m\n";

    delete state;
    delete map;
}

void updateMap(State* state, Map& map, sf::RenderWindow& window, const std::vector<sf::IntRect>& dirtyRects) {
    for (const auto& rect : dirtyRects) {
        const State& m_state = *state;
        sf::View view(sf::FloatRect(rect.left, rect.top, rect.width, rect.height));
        window.setView(view);
        
        window.clear(sf::Color::Transparent);
        map.drawMapArea(m_state, window, rect);
        window.display();
    }
}

void moveCharacter(State* state, Map& map, sf::RenderWindow& window, Direction direction) {
    sf::Vector2i previousPosition = state->getCharacterPosition();
    state->moveCharacter(direction);
    sf::Vector2i newPosition = state->getCharacterPosition();

    std::vector<sf::IntRect> dirtyRects = {
        sf::IntRect(previousPosition.x * TILE_SIZE, previousPosition.y * TILE_SIZE, TILE_SIZE, TILE_SIZE),
        sf::IntRect(newPosition.x * TILE_SIZE, newPosition.y * TILE_SIZE, TILE_SIZE, TILE_SIZE)
    };

    updateMap(state, map, window, dirtyRects);
}

int main() {
    int choice;
    while (true) {
        std::cout << "请选择功能：\n";
        std::cout << "1. 解决谜题 (solve)\n";
        std::cout << "2. 生成新关卡 (generate)\n";
        std::cout << "3. 玩游戏 (play)\n";
        std::cout << "4. 退出 (q)\n";
        std::cout << "请输入数字选择功能：";
        std::cin >> choice;

        switch (choice) {
            case 1:
                solvePuzzle();
                break;
            case 2:
                generateLevel();
                break;
            case 3:
                playGame();
                break;
            case 4:
                std::cout << "程序已退出。\n";
                return 0;
            default:
                std::cerr << "无效的命令。请使用 1 解决谜题，2 生成关卡，3 玩游戏，或 4 退出。\n";
        }
    }

    return 0;
}

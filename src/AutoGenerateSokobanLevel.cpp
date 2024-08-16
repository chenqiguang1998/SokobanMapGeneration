#include "pch.h"
#include <iostream>
#include "State.h"
#include "Map.h"
#include "Solver.h"
#include "GenerateLevel.h"
#include <ctime>
#include <unistd.h> // 用于sleep函数

void solvePuzzle() {
    // 初始化状态、地图和求解器
    TileType tilesample[49] = {
        Wall, Wall, Wall, Wall, Wall, Wall, Wall,
        Wall, Aid, Floor, Aid, Floor, Aid, Wall,
        Wall, Floor, Box, Box, Box, Floor, Wall,
        Wall, Aid, Box, Character, Box, Aid, Wall,
        Wall, Floor, Box, Box, Box, Floor, Wall,
        Wall, Aid, Floor, Aid, Floor, Aid, Wall,
        Wall, Wall, Wall, Wall, Wall, Wall, Wall,
    };
    TileType *tiles = new TileType[49];
    for (int i = 0; i < 49; i++) {
        tiles[i] = tilesample[i];
    }
    State *state = new State(7, 7);
    state->setLevel((TileType *)tiles);
    Map *map = new Map();
    Solver solver(state);
    map->drawMap(state);

    int res = solver.run();
    if (res == -1) {
        std::cerr << "\033[31m该关卡无解！！！\033[0m\n";  // 使用 ANSI 颜色码设置字体颜色
    }
    else if (res == 1) {
        map->drawMap(state);
        int stepnum = solver.getStepList().size(); // 使用公共访问器函数
        solver.drawStep();
        std::cout << "\033[31m总共的迭代次数\033[0m" << solver.getIterNum() << "\n"; // 使用公共访问器函数
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
    map->drawMap(state);

    // 迭代生成关卡
    srand(static_cast<unsigned>(time(NULL)) * 10);
    int gtime = 0;
    int trytime = 100;
    while (trytime--)
    {
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
            int stepnum = solver.getStepList().size(); // 使用公共访问器函数
            // solver.drawStep();
            std::cout << "\033[31m总共的迭代次数\033[0m" << solver.getIterNum() << "\n"; // 使用公共访问器函数
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
    // 初始化状态、地图和求解器
    TileType tilesample[49] = {
        Wall, Wall, Wall, Wall, Wall, Wall, Wall,
        Wall, Aid, Floor, Aid, Floor, Aid, Wall,
        Wall, Floor, Box, Box, Box, Floor, Wall,
        Wall, Aid, Box, Character, Box, Aid, Wall,
        Wall, Floor, Box, Box, Box, Floor, Wall,
        Wall, Aid, Floor, Aid, Floor, Aid, Wall,
        Wall, Wall, Wall, Wall, Wall, Wall, Wall,
    };
    TileType *tiles = new TileType[49];
    for (int i = 0; i < 49; i++) {
        tiles[i] = tilesample[i];
    }
    State *state = new State(7, 7);
    state->setLevel((TileType *)tiles);
    Map *map = new Map();

    // 游戏循环
    while (!state->ifWin()) {
        map->drawMap(state);
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
                return 0;
            default:
                std::cerr << "无效的命令。请使用 1 解决谜题，2 生成关卡，3 玩游戏，或 4 退出。\n";
        }
    }

    return 0;
}

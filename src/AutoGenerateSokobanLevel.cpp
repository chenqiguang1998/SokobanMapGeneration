#include "pch.h"
#include <iostream>
#include "State.h"
#include "Map.h"
#include "Solver.h"
#include "GenerateLevel.h"
#include <ctime>
#include <unistd.h> // 用于sleep函数

int main()
{
    // 以下注释掉的算法可以用来解一个推箱子谜题。
    /*
    TileType tilesample[49] = {
        Wall, Wall, Wall, Wall, Wall, Wall, Wall,
        Wall, Aid, Floor, Aid, Floor, Aid, Wall,
        Wall, Floor, Box, Box, Box, Floor, Wall,
        Wall, Aid, Box, Character, Box, Aid, Wall,
        Wall, Floor, Box, Box, Box, Floor, Wall,
        Wall, Aid, Floor, Aid, Floor, Aid, Wall,
        Wall, Wall, Wall, Wall, Wall, Wall, Wall,
    };
    TileType * tiles = new TileType[49];
    for (int i = 0; i < 49; i++) {
        tiles[i] = tilesample[i];
    }
    State * state = new State(7, 7);
    state->setLevel((TileType *)tiles);
    Map * map = new Map();
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
    */
    // 以下算法用来生成一个新的推箱子关卡
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

    // 以下注释掉的算法可以用来让玩家玩一局推箱子，需要给定一个关卡的初始state
    /*
    while (!state->ifWin()) {
        map->drawMap(state);
        std::cout << "\033[1m请输入操作：w向上，s向下，a向左，d向右\033[0m\n";
        char c = getchar();
        getchar();
        if (c == 'w') {
            state->up();
        }
        if (c == 's') {
            state->down();
        }
        if (c == 'a') {
            state->left();
        }
        if (c == 'd') {
            state->right();
        }
    }
    map->drawMap(state);
    std::cout << "\033[31m恭喜胜利！！！\033[0m\n";
    */
    delete state;
    delete map;
}

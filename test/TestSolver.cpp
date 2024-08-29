#include "pch.h"
#include "Solver.h"
#include "State.h"  // 假设你的 State 类定义在这个头文件中
#include <iostream>
#include <cassert>

// 创建测试状态的函数
State* createTestState(int width, int height, const TileType* tiles) {
    State* state = new State(width, height);
    for (int i = 0; i < width * height; ++i) {
        state->setTile(i % width, i / width, tiles[i]); // 设置每个瓷砖的类型
    }
    return state;
}

// 测试 Solver 类的不同求解算法
void testSolverWithSampleMap() {
    // 定义地图尺寸
    const int width = 7;
    const int height = 7;

    // 定义地图数据
    TileType tilesample[49] = {
        Wall, Wall, Wall, Wall, Wall, Wall, Wall,
        Wall, Aid, Floor, Aid, Floor, Aid, Wall,
        Wall, Floor, Box, Box, Box, Floor, Wall,
        Wall, Aid, Box, Character, Box, Aid, Wall,
        Wall, Floor, Box, Box, Box, Floor, Wall,
        Wall, Aid, Floor, Aid, Floor, Aid, Wall,
        Wall, Wall, Wall, Wall, Wall, Wall, Wall,
    };

    // // 创建新的初始状态以测试 A* 算法
    // // 为了确保独立性，最好重新创建一个初始状态
    // State* initialStateForAStar = createTestState(width, height, tilesample);

    // // 测试 A* 搜索算法
    // std::cout << "运行 A* 搜索算法...\n";
    // Solver solverAStar(initialStateForAStar);
    // int resultAStar = solverAStar.runAStar();  // 使用 A* 搜索
    // assert(resultAStar == 1);  // 假设 1 表示求解成功
    // std::cout << "A* 搜索算法测试通过！\n";
    // solverAStar.drawStep();


    // 创建初始状态
    State* initialState = createTestState(width, height, tilesample);

    // 测试深度优先搜索算法
    std::cout << "运行深度优先搜索算法...\n";
    Solver solverDFS(initialState);
    int resultDFS = solverDFS.run();  // 使用深度优先搜索
    assert(resultDFS == 1);  // 假设 1 表示求解成功
    std::cout << "深度优先搜索算法测试通过！\n";
    solverDFS.drawStep();



    // 清理内存
    delete initialState;
    // delete initialStateForAStar;
}

int main() {
    testSolverWithSampleMap();
    return 0;
}

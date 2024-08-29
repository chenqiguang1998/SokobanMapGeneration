#pragma once
#include "State.h"

class StateNode {
public:
    State* currentstate = nullptr;
    StateNode* nextstate = nullptr;
    StateNode* parentstate = nullptr;
    int depth = 0; // 节点的深度
    int heuristic = 0; // 启发式函数值，用于 A* 算法

    // 带参数的构造函数，用于初始化状态和启发式值
    StateNode(State* state = nullptr, int heuristicValue = 0) 
        : currentstate(state), heuristic(heuristicValue) {}

    // 析构函数
    ~StateNode();

    // 检查状态是否已经存在
    bool ifContain(State* state) const;

    // 添加新状态节点
    StateNode* addState(State* state);

    // 删除节点和其后续节点
    void deleteNode();
};

#pragma once
#include "State.h"
#include "StateNode.h"
#include "Map.h"
#include <list>

class Solver {
public:
    Solver(State* state);
    ~Solver();

    int run(); // 自动求解
    bool ifContain(State* state) const; // 检查状态是否已存在
    StateNode* addState(State* state); // 添加状态并返回相应的 StateNode
    void drawStep() const; // 绘制步骤

    // 提供公共访问器函数
    const std::list<StateNode*>& getStepList() const { return steplist; }
    int getIterNum() const { return iterNum; }

private:
    int calculateCode(State* state) const; // 计算状态的唯一编码

    int width;
    int height;
    StateNode** statenodes; // 存储状态节点的数组
    int* statenodesamount; // 存储每个状态编码对应的状态节点数量
    std::list<StateNode*> unexploidlist; // 存储待处理的状态节点列表
    std::list<StateNode*> steplist; // 存储解决方案步骤列表
    Map map; // 绘制地图
    int iterNum; // 迭代次数
};

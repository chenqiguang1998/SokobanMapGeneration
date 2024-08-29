#pragma once

#include "State.h"
#include "StateNode.h"
#include "Map.h"
#include <list>
#include <memory>
#include <set>
#include <queue>

class Solver {
public:
    // 构造函数，初始化解题器
    Solver(State* state);
    
    // 析构函数，清理资源
    ~Solver();

    // 自动求解方法
    int run();

    // A* 搜索方法
    int runAStar();

    // 检查状态是否已存在
    bool ifContain(State* state) const;

    // 添加状态并返回相应的 StateNode
    StateNode* addState(State* state);

    // 绘制步骤
    void drawStep() const;

    // 提供公共访问器函数
    const std::list<StateNode*>& getStepList() const { return steplist; }
    int getIterNum() const { return iterNum; }

private:
    // 计算状态的唯一编码
    int calculateCode(State* state) const;

    // 启发式函数：计算曼哈顿距离的示例
    int heuristic(State* state) const;

    int width; // 地图宽度
    int height; // 地图高度
    StateNode** statenodes; // 存储状态节点的数组
    int* statenodesamount; // 存储每个状态编码对应的状态节点数量
    std::list<StateNode*> unexploidlist; // 存储待处理的状态节点列表
    std::list<StateNode*> steplist; // 存储解决方案步骤列表
    Map map; // 绘制地图
    int iterNum; // 迭代次数
};

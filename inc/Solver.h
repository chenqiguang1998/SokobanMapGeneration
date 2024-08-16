#pragma once
#include "State.h"
#include "StateNode.h"
#include "Map.h"
#include <list>
#include <memory>

class Solver {
public:
    Solver(State* state);
    ~Solver();
    int run();
    bool ifContain(State* state) const;
    StateNode* addState(State* state);
    void drawStep();

    // 提供公共访问器函数
    const std::list<StateNode*>& getStepList() const { return steplist; }
    int getIterNum() const { return iterNum; }

private:
    int calculateCode(State* state) const;

    int width;
    int height;
    StateNode** statenodes;
    int* statenodesamount;
    std::list<StateNode*> unexploidlist;
    std::list<StateNode*> steplist;
    Map map;
    int iterNum;
};

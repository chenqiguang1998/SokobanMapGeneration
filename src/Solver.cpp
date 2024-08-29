#include "Solver.h"
#include <iostream>
#include <limits>

// 构造函数
Solver::Solver(State* state) : width(state->width), height(state->height), iterNum(0) {
    statenodes = new StateNode*[height * width]();
    statenodesamount = new int[height * width]();

    // 初始化 statenodes 数组
    for (int i = 0; i < height * width; ++i) {
        statenodes[i] = new StateNode();
    }

    State* newstate = state->clone();
    newstate->charFloodFill();
    unexploidlist.push_back(addState(newstate));
}

// 析构函数
Solver::~Solver() {
    for (int i = 0; i < height * width; ++i) {
        statenodes[i]->deleteNode();
        delete statenodes[i];
    }
    delete[] statenodes;
    delete[] statenodesamount;
}

// 计算状态的唯一编码
int Solver::calculateCode(State* state) const {
    int code = 0;
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            if (state->tiles[i * width + j] == Box || state->tiles[i * width + j] == BoxinAid) {
                code += i * width + j;
            }
        }
    }
    return code % (height * width);
}

// 启发式函数：计算曼哈顿距离的示例
int Solver::heuristic(State* state) const {
    int distance = 0;
    // 示例启发式函数：计算每个箱子到目标位置的曼哈顿距离
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            if (state->tiles[i * width + j] == Box) {
                // 曼哈顿距离计算示例
                // 假设目标位置是 (targetX, targetY)
                int targetX = 0; // 需要定义实际目标位置
                int targetY = 0; // 需要定义实际目标位置
                distance += std::abs(i - targetX) + std::abs(j - targetY);
            }
        }
    }
    return distance;
}

// 添加状态并返回相应的 StateNode
StateNode* Solver::addState(State* state) {
    int code = calculateCode(state);
    statenodesamount[code]++;
    return statenodes[code]->addState(state);
}

// 检查状态是否已存在
bool Solver::ifContain(State* state) const {
    int code = calculateCode(state);
    return statenodes[code]->ifContain(state);
}

// A* 搜索算法
int Solver::runAStar() {
    // 优先队列，用于 A* 搜索
    auto cmp = [](const StateNode* a, const StateNode* b) {
        return a->depth + a->heuristic > b->depth + b->heuristic;
    };
    std::priority_queue<StateNode*, std::vector<StateNode*>, decltype(cmp)> openList(cmp);
    std::set<State*> closedList;

    // 初始化
    State* startState = unexploidlist.front()->currentstate;
    StateNode* startNode = new StateNode(startState);
    startNode->depth = 0;
    startNode->heuristic = heuristic(startState);
    openList.push(startNode);

    while (!openList.empty()) {
        StateNode* currentNode = openList.top();
        openList.pop();
        State* currentState = currentNode->currentstate;

        if (currentState->ifWin()) {
            // 记录路径
            StateNode* stepNode = currentNode;
            while (stepNode != nullptr) {
                steplist.push_front(stepNode);
                stepNode = stepNode->parentstate;
            }
            return 1;
        }

        closedList.insert(currentState);

        Direction directions[4] = {D_UP, D_DOWN, D_LEFT, D_RIGHT};
        
        // 遍历所有箱子的位置
        for (int i = 0; i < height; ++i) {
            for (int j = 0; j < width; ++j) {
                if (currentState->tiles[i * width + j] == Box || currentState->tiles[i * width + j] == BoxinAid) {
                    for (Direction dir : directions) {
                        State* newState = currentState->boxPushed(i, j, dir); // 在此处使用 i 和 j
                        if (newState && closedList.find(newState) == closedList.end()) {
                            int g = currentNode->depth + 1;
                            int h = heuristic(newState);
                            StateNode* newNode = new StateNode(newState);
                            newNode->depth = g;
                            newNode->heuristic = h;
                            newNode->parentstate = currentNode;
                            openList.push(newNode);
                        }
                    }
                }
            }
        }
    }
    return -1;
}


// 自动求解方法（保留原有实现）
int Solver::run() {
    while (!unexploidlist.empty()) {
        iterNum++;

        StateNode* currentNode = unexploidlist.front();
        int depth = currentNode->depth;
        unexploidlist.pop_front();
        State* currentState = currentNode->currentstate;

        State* tempState = currentState->clone();
        Direction directions[4] = {D_UP, D_DOWN, D_LEFT, D_RIGHT};

        for (int i = 0; i < currentState->height; ++i) {
            for (int j = 0; j < currentState->width; ++j) {
                if (tempState->tiles[i * currentState->width + j] == Box || tempState->tiles[i * currentState->width + j] == BoxinAid) {
                    for (Direction dir : directions) {
                        State* newState = tempState->boxPushed(i, j, dir);
                        if (newState) {
                            newState->charFloodFill();
                            if (newState->ifDead() || ifContain(newState)) {
                                delete newState;
                            } else {
                                StateNode* newNode = addState(newState);
                                newNode->depth = depth + 1;
                                newNode->parentstate = currentNode;
                                unexploidlist.push_back(newNode);

                                if (newState->ifWin()) {
                                    StateNode* stepNode = newNode;
                                    while (stepNode != nullptr) {
                                        steplist.push_front(stepNode);
                                        stepNode = stepNode->parentstate;
                                    }
                                    return 1;
                                }
                            }
                        }
                    }
                }
            }
        }
        delete tempState;
    }
    return -1;
}

// 绘制步骤
void Solver::drawStep() const {
    for (const auto& step : steplist) {
        map.drawMap(step->currentstate);
        std::cout << "\n";
    }
}

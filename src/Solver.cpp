#include "pch.h"
#include "Solver.h"
#include <iostream>

Solver::Solver(State* state) {
    width = state->width;
    height = state->height;
    statenodes = new StateNode*[height * width]();
    statenodesamount = new int[height * width]();

    // Initialize statenodes with new StateNode
    for (int i = 0; i < height * width; ++i) {
        statenodes[i] = new StateNode();
    }

    State* newstate = state->clone();
    newstate->charFloodFill();
    unexploidlist.push_back(addState(newstate));
}

Solver::~Solver() {
    for (int i = 0; i < height * width; ++i) {
        statenodes[i]->deleteNode();
        delete statenodes[i];
    }
    delete[] statenodes;
    delete[] statenodesamount;
}

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

StateNode* Solver::addState(State* state) {
    int code = calculateCode(state);
    statenodesamount[code]++;
    return statenodes[code]->addState(state);
}

bool Solver::ifContain(State* state) const {
    int code = calculateCode(state);
    return statenodes[code]->ifContain(state);
}

// 自动求解
int Solver::run() {
    iterNum = 0;
    while (!unexploidlist.empty()) {
        iterNum++;

        StateNode* orisn = unexploidlist.front();
        int depth = orisn->depth;
        unexploidlist.pop_front();
        State* oristate = orisn->currentstate;

        State* tempstate = oristate->clone();
        Direction alldirection[4] = {D_UP, D_DOWN, D_LEFT, D_RIGHT};
        for (int i = 0; i < oristate->height; ++i) {
            for (int j = 0; j < oristate->width; ++j) {
                if (tempstate->tiles[i * oristate->width + j] == Box || tempstate->tiles[i * oristate->width + j] == BoxinAid) {
                    for (int k = 0; k < 4; ++k) {
                        State* newstate = tempstate->boxPushed(i, j, alldirection[k]);
                        if (newstate != nullptr) {
                            newstate->charFloodFill();
                            if (newstate->ifDead() || ifContain(newstate)) {
                                delete newstate;
                            } else {
                                StateNode* sn = addState(newstate);
                                sn->depth = depth + 1;
                                sn->parentstate = orisn;
                                unexploidlist.push_back(sn);

                                if (newstate->ifWin()) {
                                    StateNode* tempsn = sn;
                                    while (tempsn != nullptr) {
                                        steplist.push_front(tempsn);
                                        tempsn = tempsn->parentstate;
                                    }
                                    return 1;
                                }
                            }
                        }
                    }
                }
            }
        }
        delete tempstate;
    }
    return -1;
}

void Solver::drawStep(){
    for (const auto& step : steplist) {
        // 不能使用 const Map & 因为 map 是 Solver 的成员变量，不能在 const 成员函数中修改
        map.drawMap(step->currentstate);
        std::cout << "\n"; // Linux 下使用 std::cout
    }
}

#include "pch.h"
#include "Solver.h"
#include <iostream>

// Constructor
Solver::Solver(State* state) : width(state->width), height(state->height), iterNum(0) {
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

// Destructor
Solver::~Solver() {
    for (int i = 0; i < height * width; ++i) {
        statenodes[i]->deleteNode();
        delete statenodes[i];
    }
    delete[] statenodes;
    delete[] statenodesamount;
}

// Calculate a unique code for the given state
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

// Add a state to the list and return the corresponding StateNode
StateNode* Solver::addState(State* state) {
    int code = calculateCode(state);
    statenodesamount[code]++;
    return statenodes[code]->addState(state);
}

// Check if the state is already contained in the list
bool Solver::ifContain(State* state) const {
    int code = calculateCode(state);
    return statenodes[code]->ifContain(state);
}

// Automatically solve the puzzle
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

// Draw the steps to the map
void Solver::drawStep() const {
    for (const auto& step : steplist) {
        map.drawMap(step->currentstate);
        std::cout << "\n";
    }
}

#pragma once
#include "State.h"

class StateNode {
public:
    State* currentstate = nullptr;
    StateNode* nextstate = nullptr;
    StateNode* parentstate = nullptr;
    int depth = 0; // Initialize depth

    StateNode(); // Constructor
    ~StateNode(); // Destructor to handle clean-up

    bool ifContain(State* state) const; // Mark as const since it doesn't modify the object
    StateNode* addState(State* state);
    void deleteNode(); // Delete node and its next nodes
};

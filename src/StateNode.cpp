#include "StateNode.h"

void StateNode::deleteNode() {
    if (nextstate != nullptr) {
        nextstate->deleteNode();
    }
    if (currentstate != nullptr) {
        delete currentstate;
    }
    delete nextstate;  // Add this to avoid memory leak
    delete this;       // Add this to delete the current node
}

bool StateNode::ifContain(State *state) {
    if (this->currentstate != nullptr && this->currentstate->isEqual(state)) {
        return true;
    }
    if (this->nextstate != nullptr) {
        return this->nextstate->ifContain(state);
    }
    return false;
}

StateNode *StateNode::addState(State *state) {
    if (currentstate == nullptr) {
        this->currentstate = state;
        return this;
    }
    else if (nextstate != nullptr) {
        return nextstate->addState(state);
    }
    else {
        StateNode *sn = new StateNode();
        sn->currentstate = state;
        nextstate = sn;
        return sn;
    }
}

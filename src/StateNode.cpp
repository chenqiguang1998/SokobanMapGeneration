#include "StateNode.h"

// Constructor
StateNode::StateNode() : currentstate(nullptr), nextstate(nullptr), parentstate(nullptr), depth(0) {}

// Destructor
StateNode::~StateNode() {
    deleteNode(); // Ensure proper cleanup
}

// Function to check if the state is contained in the list
bool StateNode::ifContain(State* state) const {
    const StateNode* current = this;
    while (current != nullptr) {
        if (current->currentstate != nullptr && current->currentstate->isEqual(state)) {
            return true;
        }
        current = current->nextstate;
    }
    return false;
}

// Function to add a new state to the list
StateNode* StateNode::addState(State* state) {
    StateNode* current = this;
    while (true) {
        if (current->currentstate == nullptr) {
            current->currentstate = state;
            return current;
        } else if (current->nextstate == nullptr) {
            current->nextstate = new StateNode();
            current->nextstate->currentstate = state;
            return current->nextstate;
        }
        current = current->nextstate;
    }
}

// Function to delete nodes recursively
void StateNode::deleteNode() {
    while (nextstate != nullptr) {
        StateNode* next = nextstate;
        nextstate = nextstate->nextstate; // Move to the next node before deleting
        delete next;
    }
    delete currentstate; // Delete the state associated with this node
}

#include <iostream>
#include <stdexcept>
#include <vector>

using namespace std;

// ==============================================================================
// THREE STACKS, ONE ARRAY ARCHITECTURE (Using Free-List Trick)
// Supports K stacks (specifically 3 here) in a single array in strict O(1) time.
// ==============================================================================
template <typename Object>
class ThreeStacks {
private:
    Object* array; // Actual array holding data
    int* nextNode; // Array holding the "next" index pointers
    int top[3];    // Top indices for Stacks 1,2, and 3
    int freeSpot;  // Index of the first available free slot
    int capacity;

public:
    explicit ThreeStacks(int cap = 15) : capacity{ cap } {
        array = new Object[capacity];
        nextNode = new int[capacity];

        // Initially all stacks are empty, -1 represents empty
        for (int i = 0; i < 3; i++) {
            top[i] = -1;
        }

        // Initialize the free list
        freeSpot = 0;
        for (int i = 0; i < capacity - 1; i++) {
            nextNode[i] = i + 1;
        }
        nextNode[capacity - 1] = -1;
    }

    ~ThreeStacks() {
        delete[] array;
        delete[] nextNode;
    }

    void push(int stackNum, const Object& x) {
        if (stackNum < 0 || stackNum > 2) throw invalid_argument("Invalid Stack Number!");

        // Is there any slot left?
        if (freeSpot == -1) {
            throw overflow_error("Stack Overflow: The array is completely full!");
        }

        // Claim the first available free slot
        int insertIndex = freeSpot;

        // Update the freeSpot to the next available empty slot
        freeSpot = nextNode[insertIndex];

        // Insert the data
        array[insertIndex] = x;

        // Link this new node to the old top of the specific stack
        nextNode[insertIndex] = top[stackNum];

        // Update the top pointer of this stack to the new index
        top[stackNum] = insertIndex;

    }

    void pop(int stackNum) {
        if (stackNum < 0 || stackNum > 2) throw invalid_argument("Invalid Stack Number!");

        if (isEmpty(stackNum)) {
            throw underflow_error("Underflow: This stack is already empty!");
        }

        // Find the index
        int popIndex = top[stackNum];

        // Move the top pointer down
        top[stackNum] = nextNode[popIndex];

        // Link the pop index back into the Free list
        nextNode[popIndex] = freeSpot;
        freeSpot = popIndex;
    }

    // Peek and Helper Functions
    const Object& peek(int stackNum) const {
        if (stackNum < 0 || stackNum > 2) throw invalid_argument("Invalid Stack Number!");

        if (isEmpty(stackNum)) {
            throw underflow_error("Underflow: This stack is empty!");
        }
        return array[top[stackNum]];
    }

    bool isEmpty(int stackNum) const {
        return top[stackNum] == -1;
    }
};

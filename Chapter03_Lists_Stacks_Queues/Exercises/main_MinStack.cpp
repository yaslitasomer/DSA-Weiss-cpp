#include <iostream>
#include "../Stack/ArrayStack.h"
#include <stdexcept>

using namespace std;

// ==============================================================================
// THE MIN-STACK ARCHITECTURE (Exercise 3.25 A)
// Supports push, pop, and findMin in strict O(1) worst-case time.
// ==============================================================================
template <typename Object>
class MinStack {
private:
    ArrayStack<Object> mainStack;
    ArrayStack<Object> minStack; // Holds only the historical minimums

public:

    void push(const Object& x) {
        mainStack.push(x);

        // If the minStack is empty or the new value is smaller than/equal to the current minimum, we push it to minStack
        if (minStack.empty() || x <= minStack.top()) {
            minStack.push(x);
        }
    }

    void pop() {
        if (mainStack.empty()) {
            throw underflow_error("Underflow: Stack is already empty!");
        }

        if (minStack.top() == mainStack.top()) {
            minStack.pop();
        }
        mainStack.pop();
    }

    const Object& findMin() const {
        if (mainStack.empty()) {
            throw underflow_error("Underflow: Stack is empty!");
        }
        return minStack.top();
    }

    const Object& top() const {
        if (mainStack.empty()) {
            throw underflow_error("Underflow: Stack is empty!");
        }
        return mainStack.top();
    }

    bool isEmpty() const {
        return mainStack.empty();
    }
};

int main() {
    cout << "=== MIN-STACK (O(1) findMin) DIAGNOSTICS ===\n\n";

    MinStack<int> myMinStack;

    cout << ">>> TEST 1: Pushing Elements <<<\n";
    cout << "Pushing 5...\n"; myMinStack.push(5);
    cout << "Current Min: " << myMinStack.findMin() << "\n\n";

    cout << "Pushing 7...\n"; myMinStack.push(7);
    cout << "Current Min: " << myMinStack.findMin() << " (Should still be 5)\n\n";

    cout << "Pushing 3...\n"; myMinStack.push(3);
    cout << "Current Min: " << myMinStack.findMin() << " (New Min is 3!)\n\n";

    // Pushing a duplicate minimum
    cout << "Pushing another 3...\n"; myMinStack.push(3);
    cout << "Current Min: " << myMinStack.findMin() << "\n\n";

    cout << ">>> TEST 2: Popping Elements <<<\n";

    cout << "Popping the top element (3)...\n";
    myMinStack.pop();
    cout << "Current Min: " << myMinStack.findMin() << " (Should still be 3 because of the duplicate)\n\n";

    cout << "Popping the next element (3)...\n";
    myMinStack.pop();
    cout << "Current Min: " << myMinStack.findMin() << " (The 3 is gone, 5 is the King again!)\n\n";

    cout << "Popping the next element (7)...\n";
    myMinStack.pop();
    cout << "Current Min: " << myMinStack.findMin() << " (Still 5)\n\n";

    cout << "ALL DIAGNOSTICS COMPLETED SAFELY.\n";
    return 0;
}
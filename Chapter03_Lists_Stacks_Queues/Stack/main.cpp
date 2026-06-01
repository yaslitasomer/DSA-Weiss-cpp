#include <iostream>
#include <string>
#include <stdexcept>
#include "ArrayStack.h"
#include "LinkedStack.h"

using namespace std;

// ==============================================================================
// GENERIC TEST FUNCTION
// This function doesn't care what the underlying engine is (Array or Linked List).
// As long as the class has push(), pop(), top(), and empty(), it will test it!
// ==============================================================================
template <typename StackType>
void runStackDiagnostics(StackType& stack, const string& architectureName) {
    cout << ">>> INITIALIZING DIAGNOSTICS FOR: " << architectureName << " <<<\n";

    // 1. Initial State
    cout << "[Step 1] Initial State check...\n";
    cout << "         Is stack empty? " << (stack.empty() ? "Yes" : "No") << "\n";

    // 2. Push Operations
    cout << "[Step 2] Pushing elements: 'Task 1', 'Task 2', 'Task 3'...\n";
    stack.push("Task 1");
    stack.push("Task 2");
    stack.push("Task 3");

    cout << "         Current Size: " << stack.size() << "\n";
    cout << "         Element at Top: '" << stack.top() << "' (Should be 'Task 3')\n\n";

    // 3. Pop Operations (Verifying LIFO: Last In, First Out)
    cout << "[Step 3] Popping elements to verify LIFO behavior:\n";
    while (!stack.empty()) {
        cout << "         Processing and popping: '" << stack.top() << "'\n";
        stack.pop();
    }
    cout << "         Stack is now empty. Size: " << stack.size() << "\n\n";

    // 4. Exception Safety (Triggering Underflow)
    cout << "[Step 4] Testing Exception Safety (Popping from empty stack)...\n";
    try {
        cout << "         Attempting to pop...\n";
        stack.pop();
        cout << "         FAIL: Stack allowed pop when empty!\n";
    }
    catch (const underflow_error& e) {
        cout << "         SUCCESS - Exception Caught: " << e.what() << "\n";
    }

    cout << ">>> DIAGNOSTICS COMPLETED FOR: " << architectureName << " <<<\n\n";
    cout << "--------------------------------------------------------\n\n";
}

int main() {
    cout << "=== C++ STACK ARCHITECTURE TEST ENGINE ===\n\n";

    // Test Engine 1: Array (Vector) Based Stack
    ArrayStack<string> browserHistory;
    runStackDiagnostics(browserHistory, "ArrayStack (Vector-Driven)");

    // Test Engine 2: Singly Linked List Based Stack
    LinkedStack<string> functionCallStack;
    runStackDiagnostics(functionCallStack, "LinkedStack (Node-Driven)");

    cout << "All systems nominal!\n";
    return 0;
}
#include <iostream>
#include <vector>

using namespace std;

// ==============================================================================
// EXAMPLE 1: THE BAD WAY (Tail Recursion)
// WARNING: This is mathematically correct but architecturally dangerous!
// If the container has hundreds of thousands of elements, this will cause
// a Stack Overflow because each recursive call creates a new Stack Frame.
// ==============================================================================
template <typename Iterator>
void printRecursive(Iterator start, Iterator end, ostream& out = cout) {

    // Base Case:
    if (start == end)
        return;

    // Print current element and advance the iterator
    cout << *start++ << " ";

    // THE DANGER ZONE: Calling the function itself at the very end (Tail Recursion).
    // This wastes memory by keeping the old function states alive in the Call Stack.
    printRecursive(start, end, out);
}

// ==============================================================================
// EXAMPLE 2: THE GOOD WAY (Mechanically Eliminated Tail Recursion)
// BEST PRACTICE: This uses only one Stack Frame (O(1) memory) and will NEVER crash,
// regardless of how massive the container is.
// ==============================================================================
template <typename Iterator>
void printIterative(Iterator start, Iterator end, ostream& out = cout) {

    // Enclosing the logic in an infinite loop instead of a recursive call
    while (true) {

        // Base case: Break the loop and exit the function if we hit the end
        if (start == end) {
            return;
        }

        // Print the current element and advance the iterator
        out << *start++ << " ";

        // The loop simply restarts here without consuming additional memory!
    }
}

// ==============================================================================
// TEST AUTOMATION
// ==============================================================================
int main() {
    cout << "=== TAIL RECURSION VS ITERATION TEST ===\n\n";

    // Creating a standard vector to test our print functions
    vector<int> numbers = { 10, 20, 30, 40, 50 };

    // Testing the Recursive Approach
    cout << "1. Printing using Recursive Approach (Danger Zone):\n[ ";
    printRecursive(numbers.begin(), numbers.end());
    cout << "]\n\n";

    // Testing the Iterative Approach
    cout << "2. Printing using Iterative Approach (Best Practice):\n[ ";
    printIterative(numbers.begin(), numbers.end());
    cout << "]\n\n";

    cout << "Note: Both produce the exact same output, but under the hood, \n";
    cout << "the Iterative approach is infinitely safer and consumes O(1) stack memory.\n";

    return 0;
}
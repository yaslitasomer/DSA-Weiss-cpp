#include <iostream>
#include "TwoStacks.h"
#include <stdexcept>

using namespace std;

int main() {
    cout << "=== TWO STACKS, ONE ARRAY DIAGNOSTICS ===\n\n";

    // Creating an array with a strict capacity of 5 elements
    TwoStacks<int> myStacks(5);

    cout << ">>> TEST 1: Pushing Elements <<<\n";
    cout << "Pushing 10 and 20 into Stack 1...\n";
    myStacks.push1(10);
    myStacks.push1(20);

    cout << "Pushing 90 and 80 into Stack 2...\n";
    myStacks.push2(90);
    myStacks.push2(80);

    cout << "\nCurrent State:\n";
    cout << "Stack 1 Top: " << myStacks.peek1() << "\n";
    cout << "Stack 2 Top: " << myStacks.peek2() << "\n\n";

    cout << ">>> TEST 2: The Perfect Collision (Overflow Test) <<<\n";
    cout << "Array currently holds 4 elements out of 5. Only 1 slot remains.\n";

    cout << "Pushing 30 into Stack 1 (Filling the very last slot)...\n";
    myStacks.push1(30);

    try {
        cout << "Attempting to push 70 into Stack 2...\n";
        myStacks.push2(70); // THIS LINE WILL TRIGGER THE ALARM!
    }
    catch (const overflow_error& e) {
        cout << "[CRITICAL INTERCEPT] " << e.what() << "\n";
        cout << "Architecture works flawlessly! No overflow until fully occupied.\n\n";
    }

    cout << ">>> TEST 3: Popping Elements <<<\n";
    cout << "Popping one element from Stack 1...\n";
    myStacks.pop1();
    cout << "New Top of Stack 1: " << myStacks.peek1() << "\n\n";

    cout << "ALL DIAGNOSTICS COMPLETED SAFELY.\n";
    return 0;
}
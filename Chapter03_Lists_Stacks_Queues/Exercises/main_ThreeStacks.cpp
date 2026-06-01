#include <iostream>
#include <stdexcept>
#include "ThreeStacks.h"

using namespace std;

int main() {
    cout << "=== THREE STACKS IN ONE ARRAY (FREE-LIST) DIAGNOSTICS ===\n\n";

    // Create an array with only 6 slots total
    ThreeStacks<string> myStacks(6);

    cout << ">>> TEST 1: Pushing into different stacks <<<\n";
    myStacks.push(0, "Apple");  // Stack 0
    myStacks.push(1, "Banana"); // Stack 1
    myStacks.push(2, "Cherry"); // Stack 2
    myStacks.push(0, "Avocado");// Stack 0 gets another one

    cout << "Stack 0 Top: " << myStacks.peek(0) << "\n";
    cout << "Stack 1 Top: " << myStacks.peek(1) << "\n";
    cout << "Stack 2 Top: " << myStacks.peek(2) << "\n\n";

    cout << ">>> TEST 2: Overflow Capability (Using every last slot) <<<\n";
    myStacks.push(2, "Coconut"); // Slot 5 used
    myStacks.push(1, "Berry");   // Slot 6 used (ARRAY IS NOW FULL)

    try {
        cout << "Attempting to push one more item into Stack 1...\n";
        myStacks.push(1, "Blueberry"); // THIS WILL TRIGGER OVERFLOW
    }
    catch (const overflow_error& e) {
        cout << "[INTERCEPTED] " << e.what() << "\n\n";
    }

    cout << ">>> TEST 3: Recycling Memory (Pop and Push again) <<<\n";
    cout << "Popping from Stack 0 (Avocado removed)...\n";
    myStacks.pop(0);

    cout << "Pushing 'Dragonfruit' into Stack 2 (Reusing the freed slot!)...\n";
    myStacks.push(2, "Dragonfruit"); // Succeeds because we recycled memory!
    cout << "Stack 2 New Top: " << myStacks.peek(2) << "\n\n";

    cout << "ALL DIAGNOSTICS COMPLETED SAFELY.\n";
    return 0;
}
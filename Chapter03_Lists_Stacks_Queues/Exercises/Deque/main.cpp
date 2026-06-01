#include <iostream>
#include "Deque.h"

using namespace std;

int main() {
    cout << "=== DEQUE (O(1) DOUBLE-ENDED QUEUE) DIAGNOSTICS ===\n\n";

    Deque<int> myDeque;

    // ---------------------------------------------------------
    // TEST 1: FRONT OPERATIONS (Push)
    // ---------------------------------------------------------
    cout << ">>> TEST 1: Pushing to Front <<<\n";
    cout << "Pushing 20, then 10...\n";
    myDeque.push(20);
    myDeque.push(10);
    // Logical order from front to rear: [10, 20]

    // ---------------------------------------------------------
    // TEST 2: REAR OPERATIONS (Inject)
    // ---------------------------------------------------------
    cout << ">>> TEST 2: Injecting to Rear <<<\n";
    cout << "Injecting 30, then 40...\n";
    myDeque.inject(30);
    myDeque.inject(40);
    // Logical order from front to rear: [10, 20, 30, 40]

    cout << "Current Size: " << myDeque.size() << " (Expected: 4)\n\n";

    // ---------------------------------------------------------
    // TEST 3: REMOVALS (Pop and Eject)
    // ---------------------------------------------------------
    cout << ">>> TEST 3: Extracting Elements <<<\n";

    // Should return 10
    cout << "Popped from Front: " << myDeque.pop() << "\n";

    // Should return 40
    cout << "Ejected from Rear: " << myDeque.eject() << "\n";

    // Logical order remaining: [20, 30]
    cout << "Current Size: " << myDeque.size() << " (Expected: 2)\n\n";

    cout << "Popped from Front again: " << myDeque.pop() << "\n"; // Returns 20
    cout << "Ejected from Rear again: " << myDeque.eject() << "\n\n"; // Returns 30

    // ---------------------------------------------------------
    // TEST 4: UNDERFLOW PROTECTION
    // ---------------------------------------------------------
    cout << ">>> TEST 4: Empty Extraction Defense <<<\n";
    try {
        myDeque.pop(); // Should explode since it's empty
    }
    catch (const underflow_error& e) {
        cout << "[INTERCEPTED] " << e.what() << "\n";
    }

    cout << "\nALL DIAGNOSTICS COMPLETED SAFELY.\n";
    return 0;
}
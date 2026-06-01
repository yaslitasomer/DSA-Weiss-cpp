#include <iostream>
#include "UpdatedVector.h"


void printVector(UpdatedVector<int>& vec, const string& name) {
    cout << name << " : [ ";
    for (auto it = vec.begin(); it != vec.end(); ++it) {
        cout << *it << " ";
    }
    cout << "]\n";
}

int main() {
    cout << "=== ULTIMATE SAFE UpdatedVector DIAGNOSTICS ===\n\n";
    UpdatedVector<int> myVec;
    myVec.push_back(10);
    myVec.push_back(20);
    myVec.push_back(30);

    // ---------------------------------------------------------
    // TEST 1: INSERT AND ERASE
    // ---------------------------------------------------------
    cout << ">>> TEST 1: Insert and Erase Operations <<<\n";
    printVector(myVec, "Original UpdatedVector ");

    // Insert 15 at index 1
    auto insertPos = myVec.begin();
    ++insertPos;
    myVec.insert(insertPos, 15);
    printVector(myVec, "After insert(15)");

    // Erase the first element (10)
    myVec.erase(myVec.begin());
    printVector(myVec, "After erase(pos0)");
    cout << "--------------------------------------------------------\n\n";

    // ---------------------------------------------------------
    // TEST 2: BOUNDS CHECKING (Catching Out of Range)
    // ---------------------------------------------------------
    cout << ">>> TEST 2: Bounds Checking (operator[]) <<<\n";
    try {
        cout << "Attempting to read myVec[100]...\n";
        int badRead = myVec[100];
        cout << badRead; // Should not reach here
    }
    catch (const std::out_of_range& e) {
        cout << "[INTERCEPTED] " << e.what() << "\n";
    }
    cout << "--------------------------------------------------------\n\n";

    // ---------------------------------------------------------
    // TEST 3: FAIL-FAST ITERATOR (Catching Stale Iterators)
    // ---------------------------------------------------------
    cout << ">>> TEST 3: Stale Iterator Security <<<\n";
    auto staleIt = myVec.begin(); // Grabs the current version seal
    cout << "Iterator successfully points to: " << *staleIt << "\n";

    cout << "Simulating a structural change behind the iterator's back (push_back)...\n";
    myVec.push_back(99);

    try {
        cout << "Attempting to use the old iterator...\n";
        cout << *staleIt << "\n"; // THIS WILL TRIGGER THE ALARM
    }
    catch (const std::logic_error& e) {
        cout << "[INTERCEPTED] " << e.what() << "\n";
    }
    cout << "--------------------------------------------------------\n\n";

    cout << "ALL DIAGNOSTICS COMPLETED SAFELY. PROGRAM DID NOT CRASH!\n";
    return 0;
}
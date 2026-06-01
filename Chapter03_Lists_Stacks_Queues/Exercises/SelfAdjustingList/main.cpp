#include <iostream>
#include "SelfAdjustingArray.h"
#include "SelfAdjustingLinkedList.h"

using namespace std;

// ==============================================================================
// DIAGNOSTICS ENGINE (TESTING BOTH STRUCTURES)
// ==============================================================================
int main() {
    cout << "=== SELF-ADJUSTING STRUCTURES DIAGNOSTICS ===\n\n";

    // ---------------------------------------------------------
    // 1. TESTING ARRAY IMPLEMENTATION
    // ---------------------------------------------------------
    cout << ">>> 1. SelfAdjustingArray Engine <<<\n";
    SelfAdjustingArray<int> arrayList(10);

    // Inserting elements (Remember: they are pushed to the front)
    arrayList.insert(10);
    arrayList.insert(20);
    arrayList.insert(30);
    arrayList.insert(40);

    cout << "Initial Array State : ";
    arrayList.printList(); // Expected: [ 40 30 20 10 ]

    cout << "Action: Finding '20'\n";
    arrayList.find(20);

    cout << "Updated Array State : ";
    arrayList.printList(); // Expected: [ 20 40 30 10 ]
    cout << "--------------------------------------------------------\n\n";

    // ---------------------------------------------------------
    // 2. TESTING LINKED LIST IMPLEMENTATION
    // ---------------------------------------------------------
    cout << ">>> 2. SelfAdjustingLinkedList Engine <<<\n";
    SelfAdjustingLinkedList<int> linkedList;

    linkedList.insert(10);
    linkedList.insert(20);
    linkedList.insert(30);
    linkedList.insert(40);

    cout << "Initial List State  : ";
    linkedList.printList(); // Expected: [ 40 -> 30 -> 20 -> 10 ]

    cout << "Action: Finding '10'\n";
    linkedList.find(10);

    cout << "Updated List State  : ";
    linkedList.printList(); // Expected: [ 10 -> 40 -> 30 -> 20 ]
    cout << "--------------------------------------------------------\n\n";

    cout << "ALL DIAGNOSTICS COMPLETED SAFELY.\n";
    return 0;
}
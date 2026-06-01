#include <iostream>
#include "../LinkedLists/SinglyLinkedList.h" 

using namespace std;

// Const ortam testi için yardımcı fonksiyon
void testConstEnvironment(const SinglyLinkedList<int>& list) {
    cout << "--- Const Environment Test ---\n";
    list.printReverseConst();
}

int main() {
    cout << "=== NO-DUMMY CONSTANT SPACE REVERSE PRINT DIAGNOSTICS ===\n\n";

    SinglyLinkedList<int> myList;

    myList.insert(10, myList.size());
    myList.insert(20, myList.size());
    myList.insert(30, myList.size());
    myList.insert(40, myList.size());
    myList.insert(50, myList.size());

    // Expected: [ 10 -> 20 -> 30 -> 40 -> 50 ]
    cout << "1. Original List Before Operations:\n";
    myList.printList();
    cout << "--------------------------------------------------------\n\n";

    // O(N) Time - Non-Const Test
    cout << "2. Triggering Non-Const O(N) Reversal (Pointer Flipping):\n";
    myList.printReverseFast();
    cout << "--------------------------------------------------------\n\n";

    cout << "3. Verifying List Restoration:\n";
    myList.printList();

    cout << "\nInserting 60 to the end to verify 'tail' integrity...\n";
    myList.insert(60, myList.size());
    myList.printList();
    cout << "-> If 60 was added perfectly, our pointers survived the reversal!\n";
    cout << "--------------------------------------------------------\n\n";

    // O(N^2) Time - Const Test
    cout << "4. Triggering Strict Const O(N^2) Reversal (Quadratic Traversal):\n";
    testConstEnvironment(myList);
    cout << "--------------------------------------------------------\n\n";

    cout << "ALL SPACE-TIME COMPLEXITY DIAGNOSTICS COMPLETED SAFELY.\n";
    return 0;
}
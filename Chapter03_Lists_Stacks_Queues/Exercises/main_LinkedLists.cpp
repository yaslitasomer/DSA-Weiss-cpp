#include <iostream>
#include <stdexcept>
#include "SinglyLinkedList.h"
#include "SortedSinglyLinkedList.h"

using namespace std;

int main() {
    // ---------------------------------------------------------
    // PART 1: STANDARD SINGLY LINKED LIST
    // ---------------------------------------------------------
    cout << "========================================================\n";
    cout << "   PART 1: STANDARD SINGLY LINKED LIST DIAGNOSTICS\n";
    cout << "========================================================\n\n";

    SinglyLinkedList<int> standardList;

    cout << ">>> Adding Elements (Unsorted) <<<\n";
    standardList.addIfAbsent(50);
    standardList.addIfAbsent(10);
    standardList.addIfAbsent(30);
    standardList.addIfAbsent(20);

    // Output should be: [ 20 -> 30 -> 10 -> 50 ] (Because we insert at the front)
    standardList.printList();

    cout << "\n>>> Removal Test <<<\n";
    cout << "Removing 30...\n";
    standardList.remove(30);
    standardList.printList();
    cout << "\n\n";

    // ---------------------------------------------------------
    // PART 2: SORTED SINGLY LINKED LIST
    // ---------------------------------------------------------
    cout << "========================================================\n";
    cout << "   PART 2: SORTED SINGLY LINKED LIST DIAGNOSTICS\n";
    cout << "========================================================\n\n";

    SortedSinglyLinkedList<int> sortedList;

    cout << ">>> TEST 1: Sorted Insertion (addIfAbsent) <<<\n";
    cout << "Inserting 50, 10, 30, 20, 10 (Duplicate)...\n";

    // We insert them in a completely random order
    sortedList.addIfAbsent(50);
    sortedList.addIfAbsent(10);
    sortedList.addIfAbsent(30);
    sortedList.addIfAbsent(20);
    sortedList.addIfAbsent(10); // Should be ignored

    // Output MUST be: [ 10 -> 20 -> 30 -> 50 ]
    sortedList.printList();
    cout << "Size should be 4. Actual: " << sortedList.size() << "\n\n";

    cout << ">>> TEST 2: Early Exit Search (find) <<<\n";
    // It should stop searching as soon as it sees 50
    int index = sortedList.find(40);
    cout << "Searching for 40 (Not in list). Index returned: " << index << " (Should be -1)\n\n";

    cout << ">>> TEST 3: Removal in Sorted List <<<\n";
    cout << "Removing 20 (Middle element)...\n";
    sortedList.remove(20);
    sortedList.printList();

    cout << "\nRemoving 10 (First element)...\n";
    sortedList.remove(10);
    sortedList.printList();

    cout << "\nRemoving 50 (Last element)...\n";
    sortedList.remove(50);
    sortedList.printList();

    cout << "\n========================================================\n";
    cout << "ALL DIAGNOSTICS COMPLETED SAFELY.\n";
    cout << "========================================================\n";

    return 0;
}
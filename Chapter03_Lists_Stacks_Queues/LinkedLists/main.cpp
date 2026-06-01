#include <iostream>
#include <vector>
#include <string>
#include <list>
#include "SinglyLinkedList.h" 
#include "DoublyLinkedList.h"

using namespace std;

int main() {
    /* SINGLY LINKED LIST TEST
    cout << "=== SINGLY LINKED LIST TEST ENGINE ===\n\n";

    SinglyLinkedList<string> playlist;
    cout << "Is playlist empty? " << (playlist.isEmpty() ? "Yes" : "No") << "\n\n";

    cout << "--- Inserting Elements ---\n";
    playlist.insert("Song A", 0);
    playlist.insert("Song B", 1);
    playlist.insert("Song C", 2);
    playlist.insert("Song Z", 1);

    playlist.printList();
    cout << "Current Size: " << playlist.size() << "\n\n";

    cout << "--- Searching Elements ---\n";
    cout << "Element at index 2: " << playlist.findKth(2) << "\n";
    cout << "Index of 'Song C': " << playlist.find("Song C") << "\n";
    cout << "Index of 'Song X' (Not exist): " << playlist.find("Song X") << "\n\n";

    cout << "--- Removing Elements ---\n";

    cout << "Removing 'Song Z' (Middle)...\n";
    playlist.remove("Song Z");
    playlist.printList();

    cout << "Removing 'Song A' (Head)...\n";
    playlist.remove("Song A");
    playlist.printList();

    cout << "Removing 'Song C' (Tail)...\n";
    playlist.remove("Song C");
    playlist.printList();

    cout << "Current Size: " << playlist.size() << "\n\n";

    cout << "--- Clearing the List ---\n";
    playlist.makeEmpty();
    cout << "Is playlist empty now? " << (playlist.isEmpty() ? "Yes" : "No") << "\n";
    playlist.printList();

    cout << "\nAll tests completed...\n";
    */
    /*
    cout << "=== DOUBLY LINKED LIST TEST ENGINE ===\n\n";

    // 1. Creation and Initialization
    DoublyLinkedList<string> trainRoute;
    cout << "Is the route empty initially? " << (trainRoute.isEmpty() ? "Yes" : "No") << "\n\n";

    // 2. Testing Insertions
    cout << "--- Inserting Elements ---\n";

    // Insert at front (index 0)
    trainRoute.insert("Station Central", 0);

    // Insert at front again
    trainRoute.insert("Station North", 0);

    // Insert at the end (index 2)
    trainRoute.insert("Station South", 2);

    // Insert in the middle (index 2)
    trainRoute.insert("Station East", 2);

    trainRoute.printList();
    cout << "Current Size: " << trainRoute.size() << "\n\n";

    // Expected Output:
    // [Station North <-> Station Central <-> Station East <-> Station South]

    // 3. Testing the Bidirectional Search (findKth)
    cout << "--- Searching Elements (Bidirectional Optimization) ---\n";
    // This will start from the head (index < size / 2)
    cout << "Element at index 1 (First Half): " << trainRoute.findKth(1) << "\n";
    // This will start from the tail (index >= size / 2)
    cout << "Element at index 3 (Second Half): " << trainRoute.findKth(3) << "\n";

    cout << "Index of 'Station East': " << trainRoute.find("Station East") << "\n";
    cout << "Index of 'Station West' (Does not exist): " << trainRoute.find("Station West") << "\n\n";

    // 4. Testing Removals
    cout << "--- Removing Elements ---\n";

    cout << "Removing 'Station East' (Middle)...\n";
    trainRoute.remove("Station East");
    trainRoute.printList();

    cout << "Removing 'Station North' (Head)...\n";
    trainRoute.remove("Station North");
    trainRoute.printList();

    cout << "Removing 'Station South' (Tail)...\n";
    trainRoute.remove("Station South");
    trainRoute.printList();

    cout << "Current Size: " << trainRoute.size() << "\n\n";

    // Expected Output:
    // [Station Central]

    // 5. Testing makeEmpty
    cout << "--- Clearing the List ---\n";
    trainRoute.makeEmpty();
    cout << "Is the route empty now? " << (trainRoute.isEmpty() ? "Yes" : "No") << "\n";
    trainRoute.printList();

    cout << "\nAll operations executed!\n";
    */
    cout << "=== TESTING C++ STL: VECTOR vs LIST ===\n\n";

    // =========================================================
    // 1. TESTING std::vector (Dynamic Array)
    // Fast indexing, slow at inserting to the front.
    // =========================================================
    cout << "--- 1. std::vector Tests ---\n";
    vector<string> myVector;

    // We can reserve memory in advance to avoid reallocation
    myVector.reserve(10);
    cout << "Initial Vector Capacity: " << myVector.capacity() << "\n";

    // Adding to the back is fast O(1)
    myVector.push_back("Apple");
    myVector.push_back("Banana");
    myVector.push_back("Cherry");

    // Fast O(1) Indexing! (Only vector has this)
    cout << "Vector element at index 1: " << myVector[1] << "\n";

    // Bounds-checked indexing using .at()
    try {
        cout << "Trying to access index 5: ";
        cout << myVector.at(5) << "\n";
    }
    catch (const out_of_range& e) {
        cout << "Caught Error! " << e.what() << "\n";
    }

    cout << "Vector Size: " << myVector.size() << "\n\n";

    // =========================================================
    // 2. TESTING std::list (Doubly Linked List)
    // No indexing, but extremely fast at front/back operations.
    // =========================================================
    cout << "--- 2. std::list Tests ---\n";
    std::list<string> myList;

    // Adding to the back
    myList.push_back("Dog");
    myList.push_back("Elephant");

    // FAST insertion to the front O(1) (Vector doesn't have this efficiently!)
    myList.push_front("Cat");

    // We cannot do myList[1] here! 
    // We must use .front() or .back() to peek at the ends.
    cout << "List Front: " << myList.front() << "\n";
    cout << "List Back: " << myList.back() << "\n";

    cout << "List Size before pop: " << myList.size() << "\n";

    // Removing from both ends O(1)
    myList.pop_front();
    myList.pop_back();

    cout << "List Front after pop: " << myList.front() << "\n";
    cout << "List Size after pop: " << myList.size() << "\n\n";

    // =========================================================
    // 3. COMMON STL OPERATIONS (clear and empty)
    // =========================================================
    cout << "--- 3. Clearing Containers ---\n";

    myVector.clear();
    myList.clear();

    cout << "Is vector empty? " << (myVector.empty() ? "Yes" : "No") << "\n";
    cout << "Is list empty? " << (myList.empty() ? "Yes" : "No") << "\n";

    cout << "\nSTL Testing Completed Successfully!\n";
    return 0;
}
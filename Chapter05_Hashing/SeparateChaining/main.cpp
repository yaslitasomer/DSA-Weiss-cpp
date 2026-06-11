#include "SeparateChaining.h"
#include <iostream>

using namespace std;

int main() {
    cout << "=== SEPARATE CHAINING HASH TABLE DIAGNOSTICS ===\n\n";

    // Initialize table with a small prime number to force collisions easily
    HashTable<string> myTable(5);

    cout << "1. Inserting distinct strings...\n";
    myTable.insert("Apple");
    myTable.insert("Banana");
    myTable.insert("Cherry");
    myTable.insert("Date");

    myTable.displayTable();

    cout << "\n2. Forcing a collision explicitly (Adding more items than slots)...\n";
    // This will trigger the load factor to exceed 1.0, causing an automatic REHASH!
    myTable.insert("Elderberry");
    myTable.insert("Fig");
    myTable.insert("Grape");

    cout << "   Notice how the table size expanded to the next prime (11)\n";
    cout << "   and elements were re-distributed (Rehashed) to maintain O(1) access!\n";
    myTable.displayTable();

    cout << "\n3. Testing Contains & Remove...\n";
    cout << "   Contains 'Cherry'? : " << (myTable.contains("Cherry") ? "YES" : "NO") << "\n";
    cout << "   Removing 'Cherry'...\n";
    myTable.remove("Cherry");
    cout << "   Contains 'Cherry'? : " << (myTable.contains("Cherry") ? "YES" : "NO") << "\n";

    cout << "\nALL HASHING DIAGNOSTICS COMPLETED SAFELY.\n";
    return 0;
}
#include "QuadraticHashTable.h"
#include <iostream>

using namespace std;

int main() {
    cout << "=== QUADRATIC PROBING HASH TABLE DIAGNOSTICS ===\n\n";

    // Initialize with size 7 (Prime)
    QuadraticHashTable<int> myTable(7);

    // For integers, our generic StringHash won't work perfectly if we don't adapt it.
    // Let's assume the user will insert ints and C++ will cast them or we write an IntHash.
    // To keep it strictly to the book's string example, we use strings.
    QuadraticHashTable<string> stringTable(7);

    cout << "1. Inserting elements to test Quadratic Probing...\n";
    stringTable.insert("Apple");
    stringTable.insert("Banana");
    stringTable.insert("Cherry");

    stringTable.displayTable();

    cout << "\n2. Testing Lazy Deletion (Removing 'Banana')...\n";
    stringTable.remove("Banana");
    stringTable.displayTable();

    cout << "\n3. Triggering Rehash by surpassing 50% load factor...\n";
    stringTable.insert("Date");
    stringTable.insert("Elderberry"); // This 5th element pushes occupied cells > 3 (Half of 7)

    cout << "   Notice how the table doubled to the next prime (17)\n";
    cout << "   and the <DELETED> 'Banana' was completely purged from memory during Rehash!\n";
    stringTable.displayTable();

    cout << "\nALL QUADRATIC PROBING DIAGNOSTICS COMPLETED SAFELY.\n";
    return 0;
}
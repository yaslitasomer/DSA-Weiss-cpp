#include <iostream>
#include "DoubleHashTable.h"

using namespace std;

// ==============================================================================
// DIAGNOSTICS ENGINE (Replicating Textbook Figure 5.18)
// ==============================================================================
int main() {
    cout << "=== DOUBLE HASHING DIAGNOSTICS ===\n\n";

    DoubleHashTable table(10); // Size 10, R = 7

    cout << "Inserting 89, 18, 49, 58, 69 (Same as textbook example)...\n";
    table.insert(89); // hash1 = 9
    table.insert(18); // hash1 = 8
    table.insert(49); // hash1 = 9 (Collision!) -> hash2 = 7 - (49%7) = 7 -> Jump to 6
    table.insert(58); // hash1 = 8 (Collision!) -> hash2 = 7 - (58%7) = 5 -> Jump to 3
    table.insert(69); // hash1 = 9 (Collision!) -> hash2 = 7 - (69%7) = 1 -> Jump to 0

    cout << "\nResulting Table Architecture:\n";
    table.displayTable();

    cout << "\nALL DOUBLE HASHING DIAGNOSTICS COMPLETED SAFELY.\n";
    return 0;
}
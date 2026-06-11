#include <iostream>
#include <vector>
#include <string>
#include <random>
#include <algorithm>
#include "CuckooHashTable.h"

using namespace std;

int main() {
    cout << "=== CUCKOO HASHING DIAGNOSTICS ===\n\n";

    // Initialize with 2 hash functions
    CuckooHashTable<string, StringHashFamily> cuckoo(11, 2);

    cout << "1. Inserting elements to test standard placement...\n";
    cuckoo.insert("Apple");
    cuckoo.insert("Banana");
    cuckoo.insert("Cherry");
    cuckoo.displayTable();

    cout << "\n2. Forcing multiple collisions to trigger Cuckoo Evictions & Rehashes...\n";
    // We add enough elements to push the load factor, triggering expansions or evictions.
    cuckoo.insert("Date");
    cuckoo.insert("Elderberry");
    cuckoo.insert("Fig");
    cuckoo.insert("Grape");
    cuckoo.insert("Honeydew");

    cout << "   Table after intense nest-kicking and potential auto-rehashing:\n";
    cuckoo.displayTable();

    cout << "\n3. Testing O(1) Removal (No lazy deletion needed)...\n";
    cuckoo.remove("Banana");
    cout << "   Contains 'Banana'? : " << (cuckoo.contains("Banana") ? "YES" : "NO") << "\n";

    cout << "\nALL CUCKOO HASHING DIAGNOSTICS COMPLETED SAFELY.\n";
    return 0;
}
#include <iostream>
#include <string>
#include "List.h"

using namespace std;

int main() {
    cout << "=== CUSTOM STL LIST TEST ENGINE ===\n\n";

    // 1. Creation and Basic Methods
    cout << "--- 1. Testing Initialization & Capacity ---\n";
    List<string> playlist;
    cout << "Is playlist empty? " << (playlist.empty() ? "Yes" : "No") << "\n";
    cout << "Initial size: " << playlist.size() << "\n\n";

    // 2. Testing push_back and push_front
    cout << "--- 2. Testing push_back & push_front ---\n";
    playlist.push_back("Song B");
    playlist.push_back("Song C");
    playlist.push_front("Song A"); // Should be at the very front

    cout << "Current Size: " << playlist.size() << "\n";
    cout << "Front element: " << playlist.front() << "\n";
    cout << "Back element: " << playlist.back() << "\n\n";

    // 3. Testing Iterators (Forward & Backward Traversing)
    cout << "--- 3. Testing Iterators (Forward & Backward) ---\n";
    cout << "Forward Traversal: [ ";
    for (auto itr = playlist.begin(); itr != playlist.end(); itr++) {
        cout << *itr << " ";
    }
    cout << "]\n";

    cout << "Backward Traversal: [ ";
    for (auto itr = --playlist.end(); itr != --playlist.begin(); itr--) {
        cout << *itr << " ";
    }
    cout << "]\n\n";

    // 4. Testing Middle Insertion & Erase
    cout << "--- 4. Testing Middle Insert & Single Erase ---\n";
    auto midItr = playlist.begin();
    ++midItr; // Move to the second element (Song B)

    // Insert "Song X" before "Song B"
    playlist.insert(midItr, "Song X");

    cout << "List after inserting 'Song X': ";
    for (const auto& song : playlist) cout << song << " ";
    cout << "\n";

    // Erase "Song X"
    midItr = playlist.begin();
    ++midItr; // Points to 'Song X'
    playlist.erase(midItr);

    cout << "List after erasing 'Song X': ";
    for (const auto& song : playlist) cout << song << " ";
    cout << "\n\n";

    // 5. Testing The Big Five (Copying)
    cout << "--- 5. Testing Copy Constructor (The Big Five) ---\n";
    List<string> backupList = playlist; // Triggers Copy Constructor
    backupList.push_back("Song D");

    cout << "Original List Size: " << playlist.size() << "\n";
    cout << "Backup List Size: " << backupList.size() << " (Deep Copy works!)\n\n";

    // 6. Testing pop_front, pop_back, and Range Erase
    cout << "--- 6. Testing Pops & Range Erase ---\n";
    backupList.pop_front();
    backupList.pop_back();
    cout << "Backup after pops: ";
    for (const auto& song : backupList) cout << song << " ";
    cout << "\n";

    cout << "Erasing the entire backup list using range erase...\n";
    backupList.erase(backupList.begin(), backupList.end());
    cout << "Is backup empty now? " << (backupList.empty() ? "Yes" : "No") << "\n\n";

    // 7. Destructor Test (Implicit)
    cout << "--- 7. Memory Cleanup ---\n";
    playlist.clear();
    cout << "Original playlist cleared. Size: " << playlist.size() << "\n";

    // 8. Testing operator- (Exercise 3.13 - Iterator Subtraction)
    cout << "--- 8. Testing operator- (Iterator Distance) ---\n";

    // Repopulate the list since we cleared it in Step 7!
    playlist.push_back("Track 1");
    playlist.push_back("Track 2");
    playlist.push_back("Track 3");
    playlist.push_back("Track 4");
    playlist.push_back("Track 5");

    cout << "Repopulated List for Test 8: [ ";
    for (const auto& song : playlist) cout << song << " ";
    cout << "]\n";

    auto itStart = playlist.begin(); // Points to "Track 1"
    auto itEnd = playlist.end();     // Points to Dummy Tail

    auto itMid = playlist.begin();
    ++itMid; ++itMid;                // Points to "Track 3"

    // TEST SCENARIOS
    cout << "Distance from Start to End (itEnd - itStart) : " << (itEnd - itStart) << "  (Expected: 5)\n";
    cout << "Distance from End to Start (itStart - itEnd) : " << (itStart - itEnd) << " (Expected: -5)\n";
    cout << "Distance from Start to Mid (itMid - itStart) : " << (itMid - itStart) << "  (Expected: 2)\n";
    cout << "Distance from Mid to itself  (itMid - itMid) : " << (itMid - itMid) << "  (Expected: 0)\n\n";
    cout << "If the program ends without crashing, the Destructor worked perfectly!\n\n";

    return 0;
}
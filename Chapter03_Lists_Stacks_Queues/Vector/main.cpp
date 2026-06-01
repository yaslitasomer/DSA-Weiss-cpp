#include <iostream>
#include <string>
#include "Vector.h"

using namespace std;

int main() {
    cout << "=== CUSTOM VECTOR TEST ENGINE ===\n\n";

    // 1. Initialization & Capacity Testing
    cout << "--- 1. Testing Initialization & Capacity ---\n";
    Vector<int> numbers;
    cout << "Initial Size: " << numbers.size() << "\n";
    cout << "Initial Capacity: " << numbers.capacity() << "\n";
    cout << "Is Vector empty? " << (numbers.empty() ? "Yes" : "No") << "\n\n";

    // 2. Testing push_back & Dynamic Resizing (Reserve under the hood)
    cout << "--- 2. Testing push_back & Auto-Resizing ---\n";
    for (int i = 1; i <= 20; i++) {
        numbers.push_back(i * 10);
    }
    cout << "Size after 20 pushes: " << numbers.size() << "\n";
    cout << "Capacity after 20 pushes: " << numbers.capacity() << " (Dynamically grew!)\n";
    cout << "Last element (back): " << numbers.back() << "\n\n";

    // 3. Testing Iterators (Your custom begin() and end())
    // This uses the C++11 Range-based for loop, which entirely relies on iterators!
    cout << "--- 3. Testing Iterators (Ranged For Loop) ---\n";
    cout << "Elements: [ ";
    for (const auto& num : numbers) {
        cout << num << " ";
    }
    cout << "]\n\n";

    // 4. Testing operator[] (Const & Non-Const)
    cout << "--- 4. Testing operator[] ---\n";
    cout << "Element at index 5 (Before): " << numbers[5] << "\n";
    numbers[5] = 999; // Using non-const operator[] to modify
    cout << "Element at index 5 (After modification): " << numbers[5] << "\n\n";

    // 5. Testing pop_back
    cout << "--- 5. Testing pop_back ---\n";
    cout << "Size before pop: " << numbers.size() << "\n";
    numbers.pop_back();
    cout << "Size after pop: " << numbers.size() << "\n";
    cout << "New last element: " << numbers.back() << "\n\n";

    // 6. Testing The Big Five (Copy Constructor & Assignment)
    cout << "--- 6. Testing Copy Semantics (The Big Five) ---\n";
    Vector<int> copiedNumbers = numbers; // Triggers Copy Constructor
    copiedNumbers[0] = 777; // Modify copy to ensure deep copy worked

    cout << "Original Vector index 0: " << numbers[0] << "\n";
    cout << "Copied Vector index 0: " << copiedNumbers[0] << " (Deep copy successful!)\n\n";

    // 7. Testing explicit resize()
    cout << "--- 7. Testing resize() ---\n";
    Vector<string> words;
    words.resize(5); // Explicitly size to 5
    words[0] = "Hello";
    words[4] = "World";
    cout << "Words Size: " << words.size() << "\n";
    cout << "Words Capacity: " << words.capacity() << "\n";
    cout << "Words[0]: " << words[0] << ", Words[4]: " << words[4] << "\n\n";

    cout << "All advanced Custom Vector tests completed!\n";
    return 0;
}
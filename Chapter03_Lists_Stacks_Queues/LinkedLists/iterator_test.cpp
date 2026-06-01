#include <iostream>
#include <list>
#include <vector>

using namespace std;

template <typename Container>
void printContainer(const Container& c, const string& name) {
    cout << name << ": [";

    for (auto itr = c.begin(); itr != c.end(); itr++) {
        cout << *itr << " ";
    }

    cout << "]\n";
}

int main() {
    cout << "=== ITERATORS DEMYSTIFIED ===\n\n";

    // 1. Let's create a list and a vector
    list<int> numbersList = { 10, 20, 30, 40, 50 };
    vector<string> wordsVector = { "Apple", "Banana", "Cherry" };

    // 2. OLD WAY: Using explicit iterators (Like the book shows)
    cout << "--- The 'Old' Iterator Way ---\n";
    list<int>::iterator it = numbersList.begin(); // Point to first item

    cout << "First item is: " << *it << "\n";
    it++; // Move to next item
    cout << "Second item is: " << *it << "\n\n";

    // 3. GENERIC WAY: Passing containers to our iterator-based function
    cout << "--- Using the Generic Function ---\n";
    printContainer(numbersList, "My Numbers");
    printContainer(wordsVector, "My Words");
    cout << "\n";

    // 4. MODERN WAY: C++11 Range-based for loop (Under the hood, this uses iterators!)
    cout << "--- The Modern C++ Way (Ranged For) ---\n";
    cout << "Modern List Print: ";
    for (const auto& num : numbersList) {
        cout << num << " ";
    }
    cout << "\n";

    return 0;
}
/*Implement the STL find routine that returns the iterator containing the first occurence
of x in the range that begin sat start and extends up to but not including end.
If x is not found, end is returned. This is a nonclass(globalfunction) with signature
template <typename Iterator, typename Object>
iterator find( Iterator start, Iterator end, const Object & x );*/

#include <iostream>
#include <vector>
#include <list>
#include <string>

using namespace std;


template <typename Iterator, typename Object>
Iterator find(Iterator start, Iterator end, const Object& x) {
    while (start != end) {
        if (*start == x)
            return start;
        start++;
    }
    return end;
}

int main() {
    cout << "=== CUSTOM STL FIND DIAGNOSTICS ===\n\n";

    // ---------------------------------------------------------
    // TEST 1: Vector of Integers
    // ---------------------------------------------------------
    cout << ">>> SCENARIO 1: Vector Search <<<\n";
    vector<int> numbers = { 10, 20, 30, 40, 50 };
    int targetNum = 30;

    auto it1 = ::find(numbers.begin(), numbers.end(), targetNum);

    if (it1 != numbers.end()) {
        cout << "[FOUND] Target " << targetNum << " exists in the vector.\n";
    }
    else {
        cout << "[ERROR] Target " << targetNum << " NOT found!\n";
    }

    // ---------------------------------------------------------
    // TEST 2: List of Strings (Testing Template Flexibility)
    // ---------------------------------------------------------
    cout << "\n>>> SCENARIO 2: Linked List Search <<<\n";
    list<string> fruits = { "Apple", "Banana", "Cherry" };
    string targetFruit = "Mango"; // This one doesn't exist!

    auto it2 = ::find(fruits.begin(), fruits.end(), targetFruit);

    if (it2 != fruits.end()) {
        cout << "[FOUND] Target " << targetFruit << " exists in the list.\n";
    }
    else {
        cout << "[NOT FOUND] Target " << targetFruit << " is correctly reported as missing (Returned 'end').\n";
    }

    return 0;
}
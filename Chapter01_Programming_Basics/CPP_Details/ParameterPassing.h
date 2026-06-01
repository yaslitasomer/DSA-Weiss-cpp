#include <iostream>
#include <string>
#include <vector>

using namespace std;

// Call-by-value
void incrementByValue(int num) {
    num += 100;
}

// Call-by-reference
void incrementByReference(int& num) {
    num += 100;
}

// Call-by-constant-reference, for big objects, no copying, no change
void printFirstElement(const vector<int>& arr) {
    if (!arr.empty()) {
        cout << "First element: " << arr[0] << endl;
    }
}

// Rvalue reference
void processTempValue(string&& tempStr) {
    cout << "Message: " << tempStr << endl;
}

/*
* RETURN PASSING
*/

// Return-by-value
int sum(int num1, int num2) {
    return num1 + num2;
}

// Return-by-constant-reference
// no copy, no change
const string& getFirstItemReadOnly(const vector<string>& arr) {
    return arr[0];
}

// Return-by-reference
string& getFirstItemModifiable(vector<string>& arr) {
    return arr[0];
}

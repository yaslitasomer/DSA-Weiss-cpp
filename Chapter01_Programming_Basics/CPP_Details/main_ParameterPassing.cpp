#include "ParameterPassing.h"
#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main() {
    int val = 100;

    incrementByValue(val);
    cout << "After incrementByValue func: " << val << endl;

    incrementByReference(val);
    cout << "After incrementByReference func: " << val << endl;

    vector<int> myVector = { 1, 2, 3, 4, 5, 6 };
    printFirstElement(myVector);

    string name = "Omer";
    processTempValue(name + " Y.");
    processTempValue("Just a temp string...");

    cout << "---\nReturn by value" << endl;
    int result = sum(5, 10);
    cout << "Sum: " << result << endl;

    cout << "Return by const reference" << endl;
    vector<string> myWords = {"Apple", "Banana", "Lemon"};
    
    const string& firstWord = getFirstItemReadOnly(myWords);
    cout << "First word: " << firstWord << endl;
    // firstWord = "Melon"; (ERROR)

    cout << "Return by reference" << endl;
    string& changeableWord = getFirstItemModifiable(myWords);
    changeableWord = "Strawberry";
    cout << "Changeable word: " << changeableWord << endl;

} 
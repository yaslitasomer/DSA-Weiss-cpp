#include <iostream>
#include <string>
#include "ArrayStack.h"
#include <unordered_map>

using namespace std;

bool isBalanced(const string& code) {
    ArrayStack<char> s;

    unordered_map<char, char> pairs = {
        {')', '('},
        {']', '['},
        {'}', '{'}
    };

    for (char c : code) {
        if (c == '(' || c == '[' || c == '{') {
            s.push(c);
        }

        else if (pairs.find(c) != pairs.end()) {
            if (s.empty()) {
                cout << "Error: Unexpected closing symbol '" << c << "'\n";
                return false;
            }

            char topChar = s.top();
            s.pop();

            if (topChar != pairs[c]) {
                cout << "Error: Mismatch! The last opened symbol was '" << topChar
                    << "', but tried to close with '" << c << "'!\n";
                return false;
            }
        }
    }

    if (!s.empty()) {
        cout << "Error: Missing closing symbol for '" << s.top() << "'\n";
        return false;
    }

    return true;
}

int main() {
    cout << "=== C++ SYNTAX BALANCER TEST ENGINE ===\n\n";

    // Let's store our test scenarios in a vector structure
    struct TestCase {
        string name;
        string code;
        bool expectedResult;
    };

    vector<TestCase> tests = {
        {"1. Flawless C++ Code", "int main() { vector<int> v = {1, 2, (3 + 4)}; return 0; }", true},
        {"2. Only Valid Parentheses", "([{}])(){[]}", true},
        {"3. Mismatch", "int main() { array[5) = 1; }", false},
        {"4. Missing Close", "void func() { if(true) { cout << 'Hi'; } ", false},
        {"5. Extra Close", "if (x == 5) } cout << x;", false}
    };

    // Feed all tests into our engine sequentially
    int passed = 0;
    for (const auto& test : tests) {
        cout << "Testing: " << test.name << "\n";
        cout << "Code snippet: " << test.code << "\n";

        bool result = isBalanced(test.code);

        if (result == test.expectedResult) {
            cout << "[SUCCESS] Engine predicted correctly!\n";
            passed++;
        }
        else {
            cout << "[FAILED] Engine made a mistake!\n";
        }
        cout << "--------------------------------------------------------\n";
    }

    // Final Report
    cout << "\n=== TEST REPORT ===\n";
    cout << "Total Tests: " << tests.size() << "\n";
    cout << "Passed: " << passed << "\n";

    if (passed == tests.size()) {
        cout << "Status: FLAWLESS!\n";
    }

    return 0;
}
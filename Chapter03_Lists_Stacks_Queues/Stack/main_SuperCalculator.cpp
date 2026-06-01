#include <istream>
#include <string>
#include <sstream>
#include <stdexcept>
#include "ArrayStack.h"
#include <iostream>

using namespace std;

int getPrecedence(const string& op) {
    if (op == "*" || op == "/") return 2;
    if (op == "+" || op == "-") return 1;
    return 0;
}

string infixToPostfix(const string& infix) {
    ArrayStack<string> s;
    istringstream iss(infix);
    string token;
    string postfix = "";

    while (iss >> token) {

        // If it is opening paranthesis, push it directly
        if (token == "(") {
            s.push(token);
        }

        // If it is closing paranthesis, pop everything until the opening one
        else if (token == ")") {
            while (!s.empty() && s.top() != "(") {
                postfix += s.top() + " ";
                s.pop();
            }
            if (!s.empty()) s.pop();
        }

        // If an operator arrives
        else if (token == "+" || token == "-" || token == "*" || token == "/") {
            // Pop operators if they have greater than or equal precedence
            while (!s.empty() && getPrecedence(s.top()) >= getPrecedence(token)) {
                postfix += s.top() + " ";
                s.pop();
            }
            // Then push the current operator
            s.push(token);
        }

        // If it is an operand
        else {
            postfix += token + " ";
        }
    }

    // Pop all remaining operators from the stack
    while (!s.empty()) {
        postfix += s.top() + " ";
        s.pop();
    }

    postfix.pop_back();
    return postfix;
}

// CALCULATOR ENGINE (POSTFIX EVALUATOR)
int evaluatePostfix(const string& expression) {
    ArrayStack<int> s;
    istringstream iss(expression);
    string token;

    while (iss >> token) {
        if (token == "+" || token == "-" || token == "*" || token == "/") {
            // Safety check
            if (s.size() < 2)
                throw invalid_argument("Error: Invalid postfix expression!");

            int rightOperand = s.top(); s.pop();
            int leftOperand = s.top(); s.pop();

            if (token == "+") s.push(leftOperand + rightOperand);
            if (token == "-") s.push(leftOperand - rightOperand);
            if (token == "*") s.push(leftOperand * rightOperand);
            if (token == "/") {
                if (rightOperand == 0) throw runtime_error("Error: Division by zero!");
                s.push(leftOperand / rightOperand);
            }
        }
        else {
            s.push(stoi(token));
        }
    }
    return s.top();
}

// THE SUPER CALCULATOR
int superCalculator(const string& humanMath) {
    string machineMath = infixToPostfix(humanMath);
    cout << "Converted to postfix: " << machineMath << endl;
    return evaluatePostfix(machineMath);
}

int main() {
    cout << "=== UNIFIED SYSTEM TEST ENGINE ===\n\n";

    // ---------------------------------------------------------
    // TEST SUITE 1: INFIX TO POSTFIX CONVERTER (Strings/Letters)
    // ---------------------------------------------------------
    cout << ">>> STARTING SUITE 1: CONVERTER DIAGNOSTICS <<<\n\n";

    struct ConverterTest {
        string name;
        string infixExpression;
        string expectedPostfix;
    };

    vector<ConverterTest> converterTests = {
        {"Simple Addition", "A + B", "A B +"},
        {"Operator Precedence", "A + B * C", "A B C * +"},
        {"Parentheses Override", "( A + B ) * C", "A B + C *"},
        {"The Ultimate Book Example", "a + b * c + ( d * e + f ) * g", "a b c * + d e * f + g * +"}
    };

    int converterPassed = 0;
    for (const auto& test : converterTests) {
        cout << "Testing: " << test.name << "\n";
        string result = infixToPostfix(test.infixExpression);
        if (result == test.expectedPostfix) {
            cout << "[SUCCESS] Match found: " << result << "\n";
            converterPassed++;
        }
        else {
            cout << "[FAILED] Expected: " << test.expectedPostfix << " but got: " << result << "\n";
        }
        cout << "--------------------------------------------------------\n";
    }

    // ---------------------------------------------------------
    // TEST SUITE 2: SUPER CALCULATOR (Integers/Math)
    // ---------------------------------------------------------
    cout << "\n>>> STARTING SUITE 2: SUPER CALCULATOR DIAGNOSTICS <<<\n\n";

    struct CalculatorTest {
        string name;
        string mathExpression;
        int expectedResult;
    };

    vector<CalculatorTest> calculatorTests = {
        {"Basic Precedence", "2 + 3 * 4", 14},
        {"Left-to-Right Associativity", "10 - 2 - 3", 5},
        {"Parentheses Overriding", "( 10 - 2 ) * 3", 24},
        {"Deeply Nested Parentheses", "( ( 5 + 3 ) / 2 ) * 4", 16},
        {"The Numeric Final Boss", "1 + 2 * 3 + ( 4 * 5 + 6 ) * 7", 189}
    };

    int calculatorPassed = 0;
    for (const auto& test : calculatorTests) {
        cout << "Testing: " << test.name << "\n";
        cout << "Expression: " << test.mathExpression << "\n";

        try {
            int result = superCalculator(test.mathExpression);
            if (result == test.expectedResult) {
                cout << "[SUCCESS] Calculated perfectly: " << result << "\n";
                calculatorPassed++;
            }
            else {
                cout << "[FAILED] Expected: " << test.expectedResult << " but got: " << result << "\n";
            }
        }
        catch (const exception& e) {
            cout << "[FATAL ERROR] " << e.what() << "\n";
        }
        cout << "--------------------------------------------------------\n";
    }

    // ---------------------------------------------------------
    // FINAL REPORT
    // ---------------------------------------------------------
    cout << "\n=== FULL SYSTEM DIAGNOSTICS REPORT ===\n";
    cout << "Converter Tests Passed : " << converterPassed << " / " << converterTests.size() << "\n";
    cout << "Calculator Tests Passed: " << calculatorPassed << " / " << calculatorTests.size() << "\n";

    if (converterPassed == converterTests.size() && calculatorPassed == calculatorTests.size()) {
        cout << "\nStatus: ALL SYSTEMS FLAWLESS! The architecture is ready for production.\n";
    }
    else {
        cout << "\nStatus: WARNING! Some modules failed. Check the logs above.\n";
    }

    return 0;
}
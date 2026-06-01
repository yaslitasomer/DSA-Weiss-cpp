#include <iostream>
#include <string>
#include <sstream>
#include <stdexcept>
#include <vector>
#include <cmath> // [YENİ EKLENDİ]: Üs alma (pow) fonksiyonu için gerekli!
#include "../Stack/ArrayStack.h"

using namespace std;

int getPrecedence(const string& op) {
    if (op == "^") return 3;
    if (op == "*" || op == "/") return 2;
    if (op == "+" || op == "-") return 1;
    return 0;
}

bool isRightAssociative(const string& op) {
    return op == "^";
}

string infixToPostfix(const string& infix) {
    ArrayStack<string> s;
    istringstream iss(infix);
    string token;
    string postfix = "";

    while (iss >> token) {
        if (token == "(") {
            s.push(token);
        }
        else if (token == ")") {
            while (!s.empty() && s.top() != "(") {
                postfix += s.top() + " ";
                s.pop();
            }
            if (!s.empty()) s.pop();
        }

        else if (token == "+" || token == "-" || token == "*" || token == "/" || token == "^") {

            while (!s.empty() && s.top() != "(") {
                int topPrec = getPrecedence(s.top());
                int tokenPrec = getPrecedence(token);

                if (topPrec > tokenPrec || (topPrec == tokenPrec && !isRightAssociative(token))) {
                    postfix += s.top() + " ";
                    s.pop();
                }
                else {
                    break;
                }
            }
            s.push(token);
        }
        else {
            postfix += token + " ";
        }
    }

    while (!s.empty()) {
        postfix += s.top() + " ";
        s.pop();
    }

    postfix.pop_back();
    return postfix;
}

string postfixToInfix(const string& postfix) {
    ArrayStack<string> s;
    istringstream iss(postfix);
    string token;

    while (iss >> token) {
        if (token == "+" || token == "-" || token == "*" || token == "/" || token == "^") {
            if (s.size() < 2) throw invalid_argument("Error: Invalid postfix expression!");

            string rightOperand = s.top(); s.pop();
            string leftOperand = s.top(); s.pop();

            // Etrafına parantez sararak eski haline (Infix) getir ve yığına at
            string combined = "( " + leftOperand + " " + token + " " + rightOperand + " )";
            s.push(combined);
        }
        else {
            s.push(token);
        }
    }

    return s.top();
}

int evaluatePostfix(const string& expression) {
    ArrayStack<int> s;
    istringstream iss(expression);
    string token;

    while (iss >> token) {
        if (token == "+" || token == "-" || token == "*" || token == "/" || token == "^") {
            if (s.size() < 2) throw invalid_argument("Error: Invalid postfix expression!");

            int rightOperand = s.top(); s.pop();
            int leftOperand = s.top(); s.pop();

            if (token == "+") s.push(leftOperand + rightOperand);
            if (token == "-") s.push(leftOperand - rightOperand);
            if (token == "*") s.push(leftOperand * rightOperand);
            if (token == "/") {
                if (rightOperand == 0) throw runtime_error("Error: Division by zero!");
                s.push(leftOperand / rightOperand);
            }
            // [YENİ EKLENDİ]: pow() fonksiyonu ile üs hesaplama
            if (token == "^") s.push(pow(leftOperand, rightOperand));
        }
        else {
            s.push(stoi(token));
        }
    }
    return s.top();
}

// ==============================================================================
// THE SUPER CALCULATOR (MİMARİSİ SABİT KALDI)
// ==============================================================================
int superCalculator(const string& humanMath) {
    string machineMath = infixToPostfix(humanMath);
    cout << "Converted to postfix: " << machineMath << endl;
    return evaluatePostfix(machineMath);
}

// ==============================================================================
// DIAGNOSTICS ENGINE
// ==============================================================================
int main() {
    cout << "=== EXERCISE 3.23 (A, B, C) SUPER CALCULATOR ===\n\n";

    cout << ">>> TEST 1: Exponentiation (a ^ b ^ c) <<<\n";
    string mathExp = "2 ^ 3 ^ 2"; // Should be 2^(3^2) = 2^9 = 512

    string machineMath = infixToPostfix(mathExp);
    cout << "Infix   : " << mathExp << "\n";
    cout << "Postfix : " << machineMath << "\n";

    int result = evaluatePostfix(machineMath);
    cout << "Result  : " << result << " (Expected: 512)\n";
    cout << "--------------------------------------------------------\n\n";

    cout << ">>> TEST 2: Postfix back to Infix <<<\n";
    string postfixStr = "a b c * + d e * f + g * +";

    cout << "Original Postfix : " << postfixStr << "\n";
    string reversedInfix = postfixToInfix(postfixStr);
    cout << "Reversed Infix   : " << reversedInfix << "\n";
    cout << "--------------------------------------------------------\n\n";

    return 0;
}
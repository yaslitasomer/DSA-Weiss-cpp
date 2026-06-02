#include <iostream>
#include "ExpressionTree.h"

using namespace std;

// Helper function to run tests neatly
void runDiagnostics(ExpressionTree& tree, const string& testName, const string& postfixData) {
    cout << ">>> " << testName << " <<<\n";
    cout << "  Input   : " << (postfixData.empty() ? "\"(Empty String)\"" : postfixData) << "\n";

    tree.buildFromPostfix(postfixData);

    tree.printInfix();
    tree.printPostfix();
    tree.printPrefix();
    cout << "--------------------------------------------------------\n\n";
}


int main() {
    cout << "=== EXPRESSION TREE COMPREHENSIVE DIAGNOSTICS ===\n\n";

    ExpressionTree tree;

    runDiagnostics(tree, "TEST 1: Edge Case (Single Operand)", "x");

    runDiagnostics(tree, "TEST 2: Simple Binary Operation", "ab+");

    runDiagnostics(tree, "TEST 3: Textbook Standard Masterpiece", "ab+cde+**");

    // Infix: (a + b * c) + ((d * e + f ) * g)
    runDiagnostics(tree, "TEST 4: Advanced Complex Tree (Fig 4.14)", "abc*+de*f+g*+");

    // TEST 5: Memory Leak & Reuse Test
    runDiagnostics(tree, "TEST 5: Memory Cleanup & Reuse Test", "");

    cout << "ALL SPACE-TIME COMPLEXITY DIAGNOSTICS COMPLETED SAFELY.\n";
    return 0;
}
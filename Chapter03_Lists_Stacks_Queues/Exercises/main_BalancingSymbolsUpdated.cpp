#include <iostream>
#include <string>
#include <unordered_map>
#include "../Stack/ArrayStack.h"

using namespace std;

struct SymbolInfo {
    char symbol;
    int line;
};

bool isBalanced(const string& code) {
    ArrayStack<SymbolInfo> s;
    int currentLine = 1;

    for (int i = 0; i < code.length(); i++) {
        if (code[i] == '\n') {
            currentLine++;
            continue;
        }

        // Inside comment
        if (!s.empty() && s.top().symbol == '*') {
            if (code[i] == '*' && i + 1 < code.length() && code[i + 1] == '/') {
                s.pop();
                i++;
            }
            continue;
        }

        // Comment opening
        if (code[i] == '/' && i + 1 < code.length() && code[i + 1] == '*') {
            s.push({ '*', currentLine });
            i++;
        }

        // Ordenary openings
        else if (code[i] == '(' || code[i] == '[' || code[i] == '{') {
            s.push({ code[i], currentLine });
        }

        // Closing
        else if (code[i] == ')' || code[i] == ']' || code[i] == '}') {
            if (s.empty()) {
                cout << "[ERROR] Line " << currentLine << ": Unexpected closing symbol '" << code[i] << "' without an opener!\n";
                return false;
            }

            SymbolInfo topSym = s.top();
            s.pop();

            // Eşleşme Kontrolü (Requirement C: Muhtemel sebebi açıklıyoruz)
            if ((code[i] == ')' && topSym.symbol != '(') ||
                (code[i] == ']' && topSym.symbol != '[') ||
                (code[i] == '}' && topSym.symbol != '{')) {

                cout << "[ERROR] Line " << currentLine
                    << ": Mismatch! Found '" << code[i]
                    << "', but expected closing for '" << topSym.symbol
                    << "' from line " << topSym.line << ".\n";
                return false;
            }
        }
        // 4. Beklenmeyen Yorum Kapanışı (*/) Yakalama
        else if (code[i] == '*' && i + 1 < code.length() && code[i + 1] == '/') {
            cout << "[ERROR] Line " << currentLine
                << ": Found '*/' outside of any comment block!\n";
            return false;
        }
    }

    // =======================================================
    // DURUM C: KOD BİTTİ, YIĞIN BOŞ MU? (Kapanmamış Semboller)
    // =======================================================
    if (!s.empty()) {
        SymbolInfo unclosed = s.top();
        if (unclosed.symbol == '*') {
            cout << "[ERROR] Unclosed comment block '/*' that started on line "
                << unclosed.line << "!\n";
        }
        else {
            cout << "[ERROR] Missing closing symbol for '" << unclosed.symbol
                << "' that was opened on line " << unclosed.line << "!\n";
        }
        return false;
    }

    cout << "[SUCCESS] All C++ symbols are perfectly balanced!\n";
    return true;
}

int main() {
    string test1 = "int main() {\n  /* This is a comment { [ ( */\n  return 0;\n}";
    string test2 = "int main() {\n  printf(\"Hello\");\n  }\n}";
    string test3 = "\n\n/* Missing close comment \n int x = 5;\n";

    cout << "--- TEST 1 (Valid with comments) ---\n";
    isBalanced(test1);

    cout << "\n--- TEST 2 (Extra brace) ---\n";
    isBalanced(test2);

    cout << "\n--- TEST 3 (Unclosed Comment) ---\n";
    isBalanced(test3);

    return 0;
}
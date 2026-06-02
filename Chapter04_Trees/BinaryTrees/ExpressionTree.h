#include <iostream>
#include <stack>
#include <string>
#include <cctype>

using namespace std;

// Converts a Postfix expression into a Binary Expression Tree
class ExpressionTree {
private:
    struct BinaryNode
    {
        char element;
        BinaryNode* left;
        BinaryNode* right;

        BinaryNode(char e, BinaryNode* l = nullptr, BinaryNode* r = nullptr) : element{ e }, left{ l }, right{ r } {}
    };

    BinaryNode* root;

    // Recursive deletion
    void makeEmpty(BinaryNode*& t) {
        if (t != nullptr) {
            makeEmpty(t->left);
            makeEmpty(t->right);
            delete t;
        }
        t = nullptr;
    }

    void printInfix(BinaryNode* t) const {
        if (t != nullptr) {
            if (t->left != nullptr) cout << "(";
            printInfix(t->left);
            cout << t->element;
            printInfix(t->right);
            if (t->right != nullptr) cout << ")";
        }
    }

    void printPostfix(BinaryNode* t) const {
        if (t != nullptr) {
            printPostfix(t->left);
            printPostfix(t->right);
            cout << t->element;
        }
    }

    void printPrefix(BinaryNode* t) const {
        if (t != nullptr) {
            cout << t->element;
            printPostfix(t->left);
            printPostfix(t->right);
        }
    }

public:
    ExpressionTree() : root{ nullptr } {}

    ~ExpressionTree() {
        makeEmpty(root);
    }

    void buildFromPostfix(const string& postfix) {
        makeEmpty(root);

        stack<BinaryNode*> nodeStack;

        for (char ch : postfix) {
            if (ch == ' ') continue;

            if (isalnum(ch)) {
                nodeStack.push(new BinaryNode(ch));
            }
            else {
                BinaryNode* rightChild = nodeStack.top();
                nodeStack.pop();

                BinaryNode* leftChild = nodeStack.top();
                nodeStack.pop();

                BinaryNode* parent = new BinaryNode(ch, leftChild, rightChild);
                nodeStack.push(parent);
            }
        }

        if (!nodeStack.empty()) {
            root = nodeStack.top();
        }
    }

    void printInfix() const {
        cout << "  Infix   : ";
        if (root == nullptr) cout << "(Empty Tree)";
        else printInfix(root);
        cout << "\n";
    }

    void printPostfix() const {
        cout << "  Postfix : ";
        if (root == nullptr) cout << "(Empty Tree)";
        else printPostfix(root);
        cout << "\n";
    }

    void printPrefix() const {
        cout << "  Prefix  : ";
        if (root == nullptr) cout << "(Empty Tree)";
        else printPrefix(root);
        cout << "\n";
    }
};
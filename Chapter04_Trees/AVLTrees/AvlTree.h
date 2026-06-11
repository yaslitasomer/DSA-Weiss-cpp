#include <iostream>
#include <algorithm>
#include <cmath>
#include <stack>

using namespace std;

// ==============================================================================
// AVL TREE ARCHITECTURE (Adelson-Velskii and Landis)
// Self-balancing Binary Search Tree.
// Guarantees O(log N) operations by strictly maintaining a height balance.
// ==============================================================================
template <typename Comparable>
class AvlTree {
private:
    // AVL NODE
    struct AvlNode
    {
        Comparable element;
        AvlNode* left;
        AvlNode* right;
        int height;

        AvlNode(const Comparable& e, AvlNode* l, AvlNode* r, int h = 0) : element{ e }, left{ l }, right{ r }, height{ h } {}

        AvlNode(Comparable&& e, AvlNode* l, AvlNode* r, int h = 0) : element{ std::move(e) }, left{ l }, right{ r }, height{ h } {}
    };

    AvlNode* root;

    static const int ALLOWED_IMBALANCE = 1;

    // Computes height of a Node
    int height(AvlNode* t) const {
        return t == nullptr ? -1 : t->height;
    }

    AvlNode* findMin(AvlNode* t) const {
        if (t == nullptr) return nullptr;
        if (t->left == nullptr) return t;
        return findMin(t->left);
    }

    AvlNode* findMax(AvlNode* t) const {
        if (t != nullptr) {
            while (t->right != nullptr) {
                t = t->right;
            }
        }
        return t;
    }

    void makeEmpty(AvlNode*& t) {
        if (t != nullptr) {
            makeEmpty(t->left);
            makeEmpty(t->right);
            delete t;
        }
        t = nullptr;
    }

    void printTree(AvlNode* t, ostream& out) const {
        if (t != nullptr) {
            printTree(t->left, out);
            out << t->element << " ";
            printTree(t->right, out);
        }
    }

    void insert(const Comparable& x, AvlNode*& t) {
        if (t == nullptr) {
            t = new AvlNode(x, nullptr, nullptr);
        }
        else if (x < t->element) {
            insert(x, t->left);
        }
        else if (x > t->element) {
            insert(x, t->right);
        }

        balance(t);
    }

    void remove(const Comparable& x, AvlNode*& t) {
        if (t == nullptr) return;

        if (x < t->element)
            remove(x, t->left);
        else if (x > t->element)
            remove(x, t->right);
        else if (t->left != nullptr && t->right != nullptr) { // Two children
            t->element = findMin(t->right)->element;
            remove(t->element, t->right);
        }
        else {
            AvlNode* oldNode = t;
            t = (t->left != nullptr) ? t->left : t->right;
            delete oldNode;
        }

        balance(t);
    }

    void balance(AvlNode*& t) {
        if (t == nullptr) return;

        if (height(t->left) - height(t->right) > ALLOWED_IMBALANCE) {
            if (height(t->left->left) >= height(t->left->right))
                rotateWithLeftChild(t);
            else
                doubleWithLeftChild(t);
        }
        else if (height(t->right) - height(t->left) > ALLOWED_IMBALANCE) {
            if (height(t->right->right) >= height(t->right->left))
                rotateWithRightChild(t);
            else
                doubleWithRightChild(t);
        }

        t->height = max(height(t->left), height(t->right)) + 1;
    }

    // THE ROTATIONS

    /**
    * Rotate binary tree node with left child.
    * For AVL trees, this is a single rotation for case 1.
    * Update heights, then set new root.
    */
    void rotateWithLeftChild(AvlNode*& k2) {
        AvlNode* k1 = k2->left;
        k2->left = k1->right;
        k1->right = k2;
        k2->height = max(height(k2->left), height(k2->right)) + 1;
        k1->height = max(height(k1->left), k2->height) + 1;
        k2 = k1;
    }

    /**
    * Rotate binary tree node with right child.
    * For AVL trees, this is a single rotation for case 4.
    * Update heights, then set new root.
    */
    void rotateWithRightChild(AvlNode*& k1) {
        AvlNode* k2 = k1->right;
        k1->right = k2->left;
        k2->left = k1;
        k1->height = max(height(k1->left), height(k1->right)) + 1;
        k2->height = max(height(k2->left), k1->height) + 1;
        k1 = k2;
    }

    /**
    * Double rotate binary tree node: first left child
    * with its right child; then node k3 with new left child.
    * For AVL trees, this is a double rotation for case 2.
    * Update heights, then set new root.
    */
    void doubleWithLeftChild(AvlNode*& k3) {
        rotateWithRightChild(k3->left);
        rotateWithLeftChild(k3);
    }

    /**
    * Double rotate binary tree node: first right child
    * with its left child; then node k3 with new right child.
    * For AVL trees, this is a double rotation for case 3.
    * Update heights, then set new root.
    */
    void doubleWithRightChild(AvlNode*& k3) {
        rotateWithLeftChild(k3->right);
        rotateWithRightChild(k3);
    }

    // VISUALIZATION HELPER
    void printTreeVisual(AvlNode* t, int space) const {
        if (t == nullptr) return;
        space += 5;
        printTreeVisual(t->right, space);
        cout << "\n";
        for (int i = 5; i < space; i++) cout << " ";
        cout << t->element << endl;
        printTreeVisual(t->left, space);
    }

    // LINEAR TIME AVL VERIFIER (O(N))
    int checkAVL(AvlNode* t) const {
        if (t == nullptr) return -1;

        // Find the actual heights of left and right subtrees
        int leftHeight = checkAVL(t->left);
        if (leftHeight == -2) return -2;

        int rightHeight = checkAVL(t->right);
        if (rightHeight == -2) return -2;

        // Verify if the stored 'height' value in the current node is correct
        int actualHeight = std::max(leftHeight, rightHeight) + 1;
        if (t->height != actualHeight) {
            cout << "CRITICAL ERROR: Height mismatch at node " << t->element << "!\n";
            return -2;
        }

        // Check if the AVL Balance Property is violated
        if (std::abs(leftHeight - rightHeight) > 1) {
            cout << "CRITICAL ERROR: Balance property violated at node " << t->element << "!\n";
            return -2;
        }

        // If everything is perfect, return the actual height
        return actualHeight;

    }

public:
    AvlTree() : root{ nullptr } {}

    ~AvlTree() {
        makeEmpty(root);
    }

    void insert(const Comparable& x) {
        insert(x, root);
    }

    void remove(const Comparable& x) {
        remove(x, root);
    }

    void printTree() const {
        if (root == nullptr)
            cout << "Empty Tree\n";
        else {
            printTree(root, cout);
            cout << "\n";
        }
    }

    void printTreeVisual() const {
        if (root == nullptr)
            cout << "Empty Tree\n";
        else {
            cout << "--- VISUAL AVL TREE (Rotated Left by 90 Degrees) ---\n";
            printTreeVisual(root, 0);
            cout << "\n----------------------------------------------------\n";
        }
    }

    bool verifyAVL() const {
        if (root == nullptr) return true;

        bool isValid = (checkAVL(root) != -2);
        if (isValid)
            cout << "AVL Integrity Check Passed: Tree is perfectly balanced and heights are correct.\n";
        return isValid;
    }

    // ---------------------------------------------------------
    // NON-RECURSIVE (ITERATIVE) AVL INSERT
    // Uses a stack of Double Pointers to perfectly mimic recursion
    // without using the Call Stack.
    // ---------------------------------------------------------
    void insertIterative(const Comparable& x) {
        if (root == nullptr) {
            root = new AvlNode{ x, nullptr, nullptr };
            return;
        }

        // We store Double Pointers (pointers to pointers) instead of nodes!
        // This allows us to modify the actual tree links (parent's left/right) during backtracking.
        std::stack<AvlNode**> path;
        AvlNode** curr = &root;

        // Traverse down to find the insertion point
        while (*curr != nullptr) {
            path.push(curr); // Push the traversed path into the stack

            if (x < (*curr)->element) {
                curr = &((*curr)->left);
            }

            else if (x > (*curr)->element) {
                curr = &((*curr)->right);
            }

            else {
                return; // Duplicate, do nothing
            }
        }

        // Insert the new node at the discovered empty spot
        *curr = new AvlNode{ x, nullptr, nullptr };

        // Backtrack the path to update heights and balance the tree
        while (!path.empty()) {
            AvlNode** nodePtr = path.top();
            path.pop();

            balance(*nodePtr);
        }
    }
};
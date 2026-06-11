#include <iostream>

using namespace std;

// ==============================================================================
// ORDER STATISTIC TREE (Augmented BST)
// Supports finding the K-th smallest element in strictly O(log N) time.
// ==============================================================================
template <typename Comparable>
class OrderStatisticTree {
private:
    // ---------------------------------------------------------
    // 1. AUGMENTED NODE STRUCTURE
    // We add 'leftSize' to instantly know how many elements are smaller!
    // ---------------------------------------------------------
    struct BinaryNode {
        Comparable element;
        BinaryNode* left;
        BinaryNode* right;
        int leftSize; // Tracks the number of nodes in the left subtree

        BinaryNode(const Comparable& ele, BinaryNode* lt = nullptr, BinaryNode* rt = nullptr)
            : element{ ele }, left{ lt }, right{ rt }, leftSize{ 0 } {
        }
    };

    BinaryNode* root;

    // ---------------------------------------------------------
    // 2. MODIFIED INSERTION ENGINE
    // Automatically updates the 'leftSize' counter as we travel down.
    // ---------------------------------------------------------
    void insert(const Comparable& x, BinaryNode*& t) {
        if (t == nullptr) {
            t = new BinaryNode(x);
        }
        else if (x < t->element) {
            // We are inserting to the left, so this node's left subtree grows!
            t->leftSize++;
            insert(x, t->left);
        }
        else if (t->element < x) {
            // Inserting to the right does NOT affect the leftSize
            insert(x, t->right);
        }
    }

    // ---------------------------------------------------------
    // 3. THE O(log N) findKth ENGINE (The Magic)
    // ---------------------------------------------------------
    BinaryNode* findKth(int k, BinaryNode* t) const {
        if (t == nullptr) {
            return nullptr; // Out of bounds
        }

        // The exact rank of the current node is (leftSize + 1)
        int currentRank = t->leftSize + 1;

        if (k == currentRank) {
            // BINGO! We found exactly the K-th element
            return t;
        }
        else if (k < currentRank) {
            // The element we want is strictly in the left subtree
            return findKth(k, t->left);
        }
        else {
            // The element is in the right subtree.
            // IMPORTANT: We must adjust K! If we skip the left subtree and the current node,
            // we must subtract those elements from our target K.
            return findKth(k - currentRank, t->right);
        }
    }

    void makeEmpty(BinaryNode* t) {
        if (t != nullptr) {
            makeEmpty(t->left);
            makeEmpty(t->right);
            delete t;
        }
    }

public:
    OrderStatisticTree() : root{ nullptr } {}
    ~OrderStatisticTree() { makeEmpty(root); }

    void insert(const Comparable& x) {
        insert(x, root);
    }

    // Returns the K-th smallest element (1-based index)
    void printKth(int k) const {
        BinaryNode* result = findKth(k, root);
        if (result != nullptr) {
            cout << "The " << k << "-th smallest element is: " << result->element << "\n";
        }
        else {
            cout << "Error: The " << k << "-th smallest element does not exist.\n";
        }
    }
};

// ==============================================================================
// DIAGNOSTICS ENGINE
// ==============================================================================
int main() {
    cout << "=== ORDER STATISTIC TREE (O(log N) K-th FINDER) ===\n\n";

    OrderStatisticTree<int> ost;

    // Building the tree
    // Insertions: 50, 30, 70, 20, 40, 60, 80
    // Sorted order would be: 20, 30, 40, 50, 60, 70, 80
    cout << "1. Inserting elements: 50, 30, 70, 20, 40, 60, 80\n";
    ost.insert(50);
    ost.insert(30);
    ost.insert(70);
    ost.insert(20);
    ost.insert(40);
    ost.insert(60);
    ost.insert(80);
    cout << "   Sorted sequence conceptually: [20, 30, 40, 50, 60, 70, 80]\n\n";

    // Testing O(log N) retrieval
    cout << "2. Extracting K-th smallest elements instantly:\n";
    ost.printKth(1); // Expected: 20
    ost.printKth(3); // Expected: 40
    ost.printKth(4); // Expected: 50 (The root itself)
    ost.printKth(7); // Expected: 80
    ost.printKth(10); // Expected: Error

    cout << "\nALL ORDER STATISTIC DIAGNOSTICS COMPLETED SAFELY.\n";
    return 0;
}
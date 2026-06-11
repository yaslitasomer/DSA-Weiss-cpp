#include <iostream>
#include <algorithm> // for std::max

using namespace std;

// ==============================================================================
// LAZY DELETION BINARY SEARCH TREE
// Soft deletes nodes instead of physically removing them.
// Time Complexity: O(log N) for Insert, Delete, and Search.
// ==============================================================================
template <typename Comparable>
class LazyBST {
private:
    // Node Structure
    struct BinaryNode
    {
        Comparable element;
        BinaryNode* left;
        BinaryNode* right;
        bool isDeleted;

        BinaryNode(const Comparable& e, BinaryNode* l, BinaryNode* r, bool deleted = false) : element{ e }, left{ l }, right{ r }, isDeleted{ deleted } {}

        BinaryNode(Comparable&& e, BinaryNode* l, BinaryNode* r, bool deleted = false) : element{ std::move(e) }, left{ l }, right{ r }, isDeleted{ deleted } {}
    };

    BinaryNode* root;

    void insert(const Comparable& x, BinaryNode*& t) {
        if (t == nullptr) {
            t = new BinaryNode{ x, nullptr, nullptr };
        }
        else if (x < t->element) {
            insert(x, t->left);
        }
        else if (x > t->element) {
            insert(x, t->right);
        }
        else {
            // DUPLICATE FOUND
            // If it was previously soft-deleted, resurrect it
            if (t->isDeleted)
                t->isDeleted = false;
        }
    }

    void remove(const Comparable& x, BinaryNode*& t) {
        if (t == nullptr) return;

        if (x < t->element) {
            remove(x, t->left);
        }
        else if (x > t->element) {
            remove(x, t->right);
        }
        else {
            t->isDeleted = true;
        }
    }

    BinaryNode* findMin(BinaryNode* t) const {
        if (t == nullptr) return nullptr;

        // Try to find an active node on left subtree first
        BinaryNode* leftResult = findMin(t->left);
        if (leftResult != nullptr) return leftResult;

        // Check if the current node is active
        if (!t->isDeleted) return t;

        // If current is deleted...
        return findMin(t->right);
    }

    BinaryNode* findMax(BinaryNode* t) const {
        if (t == nullptr) return nullptr;

        // Try to find an active node on right subtree first
        BinaryNode* rightResult = findMax(t->right);
        if (rightResult != nullptr) return rightResult;

        // Check if the current node is active
        if (!t->isDeleted) return t;

        // If current is deleted...
        return findMax(t->left);
    }

    bool contains(const Comparable& x, BinaryNode* t) const {
        if (t == nullptr)
            return false;

        else if (x < t->element) {
            return contains(x, t->left);
        }

        else if (x > t->element) {
            return contains(x, t->right);
        }

        else {
            return !(t->isDeleted);
        }
    }

    void makeEmpty(BinaryNode* t) {
        if (t != nullptr) {
            makeEmpty(t->left);
            makeEmpty(t->right);
            delete t;
        }
        t = nullptr;
    }

    BinaryNode* clone(BinaryNode* t) const {
        if (t == nullptr) return nullptr;

        return new BinaryNode{ t->element, t->left, t->right, t->isDeleted };
    }

    // Prints the tree in inorder traversal
    void printTree(BinaryNode* t, ostream& out) const {
        if (t != nullptr) {
            printTree(t->left, out);

            if (!t->isDeleted)
                out << t->element << " ";

            printTree(t->right, out);
        }
    }

    void printPhysicalTree(BinaryNode* t, int space) const {
        if (t == nullptr) return;
        space += 5;
        printPhysicalTree(t->right, space);
        cout << "\n";
        for (int i = 5; i < space; i++) cout << " ";

        if (t->isDeleted) cout << "[" << t->element << "]\n";
        else cout << t->element << endl;

        printPhysicalTree(t->left, space);
    }

public:
    LazyBST() : root{ nullptr } {}

    LazyBST(const LazyBST& rhs) : root{ nullptr } {
        root = clone(rhs.root);
    }

    LazyBST(LazyBST&& rhs) : root{ rhs.root } {
        rhs.root = nullptr;
    }

    ~LazyBST() {
        makeEmpty();
    }

    LazyBST& operator=(const LazyBST& rhs) {
        LazyBST copy = rhs;
        std::swap(*this, copy);
        return *this;
    }

    LazyBST& operator=(LazyBST&& rhs) {
        std::swap(root, rhs.root);
        return *this;
    }

    const Comparable& findMin() const {
        return findMin(root)->element;
    }

    const Comparable& findMax() const {
        return findMax(root)->element;
    }

    bool contains(const Comparable& x) const {
        return contains(x, root);
    }

    bool isEmpty() const {
        return root == nullptr;
    }


    void makeEmpty() {
        makeEmpty(root);
    }

    void insert(const Comparable& x) {
        insert(x, root);
    }

    void insert(Comparable&& x) {
        insert(std::move(x), root);
    }

    void remove(const Comparable& x) {
        remove(x, root);
    }

    void printTree() const {
        printTree(root, cout);
        cout << endl;
    }

    void showPhysicalMemory() const {
        cout << "--- PHYSICAL MEMORY STATE ( [X] means deleted ) ---\n";
        printPhysicalTree(root, 0);
        cout << "\n---------------------------------------------------\n";
    }
};
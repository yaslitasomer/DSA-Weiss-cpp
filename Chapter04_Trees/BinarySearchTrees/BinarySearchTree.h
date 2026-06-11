#include <iostream>
#include <algorithm> // for std::max
#include <queue>

using namespace std;

// BINARY SEARCH TREE (BST) ARCHITECTURE
// Time Complexity: Average O(log N) for Search, Insert, and Delete.
template<typename Comparable>
class BinarySearchTree {
private:
    // Node Structure
    struct BinaryNode
    {
        Comparable element;
        BinaryNode* left;
        BinaryNode* right;

        BinaryNode(const Comparable& e, BinaryNode* l, BinaryNode* r) : element{ e }, left{ l }, right{ r } {}

        BinaryNode(Comparable&& e, BinaryNode* l, BinaryNode* r) : element{ std::move(e) }, left{ l }, right{ r } {}
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
            return;
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
        else if (t->left != nullptr && t->right != nullptr) {
            // CASE: Two children
            // Replace with the smallest element in the right subtree
            t->element = findMin(t->right)->element;
            remove(t->element, t->right);
        }
        else {
            // Zero or onechild
            BinaryNode* oldNode = t;
            t = (t->left != nullptr) ? t->left : t->right;
            delete oldNode;
        }
    }

    BinaryNode* findMin(BinaryNode* t) const {
        if (t == nullptr) return nullptr;
        if (t->left == nullptr) return t;
        return findMin(t->left);
    }

    BinaryNode* findMax(BinaryNode* t) const {
        if (t != nullptr) {
            while (t->right != nullptr) {
                t = t->right;
            }
        }
        return t;
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
            return true;
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

        return new BinaryNode{ t->element, t->left, t->right };
    }

    // Prints the tree in inorder traversal
    void printTree(BinaryNode* t, ostream& out) const {
        if (t != nullptr) {
            printTree(t->left, out);
            out << t->element << " ";
            printTree(t->right, out);
        }
    }

    void printTreeVisual(BinaryNode* t, int space) const {
        // Base Case
        if (t == nullptr) return;

        space += 5;

        printTreeVisual(t->right, space);

        cout << "\n";
        for (int i = 5; i < space; i++) {
            cout << " ";
        }
        cout << t->element << endl;

        printTreeVisual(t->left, space);
    }

    // ---------------------------------------------------------
    // EXERCISE 4.32: VALIDATE BINARY SEARCH TREE
    // Time Complexity: O(N) - Visits each node exactly once.
    // Passes min and max bounds down the recursive calls.
    // ---------------------------------------------------------
    bool isBST(BinaryNode* t, const Comparable* minVal = nullptr, const Comparable* maxVal = nullptr) const {
        // Base Case
        if (t == nullptr) return true;

        // Check if the current node violates the min/max constraints
        if (minVal != nullptr && t->element <= *minVal) return false;
        if (maxVal != nullptr && t->element >= *maxVal) return false;


        // Recursively validate left and right subtrees with updated constraints
        // Left subtree must be strictly less than current node's value
        // Right subtree must be strictly greater than current node's value
        return isBST(t->left, minVal, &(t->element)) && isBST(t->right, &(t->element), maxVal);
    }

    // ---------------------------------------------------------
    // EXERCISE 4.37: RANGE QUERY (Print items between k1 and k2)
    // Time Complexity: O(K + log N) where K is the number of printed nodes.
    // Strategically prunes branches that are out of bounds.
    // ---------------------------------------------------------
    void printRange(BinaryNode* t, const Comparable& k1, const Comparable& k2) const {
        if (t == nullptr) return;

        // If the current element is greater than k1, there might be valid elements in left subtree
        if (k1 < t->element) {
            printRange(t->left, k1, k2);
        }

        // If the current element is within the range, print it
        if (k1 <= t->element && t->element <= k2) {
            cout << t->element << " ";
        }

        // If current element is less than k2, there might be valid elements in right subtree
        if (t->element < k2) {
            printRange(t->right, k1, k2);
        }
    }

    // ---------------------------------------------------------
    // EXERCISE 4.45: SIMILAR TREES
    // Time Complexity: O(N) - Recursively checks if both trees 
    // have the exact same structure and values.
    // ---------------------------------------------------------
    bool isSimilar(BinaryNode* t1, BinaryNode* t2) const {
        if (t1 == nullptr && t2 == nullptr) return true;

        if (t1 == nullptr || t2 == nullptr) return false;

        return (t1->element == t2->element) && isSimilar(t1->left, t2->left) && isSimilar(t1->right, t2->right);
    }

    void mirror(BinaryNode* t) {
        if (t != nullptr) {
            BinaryNode* temp = t->left;
            t->left = t->right;
            t->right = temp;

            mirror(t->left);
            mirror(t->right);
        }
    }

    // ---------------------------------------------------------
    // EXERCISE 4.46: ISOMORPHIC TREES (Flip Equivalent)
    // Time Complexity: O(N) in average case, tests if T1 can be 
    // transformed into T2 by swapping some left/right children.
    // ---------------------------------------------------------
    bool isIsomorphic(BinaryNode* t1, BinaryNode* t2) const {
        if (t1 == nullptr && t2 == nullptr) return true;

        if (t1 == nullptr || t2 == nullptr) return false;

        if (t1->element != t2->element) return false;

        // Case 1: Children are not swapped
        bool notSwapped = isIsomorphic(t1->left, t2->left) && isIsomorphic(t1->right, t2->right);

        // Case 2: Children are swapped
        bool swapped = isIsomorphic(t1->left, t2->right) && isIsomorphic(t1->right, t2->left);

        return swapped || notSwapped;
    }

    // ---------------------------------------------------------
    // THE O(N) FLATTENING ENGINE (DSW Algorithm - Phase 1)
    // Flattens the BST into a right-leaning spine using Double Pointers.
    // ---------------------------------------------------------
    void treeToSpine(BinaryNode** currPtr) {
        while (*currPtr != nullptr) {
            // If there is a left child, eliminate it via a Right Rotation
            if ((*currPtr)->left != nullptr) {
                BinaryNode* leftChild = (*currPtr)->left;
                (*currPtr)->left = leftChild->right;
                leftChild->right = *currPtr;
                *currPtr = leftChild;
                // Do not advance; loop again to check the new root's left child
            }
            else {
                // Node is perfectly on the spine; advance to the right child
                currPtr = &((*currPtr)->right);
            }
        }
    }


public:
    BinarySearchTree() : root{ nullptr } {}

    BinarySearchTree(const BinarySearchTree& rhs) : root{ nullptr } {
        root = clone(rhs.root);
    }

    BinarySearchTree(BinarySearchTree&& rhs) : root{ rhs.root } {
        rhs.root = nullptr;
    }

    ~BinarySearchTree() {
        makeEmpty();
    }

    BinarySearchTree& operator=(const BinarySearchTree& rhs) {
        BinarySearchTree copy = rhs;
        std::swap(*this, copy);
        return *this;
    }

    BinarySearchTree& operator=(BinarySearchTree&& rhs) {
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

    void printTree(ostream& out = cout) const {
        if (isEmpty()) {
            out << "Empty tree\n";
        }
        else {
            printTree(root, out);
            out << "\n";
        }
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

    void printTreeVisual() const {
        if (isEmpty()) {
            cout << "Empty Tree!" << endl;
        }
        else {
            cout << "--- VISUAL TREE (Rotated Left by 90 Degrees) ---\n";
            printTreeVisual(root, 0);
            cout << "\n------------------------------------------------\n";
        }
    }

    bool isBST() const {
        return isBST(root, nullptr, nullptr);
    }

    void printRange(const Comparable& k1, const Comparable& k2) const {
        if (k1 > k2) {
            cout << "Invalid Range!\n";
            return;
        }
        printRange(root, k1, k2);
    }

    // ---------------------------------------------------------
    // EXERCISE 4.40: LEVEL-ORDER TRAVERSAL (Breadth-First Search)
    // Time Complexity: O(N) - Uses a queue to visit nodes depth by depth.
    // ---------------------------------------------------------
    void printLevelOrder() const {
        if (root == nullptr) {
            cout << "Tree is empty!" << endl;
            return;
        }

        std::queue<BinaryNode*> q;
        q.push(root);

        while (!q.empty()) {
            BinaryNode* current = q.front();
            q.pop();

            cout << current->element << " ";

            if (current->left != nullptr)
                q.push(current->left);
            if (current->right != nullptr)
                q.push(current->right);
        }
        cout << endl;
    }

    bool isSimilar(const BinarySearchTree& other) const {
        return isSimilar(this->root, other.root);
    }

    void mirror() {
        mirror(root);
    }

    bool isIsomorphic(const BinarySearchTree& other) const {
        return isIsomorphic(this->root, other.root);
    }

    // ---------------------------------------------------------
    // PUBLIC API FOR TRANSFORMATION
    // ---------------------------------------------------------
    void flatten() {
        treeToSpine(&root);
    }
};
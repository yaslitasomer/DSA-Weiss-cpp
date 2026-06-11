#include <iostream>
#include "BinarySearchTree.h"
#include <random>

using namespace std;

int main() {
    cout << "=== BINARY SEARCH TREE (BST) DIAGNOSTICS ===\n\n";

    BinarySearchTree<int> bst;

    // 1. TESTING INSERTIONS
    cout << "1. Inserting elements: 50, 30, 70, 20, 40, 60, 80\n";
    bst.insert(50); // Root
    bst.insert(30);
    bst.insert(70);
    bst.insert(20);
    bst.insert(40);
    bst.insert(60);
    bst.insert(80);

    // If the BST is built correctly, an INORDER print will be perfectly sorted.
    cout << "   Inorder Print (Should be sorted): ";
    bst.printTree();
    bst.printTreeVisual();
    cout << "--------------------------------------------------------\n";

    // 2. TESTING FIND MIN & MAX
    cout << "2. Verifying Extremes:\n";
    cout << "   Min Value: " << bst.findMin() << " (Expected: 20)\n";
    cout << "   Max Value: " << bst.findMax() << " (Expected: 80)\n";
    cout << "--------------------------------------------------------\n";

    // 3. TESTING CONTAINS
    cout << "3. Verifying Search (Contains):\n";
    cout << "   Contains 40? " << (bst.contains(40) ? "Yes" : "No") << "\n";
    cout << "   Contains 99? " << (bst.contains(99) ? "Yes" : "No") << "\n";
    cout << "--------------------------------------------------------\n";

    // 4. TESTING DELETIONS (The hardest part of a BST)
    cout << "4. Testing Deletions:\n";

    cout << "   a) Removing 20 (Leaf Node)...\n";
    bst.remove(20);
    cout << "      Tree state: "; bst.printTree();
    cout << "      Tree visual: "; bst.printTreeVisual();

    cout << "   b) Removing 30 (Node with one child - 40)...\n";
    bst.remove(30);
    cout << "      Tree state: "; bst.printTree();
    cout << "      Tree visual: "; bst.printTreeVisual();

    cout << "   c) Removing 50 (ROOT Node with TWO children!)...\n";
    bst.remove(50);
    cout << "      Tree state: "; bst.printTree();
    cout << "      Tree visual: "; bst.printTreeVisual();
    cout << "--------------------------------------------------------\n";

    cout << "5. Testing BST Validation:\n";
    cout << (bst.isBST() ? "The tree is a BST." : "The tree is not a BST!") << endl;
    bst.mirror();
    cout << (bst.isBST() ? "The tree is a BST." : "The tree is not a BST!") << endl;


    cout << "6. Testing Range Query:\n";
    BinarySearchTree<int> bst2;

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distr(1, 999);

    for (int i = 0; i < 15; i++) {
        int randNum = distr(gen);
        bst2.insert(randNum);
    }
    cout << "      Tree state: "; bst2.printTree();
    cout << "      Tree visual: "; bst2.printTreeVisual();
    bst2.printRange(200, 500);

    cout << "\n\n7. Testing Level Order Printing:\n";
    bst2.printLevelOrder();

    cout << "=== TREE COMPARISON DIAGNOSTICS (SIMILARITY & ISOMORPHISM) ===\n\n";

    // ---------------------------------------------------------
    // 1. SETUP: Create the Base Tree (Tree A)
    // ---------------------------------------------------------
    BinarySearchTree<int> treeA;
    treeA.insert(50);
    treeA.insert(30);
    treeA.insert(70);
    treeA.insert(20);
    treeA.insert(40);

    cout << "Tree A (Base Tree) Level-Order : ";
    treeA.printLevelOrder(); // Expected: 50 30 70 20 40
    cout << "\n";

    // ---------------------------------------------------------
    // TEST CASE 1: Identical Trees (Similar = YES, Isomorphic = YES)
    // ---------------------------------------------------------
    BinarySearchTree<int> treeB;
    treeB.insert(50);
    treeB.insert(30);
    treeB.insert(70);
    treeB.insert(20);
    treeB.insert(40);

    cout << "--- TEST 1: Comparing Tree A with Tree B (Identical Clone) ---\n";
    cout << "Are they Similar?   : " << (treeA.isSimilar(treeB) ? "YES (Passed)" : "NO (Failed)") << "\n";
    cout << "Are they Isomorphic?: " << (treeA.isIsomorphic(treeB) ? "YES (Passed)" : "NO (Failed)") << "\n\n";

    // ---------------------------------------------------------
    // TEST CASE 2: Completely Different Trees (Similar = NO, Isomorphic = NO)
    // ---------------------------------------------------------
    BinarySearchTree<int> treeC;
    treeC.insert(99);
    treeC.insert(11);
    treeC.insert(88);

    cout << "--- TEST 2: Comparing Tree A with Tree C (Completely Different) ---\n";
    cout << "Are they Similar?   : " << (treeA.isSimilar(treeC) ? "YES (Failed)" : "NO (Passed)") << "\n";
    cout << "Are they Isomorphic?: " << (treeA.isIsomorphic(treeC) ? "YES (Failed)" : "NO (Passed)") << "\n\n";

    // ---------------------------------------------------------
    // TEST CASE 3: Mirrored Trees (Similar = NO, Isomorphic = YES)
    // This is the ultimate test for Isomorphism!
    // ---------------------------------------------------------
    BinarySearchTree<int> treeD;
    treeD.insert(50);
    treeD.insert(30);
    treeD.insert(70);
    treeD.insert(20);
    treeD.insert(40);

    // Forcing a structural flip (Violates BST property, but tests general tree isomorphism perfectly)
    treeD.mirror();

    cout << "Tree D (Mirrored) Level-Order  : ";
    treeD.printLevelOrder(); // Expected: 50 70 30 40 20 (Children are swapped!)
    cout << "\n";

    cout << "--- TEST 3: Comparing Tree A with Tree D (Mirrored/Flipped) ---\n";
    cout << "Are they Similar?   : " << (treeA.isSimilar(treeD) ? "YES (Failed)" : "NO (Passed)") << "\n";
    cout << "Are they Isomorphic?: " << (treeA.isIsomorphic(treeD) ? "YES (Passed)" : "NO (Failed)") << "\n\n";

    cout << "ALL TREE COMPARISON DIAGNOSTICS COMPLETED SAFELY.\n";
    return 0;
}
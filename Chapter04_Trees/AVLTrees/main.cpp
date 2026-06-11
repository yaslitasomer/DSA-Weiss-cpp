#include <iostream>
#include "AvlTree.h"

using namespace std;

int main() {
    cout << "=== AVL TREE (SELF-BALANCING) DIAGNOSTICS ===\n\n";

    // ---------------------------------------------------------
    // TEST 1: SINGLE LEFT ROTATION
    // ---------------------------------------------------------
    AvlTree<int> avl1;
    cout << "1. Inserting 10, 20, 30 (Forces Single Left Rotation at 10)...\n";
    // Expected: Root becomes 20, with 10 on the left and 30 on the right.
    avl1.insert(10);
    avl1.insert(20);
    avl1.insert(30);
    avl1.printTreeVisual();

    // ---------------------------------------------------------
    // TEST 2: DOUBLE LEFT-RIGHT ROTATION
    // ---------------------------------------------------------
    AvlTree<int> avl2;
    cout << "2. Inserting 30, 10, 20 (Forces Double Left-Right Rotation at 30)...\n";
    // Sequence: 30 is root. 10 goes left. 20 goes right of 10.
    // Imbalance at 30: Left child (10) is "right-heavy" (20), triggering a Double Rotation!
    // Expected: Root becomes 20, with 10 on the left and 30 on the right.
    avl2.insert(30);
    avl2.insert(10);
    avl2.insert(20);
    avl2.printTreeVisual();

    // ---------------------------------------------------------
    // TEST 3: DOUBLE RIGHT-LEFT ROTATION
    // ---------------------------------------------------------
    AvlTree<int> avl3;
    cout << "3. Inserting 10, 30, 20 (Forces Double Right-Left Rotation at 10)...\n";
    // Sequence: 10 is root. 30 goes right. 20 goes left of 30.
    // Imbalance at 10: Right child (30) is "left-heavy" (20), triggering a Double Rotation!
    // Expected: Root becomes 20, with 10 on the left and 30 on the right.
    avl3.insert(10);
    avl3.insert(30);
    avl3.insert(20);
    avl3.printTreeVisual();

    // ---------------------------------------------------------
    // TEST 4: COMPREHENSIVE DELETION
    // ---------------------------------------------------------
    AvlTree<int> avl4;
    cout << "4. Complex Tree Deletion (Root Deletion with Rebalance)...\n";
    avl4.insert(50);
    avl4.insert(30);
    avl4.insert(70);
    avl4.insert(20);
    avl4.insert(40);
    avl4.insert(60);
    avl4.insert(80);
    cout << "   Before Deleting Root (50):\n";
    avl4.printTreeVisual();

    avl4.remove(50);
    cout << "   After Deleting Root (50) - (Should replace with 60 and balance):\n";
    avl4.printTreeVisual();



    cout << "5. AVL Balance Verifier...\n";
    avl1.verifyAVL();
    avl2.verifyAVL();

    cout << "\n6. Iterative Insertion...\n";
    AvlTree<int> avl5;
    avl5.insertIterative(50);
    avl5.insertIterative(30);
    avl5.insertIterative(70);
    avl5.insertIterative(20);
    avl5.insertIterative(40);
    avl5.insertIterative(60);
    avl5.insertIterative(80);
    cout << "   Before Deleting Root (50):\n";
    avl5.printTreeVisual();
    avl5.remove(50);
    cout << "   After Deleting Root (50) - (Should replace with 60 and balance):\n";
    avl5.printTreeVisual();

    cout << "\nALL SELF-BALANCING ROTATION DIAGNOSTICS COMPLETED SAFELY.\n";
    return 0;
}
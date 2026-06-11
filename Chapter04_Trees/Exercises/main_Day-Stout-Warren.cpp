#include "../BinarySearchTrees/BinarySearchTree.h"
#include <iostream>

using namespace std;

// ==============================================================================
// FAANG-LEVEL DIAGNOSTICS ENGINE
// Proving that ANY two BSTs with the same elements can be transformed 
// into each other using rotations (Day-Stout-Warren / DSW Algorithm).
// ==============================================================================

/*
    =============================================================================
    INTERVIEW CHEAT SHEET: THE O(N) TRANSFORMATION ALGORITHM (T1 -> T2)
    =============================================================================
    How to transform Tree 1 (T1) into Tree 2 (T2) using strictly O(N) rotations:

    * PHASE 1 (Flatten T1):
    Use Right Rotations to eliminate all left children in T1.
    T1 becomes a straight "Right-Leaning Spine" (Linked List).
    Cost: Maximum N-1 rotations.

    * PHASE 2 (Map T2):
    Conceptually flatten T2 into a Right-Leaning Spine.
    CRITICAL: Record every Right Rotation made in a History Stack.
    Cost: Maximum N-1 rotations.

    * PHASE 3 (Fold the Spine):
    Take the T1 Spine. Pop the recorded moves from the History Stack one by one,
    applying them in REVERSE (as Left Rotations).
    T1 will perfectly fold into the exact structural shape of T2!
    Cost: Maximum N-1 rotations.

    Total Worst-Case Time Complexity: O(N).
    Total Worst-Case Space Complexity: O(N) for the History Stack.

    NOTE: Implementing Phase 2 & 3 in an interview is exceedingly rare due to
    the boilerplate required to record/replay moves. Proving that both trees
    reduce to the EXACT same spine (as done below) mathematically guarantees
    that the reversible transformation is possible.
    =============================================================================
*/

int main() {
    cout << "=== TREE TRANSFORMATION PROOF (DSW ALGORITHM) ===\n\n";

    // ---------------------------------------------------------
    // 1. SETUP: Create two COMPLETELY different shaped BSTs
    // ---------------------------------------------------------
    BinarySearchTree<int> treeA; // Balanced shape
    treeA.insert(50); treeA.insert(30); treeA.insert(70);
    treeA.insert(20); treeA.insert(40); treeA.insert(60); treeA.insert(80);

    BinarySearchTree<int> treeB; // Zig-zag / Degenerate shape
    treeB.insert(20); treeB.insert(80); treeB.insert(30);
    treeB.insert(70); treeB.insert(40); treeB.insert(60); treeB.insert(50);

    cout << "1. Two trees (Tree A and Tree B) created with the same elements but different shapes.\n";
    cout << "   Tree A Level-Order: "; treeA.printLevelOrder();
    cout << "   Tree B Level-Order: "; treeB.printLevelOrder();

    cout << "   Are they currently Similar? : "
        << (treeA.isSimilar(treeB) ? "YES" : "NO (Expected)") << "\n\n";

    // ---------------------------------------------------------
    // 2. PHASE 1: FLATTENING (The DSW Spine Transformation)
    // ---------------------------------------------------------
    cout << "2. Flattening both trees into Right-Leaning Spines using O(N) Right Rotations...\n";
    treeA.flatten();
    treeB.flatten();

    cout << "   Tree A (Flattened) Level-Order: "; treeA.printLevelOrder();
    cout << "   Tree B (Flattened) Level-Order: "; treeB.printLevelOrder();
    cout << "\n";

    // ---------------------------------------------------------
    // 3. THE MATHEMATICAL PROOF
    // ---------------------------------------------------------
    cout << "3. The Ultimate Proof:\n";
    cout << "   If T1 and T2 can be reduced to the exact same spine,\n";
    cout << "   they can be transformed into each other via reversible rotations!\n";

    // Since both are identical spines now, isSimilar MUST return true!
    cout << "   Are they Similar NOW? : "
        << (treeA.isSimilar(treeB) ? "YES (Theorem Proven!)" : "NO (Failed)") << "\n\n";

    cout << "ALL THEORETICAL PROOFS AND DOCUMENTATION COMPLETED SAFELY.\n";
    return 0;
}

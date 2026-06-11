#include <iostream>
#include "LazyBST.h"

using namespace std;

int main() {
    cout << "=== LAZY DELETION BST DIAGNOSTICS ===\n\n";

    LazyBST<int> tree;

    cout << "1. Inserting: 50, 30, 20, 40, 70, 80\n";
    tree.insert(50);
    tree.insert(30);
    tree.insert(20);
    tree.insert(40);
    tree.insert(70);
    tree.insert(80);

    cout << "   Active Elements: "; tree.printTree();
    cout << "   Min: " << tree.findMin() << " | Max: " << tree.findMax() << "\n\n";

    cout << "2. Soft Deleting '20' (Min) and '80' (Max) and '50' (Root)...\n";
    tree.remove(20);
    tree.remove(80);
    tree.remove(50);

    cout << "   Active Elements: "; tree.printTree();
    cout << "   Contains 50? " << (tree.contains(50) ? "Yes" : "No") << "\n";

    // The magic! It shouldn't crash, and it should correctly find the new min/max
    cout << "   NEW Min: " << tree.findMin() << " (Expected: 30)\n";
    cout << "   NEW Max: " << tree.findMax() << " (Expected: 70)\n\n";

    // Let's look behind the scenes
    tree.showPhysicalMemory();

    cout << "3. Resurrecting '20'...\n";
    tree.insert(20);
    cout << "   Active Elements: "; tree.printTree();
    cout << "   NEW Min: " << tree.findMin() << " (Expected: 20)\n\n";
    tree.showPhysicalMemory();

    cout << "ALL LAZY DELETION DIAGNOSTICS COMPLETED SAFELY.\n";
    return 0;
}
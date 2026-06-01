/*Swap two adjacent elements by adjusting only the links (and not the data) using
a. singlylinkedlists
b. doublylinkedlists*/

#include <iostream>
#include "../LinkedLists/SinglyLinkedList.h"
#include "../LinkedLists/DoublyLinkedList.h"

using namespace std;

template<typename T>
void swapSinglyAdjacent(typename SinglyLinkedList<T>::Node* beforeP) {
    // Safety Check
    if (beforeP == nullptr || beforeP->next == nullptr || beforeP->next->next == nullptr)
        return;

    typename SinglyLinkedList<T>::Node* p = beforeP->next;
    typename SinglyLinkedList<T>::Node* afterP = p->next;

    p->next = afterP->next;
    afterP->next = p;
    beforeP->next = afterP;
}

template<typename T>
void swapDoublyAdjacent(typename DoublyLinkedList<T>::Node* p) {
    // Safety Check
    if (p == nullptr || p->next == nullptr)
        return;

    typename DoublyLinkedList<T>::Node* afterP = p->next;
    if (p->prev != nullptr) {
        p->prev->next = afterP; // A now points forward to C
    }
    if (afterP->next != nullptr) {
        afterP->next->prev = p; // D now points backward to B
    }
    afterP->prev = p->prev;
    p->next = afterP->next;
    afterP->next = p;
    p->prev = afterP;
}
// ==============================================================================
// HELPER FUNCTION: PRINT LIST
// Added this so we can actually see your flawless logic in action!
// ==============================================================================
template<typename NodeType>
void printSingly(NodeType* curr) {
    while (curr != nullptr) {
        cout << curr->data << (curr->next ? " -> " : "");
        curr = curr->next;
    }
    cout << "\n";
}

template<typename NodeType>
void printDoubly(NodeType* curr) {
    while (curr != nullptr) {
        cout << curr->data << (curr->next ? " <--> " : "");
        curr = curr->next;
    }
    cout << "\n";
}
void runSwapTest() {
    // --------------------------------------------------------------------------
    // SCENARIO A: SINGLY LINKED LIST
    // --------------------------------------------------------------------------
    cout << ">>> SCENARIO A: SINGLY LINKED LIST (DYNAMIC GENERATION) <<<\n";

    typename SinglyLinkedList<int>::Node* singlyHead = new SinglyLinkedList<int>::Node(10);
    typename SinglyLinkedList<int>::Node* singlyCurrent = singlyHead;

    for (int i = 20; i <= 50; i += 10) {
        singlyCurrent->next = new SinglyLinkedList<int>::Node(i);
        singlyCurrent = singlyCurrent->next;
    }

    cout << "Original List                   : ";
    printSingly(singlyHead);

    typename SinglyLinkedList<int>::Node* targetBefore = singlyHead;
    while (targetBefore != nullptr && targetBefore->data != 20) {
        targetBefore = targetBefore->next;
    }

    if (targetBefore != nullptr) {
        cout << "Target acquired! Swapping the nodes exactly after '20' (30 and 40)...\n";
        swapSinglyAdjacent<int>(targetBefore);
    }
    else {
        cout << "Error: Target node not found!\n";
    }

    cout << "Modified List                   : ";
    printSingly(singlyHead);
    cout << "--------------------------------------------------------\n\n";

    // Clean up Singly memory
    singlyCurrent = singlyHead;
    while (singlyCurrent != nullptr) {
        typename SinglyLinkedList<int>::Node* nextNode = singlyCurrent->next;
        delete singlyCurrent;
        singlyCurrent = nextNode;
    }

    // --------------------------------------------------------------------------
    // SCENARIO B: DOUBLY LINKED LIST
    // --------------------------------------------------------------------------
    cout << ">>> SCENARIO B: DOUBLY LINKED LIST (DYNAMIC GENERATION) <<<\n";

    typename DoublyLinkedList<int>::Node* doublyHead = new DoublyLinkedList<int>::Node(10);
    typename DoublyLinkedList<int>::Node* doublyCurrent = doublyHead;

    for (int i = 20; i <= 50; i += 10) {
        typename DoublyLinkedList<int>::Node* newNode = new DoublyLinkedList<int>::Node(i);
        doublyCurrent->next = newNode;
        newNode->prev = doublyCurrent;
        doublyCurrent = newNode;
    }

    cout << "Original List                   : ";
    printDoubly(doublyHead);

    typename DoublyLinkedList<int>::Node* targetP = doublyHead;
    while (targetP != nullptr && targetP->data != 30) {
        targetP = targetP->next;
    }

    if (targetP != nullptr) {
        cout << "Target acquired! Swapping '30' directly with its next neighbor (40)...\n";
        swapDoublyAdjacent<int>(targetP);
    }
    else {
        cout << "Error: Target node not found!\n";
    }

    cout << "Modified List                   : ";
    printDoubly(doublyHead);
    cout << "--------------------------------------------------------\n\n";

    // Clean up Doubly memory
    doublyCurrent = doublyHead;
    while (doublyCurrent != nullptr) {
        typename DoublyLinkedList<int>::Node* nextNode = doublyCurrent->next;
        delete doublyCurrent;
        doublyCurrent = nextNode;
    }
}
int main() {
    cout << "=== POINTER MANIPULATION DIAGNOSTICS ===\n\n";
    runSwapTest();

    return 0;
}
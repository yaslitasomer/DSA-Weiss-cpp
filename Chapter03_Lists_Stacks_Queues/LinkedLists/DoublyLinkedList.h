#ifndef DOUBLY_LINKED_LIST_H
#define DOUBLY_LINKED_LIST_H

#include <iostream>
#include <stdexcept>

using namespace std;

// ==============================================================================
// SINGLY LINKED LIST TEMPLATE CLASS SKELETON
// ==============================================================================
template <typename Object>
class DoublyLinkedList {
private:
    // ---------------------------------------------------------
    // 1. THE NODE STRUCTURE
    // ---------------------------------------------------------
    struct Node {
        Object data;
        Node* next;
        Node* prev;

        // Constructor for easy node creation
        Node(const Object& d = Object{}, Node* n = nullptr, Node* p = nullptr)
            : data{ d }, next{ n }, prev{ p } {
        }
    };

    // ---------------------------------------------------------
    // 2. PRIVATE MEMBERS (The Engine)
    // ---------------------------------------------------------
    Node* head;    // Pointer to the first node
    Node* tail;    // Pointer to the last node (makes adding to the end O(1))
    int theSize;   // Keeps track of how many items are in the list

    // ---------------------------------------------------------
    // HELPER FUNCTION:
    // Returns the actual Node pointer at a specific index.
    // ---------------------------------------------------------
    Node* getNodeAt(int index) const {
        if (index < 0 || index >= theSize) {
            throw std::out_of_range("Index out of bounds!");
        }

        Node* currentNode = nullptr;

        if (index < theSize / 2) {
            currentNode = head;
            for (int i = 0; i < index; i++) {
                currentNode = currentNode->next;
            }
        }
        else {
            currentNode = tail;
            for (int i = theSize - 1; i > index; i--)
            {
                currentNode = currentNode->prev;
            }
        }
        return currentNode;
    }
    template <typename T>
    friend void swapDoublyAdjacent(typename DoublyLinkedList<T>::Node* beforeP);
    friend void runSwapTest();
    template<typename T>
    friend void printDoubly(typename DoublyLinkedList<T>::Node* head);

public:
    // ---------------------------------------------------------
    // 3. CONSTRUCTOR & DESTRUCTOR
    // ---------------------------------------------------------
    DoublyLinkedList() {
        // TODO: Initialize 'head' and 'tail' to nullptr.
        // TODO: Initialize 'theSize' to 0.
        head = nullptr;
        tail = nullptr;
        theSize = 0;
    }

    ~DoublyLinkedList() {
        // TODO: Call makeEmpty() so we don't leak memory when the list is destroyed.
        makeEmpty();
    }

    // ---------------------------------------------------------
    // 4. TEXTBOOK ADT OPERATIONS
    // ---------------------------------------------------------

    void printList() const {
        // TODO: Create a temporary pointer starting at 'head'.
        // TODO: Use a while loop to go through the list until the pointer hits nullptr.
        // TODO: Print the 'data' of each node.
        Node* currentNode = head;
        cout << "List: [";
        while (currentNode != nullptr) {
            cout << currentNode->data;
            if (currentNode->next != nullptr)
                cout << " <--> ";
            currentNode = currentNode->next;
        }
        cout << "]\n";

    }

    void makeEmpty() {
        // TODO: Create a loop that deletes nodes one by one.
        // TODO: Be careful! Save the 'next' pointer BEFORE deleting the current node.
        // TODO: Reset head, tail, and theSize.
        Node* toDelete = head;
        while (toDelete != nullptr) {
            head = head->next;
            delete toDelete;
            toDelete = toDelete->next;
        }
        tail = nullptr;
        theSize = 0;
    }

    int find(const Object& x) const {
        // TODO: Traverse the list starting from 'head'.
        // TODO: Keep a counter (index). If you find 'x', return the index.
        // TODO: If the loop finishes and 'x' is not found, return -1.
        Node* current = head;
        for (int i = 0; i < theSize; i++)
        {
            if (current == nullptr) {
                break;
            }
            if (current->data == x)
                return i;
            current = current->next;
        }

        return -1;
    }

    const Object& findKth(int index) const {
        // TODO: First, check if index is valid (index >= 0 and index < theSize). Throw exception if not.
        // TODO: Traverse the list 'index' amount of times.
        // TODO: Return the data of the node you landed on.
        return getNodeAt(index)->data;
    }

    void insert(const Object& x, int index) {
        // TODO: Check if index is valid.
        // TODO: If index is 0 (insert at front): Create a new node pointing to current 'head', update 'head'.
        // TODO: If index > 0: Find the node at (index - 1). Create a new node pointing to its 'next'. 
        // TODO: Update the 'next' of the (index - 1) node to point to the new node.
        // TODO: If inserted at the very end, remember to update 'tail'!
        // TODO: Increase theSize.
        if (index < 0 || index > theSize) {
            throw std::out_of_range("Invalid insertion index!");
        }

        if (index == 0) {
            Node* newNode = new Node(x, head, nullptr);
            if (head != nullptr)
                head->prev = newNode;
            head = newNode;
            if (theSize == 0) {
                tail = head;
            }
        }

        else if (index == theSize) {
            Node* newNode = new Node(x, nullptr, tail);
            if (tail != nullptr) {
                tail->next = newNode;
            }
            tail = newNode;
        }

        else {
            Node* currentAtPos = getNodeAt(index);
            Node* newNode = new Node(x, currentAtPos, currentAtPos->prev);
            currentAtPos->prev->next = newNode;
            currentAtPos->prev = newNode;
        }
        theSize++;
    }

    void remove(const Object& x) {
        // TODO: If the list is empty, just return.
        // TODO: If 'x' is at the 'head': Create a temp pointer to head, move head to head->next, delete temp.
        // TODO: If 'x' is in the middle: You need to find the node BEFORE 'x'. 
        // TODO: Change the 'next' of the previous node to skip the node containing 'x'.
        // TODO: Delete the node containing 'x'.
        // TODO: If you removed the last item, update 'tail'!
        // TODO: Decrease theSize.
        if (isEmpty())
            return;

        Node* toDelete = head;
        while (toDelete != nullptr && toDelete->data != x)
        {
            toDelete = toDelete->next;
        }

        if (toDelete == nullptr) return;

        if (toDelete->prev != nullptr) {
            toDelete->prev->next = toDelete->next;
        }
        else {
            head = toDelete->next;
        }

        if (toDelete->next != nullptr) {
            toDelete->next->prev = toDelete->prev;
        }
        else {
            tail = toDelete->prev;
        }

        delete toDelete;
        theSize--;

    }

    // ---------------------------------------------------------
    // 5. HELPER METHODS
    // ---------------------------------------------------------
    bool isEmpty() const {
        // TODO: Return true if theSize is 0.
        return theSize == 0;
    }

    int size() const {
        // TODO: Return theSize.
        return theSize;
    }
};

#endif
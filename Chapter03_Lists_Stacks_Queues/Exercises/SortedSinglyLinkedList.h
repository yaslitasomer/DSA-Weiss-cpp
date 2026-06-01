#ifndef SORTED_SINGLY_LINKED_LIST_H
#define SORTED_SINGLY_LINKED_LIST_H

#include <iostream>
#include <stdexcept>

using namespace std;

// ==============================================================================
// SINGLY LINKED LIST TEMPLATE CLASS SKELETON
// ==============================================================================
template <typename Object>
class SortedSinglyLinkedList {
private:
    // ---------------------------------------------------------
    // 1. THE NODE STRUCTURE
    // ---------------------------------------------------------
    struct Node {
        Object data;
        Node* next;

        // Constructor for easy node creation
        Node(const Object& d = Object{}, Node* n = nullptr)
            : data{ d }, next{ n } {
        }
    };

    // ---------------------------------------------------------
    // 2. PRIVATE MEMBERS (The Engine) (UPDATED)
    // ---------------------------------------------------------
    Node* head;    // Pointer to the first node

    // ---------------------------------------------------------
    // HELPER FUNCTION:
    // Returns the actual Node pointer at a specific index.
    // ---------------------------------------------------------
    Node* getNodeAt(int index) const {
        if (index < -1 || index >= size()) {
            throw std::out_of_range("Index out of bounds!");
        }

        if (index == -1) return head;

        Node* currentNode = head->next;
        for (int i = 0; i < index; i++)
        {
            currentNode = currentNode->next;
        }
        return currentNode;
    }

    template <typename T>
    friend void swapSinglyAdjacent(typename SortedSinglyLinkedList<T>::Node* beforeP);
    friend void runSwapTest();
    template<typename T>
    friend void printSingly(typename SortedSinglyLinkedList<T>::Node* head);

public:
    // ---------------------------------------------------------
    // 3. CONSTRUCTOR & DESTRUCTOR
    // ---------------------------------------------------------
    SortedSinglyLinkedList() {
        // TODO: Initialize 'head' and 'tail' to nullptr.
        // TODO: Initialize 'theSize' to 0.
        head = new Node();
    }

    ~SortedSinglyLinkedList() {
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
        Node* currentNode = head->next;
        cout << "List: [";
        while (currentNode != nullptr) {
            cout << currentNode->data;
            if (currentNode->next != nullptr)
                cout << " -> ";
            currentNode = currentNode->next;
        }
        cout << "]\n";

    }

    bool contains(const Object& x) const {
        Node* current = head->next;
        while (current != nullptr) {
            if (x > current->data) {
                return false;
            }
            else if (current->data == x) {
                return true;
            }
            current = current->next;
        }
        return false;
    }

    void addIfAbsent(const Object& x) {
        if (!contains(x)) {
            Node* current = head;

            while (current->next != nullptr && current->next->data < x) {
                current = current->next;
            }

            current->next = new Node(x, current->next);

        }
    }



    void makeEmpty() {
        // TODO: Create a loop that deletes nodes one by one.
        // TODO: Be careful! Save the 'next' pointer BEFORE deleting the current node.
        // TODO: Reset head, tail, and theSize.
        Node* current = head->next;
        while (current != nullptr) {
            Node* toDelete = current;
            current = current->next;
            delete toDelete;
        }
        head->next = nullptr;
    }

    int find(const Object& x) const {
        // TODO: Traverse the list starting from 'head'.
        // TODO: Keep a counter (index). If you find 'x', return the index.
        // TODO: If the loop finishes and 'x' is not found, return -1.
        Node* current = head->next;
        for (int i = 0; i < size(); i++)
        {
            if (current == nullptr) {
                break;
            }
            if (current->data > x)
                return -1;
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

    /*void insert(const Object& x, int index) {
        // TODO: Check if index is valid.
        // TODO: If index is 0 (insert at front): Create a new node pointing to current 'head', update 'head'.
        // TODO: If index > 0: Find the node at (index - 1). Create a new node pointing to its 'next'.
        // TODO: Update the 'next' of the (index - 1) node to point to the new node.
        // TODO: If inserted at the very end, remember to update 'tail'!
        // TODO: Increase theSize.
        if (index < 0 || index > size()) {
            throw std::out_of_range("Invalid insertion index!");
        }


        else {
            Node* prev = getNodeAt(index - 1);
            prev->next = new Node(x, prev->next);
        }
    }
        */

    void remove(const Object& x) {
        // TODO: If the list is empty, just return.
        // TODO: If 'x' is at the 'head': Create a temp pointer to head, move head to head->next, delete temp.
        // TODO: If 'x' is in the middle: You need to find the node BEFORE 'x'. 
        // TODO: Change the 'next' of the previous node to skip the node containing 'x'.
        // TODO: Delete the node containing 'x'.
        // TODO: If you removed the last item, update 'tail'!
        // TODO: Decrease theSize.
        if (size() == 0)
            return;

        Node* currentNode = head;
        while (currentNode->next != nullptr && currentNode->next->data != x)
        {
            currentNode = currentNode->next;
        }

        if (currentNode->next != nullptr) {
            Node* toDelete = currentNode->next;
            currentNode->next = toDelete->next;


            delete toDelete;
        }

    }

    // ---------------------------------------------------------
    // 5. HELPER METHODS
    // ---------------------------------------------------------
    bool isEmpty() const {
        // TODO: Return true if theSize is 0.
        return size() == 0;
    }

    int size() const {
        int count = 0;
        Node* current = head->next;
        while (current != nullptr)
        {
            current = current->next;
            count++;
        }
        return count;
    }
};

#endif
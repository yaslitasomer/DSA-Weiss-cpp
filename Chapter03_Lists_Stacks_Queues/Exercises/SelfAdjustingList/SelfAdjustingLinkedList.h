#include <iostream>
#include <stdexcept>

using namespace std;

// ==============================================================================
// PART B: LINKED LIST IMPLEMENTATION (SelfAdjustingLinkedList)
// ==============================================================================
template <typename Object>
class SelfAdjustingLinkedList {
private:
    struct Node
    {
        Object data;
        Node* next;
        Node(const Object& x = Object{}, Node* n = nullptr) : data{ x }, next{ n } {}
    };

    Node* head;

public:
    SelfAdjustingLinkedList() : head{ nullptr } {}

    ~SelfAdjustingLinkedList() {
        while (head != nullptr) {
            Node* toDelete = head;
            head = head->next;
            delete toDelete;
        }
    }

    // INSERT: Always at the front, O(1) time
    void insert(const Object& x) {
        head = new Node(x, head);
    }

    // FIND: Detach the node and move it to the front
    bool find(const Object& x) {
        if (head == nullptr) return false;

        // Already at the front
        if (head->data == x) return true;

        Node* prev = head;
        Node* curr = head->next;

        while (curr != nullptr) {
            if (curr->data == x) {
                // Detach the node
                prev->next = curr->next;

                // Point its 'next' to the current head
                curr->next = head;

                // Update the head pointer
                head = curr;

                return true;
            }

            prev = curr;
            curr = curr->next;
        }
        return false;
    }

    void printList() const {
        cout << "[ ";
        Node* temp = head;
        while (temp != nullptr) {
            cout << temp->data;
            if (temp->next != nullptr) cout << " -> ";
            temp = temp->next;
        }
        cout << " ]\n";
    }


};
#include <stdexcept>

using namespace std;

// DEQUE (DOUBLE-ENDED QUEUE) ARCHITECTURE
// Implemented via a Doubly Linked List with Dummy nodes
// All operations are O(1) worst-case time
template <typename Object>
class Deque
{
private:
    struct Node
    {
        Object data;
        Node* prev;
        Node* next;

        Node(const Object& x = Object{}, Node* p = nullptr, Node* n = nullptr) : data{ x }, prev{ p }, next{ n } {}
    };

    Node* head;
    Node* tail;
    int theSize;

public:
    Deque() {
        head = new Node();
        tail = new Node();
        head->next = tail;
        tail->prev = head;
        theSize = 0;
    }

    ~Deque() {
        while (!isEmpty()) {
            pop();
        }
        delete head;
        delete tail;
    }

    bool isEmpty() const {
        return theSize == 0;
    }

    int size() const {
        return theSize;
    }

    // Insert item x on the front end of the deque
    void push(const Object& x) {
        Node* newNode = new Node(x, head, head->next);
        head->next->prev = newNode;
        head->next = newNode;
        theSize++;
    }

    // Remove the front item from the deque and return it
    Object pop() {
        if (isEmpty()) throw underflow_error("Underflow: Deque is empty!");

        Node* target = head->next;
        Object retVal = target->data;

        head->next = target->next;
        target->next->prev = head;

        delete target;
        theSize--;

        return retVal;
    }

    // Insert item x on the rear end of the deque
    void inject(const Object& x) {
        Node* newNode = new Node(x, tail->prev, tail);

        tail->prev->next = newNode;
        tail->prev = newNode;
        theSize++;
    }

    // Remove the rear item from the deque and return it
    Object eject() {
        if (isEmpty()) throw underflow_error("Underflow: Deque is empty!");

        Node* target = tail->prev;
        Object retVal = target->data;

        tail->prev = target->prev;
        target->prev->next = tail;

        theSize--;
        return retVal;
    }
};


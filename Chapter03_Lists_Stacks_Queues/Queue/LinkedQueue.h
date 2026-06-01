#ifndef LINKED_QUEUE_H
#define LINKED_QUEUE_H

#include <stdexcept>

template <typename Object>
class LinkedQueue {
private:
    struct Node {
        Object data;
        Node* next;
        Node(const Object& d, Node* n = nullptr) : data{ d }, next{ n } {}
    };

    Node* frontNode;
    Node* backNode;
    int currentSize;

public:
    LinkedQueue() : frontNode{ nullptr }, backNode{ nullptr }, currentSize{ 0 } {}

    ~LinkedQueue() {
        makeEmpty();
    }

    int size() const {
        return currentSize;
    }

    bool empty() const {
        return currentSize == 0;
    }

    void enqueue(const Object& x) {
        Node* newNode = new Node(x);

        if (empty()) {
            frontNode = backNode = newNode;
        }
        else {
            backNode->next = newNode;
            backNode = newNode;
        }
        currentSize++;
    }

    void dequeue() {
        if (empty())
            throw std::underflow_error("Queue is empty!");

        Node* oldFront = frontNode;
        frontNode = frontNode->next;
        delete oldFront;
        currentSize--;

        if (empty()) {
            backNode = nullptr;
        }
    }

    const Object& front() const {
        if (empty())
            throw std::underflow_error("Queue is empty!");
        return frontNode->data;
    }

    void makeEmpty() {
        while (!empty()) {
            dequeue();
        }
    }
};



#endif
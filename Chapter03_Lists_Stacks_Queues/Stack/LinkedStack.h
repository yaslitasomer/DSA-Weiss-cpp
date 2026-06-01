#ifndef LINKED_STACK_H
#define LINKED_STACK_H

#include <stdexcept>

template<typename Object>
class LinkedStack {
private:
    struct Node
    {
        Object data;
        Node* next;
        Node(const Object& d, Node* n = nullptr) : data{ d }, next{ n } {}
    };

    Node* topOfStack;
    int theSize;

public:
    LinkedStack() : topOfStack{ nullptr }, theSize{ 0 } {}

    ~LinkedStack() {
        makeEmpty();
    }

    void push(const Object& x) {
        topOfStack = new Node(x, topOfStack);
        theSize++;
    }

    void pop() {
        if (empty())
            throw std::underflow_error("Stack underflow!");

        Node* oldTop = topOfStack;
        topOfStack = topOfStack->next;
        delete oldTop;
        theSize--;
    }

    const Object& top() const {
        if (empty())
            throw std::underflow_error("Stack is empty!");
        return topOfStack->data;
    }

    void makeEmpty() {
        while (!empty())
            pop();
    }

    bool empty() const {
        return topOfStack == nullptr;
    }

    int size() const {
        return theSize;
    }

};










#endif
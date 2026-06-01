#ifndef ARRAY_STACK_H
#define ARRAY_STACK_H

#include <vector>
#include <stdexcept>

template <typename Object>
class ArrayStack {
private:
    std::vector<Object> theArray;

public:
    ArrayStack() = default;

    void push(const Object& x) {
        theArray.push_back(x);
    }

    void pop() {
        if (empty())
            throw std::underflow_error("Stack underflow: Cannot pop from an empty stack!");
        theArray.pop_back();
    }

    const Object& top() const {
        if (empty())
            throw std::underflow_error("Stack is empty!");
        return theArray.back();
    }

    bool empty() const {
        return theArray.empty();
    }

    int size() const {
        return theArray.size();
    }
};

#endif
#ifndef ARRAY_QUEUE_H
#define ARRAY_QUEUE_H

#include <vector>
#include <stdexcept>

template<typename Object>
class ArrayQueue {
private:
    std::vector<Object> theArray;
    int frontIndex;
    int backIndex;
    int currentSize;
    int capacity;

public:
    ArrayQueue(int initialCapacity = 10) : theArray(initialCapacity), frontIndex{ 0 }, backIndex{ -1 },
        currentSize{ 0 }, capacity{ initialCapacity } {
    }

    int size() const {
        return currentSize;
    }

    bool empty() const {
        return currentSize == 0;
    }

    void enqueue(const Object& x) {
        if (currentSize == capacity) {
            throw std::overflow_error("Queue is full!");
        }

        backIndex = (backIndex + 1) % capacity;
        theArray[backIndex] = x;
        currentSize++;
    }

    void dequeue() {
        if (empty()) {
            throw std::underflow_error("Queue is empty!");
        }

        frontIndex = (frontIndex + 1) % capacity;
        currentSize--;
    }

    const Object& front() const {
        if (empty()) {
            throw std::underflow_error("Queue is empty!");
        }
        return theArray[frontIndex];
    }

    void makeEmpty() {
        currentSize = 0;
        frontIndex = 0;
        backIndex = -1;
    }
};

#endif
#include <iostream>
#include <stdexcept>

using namespace std;

template <typename Object>
class TwoStacks {
private:
    Object* array;
    int capacity;
    int top1;
    int top2;

public:
    explicit TwoStacks(int cap = 10) : capacity{ cap } {
        array = new Object[capacity];
        top1 = -1;
        top2 = capacity;
    }

    ~TwoStacks() {
        delete[] array;
    }

    void push1(const Object& x) {
        if (top1 + 1 == top2) {
            throw overflow_error("Stack Overflow: Array is full!");
        }

        top1++;
        array[top1] = x;
    }

    void pop1() {
        if (isEmpty1()) {
            throw underflow_error("Stack1 is already empty!");
        }
        top1--;
    }

    const Object& peek1() const {
        if (isEmpty1()) {
            throw underflow_error("Stack1 is empty!");
        }
        return array[top1];
    }

    bool isEmpty1() const {
        return top1 == -1;
    }

    void push2(const Object& x) {
        if (top1 + 1 == top2) {
            throw overflow_error("Stack Overflow: Array is full!");
        }

        top2--;
        array[top2] = x;
    }

    void pop2() {
        if (isEmpty2()) {
            throw underflow_error("Stack1 is already empty!");
        }
        top2++;
    }

    const Object& peek2() const {
        if (isEmpty2()) {
            throw underflow_error("Stack1 is empty!");
        }
        return array[top2];
    }

    bool isEmpty2() const {
        return top2 == capacity;
    }
};


#include <iostream>
#include <stdexcept>

using namespace std;

// ==============================================================================
// PART A: ARRAY IMPLEMENTATION (SelfAdjustingArray)
// ==============================================================================
template <typename Object>
class SelfAdjustingArray {
private:
    Object* array;
    int capacity;
    int currentSize;

public:
    explicit SelfAdjustingArray(int cap = 10) : capacity{ cap }, currentSize{ 0 } {
        array = new Object[capacity];
    }

    ~SelfAdjustingArray() {
        delete[] array;
    }

    // INSERT : Always performed at the front, requires O(N) shifting
    void insert(const Object& x) {
        if (currentSize == capacity) {
            throw overflow_error("Error: Array capacity reached!");
        }

        // Shift all existing elements to the right by 1 to make room at the front
        for (int i = currentSize; i > 0; i--) {
            array[i] = array[i - 1];
        }

        array[0] = x;
        currentSize++;
    }

    // FIND: Move accessed element to the front
    bool find(const Object& x) {
        for (int i = 0; i < currentSize; i++) {
            if (array[i] == x) {
                if (i == 0) return true;

                // Backup the accessed element
                Object target = array[i];

                // Shift all the elements before 'i' to the right by 1
                for (int j = i; j > 0; j--) {
                    array[j] = array[j - 1];
                }

                // Set the new front
                array[0] = target;
                return true;
            }
        }
        return false;
    }

    void printList() const {
        cout << "[ ";
        for (int i = 0; i < currentSize; i++) cout << array[i] << " ";
        cout << "]\n";
    }
};
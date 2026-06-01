// Modify the Vector Class to add bounds check for indexing
#include <iostream>
#include <algorithm>
#include <stdexcept>

using namespace std;

template <typename Object>
class UpdatedVector {
public:
    static const int SPARE_CAPACITY = 16;

    explicit UpdatedVector(int initSize = 0) : theSize{ initSize }, theCapacity{ initSize + SPARE_CAPACITY }, mutationCount{ 0 } {
        objects = new Object[theCapacity];
    }

    UpdatedVector(const UpdatedVector& rhs) : theSize{ rhs.theSize }, theCapacity{ rhs.theCapacity }, objects{ nullptr } {
        objects = new Object[theCapacity];
        for (int i = 0; i < theSize; i++)
        {
            objects[i] = rhs.objects[i];
        }
    }

    UpdatedVector& operator=(const UpdatedVector& rhs) {
        UpdatedVector copy = rhs;
        std::swap(*this, copy);
        return *this;
    }

    ~UpdatedVector() {
        delete[] objects;
    }

    // THE SAFE ITERATOR CLASS
    class iterator {
    private:
        Object* current;
        const UpdatedVector<Object>* theVector; // pointer to the parent vector
        int expectedMutationCount;

        // Private constructor
        iterator(Object* p, const UpdatedVector<Object>* vec) : current{ p }, theVector{ vec }, expectedMutationCount{ vec->mutationCount } {}
        friend class UpdatedVector<Object>;

        // Security Cam
        void assertIsValid() const {
            if (theVector == nullptr || theVector->mutationCount != expectedMutationCount) {
                throw std::logic_error("STALE ITERATOR EXCEPTION: The Vector was modified while iterating!");
            }
        }
    public:
        iterator() : current{ nullptr }, theVector{ nullptr }, expectedMutationCount{ 0 } {}

        // Overloaded operators
        Object& operator*() {
            assertIsValid();
            return *current;
        }

        iterator& operator++() {
            assertIsValid();
            current++;
            return *this;
        }

        iterator& operator++(int) {
            assertIsValid();
            iterator old = *this;
            ++(*this);
            return old;
        }

        bool operator==(const iterator& rhs) const {
            return current == rhs.current;
        }

        bool operator!=(const iterator& rhs) const {
            return current != rhs.current;
        }
    };


    UpdatedVector(UpdatedVector&& rhs) : theSize{ rhs.theSize }, theCapacity{ rhs.theCapacity }, objects{ rhs.objects } {
        rhs.objects = nullptr;
        rhs.theSize = 0;
        rhs.theCapacity = 0;
    }

    UpdatedVector& operator=(UpdatedVector&& rhs) {
        std::swap(theSize, rhs.theSize);
        std::swap(theCapacity, rhs.theCapacity);
        std::swap(objects, rhs.objects);
        return *this;
    }

    void resize(int newSize) {
        if (newSize > theCapacity) {
            reserve(newSize * 2);
        }
        theSize = newSize;
    }

    void reserve(int newCapacity) {
        if (newCapacity < theSize)
            return;

        Object* newArray = new Object[newCapacity];
        for (int i = 0; i < theSize; i++)
        {
            newArray[i] = std::move(objects[i]);
        }

        theCapacity = newCapacity;
        std::swap(objects, newArray);
        delete[] newArray;

        mutationCount++;
    }

    Object& operator[](int index) {
        if (index < 0 || index >= theSize) {
            throw out_of_range("Vector index out of bounds! (Non-Const Access)");
        }
        return objects[index];
    }

    const Object& operator[](int index) const {
        if (index < 0 || index >= theSize) {
            throw out_of_range("Vector index out of bounds! (Const Access)");
        }
        return objects[index];
    }

    bool empty() const {
        return size() == 0;
    }

    int size() const {
        return theSize;
    }

    int capacity() const {
        return theCapacity;
    }

    void push_back(const Object& x) {
        if (theSize == theCapacity) {
            reserve(2 * theCapacity + 1);
        }
        objects[theSize++] = x;
        mutationCount++;
    }

    void push_back(Object&& x) {
        if (theSize == theCapacity) {
            reserve(2 * theCapacity + 1);
        }
        objects[theSize++] = std::move(x);
        mutationCount++;
    }

    void pop_back() {
        theSize--;
        mutationCount++;
    }

    const Object& back() const {
        return objects[theSize - 1];
    }

    //typedef Object* iterator;
    //typedef const Object* const_iterator;

    iterator begin() {
        return iterator(&objects[0], this);
    }



    iterator end() {
        return iterator(&objects[size()], this);
    }


    // UPDATE
    iterator insert(iterator itr, const Object& x) {
        int offset = itr.current - objects;
        if (theSize == theCapacity) {
            // Save the relative distance (offset) of the iterator before the move


            reserve(2 * theCapacity + 1); // destroys the old memory array
            itr = iterator(&objects[offset], this);
        }

        for (Object* p = &objects[theSize]; p != &objects[offset]; --p) {
            *p = *(p - 1);
        }

        objects[offset] = x;
        theSize++;
        mutationCount++; // DON'T FORGET! We modified the vector.

        return iterator(&objects[offset], this);
    }

    iterator erase(iterator itr) {
        int offset = itr.current - objects;

        for (Object* p = &objects[offset]; p != &objects[theSize - 1]; ++p) {
            *p = *(p + 1);
        }

        theSize--;
        mutationCount++;

        return iterator(&objects[offset], this);
    }

private:
    int theSize;
    int theCapacity;
    Object* objects;

    // THE VERSION CONTROL SYSTEM
    int mutationCount;
};
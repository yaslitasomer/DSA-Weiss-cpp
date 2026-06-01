#include <iostream>
using namespace std;

/*Design a class template, Collection, that stores a collection of Objects (in an array),
along with the current size of the collection. Provide public functions isEmpty,
makeEmpty, insert, remove,andcontains. contains(x) returns true if and only if an
Object that is equal to x is present in the collection.
*/

template <typename Object>
class Collection {
public:
    explicit Collection(int initialCap = 10) : currentSize{ 0 }, capacity{ initialCap } {
        arr = new Object[capacity];
    }

    // Destructor
    ~Collection() {
        delete[] arr;
    }

    // Copy Constructor
    Collection(const Collection& rhs) : currentSize{ rhs.currentSize }, capacity{ rhs.capacity } {
        arr = new Object[capacity];
        for (int i = 0; i < currentSize; i++)
        {
            arr[i] = rhs.arr[i];
        }
    }

    // Move Constructor
    Collection(Collection&& rhs) noexcept : arr{ rhs.arr }, currentSize{ rhs.currentSize }, capacity{ rhs.capacity } {
        rhs.arr = nullptr;
        rhs.capacity = 0;
        rhs.currentSize = 0;
    }

    // Copy Assignment
    Collection& operator=(const Collection& rhs) {
        if (this != &rhs) {
            Object* copyArr = new Object[rhs.capacity];
            for (int i = 0; i < rhs.currentSize; i++)
            {
                copyArr[i] = rhs.arr[i];
            }
            delete[] arr;
            arr = copyArr;
            copyArr = nullptr;
            currentSize = rhs.currentSize;
            capacity = rhs.capacity;
        }
        return *this;
    }

    // Move Assignment
    Collection& operator=(Collection&& rhs) noexcept {
        if (this != &rhs) {
            swap(this->arr, rhs.arr);
            swap(this->currentSize, rhs.currentSize);
            swap(this->capacity, rhs.capacity);
        }
        return *this;
    }

    bool isEmpty() const {
        return currentSize == 0;
    }
    void makeEmpty() {
        delete[] arr;
        currentSize = 0;
        capacity = 10;
        arr = new Object[capacity];
    }

    void insert(const Object& obj) {
        if (currentSize == capacity)
            resize();

        arr[currentSize] = obj;
        currentSize++;
    }

    bool contains(const Object& obj) const {
        for (int i = 0; i < currentSize; i++)
        {
            if (arr[i] == obj)
                return true;
        }
        return false;

    }

    void remove(const Object& obj) {
        for (int i = 0; i < currentSize; i++)
        {
            if (arr[i] == obj) {
                //Shift the rest
                for (int j = i; j < currentSize - 1; j++)
                {
                    arr[j] = move(arr[j + 1]);
                }
                currentSize--;
                return;
            }

        }
    }

    // HELPER FUNCTION
    void printState() const {
        cout << "Collection (Size: " << currentSize << "/" << capacity << "): [";
        for (int i = 0; i < currentSize; i++)
        {
            cout << arr[i] << (i < currentSize - 1 ? ", " : "");
        }
        cout << "]\n";
    }


private:
    int currentSize;
    int capacity;
    Object* arr;

    void resize() {
        int newCapacity = capacity * 2;
        Object* newArr = new Object[newCapacity];

        for (int i = 0; i < capacity; i++)
        {
            newArr[i] = move(arr[i]);
        }

        delete[] arr;
        capacity = newCapacity;
        arr = newArr;
        newArr = nullptr;

    }
};

int main() {
    cout << "--- Testing Template Collection Class ---\n\n";

    // Creating a collection of strings
    Collection<string> names;

    names.insert("Alice");
    names.insert("Bob");
    names.insert("Charlie");
    names.printState();

    cout << "Contains 'Bob'? " << (names.contains("Bob") ? "Yes" : "No") << "\n";

    cout << "\nRemoving 'Bob'...\n";
    names.remove("Bob");
    names.printState();

    cout << "Contains 'Bob'? " << (names.contains("Bob") ? "Yes" : "No") << "\n";

    cout << "\nMaking collection empty...\n";
    names.makeEmpty();
    cout << "Is empty? " << (names.isEmpty() ? "Yes" : "No") << "\n";
    names.printState();

    return 0;
}
#include <iostream>
using namespace std;

/*Design a class template, OrderedCollection, that stores a OrderedCollection of Comparables
(in an array), along with the current size of the OrderedCollection. Provide public functions
isEmpty, makeEmpty, insert, remove, findMin,andfindMax. findMin and findMax return
references to the smallest and largest, respectively, Comparable in the OrderedCollection.
Explain what can be done if these operations are performed on an empty OrderedCollection.
*/

template <typename Comparable>
class OrderedCollection {
public:
    explicit OrderedCollection(int initialCap = 10) : currentSize{ 0 }, capacity{ initialCap } {
        arr = new Comparable[capacity];
    }

    // Destructor
    ~OrderedCollection() {
        delete[] arr;
    }

    // Copy Constructor
    OrderedCollection(const OrderedCollection& rhs) : currentSize{ rhs.currentSize }, capacity{ rhs.capacity } {
        arr = new Comparable[capacity];
        for (int i = 0; i < currentSize; i++)
        {
            arr[i] = rhs.arr[i];
        }
    }

    // Move Constructor
    OrderedCollection(OrderedCollection&& rhs) noexcept : arr{ rhs.arr }, currentSize{ rhs.currentSize }, capacity{ rhs.capacity } {
        rhs.arr = nullptr;
        rhs.capacity = 0;
        rhs.currentSize = 0;
    }

    // Copy Assignment
    OrderedCollection& operator=(const OrderedCollection& rhs) {
        if (this != &rhs) {
            Comparable* copyArr = new Comparable[rhs.capacity];
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
    OrderedCollection& operator=(OrderedCollection&& rhs) noexcept {
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
        arr = new Comparable[capacity];
    }

    void insert(const Comparable& c) {
        if (currentSize == capacity)
            resize();

        int i = currentSize - 1;

        while (i >= 0 && arr[i] > c) {
            arr[i + 1] = move(arr[i]);
            i--;
        }

        arr[i + 1] = c;
        currentSize++;

    }

    bool contains(const Comparable& c) const {
        for (int i = 0; i < currentSize; i++)
        {
            if (arr[i] == c)
                return true;
        }
        return false;

    }

    void remove(const Comparable& c) {
        for (int i = 0; i < currentSize; i++)
        {
            if (arr[i] == c) {
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
        cout << "OrderedCollection (Size: " << currentSize << "/" << capacity << "): [";
        for (int i = 0; i < currentSize; i++)
        {
            cout << arr[i] << (i < currentSize - 1 ? ", " : "");
        }
        cout << "]\n";
    }

    const Comparable& findMin() const {
        if (isEmpty())
            throw underflow_error("Collection is empty...");
        return arr[0];
    }

    const Comparable& findMax() const {
        if (isEmpty())
            throw underflow_error("Collection is empty...");
        return arr[currentSize - 1];
    }


private:
    int currentSize;
    int capacity;
    Comparable* arr;

    void resize() {
        int newCapacity = capacity * 2;
        Comparable* newArr = new Comparable[newCapacity];

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
    cout << "--- Testing OrderedCollection ---\n\n";

    OrderedCollection<int> numbers;

    // Inserting elements in random order
    cout << "Inserting 50, 10, 40, 20, 30...\n";
    numbers.insert(50);
    numbers.insert(10);
    numbers.insert(40);
    numbers.insert(20);
    numbers.insert(30);

    // It will automatically sort them!
    numbers.printState();

    cout << "\nMinimum element: " << numbers.findMin() << "\n";
    cout << "Maximum element: " << numbers.findMax() << "\n";

    // Testing remove()
    cout << "\nTesting removing '30' from the collection...\n";
    numbers.remove(30);
    numbers.printState();

    // Testing the exception handling on an empty collection
    cout << "\nTesting empty collection safety...\n";
    numbers.makeEmpty();

    try {
        cout << numbers.findMin() << "\n"; // This will trigger the throw
    }
    catch (const underflow_error& e) {
        cerr << "Caught Exception: " << e.what() << "\n";
    }

    return 0;
}
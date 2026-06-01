#include <iostream>
#include <utility> // Required for std::swap

using namespace std;

class IntCell {
public:

    // Constructor
    explicit IntCell(int initialVal = 0) {
        storedValue = new int{ initialVal };
        cout << "Constructor created cell with value: " << *storedValue << endl;
    }

    // Destructor
    ~IntCell() {
        if (storedValue != nullptr) {
            cout << "Destructor freeing memory with value: " << *storedValue << endl;
            delete storedValue;
        }
    }

    // Copy Constructor
    IntCell(const IntCell& rhs) {
        cout << "Copy Constructor called." << endl;
        storedValue = new int{ *rhs.storedValue }; // DEEP COPY
    }

    // Move Constructor
    IntCell(IntCell&& rhs) noexcept : storedValue{ rhs.storedValue } {
        cout << "Move Constructor called (Stole the pointer)." << endl;
        rhs.storedValue = nullptr;
    }

    // Copy Assignment Operator
    IntCell& operator=(const IntCell& rhs) {
        cout << "Copy Assignment called.\n";

        if (this != &rhs) {
            *storedValue = *rhs.storedValue;
        }
        return *this;
    }

    // Move Assignment Operator
    IntCell& operator=(IntCell&& rhs) noexcept {
        cout << "Move Assignment operator called.\n";
        std::swap(storedValue, rhs.storedValue);
        return *this;
    }

    int read() const { return *storedValue; }
    void write(int x) { *storedValue = x; }

private:
    int* storedValue;
};

int main() {
    cout << "--- Creating a ---\n";
    IntCell a{ 10 };

    cout << "\n--- Creating b using Copy Constructor ---\n";
    IntCell b = a;

    cout << "\n--- Creating c using Move Constructor ---\n";
    IntCell c = std::move(a);

    cout << "\n--- Assigning d using Move Assignment ---\n";
    IntCell d;
    d = std::move(b);

    cout << "--- End of program: ---\n";
    return 0;

}
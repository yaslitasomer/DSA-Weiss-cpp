#include <iostream>
#include <vector>

using namespace std;

// ==============================================================================
// DOUBLE HASHING ALGORITHM
// Resolves collisions using a secondary hash function: f(i) = i * hash2(x)
// This strictly prevents both primary and secondary clustering.
// ==============================================================================
class DoubleHashTable {
public:
    enum EntryType { ACTIVE, EMPTY, DELETED };

private:
    struct HashEntry {
        int element;
        EntryType info;

        HashEntry(int e = 0, EntryType i = EMPTY)
            : element{ e }, info{ i } {
        }
    };

    vector<HashEntry> array;
    int currentSize;
    int R; // A prime number smaller than the table size, used for Hash2

    // Helper functions for prime numbers
    bool isPrime(int n) const {
        if (n == 2 || n == 3) return true;
        if (n <= 1 || n % 2 == 0) return false;
        for (int i = 3; i * i <= n; i += 2) {
            if (n % i == 0) return false;
        }
        return true;
    }

    int nextPrime(int n) const {
        if (n % 2 == 0) n++;
        while (!isPrime(n)) n += 2;
        return n;
    }

    // ---------------------------------------------------------
    // HASH 1: The Primary Hash Function
    // ---------------------------------------------------------
    size_t hash1(int key) const {
        return key % array.size();
    }

    // ---------------------------------------------------------
    // HASH 2: The Step-Size Hash Function
    // Formula: R - (key % R)
    // CRITICAL: This must NEVER evaluate to 0!
    // ---------------------------------------------------------
    size_t hash2(int key) const {
        return R - (key % R);
    }

    // ---------------------------------------------------------
    // THE DOUBLE HASHING RESOLUTION ENGINE
    // ---------------------------------------------------------
    int findPos(int x) const {
        int currentPos = hash1(x);
        int stepSize = hash2(x); // Calculate the unique jump size for this element

        // Probe until an EMPTY cell or the exact element is found
        while (array[currentPos].info != EMPTY && array[currentPos].element != x) {
            currentPos += stepSize; // Jump by the element's unique step size

            if (currentPos >= array.size()) {
                currentPos %= array.size(); // Wrap around safely
            }
        }
        return currentPos;
    }

    bool isActive(int currentPos) const {
        return array[currentPos].info == ACTIVE;
    }

public:
    // Constructor
    explicit DoubleHashTable(int size = 10) : currentSize{ 0 } {
        // Book uses size 10 for demonstration (though prime is better in reality)
        array.resize(size);
        R = 7; // R must be a prime smaller than TableSize
        makeEmpty();
    }

    void makeEmpty() {
        currentSize = 0;
        for (auto& entry : array) {
            entry.info = EMPTY;
        }
    }

    bool insert(int x) {
        int currentPos = findPos(x);

        if (isActive(currentPos)) {
            return false; // Duplicate
        }

        array[currentPos].element = x;
        array[currentPos].info = ACTIVE;
        currentSize++;
        return true;
    }

    void displayTable() const {
        cout << "--- DOUBLE HASHING TABLE (Size: " << array.size() << ", R: " << R << ") ---\n";
        for (size_t i = 0; i < array.size(); ++i) {
            cout << "[" << i << "] : ";
            if (array[i].info == EMPTY) cout << "---";
            else if (array[i].info == DELETED) cout << "<DELETED>";
            else cout << array[i].element;
            cout << "\n";
        }
        cout << "--------------------------------------------------\n";
    }
};


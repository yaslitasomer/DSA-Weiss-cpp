#include <iostream>
#include <vector>
#include <string>

using namespace std;

// ==============================================================================
// 1. THE HASH FUNCTION (Horner's Rule)
// ==============================================================================
class StringHash {
public:
    size_t operator()(const string& key) const {
        size_t hashVal = 0;
        for (char ch : key) {
            hashVal = 37 * hashVal + ch;
        }
        return hashVal;
    }
};

// ==============================================================================
// 2. QUADRATIC PROBING HASH TABLE
// Resolves collisions using f(i) = i^2 probing sequence.
// Guarantees an empty slot if Load Factor (Lambda) < 0.5 and TableSize is Prime.
// ==============================================================================
template<typename HashedObj, typename HashFamily = StringHash>
class QuadraticHashTable {
public:
    // Represents the Lazy Deletion states of a cell
    enum EntryType { ACTIVE, EMPTY, DELETED };

private:
    struct HashEntry
    {
        HashedObj element;
        EntryType info;

        HashEntry(const HashedObj& e = HashedObj{}, EntryType i = EMPTY) : element{ e }, info{ i } {}
    };

    vector<HashEntry> array;
    int currentSize; // Number of active elements
    int occupiedCells; // Number of active + deleted elements

    // Prime number utilities
    bool isPrime(int n) const {
        if (n == 2 || n == 3) return true;
        if (n == 1 || n % 2 == 0) return false;
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

    size_t myhash(const HashedObj& x) const {
        static HashFamily hf;
        return hf(x) % array.size();
    }

    // ---------------------------------------------------------
    // THE QUADRATIC RESOLUTION ENGINE (findPos)
    // Avoids expensive multiplication (i * i) by using the formula:
    // f(i) = f(i-1) + 2i - 1
    // ---------------------------------------------------------
    int findPos(const HashedObj& x) const {
        int offSet = 1;
        int currentPos = myhash(x);

        // Continue probing until we find an EMPTY cell or the exact element
        while (array[currentPos].info != EMPTY && array[currentPos].element != x) {
            currentPos += offSet; // Compute next probe
            offSet += 2;

            // Wrap around the array securely without using the expensive modulo operator
            if (currentPos >= array.size()) {
                currentPos -= array.size();
            }
        }
        return currentPos;
    }

    bool isActive(int currentPos) const {
        return array[currentPos].info == ACTIVE;
    }

    // ---------------------------------------------------------
    // THE REHASH ENGINE
    // Triggers when the table is more than half full (Lambda > 0.5)
    // ---------------------------------------------------------
    void rehash() {
        vector<HashEntry> oldArray = array;

        // Create new double-sized, empty table
        array.resize(nextPrime(2 * oldArray.size()));
        for (auto& entry : array) {
            entry.info = EMPTY;
        }

        // Reset counters and copy only ACTIVE elements over
        currentSize = 0;
        occupiedCells = 0;
        for (auto& entry : oldArray) {
            if (entry.info == ACTIVE) {
                insert(entry.element);
            }
        }
    }

public:
    explicit QuadraticHashTable(int size = 11) : currentSize{ 0 }, occupiedCells{ 0 } {
        array.resize(nextPrime(size));
        makeEmpty();
    }

    void makeEmpty() {
        currentSize = 0;
        occupiedCells = 0;
        for (auto& entry : array) {
            entry.info = EMPTY;
        }
    }

    bool contains(const HashedObj& x) const {
        return isActive(findPos(x));
    }

    // ---------------------------------------------------------
    // INSERTION (O(1) Average Time)
    // ---------------------------------------------------------
    bool insert(const HashedObj& x) {
        int currentPos = findPos(x);

        // If it's already in the table and ACTIVE, do nothing
        if (isActive(currentPos)) {
            return false;
        }

        // Otherwise, insert it!
        array[currentPos].element = x;
        array[currentPos].info = ACTIVE;
        currentSize++;
        occupiedCells++;

        // Rule of Quadratic Probing: Table must NEVER be more than 50% full!
        if (occupiedCells > array.size() / 2) {
            rehash();
        }

        return true;
    }

    // ---------------------------------------------------------
    // LAZY DELETION (O(1) Average Time)
    // ---------------------------------------------------------
    bool remove(const HashedObj& x) {
        int currentPos = findPos(x);

        if (!isActive(currentPos)) {
            return false; // Item not found or already deleted
        }

        // Soft Delete: Mark it as DELETED, but keep it in memory
        array[currentPos].info = DELETED;
        currentSize--;
        // Note: We DO NOT decrement occupiedCells because a DELETED cell 
        // still affects the probe sequence and takes up physical space.

        return true;
    }

    // Visualizer to trace the probing and lazy deletion
    void displayTable() const {
        cout << "--- QUADRATIC HASH TABLE (Size: " << array.size()
            << ", Active: " << currentSize << ", Occupied: " << occupiedCells << ") ---\n";

        for (size_t i = 0; i < array.size(); ++i) {
            cout << "[" << i << "] : ";
            if (array[i].info == EMPTY) cout << "---";
            else if (array[i].info == DELETED) cout << "<DELETED> (" << array[i].element << ")";
            else cout << array[i].element;
            cout << "\n";
        }
        cout << "-------------------------------------------------------\n";
    }
};
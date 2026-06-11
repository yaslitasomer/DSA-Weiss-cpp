#include <list>
#include <vector>
#include <string>
#include <iostream>
#include <algorithm>

using namespace std;
// ==============================================================================
// 1. THE HASH FUNCTION (Horner's Rule)
// From Textbook Figure 5.4: Computes a polynomial function (base 37) to 
// evenly distribute strings across the hash table.
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
// 2. SEPARATE CHAINING HASH TABLE
// Resolves collisions by maintaining a Linked List (std::list) at each index.
// ==============================================================================
template<typename HashedObj, typename HashFamily = StringHash>
class HashTable {
private:
    vector<list<HashedObj>> theLists; // The array of linked lists
    int currentSize;                  // Number of elements in the table

    // Helper to keep table size prime for better distribution
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

    // The internal hash router
    size_t myHash(const HashedObj& x) const {
        static HashFamily hf;
        return hf(x) % theLists.size();
    }

    // ---------------------------------------------------------
    // THE REHASH ENGINE (Dynamic Resizing)
    // When the Load Factor (Lambda) > 1.0, we double the table size
    // and re-distribute all existing elements to maintain O(1) speed.
    // ---------------------------------------------------------
    void rehash() {
        vector<list<HashedObj>> oldLists = theLists;

        // Create new double-sized, empty table
        theLists.resize(nextPrime(2 * theLists.size()));
        for (auto& thisList : theLists)
            thisList.clear();

        // Copy table
        currentSize = 0;
        for (auto& thisList : oldLists) {
            for (auto& x : thisList) {
                insert(x);
            }
        }
    }

public:
    explicit HashTable(int size = 11) : currentSize{ 0 } {
        theLists.resize(size);
    }

    void makeEmpty() {
        for (auto& thisList : theLists)
            thisList.clear();
        currentSize = 0;
    }

    bool contains(const HashedObj& x) const {
        const auto& whichList = theLists[myHash(x)];
        return find(begin(whichList), end(whichList), x) != end(whichList);
    }

    // ---------------------------------------------------------
    // INSERTION (O(1) Average Time)
    // ---------------------------------------------------------
    bool insert(const HashedObj& x) {
        auto& whichList = theLists[myHash(x)];

        // Prevent duplicates
        if (find(begin(whichList), end(whichList), x) != end(whichList)) {
            return false;
        }

        whichList.push_back(x);

        // Rehash if load factor exceeds 1.0
        if (++currentSize > theLists.size()) {
            rehash();
        }

        return true;
    }

    // ---------------------------------------------------------
    // DELETION (O(1) Average Time)
    // ---------------------------------------------------------
    bool remove(const HashedObj& x) {
        auto& whichList = theLists[myHash(x)];
        auto itr = find(begin(whichList), end(whichList), x);

        if (itr == end(whichList))
            return false;

        whichList.erase(itr);
        --currentSize;
        return true;
    }

    // Visualizer to see the actual chains (Linked Lists)
    void displayTable() const {
        cout << "--- HASH TABLE ARCHITECTURE (Load Factor: "
            << (double)currentSize / theLists.size() << ") ---\n";

        for (size_t i = 0; i < theLists.size(); ++i) {
            cout << "[" << i << "] : ";
            if (theLists[i].empty()) {
                cout << "(empty)";
            }
            else {
                for (const auto& item : theLists[i]) {
                    cout << item << " -> ";
                }
                cout << "NULL";
            }
            cout << "\n";
        }
        cout << "------------------------------------------------------\n";
    }
};

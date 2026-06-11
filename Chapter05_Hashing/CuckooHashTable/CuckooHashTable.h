#include <iostream>
#include <vector>
#include <string>
#include <random>
#include <algorithm>

using namespace std;

// ==============================================================================
// 1. THE HASH FAMILY ENGINE
// Generates a specified number of independent hash functions for strings
// by using randomly generated multipliers.
// ==============================================================================
class StringHashFamily {
private:
    vector<int> MULTIPLIERS;
    mt19937 rng; // Modern C++ Mersenne Twister RNG

public:
    // Constructor initializes 'count' number of hash functions
    StringHashFamily(int count = 2) {
        MULTIPLIERS.resize(count);
        random_device rd;
        rng.seed(rd());
        generateNewFunctions();
    }

    int getNumberOfFunctions() const {
        return MULTIPLIERS.size();
    }

    // Generates a completely new set of random multipliers for the hash functions
    void generateNewFunctions() {
        uniform_int_distribution<int> dist(1, 999999);
        for (auto& mult : MULTIPLIERS) {
            mult = dist(rng);
        }
    }

    // Evaluates the string using the specified hash function index ('which')
    size_t hash(const string& x, int which) const {
        const int multiplier = MULTIPLIERS[which];
        size_t hashVal = 0;

        for (char ch : x) {
            hashVal = multiplier * hashVal + ch;
        }
        return hashVal;
    }
};

// ==============================================================================
// 2. CUCKOO HASH TABLE
// Guarantees Worst-Case O(1) Lookups by ensuring every element is exactly at 
// one of its 'numHashFunctions' possible locations. Uses eviction (nest-kicking).
// ==============================================================================
template<typename AnyType, typename HashFamily>
class CuckooHashTable {
private:
    struct HashEntry {
        AnyType element;
        bool isActive;

        HashEntry(const AnyType& e = AnyType{}, bool a = false)
            : element{ e }, isActive{ a } {
        }
    };

    static constexpr double MAX_LOAD = 0.40;     // Table expands if 40% full
    static constexpr int ALLOWED_REHASHES = 5;   // Max rehashes before forced expansion
    static constexpr int COUNT_LIMIT = 100;      // Max evictions before declaring a "Cycle"

    vector<HashEntry> array;
    int currentSize;
    int numHashFunctions;
    int rehashes;
    HashFamily hashFunctions;
    mt19937 rng; // Random generator for eviction choices

    // Prime number utilities
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

    // Computes the hash code for x using the specified hash function index
    size_t myhash(const AnyType& x, int which) const {
        return hashFunctions.hash(x, which) % array.size();
    }

    bool isActive(int currentPos) const {
        return currentPos >= 0 && currentPos < array.size() && array[currentPos].isActive;
    }

    // Searches all valid hash locations. Returns index if found, -1 otherwise.
    int findPos(const AnyType& x) const {
        for (int i = 0; i < numHashFunctions; ++i) {
            int pos = myhash(x, i);
            if (isActive(pos) && array[pos].element == x) {
                return pos;
            }
        }
        return -1;
    }

    // ---------------------------------------------------------
    // REHASHING & EXPANSION ENGINES
    // ---------------------------------------------------------
    void expand() {
        cout << "   [SYSTEM] Max load or rehash limit reached. Expanding table...\n";
        rehash(static_cast<int>(array.size() / MAX_LOAD));
    }

    void rehash() {
        cout << "   [SYSTEM] Cycle detected! Generating new hash functions...\n";
        hashFunctions.generateNewFunctions();
        rehash(array.size());
    }

    void rehash(int newSize) {
        vector<HashEntry> oldArray = array;

        array.resize(nextPrime(newSize));
        for (auto& entry : array) {
            entry.isActive = false;
        }

        currentSize = 0;
        for (auto& entry : oldArray) {
            if (entry.isActive) {
                insert(entry.element);
            }
        }
    }

    // ---------------------------------------------------------
    // THE CUCKOO EVICTION ENGINE (The Magic)
    // ---------------------------------------------------------
    bool insertHelper1(const AnyType& xx) {
        AnyType x = xx;

        while (true) {
            int lastPos = -1;
            int pos;

            // Attempt to place 'x' by evicting items up to COUNT_LIMIT times
            for (int count = 0; count < COUNT_LIMIT; ++count) {

                // 1. Try to find an empty valid spot first
                for (int i = 0; i < numHashFunctions; ++i) {
                    pos = myhash(x, i);
                    if (!isActive(pos)) {
                        array[pos] = HashEntry{ x, true };
                        ++currentSize;
                        return true; // Successfully placed!
                    }
                }

                // 2. No empty spots! We must EVICT an existing item.
                int i = 0;
                uniform_int_distribution<int> dist(0, numHashFunctions - 1);
                do {
                    // Pick a random hash function to determine who gets kicked out
                    pos = myhash(x, dist(rng));
                } while (pos == lastPos && i++ < 5); // Try not to re-evict the same item immediately

                lastPos = pos;

                // 3. The Cuckoo Kick: Swap 'x' with the occupant.
                // The occupant now becomes 'x' and must find a new nest in the next iteration!
                std::swap(x, array[pos].element);
            }

            // If we reach here, we hit COUNT_LIMIT. A Cycle is detected!
            if (++rehashes > ALLOWED_REHASHES) {
                expand(); // Make table bigger
                rehashes = 0;
            }
            else {
                rehash(); // Keep same size, but change the hash mathematical formulas
            }
        }
    }

public:
    explicit CuckooHashTable(int size = 11, int numFunctions = 2)
        : numHashFunctions(numFunctions), currentSize{ 0 }, rehashes{ 0 } {
        array.resize(nextPrime(size));
        random_device rd;
        rng.seed(rd());
        makeEmpty();
    }

    void makeEmpty() {
        currentSize = 0;
        for (auto& entry : array) {
            entry.isActive = false;
        }
    }

    bool contains(const AnyType& x) const {
        return findPos(x) != -1;
    }

    bool remove(const AnyType& x) {
        int currentPos = findPos(x);
        if (!isActive(currentPos)) {
            return false;
        }
        array[currentPos].isActive = false;
        --currentSize;
        return true; // No lazy deletion issues here! It's physically gone.
    }

    bool insert(const AnyType& x) {
        if (contains(x)) return false;

        if (currentSize >= array.size() * MAX_LOAD) {
            expand();
        }

        return insertHelper1(x);
    }

    void displayTable() const {
        cout << "--- CUCKOO HASH TABLE (Size: " << array.size() << ") ---\n";
        for (size_t i = 0; i < array.size(); ++i) {
            cout << "[" << i << "] : ";
            if (array[i].isActive) cout << array[i].element;
            else cout << "---";
            cout << "\n";
        }
        cout << "------------------------------------------\n";
    }
};
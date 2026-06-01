/*You are given a list, L, and another list, P, containing integers sorted in ascending
order. The operation printLots(L,P) will print the elements in L that are in positions
specified by P. For instance, if P = 1,3,4,6, the elements in positions 1, 3, 4, and 6
in L are printed. Write the procedure printLots(L,P). You may use only the public
STL container operations. What is the running time of your procedure? 
*/


#include <iostream>
#include <list>
#include <string>

using namespace std;

// ==============================================================================
// EXERCISE: PRINT LOTS (O(N))
// ==============================================================================
template <typename Object>
void printLots(const list<Object>& L, const list<int>& P) {
    auto iterL = L.begin();
    int currentPos = 0;

    cout << "--- Extracting elements based on P... ---\n";

    for (int targetPos : P) {
        while (iterL != L.end() && currentPos < targetPos) {
            iterL++;
            currentPos++;
        }

        if (iterL != L.end()) {
            cout << "[FOUND] Position " << targetPos << " : " << *iterL << endl;
        }
        else {
            cout << "[ERROR] Position " << targetPos << " : OUT OF BOUNDS!\n";
        }
    }

}


int main() {
    cout << "=== EXERCISE: PRINT LOTS DIAGNOSTICS ===\n\n";

    // Create the main list L (e.g., words or letters)
    list<string> L = { "Apple", "Banana", "Cherry", "Date", "Elderberry", "Fig", "Grape" };

    // Create the position list P (Sorted in ascending order)
    // We want the elements at index 1, 3, 4, and 6.
    list<int> P1 = { 1, 3, 4, 6 };
    list<int> P2 = { 1, 3, 4, 10 };


    cout << "List L: [Apple, Banana, Cherry, Date, Elderberry, Fig, Grape]\n";
    cout << "List P1 (Target Indices): [1, 3, 4, 6]\n\n";

    // Execute the algorithm
    printLots(L, P1);
    cout << "\n\nList P1 (Target Indices): [1, 3, 4, 10]\n\n";
    printLots(L, P2);

    cout << "\nStatus: EXECUTION COMPLETE.\n";

    return 0;
}
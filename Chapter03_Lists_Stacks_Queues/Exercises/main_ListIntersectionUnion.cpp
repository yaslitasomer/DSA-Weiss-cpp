#include <iostream>
#include <list>

using namespace std;

template <typename Object>
list<Object> getIntersection(const list<Object>& L1, const list<Object>& L2) {
    list<Object> intersectionList;

    auto itr1 = L1.begin();
    auto itr2 = L2.begin();

    while (itr1 != L1.end() && itr2 != L2.end()) {
        if (*itr1 < *itr2)
            itr1++;
        else if (*itr1 > *itr2)
            itr2++;
        else {
            intersectionList.push_back(*itr1);
            itr1++;
            itr2++;
        }
    }
    return intersectionList;
}

template <typename Object>
list<Object> getUnion(const list<Object>& L1, const list<Object>& L2) {
    list<Object> unionList;

    auto itr1 = L1.begin();
    auto itr2 = L2.begin();

    while (itr1 != L1.end() && itr2 != L2.end()) {
        if (*itr1 < *itr2) {
            unionList.push_back(*itr1);
            itr1++;
        }
        else if (*itr1 > *itr2) {
            unionList.push_back(*itr2);
            itr2++;
        }

        else {
            unionList.push_back(*itr1);
            itr1++;
            itr2++;
        }
    }

    while (itr1 != L1.end()) {
        unionList.push_back(*itr1);
        itr1++;
    }


    while (itr2 != L2.end()) {
        unionList.push_back(*itr2);
        itr2++;
    }
    return unionList;

}

// HELPER FUNCTION
template <typename Object>
void printList(const list<Object>& L, const string& listName) {
    cout << listName << " : [ ";
    for (const auto& item : L) {
        cout << item << " ";
    }
    cout << "]\n";
}

int main() {
    cout << "=== LIST INTERSECTION DIAGNOSTICS (L1 \u2229 L2) ===\n\n";

    // Create two strictly sorted lists
    list<int> L1 = { 10, 20, 30, 40, 50, 60 };
    list<int> L2 = { 15, 20, 25, 30, 55, 60, 70 };

    cout << ">>> SCENARIO A: Finding Common Elements <<<\n";
    printList(L1, "List 1 (L1)");
    printList(L2, "List 2 (L2)");

    // Execute the highly optimized O(N+M) algorithm
    list<int> result1 = getIntersection(L1, L2);

    cout << "\n--------------------------------------------------------\n";
    printList(result1, "Result (L1 \u2229 L2)");
    cout << "--------------------------------------------------------\n\n";

    // Test Union
    list<int> unionResult1 = getUnion(L1, L2);
    printList(unionResult1, "Result (L1 \u222A L2)");

    cout << "--------------------------------------------------------\n\n";

    list<int> L3 = { 10, 20, 30, 40, 50, 60 };
    list<int> L4 = { 0, 15, 25, 55, 70, 90, 100 };

    cout << ">>> SCENARIO B: Finding Common Elements <<<\n";
    printList(L3, "List 3 (L3)");
    printList(L4, "List 4 (L4)");

    // Execute the highly optimized O(N+M) algorithm
    list<int> result2 = getIntersection(L3, L4);

    cout << "\n--------------------------------------------------------\n";
    printList(result2, "Result (L3 \u2229 L4)");
    cout << "--------------------------------------------------------\n\n";

    // Test Union
    list<int> unionResult2 = getUnion(L3, L4);
    printList(unionResult2, "Result (L3 \u222A L4)");

    cout << "--------------------------------------------------------\n\n";

    return 0;
}
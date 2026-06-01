#include <iostream>
#include <vector>
using namespace std;

// Return the max item in array
template <typename Comparable>
const Comparable& findMax(const vector<Comparable>& a) {
    int maxIndex = 0;

    for (int i = 0; i < a.size(); i++)
    {
        if (a[maxIndex] < a[i])
            maxIndex = i;
    }
    return a[maxIndex];
}

int main() {

    vector<int> v1 = { 10, 15, 20 };
    vector<double> v2 = { 10.2, 23.2, 73.2 };
    vector<string> v3 = { "apple", "banana", "coconut" };

    cout << "Max element of v1: " << findMax(v1) << endl;
    cout << "Max element of v2: " << findMax(v2) << endl;
    cout << "Max element of v3: " << findMax(v3) << endl;


}
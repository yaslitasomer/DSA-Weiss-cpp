#include <iostream>
#include <vector>
#include <string>
#include <utility> // Required for std::move and std::swap

using namespace std;

// Helper Function
void printVector(const string& name, const vector<string>& vec) {
    cout << name << " contains: [";
    for (size_t i = 0; i < vec.size(); i++)
    {
        cout << vec[i];

        if (i < vec.size() - 1) {
            cout << ", ";
        }
    }
    cout << "]\n";

}

int main() {
    vector<string> v1 = { "Apple", "Pear", "Banana" };
    vector<string> v2 = { "Strawberry", "Lemon" };

    // Old Way
    cout << "Before the bad way..." << endl;
    printVector("v1", v1);
    printVector("v2", v2);

    vector<string> tmp = v1;
    v1 = v2;
    v2 = tmp;

    cout << "After the bad way..." << endl;
    printVector("v1", v1);
    printVector("v2", v2);

    // New Way
    cout << "Before the good way..." << endl;
    printVector("v1", v1);
    printVector("v2", v2);

    vector<string> tmp2 = std::move(v1);
    v1 = std::move(v2);
    v2 = std::move(tmp2);

    cout << "After the good way..." << endl;
    printVector("v1", v1);
    printVector("v2", v2);

    return 0;
}
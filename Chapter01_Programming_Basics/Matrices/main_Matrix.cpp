#include <iostream>
#include <vector>
using namespace std;

template <typename Object>
class matrix {
public:

    matrix() : array{} {}
    matrix(int rows, int cols) : array(rows) {
        for (auto& thisRow : array) {
            thisRow.resize(cols);
        }
    }

    matrix(vector<vector<Object>> v) : array{ v } {}
    matrix(vector<vector<Object>>&& v) : array{ std::move(v) } {}

    const vector<Object>& operator[](int row) const {
        return array[row];
    }

    vector<Object>& operator[](int row) {
        return array[row];
    }

    int numRows() const {
        return array.size();
    }

    int numCols() const {
        return numRows() ? array[0].size() : 0;
    }

    void resize(int rows, int cols) {
        // Step 1: Resize the outer vector (adjusting the number of rows)
        array.resize(rows);

        // Step 2: Iterate through every row and adjust its column count
        for (auto& thisRow : array) {
            thisRow.resize(cols);
        }
    }

private:
    vector<vector<Object>> array;

};

int main() {
    /*matrix<int> m1(2, 3);
    matrix<string> m2(2, 5);

    cout << "M1 Matrix Properties: Rows: " << m1.numRows() << " Cols: " << m1.numCols() << endl;
    cout << "M2 Matrix Properties: Rows: " << m2.numRows() << " Cols: " << m2.numCols() << endl;
    */
    cout << "--- Testing Matrix Zero-Parameter Constructor and Resize ---\n\n";

    // Testing the newly added Zero-Parameter Constructor
    matrix<int> m0;
    cout << "M0 Initial State : Rows: " << m0.numRows() << ", Cols: " << m0.numCols() << "\n";

    // Testing the newly added resize function
    m0.resize(4, 5);
    cout << "M0 After Resize  : Rows: " << m0.numRows() << ", Cols: " << m0.numCols() << "\n\n";

    // Testing the original constructors
    matrix<int> m1(2, 3);
    matrix<string> m2(2, 5);

    cout << "M1 Matrix Props  : Rows: " << m1.numRows() << ", Cols: " << m1.numCols() << "\n";
    cout << "M2 Matrix Props  : Rows: " << m2.numRows() << ", Cols: " << m2.numCols() << "\n";

    return 0;

}
#include <iostream>
#include "IntCell.h"
using namespace std;

int main() {
    IntCell cell1;
    IntCell cell2(10);
    IntCell cell3(10, 5);

    cout << "Cell1 contents: " << cell1.read() << endl;
    cout << "Cell2 contents: " << cell2.read() << endl;
    cout << "Cell3 contents: " << cell3.read() << endl;

    cell1.write(3);
    cell2.write(5);
    cout << "Cell1 contents: " << cell1.read() << endl;
    cout << "Cell2 contents: " << cell2.read() << endl;
}
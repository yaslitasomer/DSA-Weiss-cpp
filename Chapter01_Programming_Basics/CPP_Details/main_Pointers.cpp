#include "../CPP_Classes/IntCell.h"
#include <iostream>
using namespace std;

int main() {
    IntCell* p;
    p = new IntCell(5);
    p->write(10);
    cout << "Cell contents: " << p->read() << endl;

    delete p;

    // lvalues and rvalues
    string str = "hell";
    string& rstr = str; // another name for str, lvalue reference
    rstr += "o";
    bool cond = (&str == &rstr); // true
    cout << cond << endl;

    // rvalue reference
    string msg = "hell";
    string&& bad1 = "hello";
    string&& bad2 = msg + "0000";
    string&& sub = str.substr(0, 4);
    cout << bad2 << endl;
    return 0;
}
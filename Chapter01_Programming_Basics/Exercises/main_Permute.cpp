/*
Write the routines with the following declarations:
    void permute( const string & str );
    void permute( const string & str, int low, int high );
The first routine is a driver that calls the second and prints all the permutations of
the characters in string str.Ifstr is "abc", then the strings that are output are abc,
acb, bac, bca, cab,andcba. Use recursion for the second routine
*/

#include <iostream>
#include <string>
#include <utility> // Required for std::swap

using namespace std;

void permute(const string& str, int low, int high) {
    // BASE CASE 
    if (low == high) {
        cout << str << endl;
        return;
    }

    for (int i = low; i <= high; i++)
    {
        string currStr = str;

        swap(currStr[low], currStr[i]);
        permute(currStr, low + 1, high);
    }

}

void permute(const string& str) {
    if (str.empty())
        return;

    cout << "--- Permutations for '" << str << "' ---\n";

    permute(str, 0, str.length() - 1);
}

int main() {
    string testWord = "abc";

    permute(testWord);

    return 0;
}

#include <iostream>

using namespace std;

// Write a recursive function that returns the number of 1 in the binary representation 
// of N. Use the fact that this is equal to the number of 1 in the representation of N/2, plus 1, if N is odd.


unsigned int countBinaryOnes(unsigned int n) {
    // Base Case
    if (n == 0)
        return 0;

    return countBinaryOnes(n / 2) + (n % 2);
}


int main() {
    cout << "--- Binary 1s Counter ---\n\n";

    // Test Case 1: Number 13 (Binary: 1101 -> has three 1s)
    unsigned int test1 = 13;
    cout << "Number of 1s in " << test1 << " is: " << countBinaryOnes(test1) << "\n";

    // Test Case 2: Number 12 (Binary: 1100 -> has two 1s)
    unsigned int test2 = 12;
    cout << "Number of 1s in " << test2 << " is: " << countBinaryOnes(test2) << "\n";

    // Test Case 3: Number 255 (Binary: 11111111 -> has eight 1s)
    unsigned int test3 = 255;
    cout << "Number of 1s in " << test3 << " is: " << countBinaryOnes(test3) << "\n";

    cout << "\nAlgorithm finished successfully!\n";
    return 0;
}
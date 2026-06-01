// 1.2 Write a program to solve the word puzzle problem.

#include <iostream>
#include <vector>
#include <string>

using namespace std;

// ==============================================================================
// HELPER FUNCTION: Check if the formed word exists in our dictionary
// ==============================================================================
bool isWordInDictionary(const string& currentWord, const vector<string>& dictionary) {
    // TODO (Optional): You can write a loop here to check if 'currentWord' 
    // is inside the 'dictionary' vector.
    // Return true if found, false otherwise.
    for (auto& word : dictionary) {
        if (word == currentWord) {
            return true;
        }
    }
    return false;
}

// ==============================================================================
// MAIN ALGORITHM: Find and print all words in the grid
// ==============================================================================
void solveWordPuzzle(const vector<vector<char>>& grid, const vector<string>& dictionary) {
    int rows = grid.size();
    int cols = grid[0].size();
    string currentWord = "";

    cout << "Starting the search...\n\n";

    // TODO: Write your algorithm here!
    // 
    // Hint 1: You need nested loops to visit every cell (row, col) in the grid.
    // Hint 2: From each cell, try building a word by moving in 8 different directions.
    // Hint 3: Check if the word you are building exists in the dictionary.
    // Hint 4: If you find a word, print it (e.g., "Found word 'cat' at row 1, col 2")

    // Array for directions
    int dx[] = { -1, -1, -1, 0, 0, 1, 1, 1 };
    int dy[] = { -1, 0, 1, -1, 1, -1, 0, 1 };

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {

            for (int dir = 0; dir < 8; dir++) {
                currentWord = "";
                int r = i; // current row
                int c = j; // current col

                while (r >= 0 && c >= 0 && r < rows && c < cols) {
                    currentWord += grid[r][c];

                    // Check if valid
                    if (isWordInDictionary(currentWord, dictionary)) {
                        cout << "Found word '" << currentWord << "' starting at(" << i << ", " << j << ")\n";
                    }

                    // Move to the next cell
                    r += dx[dir];
                    c += dy[dir];
                }

            }

        }
    }

}

int main() {
    // 1. Setup the Word Search Grid (A simple 4x4 matrix for testing)
    vector<vector<char>> myGrid = {
        {'t', 'h', 'i', 's'},
        {'w', 'a', 't', 's'},
        {'o', 'a', 'h', 'g'},
        {'f', 'g', 'd', 't'}
    };

    // 2. Setup the Dictionary (The words we want to find)
    vector<string> myDictionary = { "this", "two", "fat", "that", "hat" };

    // 3. Call your function!
    solveWordPuzzle(myGrid, myDictionary);

    cout << "\nAlgorithm finished!\n";

    // 1. Setup the HARD Word Search Grid (10x10 matrix)
    vector<vector<char>> hardGrid = {
        {'a', 'l', 'g', 'o', 'r', 'i', 't', 'h', 'm', 'x'},
        {'x', 'x', 'x', 'x', 'x', 'x', 'x', 'x', 'x', 'p'},
        {'x', 'x', 'd', 'e', 'b', 'u', 'g', 'x', 'x', 'o'},
        {'x', 'x', 'x', 'x', 'x', 'x', 'x', 'x', 'x', 'i'},
        {'r', 'o', 't', 'c', 'e', 'v', 'x', 'x', 'x', 'n'}, // 'vector' goes backwards!
        {'x', 'x', 'x', 'x', 'r', 'x', 'x', 'h', 'x', 't'},
        {'x', 'x', 'e', 'd', 'o', 'n', 'x', 't', 'x', 'e'}, // 'node' goes backwards!
        {'h', 'a', 's', 'h', 'x', 'x', 'x', 'a', 'x', 'r'},
        {'x', 'x', 'x', 'x', 'x', 'x', 'x', 'm', 'x', 'x'}, // 'math' goes UP from here!
        {'c', 'l', 'a', 's', 's', 'x', 'x', 'x', 'x', 'x'}
    };

    // 2. Setup the Dictionary 
    vector<string> hardDictionary = {
        "algorithm", // Horizontal forward 
        "class",     // Horizontal forward 
        "hash",      // Horizontal forward 
        "debug",     // Horizontal forward 
        "pointer",   // Vertical down 
        "math",      // Vertical up 
        "vector",    // Horizontal backwards
        "node"       // Horizontal backwards
    };

    // 3. Call your function!
    solveWordPuzzle(hardGrid, hardDictionary);

    cout << "\nAlgorithm finished!\n";
    return 0;
}
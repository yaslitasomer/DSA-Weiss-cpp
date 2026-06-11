#include <iostream>
#include <vector>
#include <string>
#include <map>

using namespace std;

// ==============================================================================
// STL MAP & SET SHOWCASE (Word Ladder / Adjacent Words)
// Demonstrates how to use std::map to turn an O(N^2) problem into O(N log N).
// Algorithm from Section 4.8.4 (Figure 4.73)
// ==============================================================================

// ---------------------------------------------------------
// THE ALGORITHM
// Computes a map in which the keys are words and values are vectors of words
// that differ in only one character from the corresponding key.
// ---------------------------------------------------------
map<string, vector<string>> computeAdjacentWords(const vector<string>& words) {
    map<string, vector<string>> adjWords;
    map<int, vector<string>> wordsByLength;

    // Group the words by their length
    for (const auto& str : words) {
        wordsByLength[str.length()].push_back(str);
    }

    // Work on each length group separately
    for (auto& entry : wordsByLength) {
        const vector<string>& groupWords = entry.second;
        int groupNum = entry.first; // The length of the words in this group

        // Work on each character position in the word
        for (int i = 0; i < groupNum; i++) {

            // Remove one character in specified position, computing representative
            // Words with same representatives are adjacent, populate a map
            map<string, vector<string>> repToWord;

            for (const auto& str : groupWords) {
                string rep = str;
                rep.erase(i, 1); // Remove one character at index i

                // If str="wine" and i=0 -> rep="ine"
                // repToWord["ine"] will hold "wine", "dine", "fine", etc.
                repToWord[rep].push_back(str);
            }

            // Look for map values with more than one string
            for (auto& repEntry : repToWord) {
                const vector<string>& clique = repEntry.second;

                if (clique.size() >= 2) {
                    for (size_t p = 0; p < clique.size(); p++) {
                        for (size_t q = p + 1; q < clique.size(); q++) {
                            adjWords[clique[p]].push_back(clique[q]);
                            adjWords[clique[q]].push_back(clique[p]);
                        }
                    }
                }
            }


        }
    }
    return adjWords;
}

// ---------------------------------------------------------
// PRINTER HELPER
// Prints words that can be changed into at least 'minWords' other words.
// ---------------------------------------------------------
void printHighChangeables(const map<string, vector<string>>& adjacentWords, size_t minWords = 1) {
    bool foundAny = false;
    for (const auto& entry : adjacentWords) {
        const vector<string>& words = entry.second;

        if (words.size() >= minWords) {
            foundAny = true;
            cout << entry.first << " (" << words.size() << " adjacent words):";
            for (const auto& str : words) {
                cout << " " << str;
            }
            cout << "\n";
        }
    }
    if (!foundAny) {
        cout << "  No words found with at least " << minWords << " adjacent words.\n";
    }
}

// ==============================================================================
// DIAGNOSTICS ENGINE
// ==============================================================================
int main() {
    cout << "=== STL MAP ADVANCED CAPABILITIES DIAGNOSTICS ===\n\n";

    // A small sample dictionary to demonstrate the algorithm
    vector<string> dictionary = {
        "wine", "dine", "fine", "line", "mine", "nine", "pine", "vine", // *ine words
        "wide", "wife", "wipe", "wire",                                 // wi*e words
        "wind", "wing", "wink", "wins",                                 // win* words
        "boot", "foot", "hoot", "loot", "soot",                         // *oot words
        "boat", "bolt", "bout",                                         // bo*t words
        "hello", "world", "apple", "mango"                              // Lonely words (no 1-char neighbors)
    };

    cout << "1. Processing Dictionary of " << dictionary.size() << " words...\n";

    // Process the dictionary and build the adjacency map
    map<string, vector<string>> adjWords = computeAdjacentWords(dictionary);

    cout << "\n2. Words with at least 5 adjacent words:\n";
    cout << "--------------------------------------------------------\n";
    printHighChangeables(adjWords, 5);

    cout << "\n3. Checking specific word adjacencies:\n";
    cout << "--------------------------------------------------------\n";
    // Using the [] operator on a map. If it exists, it returns the vector.
    cout << "Neighbors of 'wine': ";
    if (adjWords.find("wine") != adjWords.end()) {
        for (const string& w : adjWords["wine"]) cout << w << " ";
        cout << "\n";
    }
    else {
        cout << "None\n";
    }

    cout << "Neighbors of 'boat': ";
    if (adjWords.find("boat") != adjWords.end()) {
        for (const string& w : adjWords["boat"]) cout << w << " ";
        cout << "\n";
    }
    else {
        cout << "None\n";
    }

    cout << "\n4. Checking all word adjacencies:\n";
    cout << "--------------------------------------------------------\n";
    printHighChangeables(adjWords, 2);

    cout << "\nALL STL MAP DIAGNOSTICS COMPLETED SAFELY.\n";
    return 0;
}
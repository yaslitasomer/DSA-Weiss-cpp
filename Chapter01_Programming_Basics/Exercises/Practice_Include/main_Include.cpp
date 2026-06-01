#include <iostream>
#include <fstream>
#include <string>
#include <set> // To keep track of active files and prevent infinite loops

using namespace std;

// Recursive function to read file and expand include statements
void processFile(const string& filename, set<string>& activeFiles) {

    // Check for infinite loops
    if (activeFiles.count(filename)) {
        cerr << "--- ERROR: Infinite loop detected for file: " << filename << " ---\n";
        return;
    }

    // Mark this file as "currently open"
    activeFiles.insert(filename);

    // Try to open file
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "--- ERROR: Could not open the file: " << filename << " ---\n";
        activeFiles.erase(filename);
        return;
    }

    // Read the file line by line
    string line;
    while (getline(file, line)) {

        // Check for include
        if (line.find("#include") == 0) {
            // Extract the filename from the line
            string nextFilename = line.substr(9);

            // Remove hidden \r if exists
            if (!nextFilename.empty() && nextFilename.back() == '\r') {
                nextFilename.pop_back();
            }

            // Recursion
            processFile(nextFilename, activeFiles);
        }
        else {
            cout << line << endl;
        }
    }

    // finished reading this file
    activeFiles.erase(filename);
}

int main() {
    set<string> currentlyOpenFiles;
    cout << "Starting the compiler simulator...\n\n";

    processFile("main.txt", currentlyOpenFiles);
    cout << "\nProcessing finished!\n";
    return 0;
}
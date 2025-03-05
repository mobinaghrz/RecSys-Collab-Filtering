#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

int main() {
    // Open the CSV file
    ifstream file("pinterest_finalised.csv");
    if (!file.is_open()) {
        cerr << "Error: Could not open the CSV file." << endl;
        return 1;
    }

    // Read the file into a 2D vector (rows and columns)
    vector<vector<string> > data;
    string line;
    while (getline(file, line)) {
        vector<string> row;
        stringstream ss(line);
        string cell;
        while (getline(ss, cell, ',')) {
            row.push_back(cell); // Add each cell to the row
        }
        data.push_back(row); // Add the row to the data
    }

    // Close the file
    file.close();

    // Print each cell using nested for loops (i and j)
    for (size_t i = 0; i < data.size(); ++i) { // Loop through rows
        for (size_t j = 0; j < data[i].size(); ++j) { // Loop through columns
            cout << "Row " << i << ", Column " << j << ": " << data[i][j] << endl;
        }
    }

    return 0;
}
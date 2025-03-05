#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cctype> // For isdigit()

using namespace std;

// Function to check if a string consists only of digits
bool isNumeric(const string& str) {
    for (size_t i = 0; i < str.length(); ++i) { // Use an index-based loop
        if (!isdigit(str[i])) { // Check if each character is a digit
            return false;
        }
    }
    return true;
}

// Function to search for the ID in the CSV file and return the corresponding title
string keyword_search(const string& id) {
    ifstream file("pinterest_finalised.csv"); // Open the CSV file
    if (!file.is_open()) {
        cerr << "Error: Could not open the CSV file." << endl;
        return ""; // Return an empty string if the file cannot be opened
    }

    // Read the first row (column names) and ignore it
    string line;
    if (!getline(file, line)) {
        cerr << "Error: CSV file is empty." << endl;
        return "";
    }

    // Search for the ID in the file
    while (getline(file, line)) {
        stringstream ss(line);
        string currentId;
        if (getline(ss, currentId, ',')) { // Read the first column (ID)
            if (currentId == id) { // Check if the ID matches
                // Skip the second column (description)
                string description;
                if (!getline(ss, description, ',')) {
                    cerr << "Error: Invalid row format." << endl;
                    return "";
                }
                // Read the third column (title)
                string title;
                if (!getline(ss, title, ',')) {
                    cerr << "Error: Invalid row format." << endl;
                    return "";
                }
                // Check if the title cell is empty
                if (title.empty()) {
                    return "No title found for this ID";
                }
                return title; // Return the title
            }
        }
    }

    cerr << "Error: ID not found in the CSV file." << endl;
    return ""; // Return an empty string if the ID is not found
}

int main() {
    string id;
    while (true) {
        // Prompt the user to enter an ID
        cout << "Enter an ID: ";
        cin >> id;

        // Validate the ID (check if it's numeric)
        if (!isNumeric(id)) {
            cout << "Error: ID must be numeric." << endl;
            continue; // Prompt the user again
        }

        // Search for the ID and get the corresponding title
        string title = keyword_search(id);
        if (!title.empty()) {
            cout << "ID: " << id << " -> Title: " << title << endl;
        } else {
            cout << "ID: " << id << " -> No title found for this ID" << endl;
        }

        // Ask the user if they want to search again
        cout << "Do you want to search again? (y/n): ";
        char choice;
        cin >> choice;
        if (choice != 'y' && choice != 'Y') {
            break; // Exit the loop if the user does not want to continue
        }
    }

    return 0;
}

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cctype> // For isdigit()
#include <vector>
#include <algorithm> // For sort

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
                // Read the description (quoted field)
                string description;
                if (ss.peek() == '"') { // Check if the description is quoted
                    ss.get(); // Skip the opening quote
                    getline(ss, description, '"'); // Read until the closing quote
                    ss.get(); // Skip the comma after the closing quote
                } else {
                    getline(ss, description, ','); // Read the description normally
                }

                // Read the title
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

// Function to count the number of matching words between two strings
size_t countMatchingWords(const string& title, const vector<string>& words) {
    size_t count = 0;
    for (size_t i = 0; i < words.size(); ++i) {
        if (title.find(words[i]) != string::npos) {
            count++;
        }
    }
    return count;
}

// Functor to compare two pairs based on their match count
struct CompareMatches {
    bool operator()(const pair<string, size_t>& a, const pair<string, size_t>& b) const {
        return b.second < a.second; // Sort by match count in descending order
    }
};

// Function to search for words in the CSV file and return a list of matching titles
vector<pair<string, size_t> > searchTitles(const vector<string>& words) {
    ifstream file("pinterest_finalised.csv"); // Open the CSV file
    vector<pair<string, size_t> > matchingTitles;

    if (!file.is_open()) {
        cerr << "Error: Could not open the CSV file." << endl;
        return matchingTitles;
    }

    // Read the first row (column names) and ignore it
    string line;
    if (!getline(file, line)) {
        cerr << "Error: CSV file is empty." << endl;
        return matchingTitles;
    }

    // Search for words in the file
    while (getline(file, line)) {
        stringstream ss(line);
        string currentId, description, title;

        // Read the ID
        if (!getline(ss, currentId, ',')) {
            continue; // Skip invalid rows
        }

        // Read the description (quoted field)
        if (ss.peek() == '"') { // Check if the description is quoted
            ss.get(); // Skip the opening quote
            getline(ss, description, '"'); // Read until the closing quote
            ss.get(); // Skip the comma after the closing quote
        } else {
            getline(ss, description, ','); // Read the description normally
        }

        // Read the title
        if (!getline(ss, title, ',')) {
            continue; // Skip invalid rows
        }

        // Count the number of matching words
        size_t matchCount = countMatchingWords(title, words);
        if (matchCount > 0) {
            matchingTitles.push_back(make_pair(title, matchCount));
        }
    }

    // Sort the titles by the number of matching words (descending order)
    sort(matchingTitles.begin(), matchingTitles.end(), CompareMatches());

    return matchingTitles;
}

int main() {
    string id;
    string title;
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
        title = keyword_search(id);
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

    // Split the title into words
    vector<string> words;
    stringstream ss(title);
    string word;
    while (ss >> word) {
        words.push_back(word);
    }

    // Search for words in the CSV file and get matching titles
    vector<pair<string, size_t> > matchingTitles = searchTitles(words);

    // Print the top 10 matching titles
    if (!matchingTitles.empty()) {
        cout << "\nTop 10 titles with the most matching words:" << endl;
        size_t count = 0;
        for (size_t i = 0; i < matchingTitles.size() && count < 10; ++i) {
            cout << " - " << matchingTitles[i].first << " (Matches: " << matchingTitles[i].second << ")" << endl;
            count++;
        }
    } else {
        cout << "\nNo matching titles found." << endl;
    }

    return 0;
}

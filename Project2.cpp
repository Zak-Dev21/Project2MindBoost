#include "Project2.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

// Function to load adjectives from a file
vector<string> loadAdjectives(const string& filename) {
    vector<string> adjectives;
    ifstream file(filename);
    string word;

    if (file.is_open()) {
        while (getline(file, word)) {
            adjectives.push_back(word);
        }
        file.close();
    }
    else {
        cerr << "Unable to open file: " << filename << endl;
        return {};  // Return an empty vector if file cannot be opened
    }

    return adjectives;
}

// Function to load quotes from a file and match with adjectives
vector<Quote> loadQuotes(const string& filename, const vector<string>& adjectives) {
    vector<Quote> quotes;
    ifstream file(filename);
    string line;

    if (file.is_open()) {
        int index = 0;
        while (getline(file, line)) {
            // Avoid exceeding the number of adjectives
            if (index < adjectives.size()) {
                Quote q;
                q.adjective = adjectives[index];
                q.quote = line;
                quotes.push_back(q);
                index++;
            }
            else {
                break;  // Stop if there are no more adjectives
            }
        }
        file.close();
    }
    else {
        cerr << "Unable to open file: " << filename << endl;
    }

    return quotes;
}





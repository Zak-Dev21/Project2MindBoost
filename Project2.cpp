#include "Project2.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>

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

// Function to detect emotional state and generate the corresponding inspirational quote
void detectUserEmotionalStateAndGenerateQuote(const vector<string>& adjectives, const vector<Quote>& quotes) {
    string userInput;
    cout << "Please describe your emotional state in a few sentences by including descriptive adjectives: ";
    getline(cin, userInput);
    stringstream inputStream(userInput);
    string word;
    bool stateDetected = false;

    vector<string> detectedAdjectives;

    // Convert user input to lowercase and check for matching adjectives
    while (inputStream >> word) {
        transform(word.begin(), word.end(), word.begin(), ::tolower); // Convert word to lowercase

        // Check if the word is in the list of adjectives
        if (find(adjectives.begin(), adjectives.end(), word) != adjectives.end()) {
            detectedAdjectives.push_back(word);
        }
    }

    // If adjectives were detected, find matching quotes
    if (!detectedAdjectives.empty()) {
        for (const string& detected : detectedAdjectives) {
            for (const auto& quote : quotes) {
                if (quote.adjective == detected) {
                    cout << "Detected emotional state: " << detected << endl;
                    cout << "Inspirational Quote: " << quote.quote << endl;
                    stateDetected = true;
                    break;
                }
            }
            if (stateDetected) break;  // Exit the loop once a quote is found
        }
    }

    if (!stateDetected) {
        cout << "No adjectives detected in your input. Please try using more descriptive adjectives." << endl;
    }
}





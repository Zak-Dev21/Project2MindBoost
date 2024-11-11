#include <iostream>
#include <vector>
#include <sstream>
#include <algorithm>
#include "Project2.h"
using namespace std;

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

int main() {
    vector<string> adjectives = loadAdjectives("Adjectives.txt");

    if (!adjectives.empty()) {
        // Load quotes based on the adjectives
        vector<Quote> quotes = loadQuotes("Quotes.txt", adjectives);

        if (!quotes.empty()) {
            // Detect user's emotional state based on input and provide an inspirational quote
            detectUserEmotionalStateAndGenerateQuote(adjectives, quotes);
        }
        else {
            cerr << "Quotes could not be loaded. Please check the Quotes.txt file." << endl;
        }
    }
    else {
        cerr << "Adjectives could not be loaded. Please check the Adjectives.txt file." << endl;
    }

    return 0;
}


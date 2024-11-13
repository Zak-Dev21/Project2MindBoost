#include <iostream>
#include <vector>
#include <sstream>
#include <algorithm>
#include "Project2.h"
using namespace std;



int main() {
    vector<string>* adjectives = loadAdjectives("Adjectives.txt");

    if (adjectives != nullptr && !adjectives->empty()) {
        // Load quotes based on the adjectives
        vector<Quote>* quotes = loadQuotes("Quotes.txt", adjectives);

        if (quotes != nullptr && !quotes->empty()) {
            // Detect user's emotional state based on input and provide an inspirational quote
            detectUserEmotionalStateAndGenerateQuote(adjectives, quotes);
            delete quotes;
        }
        else {
            cerr << "Quotes could not be loaded. Please check the Quotes.txt file." << endl;
            delete quotes;
        }

        delete adjectives;
    }
    else {
        cerr << "Adjectives could not be loaded. Please check the Adjectives.txt file." << endl;
        delete adjectives;
    }

    return 0;
}


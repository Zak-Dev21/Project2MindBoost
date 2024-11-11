#include <iostream>
#include <vector>
#include <sstream>
#include <algorithm>
#include "Project2.h"
using namespace std;



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


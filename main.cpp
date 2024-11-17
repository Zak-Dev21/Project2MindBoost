#include <iostream>
#include <vector>
#include <map>
#include "Project2.h"
using namespace std;

// Main function
int main() {
    // Load adjectives
    vector<string>* adjectives = loadAdjectives("adjectives.txt");
    if (!adjectives) return 1;

    // Load quotes for emotional states
    vector<Quote>* quotes = loadQuotes("quotes.txt", adjectives);
    if (!quotes) {
        delete adjectives;
        return 1;
    }

    // Define interests
    vector<string> interests = { "arts", "games", "music", "sports" };

    // Load general interest quotes
    map<string, vector<Quote>>* generalInterestQuotes = loadGeneralInterestQuotes("quotesInterests.txt");
    if (!generalInterestQuotes) {
        delete adjectives;
        delete quotes;
        return 1;
    }

    // Detect emotional state and generate quotes
    detectUserEmotionalStateAndGenerateQuote(adjectives, quotes, &interests, generalInterestQuotes);

    // Clean up dynamically allocated memory
    delete adjectives;
    delete quotes;
    delete generalInterestQuotes;

    return 0;
}
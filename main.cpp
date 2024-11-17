#include <iostream>
#include <vector>
#include <map>
#include "Project2.h"
using namespace std;

// Main function
int main() {
    time_t currentTime = time(0);
    srand(static_cast<unsigned int>(time(0)));  // Initialize random seed

    // Load adjectives
    vector<string>* adjectives = loadAdjectives("adjectives.txt");
    if (adjectives == nullptr) {
        cout << "Error loading adjectives file. Exiting program." << endl;
        return 1;
    }

    // Load quotes
    vector<Quote>* quotes = loadQuotes("quotes.txt", adjectives);
    if (quotes == nullptr) {
        cout << "Error loading quotes file. Exiting program." << endl;
        return 1;
    }


    

    // Load general interest quotes
    map<string, vector<Quote>>* generalInterestQuotes = loadGeneralInterestQuotes("quotesInterests.txt");
    if (!generalInterestQuotes) {
        delete adjectives;
        delete quotes;
        return 1;
    }

    // Initialize general interests and hobbies
    vector<string> interests = { "arts", "games", "music", "sports" };
    map<string, vector<string>> generalInterestHobbies;
    generalInterestHobbies["arts"] = { "painting", "photography", "sculpture", "graphic design" };
    generalInterestHobbies["games"] = { "board games", "video games", "puzzles", "card games" };
    generalInterestHobbies["music"] = { "playing an instrument", "singing", "composing", "listening to music" };
    generalInterestHobbies["sports"] = { "soccer", "basketball", "tennis", "swimming" };

    // Call the function to detect emotional state and generate the corresponding quote
    detectUserEmotionalStateAndGenerateQuote(adjectives, quotes, &interests, generalInterestQuotes, &generalInterestHobbies);
    
    
    // Clean up dynamically allocated memory
    delete adjectives;
    delete quotes;
    delete generalInterestQuotes;

    return 0;
}
#include <iostream>
#include <vector>
#include <map>
#include "Project2.h"
#include <algorithm>
using namespace std;


int main() {
    // Loop to allow retrying the program
    bool retry = true;
    while (retry) {
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

        // Initialize user profile
        UserProfile userProfile;
        userProfile.name = "Zak B";  // You can change this to prompt for name input

        // Call the function to detect emotional state and generate the corresponding quote
        detectUserEmotionalStateAndGenerateQuote(adjectives, quotes, &interests, generalInterestQuotes, &generalInterestHobbies, userProfile);

        // Print out the user's quote history (optional, for debugging or visualization)
        cout << "\nUser's Quote History: " << endl;
        for (const Quote& quote : userProfile.quoteHistory.history) {
            cout << "Adjective: " << quote.adjective << " | Quote: " << quote.quote << endl;
        }

        // Clean up dynamically allocated memory
        delete adjectives;
        delete quotes;
        delete generalInterestQuotes;

        // Ask the user if they want to run the program again
        string userChoice;
        cout << "\nWould you like to try again? (yes/no): ";
        getline(cin, userChoice);

        // Convert the user's input to lowercase for consistency
        transform(userChoice.begin(), userChoice.end(), userChoice.begin(), ::tolower);

        // Check if the user wants to retry
        if (userChoice != "yes" && userChoice != "y") {
            retry = false;  // Exit the loop if the user doesn't want to retry
        }
    }

    cout << "Thank you for using the program! Goodbye." << endl;
    return 0;
}

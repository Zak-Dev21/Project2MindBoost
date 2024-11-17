#ifndef Project2_h
#define Project2_h

#include <string>
#include <vector>
#include <map>

using namespace std;


struct Quote {
    string adjective;
    string quote;
    string interest;
    string category;
};

// Structure to store the quote history
struct QuoteHistory {
    vector<Quote> history;  // A vector to store the quotes a user has received
};

// Structure to store user profile data
struct UserProfile {
    string name;  // User's name
    vector<string> hobbies;  // List of hobbies
    vector<string> activities;  // List of activities or interests
    QuoteHistory quoteHistory;  // Nested structure to store quote history
};

// Function to check if user inputs appropriate input when describing emotional state (mood)
bool isValidWord(const string& word);

//Function to detect valid input when choosing interest
int getUserInterestChoice(int minChoice, int maxChoice);

// Function to load quotes from a file and store them in a vector
vector<Quote>* loadQuotes(const string& filename, const vector<string>* adjectives);

// Function to load adjectives from txt file 
vector<string>* loadAdjectives(const string& filename);

// Function to detect emotional state as well as general interest and hobby to generate the corresponding inspirational quotes and motivational message
void detectUserEmotionalStateAndGenerateQuote(const vector<string>* adjectives, const vector<Quote>* quotes, const vector<string>* interests, const map<string, vector<Quote>>* generalInterestQuotes, map<string, vector<string>>* generalInterestHobbies, UserProfile& userProfile);

map<string, vector<Quote>>* loadGeneralInterestQuotes(const string& filename);
#endif

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


// Function to check if user inputs appropriate input when describing emotional state (mood)
bool isValidWord(const string& word);

//Function to detect valid input when choosing interest
int getUserInterestChoice(int minChoice, int maxChoice);

// Function to load quotes from a file and store them in a vector
vector<Quote>* loadQuotes(const string& filename, const vector<string>* adjectives);

// Function to load adjectives from txt file 
vector<string>* loadAdjectives(const string& filename);

// Function to detect emotional state and generate the corresponding inspirational quote
void detectUserEmotionalStateAndGenerateQuote(const vector<string>* adjectives, const vector<Quote>* quotes, const vector<string>* interests, const map<string, vector<Quote>>* generalInterestQuotes);

map<string, vector<Quote>>* loadGeneralInterestQuotes(const string& filename);
#endif

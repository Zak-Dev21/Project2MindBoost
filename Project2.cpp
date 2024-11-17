#include "Project2.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include <cctype>
#include <ctime>
#include <cstdlib>
#include <map>

using namespace std;


// Helper function to check if a word is valid (only contains alphabetic characters)
bool isValidWord(const string& word) {
    for (char ch : word) {
        if (!isalpha(ch)) { // Checks if the character is not a letter
            return false;
        }
    }
    return true;
}

// Function to load adjectives from a file
vector<string>* loadAdjectives(const string& filename) {
    vector<string>* adjectives = new vector<string>; // allocating memeory dynamically for the vector
    ifstream file(filename);
    string word;

    if (file.is_open()) {
        while (getline(file, word)) {
            adjectives->push_back(word);
        }
        file.close();
    }
    else {
        cerr << "Unable to open file: " << filename << endl;
        delete adjectives; // Clean up memory if the file cannot be opened
        return nullptr;    // Return null pointer to indicate failure
    }

    return adjectives;
}

// Function to load quotes from a file and match with adjectives
vector<Quote>* loadQuotes(const string& filename, const vector<string>* adjectives) {
    vector<Quote>* quotes = new vector<Quote>;
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Unable to open file: " << filename << endl;
        delete quotes;
        return nullptr;
    }

    string line;
    while (getline(file, line)) {
        size_t pos = line.find(':');
        if (pos != string::npos) {
            Quote q;
            q.adjective = line.substr(0, pos);
            q.quote = line.substr(pos + 2); // Skip ": "
            quotes->push_back(q);
        }
        else {
            cerr << "Invalid format in line: " << line << endl;
        }
    }
    file.close();
    return quotes;
}


// Function to load general interest quotes from a file
map<string, vector<Quote>>* loadGeneralInterestQuotes(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Could not open the file: " << filename << endl;
        return nullptr;
    }

    auto generalInterestQuotes = new map<string, vector<Quote>>();
    string line, currentInterest;

    while (getline(file, line)) {
        if (line.empty()) continue;

        // Check for section headers (interests)
        if (line.find("---") != string::npos) {
            size_t start = line.find_first_not_of('-');
            size_t end = line.find_last_not_of('-');
            if (start != string::npos && end != string::npos) {
                currentInterest = line.substr(start, end - start + 1);
                // Trim any extra spaces around the interest
                currentInterest.erase(remove_if(currentInterest.begin(), currentInterest.end(), ::isspace), currentInterest.end());
                transform(currentInterest.begin(), currentInterest.end(), currentInterest.begin(), ::tolower);  // Make interest case insensitive
            }
        }
        else {
            size_t pos = line.find(':');
            if (pos != string::npos) {
                Quote q;
                q.adjective = line.substr(0, pos);
                q.quote = line.substr(pos + 2); // Skip ": "
                q.interest = currentInterest;

                // Store the quote under the corresponding interest
                (*generalInterestQuotes)[currentInterest].push_back(q);
            }
            else {
                cerr << "Invalid format in line: " << line << endl;
            }
        }
    }

    file.close();
    return generalInterestQuotes;
}

// Function to detect emotional state and generate the corresponding inspirational quote
void detectUserEmotionalStateAndGenerateQuote(const vector<string>* adjectives, const vector<Quote>* quotes, const vector<string>* interests, const map<string, vector<Quote>>* generalInterestQuotes) {
    bool validInput = false;
    srand(time(0)); // Randomization seed

    // Let the user select an interest
    cout << "Please select a general interest:\n";
    for (int i = 0; i < interests->size(); i++) {
        cout << (i + 1) << ". " << (*interests)[i] << endl;
    }
    int interestChoice;
    cout << "Enter the number for your interest: ";
    cin >> interestChoice;
    cin.ignore();  // Clear the newline from the input buffer

    string selectedInterest = (*interests)[interestChoice - 1];
    transform(selectedInterest.begin(), selectedInterest.end(), selectedInterest.begin(), ::tolower); // Normalize input to lowercase

    while (!validInput) {
        string userInput;
        cout << "Please describe your mood (emotional state) in a few sentences by including descriptive adjectives: ";
        getline(cin, userInput);
        stringstream inputStream(userInput);
        string word;
        bool stateDetected = false;
        bool invalidInputDetected = false;

        vector<string> detectedAdjectives;

        // Convert user input to lowercase and check for matching adjectives
        while (inputStream >> word) {
            transform(word.begin(), word.end(), word.begin(), ::tolower); // Convert word to lowercase

            // Check if the word is valid
            if (isValidWord(word)) {
                // Check if the word is in the list of adjectives
                if (find(adjectives->begin(), adjectives->end(), word) != adjectives->end()) {
                    detectedAdjectives.push_back(word);
                }
            }
            else {
                invalidInputDetected = true;
            }
        }

        // Notify the user if any invalid input was detected
        if (invalidInputDetected) {
            cout << "You entered invalid input. Please enter words without numbers or gibberish." << endl;
            continue; // Prompt the user to enter input again
        }

        // If adjectives were detected, find matching quotes
        if (!detectedAdjectives.empty()) {
            for (const string& detected : detectedAdjectives) {
                for (const auto& quote : *quotes) {
                    if (quote.adjective == detected) {
                        cout << "Detected emotional state: " << detected << endl;
                        cout << "Inspirational Quote: " << quote.quote << endl;
                        stateDetected = true;
                        break;
                    }
                }
                if (stateDetected) break;  // Exit the loop once a quote is found
            }
            validInput = true; // Set valid input to true if processing was successful
        }
        else {
            cout << "No valid adjectives detected in your input. Please try using more descriptive words." << endl;
        }
    }

    // Display another quote based on the selected interest
    cout << "Here is another quote based on your selected interest (" << selectedInterest << "):" << endl;
    if (generalInterestQuotes->find(selectedInterest) != generalInterestQuotes->end()) {
        const auto& quotesForInterest = generalInterestQuotes->at(selectedInterest);
        if (!quotesForInterest.empty()) {
            // Randomly select a quote from the available quotes for the selected interest
            int randomIndex = rand() % quotesForInterest.size();
            cout << "Quote: " << quotesForInterest[randomIndex].quote << endl;
        }
        else {
            cout << "No quotes available for the selected interest." << endl;
        }
    }
    else {
        cout << "No quotes available for the selected interest." << endl;
    }
}










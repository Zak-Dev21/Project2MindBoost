#include "Project2.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include <cctype>

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
    vector<Quote>* quotes = new vector<Quote>; // allocating memory dynamically to vector
    ifstream file(filename);
    string line;

    if (file.is_open()) {
        int index = 0;
        while (getline(file, line)) {
            // Avoid exceeding the number of adjectives
            if (index < adjectives->size()) {
                Quote q;
                q.adjective = (*adjectives)[index]; // access vector element through pointer dereferencing
                q.quote = line;
                quotes->push_back(q);
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
        delete quotes; // Clean up memory if the file cannot be opened
        return nullptr; // Return null pointer to indicate failure
    }

    return quotes;
}

// Function to detect emotional state and generate the corresponding inspirational quote
void detectUserEmotionalStateAndGenerateQuote(const vector<string>* adjectives, const vector<Quote>* quotes) {
    bool validInput = false;

    while (!validInput) {
        string userInput;
        cout << "Please describe your emotional state in a few sentences by including descriptive adjectives: ";
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
}





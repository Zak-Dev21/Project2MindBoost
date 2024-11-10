#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

//Function to load adjectives from text file to a vector

vector<string> loadAdjectives(const string& filename) {
    vector<string> adjectives;
    ifstream file(filename);
    string word;

    if (file.is_open()) {
        while (getline(file, word)) {
            adjectives.push_back(word);
        }

        file.close();
    }
    else {
        cerr << "Unable to open file: " << filename << endl;
    }

    return adjectives;
}

//Function to detect adjectives in user input

void detectUserEmotionalState(const vector<string>& adjectives) {
    string userInput;
    cout << "Please describe your emotional state in a few sentences by including descriptive adjectives: ";
    getline(cin, userInput);
    stringstream inputStream(userInput);
    string word;
    bool stateDetected = false;

    while (inputStream >> word) {
        transform(word.begin(), word.end(), word.begin(), ::tolower);
        if (find(adjectives.begin(), adjectives.end(), word) != adjectives.end()) {
            cout << "Detected emotional state: " << word << endl;
            stateDetected = true;
        }
    }

    if (!stateDetected) {
        cout << "No adjectives detected in your input. Therefor no emotional state to detect. Try to use more discriptive adjectives. " << endl;
    }
}

int main()
{
    vector<string> adjectives = loadAdjectives("C:/Users/ZAK/Desktop/CIS 25/Project 2/Project2MindBoost/Adjectives.txt");

    if (!adjectives.empty()) {
        // Detect user's emotional state based on input
        detectUserEmotionalState(adjectives);
    }
    else {
        cerr << "Adjectives could not be loaded. Please check the file." << std::endl;
    }

    return 0;
}

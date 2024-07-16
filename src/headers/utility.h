//src/headers/utility.h
#ifndef PROYECTO_PROGRAMACION3_UTILITY_H
#define PROYECTO_PROGRAMACION3_UTILITY_H

#include <sstream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

string toAlphabet(const string& word) {
    string result;
    for (char c : word) {
        if (c >= 'A' && c <= 'Z') {
            result += static_cast<char>(c + ('a' - 'A'));
        } else if (c >= 'a' && c <= 'z'){
            result += c;
        }
        else {
            result += ' ';
        }
    }
    return result;
}

vector<string> splitString(const string& str, char delimiter) {
    vector<string> substrings;
    stringstream ss(str);
    string substring;
    while (getline(ss, substring, delimiter)) {
        substrings.push_back(substring);
    }
    return substrings;
}

vector<string> trimLeadingSpaces(const vector<string>& vec) {
    vector<string> trimmedVec;

    // Function lambda to trim leading spaces of a string
    auto trimLeft = [](const string& s) -> string {
        auto it = find_if(s.begin(), s.end(), [](unsigned char ch) {
            return !isspace(ch);
        });
        return string(it, s.end());
    };

    // Apply the trimLeft lambda to each string in the original vector
    for (const auto& str : vec) {
        trimmedVec.push_back(trimLeft(str));
    }

    return trimmedVec;
}

#endif
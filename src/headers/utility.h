//src/headers/utility.h
#ifndef PROYECTO_PROGRAMACION3_UTILITY_H
#define PROYECTO_PROGRAMACION3_UTILITY_H

#include <sstream>

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

#endif
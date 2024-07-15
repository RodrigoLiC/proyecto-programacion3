//src/headers/utility.h
#ifndef PROYECTO_PROGRAMACION3_UTILITY_H
#define PROYECTO_PROGRAMACION3_UTILITY_H

#include <sstream>
#include <vector>
#include <string>

std::string toAlphabet(const std::string& word) {
    std::string result;
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

std::vector<std::string> splitString(const std::string& str, char delimiter) {
    std::vector<std::string> substrings;
    std::stringstream ss(str);
    std::string substring;
    while (getline(ss, substring, delimiter)) {
        substrings.push_back(substring);
    }
    return substrings;
}

#endif
//src/headers/utility.h
#ifndef PROYECTO_PROGRAMACION3_UTILITY_H
#define PROYECTO_PROGRAMACION3_UTILITY_H

#include <sstream>
#include <vector>
#include <string>
#include <algorithm>

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

std::vector<std::string> trimLeadingSpaces(const std::vector<std::string>& vec) {
    std::vector<std::string> trimmedVec;

    // Function lambda to trim leading spaces of a string
    auto trimLeft = [](const std::string& s) -> std::string {
        auto it = std::find_if(s.begin(), s.end(), [](unsigned char ch) {
            return !std::isspace(ch);
        });
        return std::string(it, s.end());
    };

    // Apply the trimLeft lambda to each string in the original vector
    for (const auto& str : vec) {
        trimmedVec.push_back(trimLeft(str));
    }

    return trimmedVec;
}

#endif
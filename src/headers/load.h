//src/headers/load.h
#ifndef PROYECTO_PROGRAMACION3_LOAD_H
#define PROYECTO_PROGRAMACION3_LOAD_H

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include "database.h"

std::vector<std::string> split(const std::string& str, char delimiter) {
    std::vector<std::string> tokens;
    std::string token;
    bool inQuotes = false;
    for (char c : str) {
        if (c == '\"') {
            inQuotes = !inQuotes;
        } else if (c == delimiter && !inQuotes) {
            tokens.push_back(token);
            token.clear();
        } else {
            token += c;
        }
    }
    if (!token.empty()) {
        tokens.push_back(token);
    }
    return tokens;
}

int load_data() {
    std::ifstream file("../datasets/mpst_full_data.csv");

    if (!file.is_open()) {
        std::cerr << "Could not open file" << "\n";
        return -1;
    }
    std::cout << "dataset file opened successfully." << "\n";
    std::cout << "Loading data..." << "\n";
    Database* Movies = Database::getInstance();
    std::string line;
    int count = 0;
    std::cout << "Movies loaded (thousands):\n";
    while (getline(file, line)) {
        int quotes_count = std::count(line.begin(), line.end(), '"');
        while (quotes_count % 2 != 0 && !file.eof()) {
            std::string extra_line;
            getline(file, extra_line);
            line += "\n" + extra_line;
            quotes_count = std::count(line.begin(), line.end(), '"');
        }
        std::vector<std::string> data = split(line, ',');
        Movies->addMovieByValues(data[0], data[1], data[2], trimLeadingSpaces(split(data[3], ',')), data[4], data[5]);
        count++;
        if (count % 1000 == 0) {
            std::cout << "|";
        }
    }
    std::cout << "\n";
    std::cout << Movies->getMovies().size() << " movies loaded." << "\n";
    file.close();
    return 0;
}

#endif

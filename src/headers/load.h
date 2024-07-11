#ifndef PROYECTO_PROGRAMACION3_LOAD_H
#define PROYECTO_PROGRAMACION3_LOAD_H

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

#include "database.h"

/** Function to split the CSV line into a vector of strings
 * ignoring commas inside quotes. **/
vector<string> split(const string& str, char delimiter) {
    vector<string> tokens;
    string token;
    bool inQuotes = false;
    for (char c : str) {
        if (c == '\"') {
            inQuotes = !inQuotes;
        } else if (c == delimiter && !inQuotes) {
            tokens.push_back(token);
            token = "";
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
    ifstream file("../datasets/mpst_full_data.csv");

    if (!file.is_open()) {
        cout << "Could not open file" << "\n";
        return -1;
    }
    cout << "File opened successfully" << "\n";
    cout << "Loading data..." << "\n";
    Database* Movies = Database::getInstance();
    string line;
    while (getline(file, line)) {
        int quotes_count = count(line.begin(), line.end(), '"');
        while (quotes_count % 2 != 0 && !file.eof()) {
            string extra_line;
            getline(file, extra_line);
            line += "\n"+ extra_line;
            quotes_count = count(line.begin(), line.end(), '"');
        }
        vector<string> data = split(line, ',');
        Movies->addMovieByValues(data[0], data[1], data[2], split(data[3], ';'), data[4], data[5]);
    }
    cout << Movies->getMovies().size() << " movies loaded." << "\n";
    file.close();
    return 0;
};


#endif
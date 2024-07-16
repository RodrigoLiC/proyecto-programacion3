// src/headers/search.h
#ifndef PROYECTO_PROGRAMACION3_SEARCH_H
#define PROYECTO_PROGRAMACION3_SEARCH_H

#include <string>
#include <vector>
#include <unordered_set>
#include <sstream>

#include "database.h"

class SearchCommand {
public:
    virtual vector<int> execute(const string& input, Database* db) = 0;
};

class MovieSearchCommand : public SearchCommand {
public:
    vector<int> execute(const string& input, Database* db) override {
        istringstream iss(input);
        vector<vector<int>> searchIndexes;
        string word;
        while (iss >> word) {
            searchIndexes.push_back(db->getTrie().getMovieIndices(word));
        }

        vector<int> intersection;
        if (!searchIndexes.empty()) {
            intersection = searchIndexes[0];
            for (size_t i = 1; i < searchIndexes.size(); ++i) {
                vector<int> currentIndices = searchIndexes[i];
                unordered_set<int> commonIndices(intersection.begin(), intersection.end());
                vector<int> newIntersection;
                for (int index : currentIndices) {
                    if (commonIndices.count(index) > 0) {
                        newIntersection.push_back(index);
                    }
                }
                intersection = newIntersection;
            }
        }
        return intersection;
    }
};

class TagSearchCommand : public SearchCommand {
public:
    vector<int> execute(const string& input, Database* db) override {
        vector<int> indices;
        cout << "Searching for tag: " << input << endl;
        vector<Movie> movies = db->getMovies();
        for (int i = 0; i < movies.size(); ++i) {
            vector<string> movieTags = movies[i].tags;
            for (const auto& tag : movieTags) {
                if (tag == input) {
                    indices.push_back(i);
                    break;
                }
            }
            if (indices.size() > 50) {
                break;
            }
        }
        cout << "Searched";
        return indices;
    }
};

#endif
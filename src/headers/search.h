//src/headers/search.h
#ifndef PROYECTO_PROGRAMACION3_SEARCH_H
#define PROYECTO_PROGRAMACION3_SEARCH_H

#include <string>
#include <vector>
#include <unordered_set>
#include <sstream>
#include "database.h"

class SearchCommand {
public:
    virtual std::vector<int> execute(const std::string& input, Database* db) = 0;
};

class MovieSearchCommand : public SearchCommand {
public:
    std::vector<int> execute(const std::string& input, Database* db) override {
        std::istringstream iss(input);
        std::vector<std::vector<int>> searchIndexes;
        std::string word;
        while (iss >> word) {
            searchIndexes.push_back(db->getTrie().getMovieIndices(word));
        }

        std::vector<int> intersection;
        if (!searchIndexes.empty()) {
            intersection = searchIndexes[0];
            for (size_t i = 1; i < searchIndexes.size(); ++i) {
                std::vector<int> currentIndices = searchIndexes[i];
                std::unordered_set<int> commonIndices(intersection.begin(), intersection.end());
                std::vector<int> newIntersection;
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

#endif

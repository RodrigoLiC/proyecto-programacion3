//src/headers/database.h
#ifndef PROYECTO_PROGRAMACION3_DATABASE_H
#define PROYECTO_PROGRAMACION3_DATABASE_H

#include <map>
#include <mutex>
#include <thread>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <unordered_set>

#include "trie.h"
#include "movie.h"
#include "utility.h"

class Database {
private:
    vector<Movie> movies;
    static Database* instance;
    Trie trie;
    Database() = default;

    // Typedef of a function pointer type
    typedef void (Database::*ProcessFunc)(const vector<string>&, int);

public:
    // Getters

    static Database* getInstance() {
        if (instance == nullptr) {
            instance = new Database();
        }
        return instance;
    }

    vector<Movie> getMovies() const {
        return movies;
    }

    Trie getTrie() const {
        return trie;
    }


    // Methods

    // Add movie
    void addMovieByValues(const string& imdbId, const string& title, const string& plotSynopsis,
                          const vector<string>& tags, const string& split, const string& synopsisSource) {
        movies.emplace_back(imdbId, title, plotSynopsis, tags, split, synopsisSource);
    }


    // Trie save/load

    void saveTrieToFile(const string& filename) {
        trie.saveTrie(filename);
    }

    void loadTrieFromFile(const string& filename) {
        trie.loadTrie(filename);
    }


    // Trie Generation

    void generateTrie() {
        int numThreads = thread::hardware_concurrency();
        int chunkSize = movies.size() / numThreads;
        vector<thread> threads;

        // Define the processing priority order
        ProcessFunc processFuncs[] = {
                &Database::processInsertWord,
                &Database::processInsertAllWords,
                &Database::processInsertPrefix,
                &Database::processInsertAllPrefixes
        };

        // Process titles
        cout << "Processing titles..." << endl;
        for (auto func : processFuncs) {
            threads.clear();
            for (int i = 0; i < numThreads; ++i) {
                int start = i * chunkSize;
                int end = (i == numThreads - 1) ? movies.size() : start + chunkSize;
                threads.emplace_back(&Database::processTitles, this, start, end, func);
            }
            for (auto &t: threads) { t.join(); }
        }

        // Process descriptions
        cout << "Processing descriptions..." << endl;
        threads.clear();
        for (int i = 0; i < numThreads; ++i) {
            int start = i * chunkSize;
            int end = (i == numThreads - 1) ? movies.size() : start + chunkSize;
            threads.emplace_back(&Database::processSubwordInDescription, this, start, end);
        }
        for (auto &t: threads) { t.join(); }
    }


    void processTitles(int start, int end, ProcessFunc processFunc) {
        for (int i = start; i < end; ++i) {
            vector<string> title = splitString(toAlphabet(movies[i].title), ' ');
            (this->*processFunc)(title, i);
        }
    }

    // Process priorities

    void processInsertWord(const vector<string>& title, int index) {
        trie.insertWord(title[0], index);
    }

    void processInsertAllWords(const vector<string>& title, int index) {
        for (const auto &word: title) {
            trie.insertWord(word, index);
        }
    }

    void processInsertPrefix(const vector<string>& title, int index) {
        trie.insertPrefix(title[0], index);
    }

    void processInsertAllPrefixes(const vector<string>& title, int index) {
        for (const auto &word: title) {
            trie.insertPrefix(word, index);
        }
    }

    void processSubwordInDescription(int start, int end) {
        for (int i = start; i < end; ++i) {
            auto description = splitString(toAlphabet(movies[i].plot_synopsis), ' ');
            unordered_set<string> uniqueWords;

            for (const auto &word: description) {
                if (uniqueWords.count(word) == 0) {
                    uniqueWords.insert(word);
                    for (int j = 0; j < word.size(); j++) {
                        string prefix = word.substr(j);
                        trie.insertPrefix(prefix, i);
                    }
                }
            }
        }
    }
};

Database* Database::instance = nullptr;

#endif

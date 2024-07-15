//src/headers/database.h
#ifndef PROYECTO_PROGRAMACION3_DATABASE_H
#define PROYECTO_PROGRAMACION3_DATABASE_H

#include <thread>
#include <vector>
#include "trie.h"
#include "utility.h"
#include <fstream>
#include <iostream>
#include <unordered_set>
#include <string>
#include <mutex>
#include <sstream>
#include <map>
#include "movie_factory.h"
#include "observer.h"

class Database : public Subject {
private:
    std::vector<Movie> movies;
    static Database* instance;
    Trie trie;
    Database() = default;

public:
    static Database* getInstance() {
        if (instance == nullptr) {
            instance = new Database();
        }
        return instance;
    }

    void addMovieObject(const Movie& movie) {
        movies.push_back(movie);
        notifyObservers();
    }

    void addMovieByValues(const std::string& imdbId, const std::string& title, const std::string& plotSynopsis,
                          const std::vector<std::string>& tags, const std::string& split, const std::string& synopsisSource) {
        movies.push_back(MovieFactory::createMovie(imdbId, title, plotSynopsis, tags, split, synopsisSource));
        notifyObservers();
    }

    std::vector<Movie> getMovies() const {
        return movies;
    }

    void processTitles(int start, int end, std::function<void(const std::vector<std::string>&, int)> processFunc) {
        for (int i = start; i < end; ++i) {
            std::vector<std::string> title = splitString(toAlphabet(movies[i].title), ' ');
            processFunc(title, i);
        }
    }

    void generateTrie() {
        int numThreads = std::thread::hardware_concurrency();
        int chunkSize = movies.size() / numThreads;
        std::vector<std::thread> threads;

        std::vector<std::function<void(const std::vector<std::string>&, int)>> processFuncs = {
                [this](const std::vector<std::string>& title, int index) { trie.insertWord(title[0], index); },
                [this](const std::vector<std::string>& title, int index) {
                    for (const auto &word: title) {
                        trie.insertWord(word, index);
                    }
                },
                [this](const std::vector<std::string>& title, int index) { trie.insertPrefix(title[0], index); },
                [this](const std::vector<std::string>& title, int index) {
                    for (const auto &word: title) {
                        trie.insertPrefix(word, index);
                    }
                }
        };

        for (const auto& func : processFuncs) {
            threads.clear();
            for (int i = 0; i < numThreads; ++i) {
                int start = i * chunkSize;
                int end = (i == numThreads - 1) ? movies.size() : start + chunkSize;
                threads.emplace_back(&Database::processTitles, this, start, end, func);
            }
            for (auto &t: threads) { t.join(); }
        }

        threads.clear();
        for (int i = 0; i < numThreads; ++i) {
            int start = i * chunkSize;
            int end = (i == numThreads - 1) ? movies.size() : start + chunkSize;
            threads.emplace_back(&Database::processSubwordInDescription, this, start, end);
        }
        for (auto &t: threads) { t.join(); }
    }

    void saveTrieToFile(const std::string& filename) {
        trie.saveTrie(filename);
    }

    void loadTrieFromFile(const std::string& filename) {
        trie.loadTrie(filename);
    }

    Trie getTrie() const {
        return trie;
    }

    void processSubwordInDescription(int start, int end) {
        for (int i = start; i < end; ++i) {
            auto description = splitString(toAlphabet(movies[i].plot_synopsis), ' ');
            std::unordered_set<std::string> uniqueWords;

            for (const auto &word: description) {
                if (uniqueWords.count(word) == 0) {
                    uniqueWords.insert(word);
                    for (int j = 0; j < word.size(); j++) {
                        std::string prefix = word.substr(j);
                        trie.insertPrefix(prefix, i);
                    }
                }
            }
        }
    }
};

Database* Database::instance = nullptr;

#endif

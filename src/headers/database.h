#ifndef PROYECTO_PROGRAMACION3_DATABASE_H
#define PROYECTO_PROGRAMACION3_DATABASE_H

#include "trie.h"
#include "utility.h"
#include <iostream>
#include <vector>
#include <string>

using namespace std;

struct Movie {
    string imdb_id;
    string title;
    string plot_synopsis;
    vector<string> tags;
    string split;
    string synopsis_source;

    Movie(const string &imdbId, const string &title, const string &plotSynopsis,
          const vector<string> &tags, const string &split, const string &synopsisSource) :
            imdb_id(imdbId),
            title(title),
            plot_synopsis(plotSynopsis),
            tags(tags),
            split(split),
            synopsis_source(synopsisSource) {}

    void imprimirPelicula() const {
        cout << "IMDB_ID: " << imdb_id << endl;
        cout << "Title: " << title << endl;
        cout << "Synopsis: " << plot_synopsis << endl;
        cout << "Split: " << split << endl;
        cout << "Synopsis Source: " << synopsis_source << endl;
        cout << "Tags: ";
        for (const string& tag : tags) {
            cout << "[" << tag << "] ";
        }
        cout << endl;
    }

    void imprimirPreview() const {
        cout << "==================================================\n";
        cout << "IMDB_ID: " << imdb_id << endl;
        cout << "Title: " << title << endl;
        if (plot_synopsis.size() > 100) {
            cout << "Synopsis: " << plot_synopsis.substr(0, 97) << "..." << endl;
        } else {
            cout << "Synopsis: " << plot_synopsis << endl;
        }
        cout << "Split: " << split << endl;
        cout << "Synopsis Source: " << synopsis_source << endl;
        cout << "Tags: ";
        for (const string& tag : tags) {
            cout << "[" << tag << "] ";
        }
        cout << "\n==================================================\n";
    }
};

class Database {
private:
    vector<Movie> movies;
    static Database* instance;
    Trie trie;
    Database() {};

public:
    static Database* getInstance() {
        if (instance == nullptr) {
            instance = new Database();
        }
        return instance;
    }

    void addMovieObject(const Movie& movie) {
        movies.push_back(movie);
    }

    void addMovieByValues(const string &imdbId, const string &title, const string &plotSynopsis,
                          const vector<string> &tags, const string &split, const string &synopsisSource) {
        movies.emplace_back(imdbId, title, plotSynopsis, tags, split, synopsisSource);
    }

    vector<Movie> getMovies() const {
        return movies;
    }

    void generateTrie() {
        cout << "Generating trie...\n";
        for (int i = 0; i < movies.size(); i++) {
            auto title = splitString(toAlphabet(movies[i].title), ' ');
            for (int j = 0; j < title[0].size(); j++) {
                trie.insertPrefix(title[0].substr(j), i);
            }
        }
        for (int i = 0; i < movies.size(); i++) {
            auto title = splitString(toAlphabet(movies[i].title), ' ');
            for (const auto& word : title) {
                for (int j = 0; j < word.size(); j++) {
                    trie.insertPrefix(word.substr(j), i);
                }
            }
        }
        for (int i = 0; i < movies.size(); i++) {
            auto description = splitString(toAlphabet(movies[i].plot_synopsis), ' ');
            for (const auto& word : description) {
                for (int j = 0; j < word.size(); j++) {
                    trie.insertPrefix(word.substr(j), i);
                }
            }
        }
        cout << "Trie generated successfully.\n";
    }

    Trie getTrie() const {
        return trie;
    }

    void saveTrieToFile(const string& filename) {
        trie.saveTrie(filename);
    }

    void loadTrieFromFile(const string& filename) {
        trie.loadTrie(filename);
    }
};

Database* Database::instance = nullptr;

#endif // PROYECTO_PROGRAMACION3_DATABASE_H

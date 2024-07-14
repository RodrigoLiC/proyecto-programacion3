#ifndef PROYECTO_PROGRAMACION3_DATABASE_H
#define PROYECTO_PROGRAMACION3_DATABASE_H

#include <thread>

#include "trie.h"
#include "utility.h"
#include <fstream>

/** Entidad que representa una película. @n
 * Estructura: @n@n
 * - imdb_id: Identificador de la película en la base de datos de IMDB. @n@n
 * - title: Título de la película. @n@n
 * - plot_synopsis: Sinopsis de la película. @n@n
 * - tags: Lista de etiquetas asociadas a la película. @n@n
 * - split: División de la película en el conjunto de entrenamiento o prueba. @n@n
 * - synopsis_source: Fuente de la sinopsis de la película.
 **/
struct Movie {
    string imdb_id;
    string title;
    string plot_synopsis;
    vector<string> tags;
    string split;
    string synopsis_source;
public:
    Movie(const string &imdbId, const string &title, const string &plotSynopsis,
          const vector<string> &tags, const string &split, const string &synopsisSource):
          imdb_id(imdbId),
          title(title),
          plot_synopsis(plotSynopsis),
          tags(tags),
          split(split),
          synopsis_source(synopsisSource) {}

    void imprimirPelicula() {
        cout << "IMDB_ID: " << imdb_id << endl;
        cout << "Title: " << title << endl;
        cout << "Synopsis: " << plot_synopsis << endl;
        cout << "Split: " << split << endl;
        cout << "Synopsis Source: " << synopsis_source << endl;
        cout << "Tags: ";
        for (const string& tag : tags) {
            cout << "["<< tag << "] ";
        }
        cout << endl;
    }
    void imprimirPreview() {
        cout << "==================================================\n";
        cout << "IMDB_ID: " << imdb_id << endl;
        cout << "Title: " << title << endl;
        if (plot_synopsis.size() > 100) {
            cout << "Synopsis: " << plot_synopsis.substr(0, 96) << "..." << endl;
        } else {
            cout << "Synopsis: " << plot_synopsis << endl;
        }
        cout << "Split: " << split << endl;
        cout << "Synopsis Source: " << synopsis_source << endl;
        cout << "Tags: ";
        for (const string& tag : tags) {
            cout << "["<< tag << "] ";
        }
        cout << "\n";
        cout << "==================================================\n";
    }
};

// Singleton
class Database {
private:
    vector<Movie> movies;
    static Database* instance;
    Trie trie;
    Database(){};

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

    vector<Movie> getMovies() {
        return movies;
    }

    void processMovies(int start, int end) {
        for (int i = start; i < end; ++i) {
            auto description = splitString(toAlphabet(movies[i].plot_synopsis), ' ');
            auto title = splitString(toAlphabet(movies[i].title), ' ');
            unordered_set<string> uniqueWords;

            for (const auto &word: title) {
                for (int j = 0; j < word.size(); j++) {
                    string prefix = word.substr(j);
                    if (uniqueWords.count(prefix) == 0) {
                        uniqueWords.insert(prefix);
                        trie.insertPrefix(prefix, i);
                    }
                }
            }

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

    void generateTrie() {
        int numThreads = thread::hardware_concurrency();
        int chunkSize = movies.size() / numThreads;
        vector<thread> threads;

        cout << "Generating trie using " << numThreads << " threads...\n";

        for (int i = 0; i < numThreads; ++i) {
            int start = i * chunkSize;
            int end = (i == numThreads - 1) ? movies.size() : start + chunkSize;
            threads.emplace_back(&Database::processMovies, this, start, end);
        }

        for (auto &t: threads) {
            t.join();
        }
    }

    void saveTrieToFile(const string& filename) {
        trie.saveTrie(filename);
    }

    void loadTrieFromFile(const string& filename) {
        trie.loadTrie(filename);
    }

    Trie getTrie() {
        return trie;
    }
};

Database* Database::instance = nullptr;


#endif
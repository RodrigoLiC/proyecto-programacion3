//src/headers/movie.h
#ifndef PROYECTO_PROGRAMACION3_MOVIE_H
#define PROYECTO_PROGRAMACION3_MOVIE_H

#include <string>
#include <vector>
#include <iostream>

class Movie {
public:
    std::string imdb_id;
    std::string title;
    std::string plot_synopsis;
    std::vector<std::string> tags;
    std::string split;
    std::string synopsis_source;

    Movie(const std::string &imdbId, const std::string &title, const std::string &plotSynopsis,
          const std::vector<std::string> &tags, const std::string &split, const std::string &synopsisSource):
            imdb_id(imdbId), title(title), plot_synopsis(plotSynopsis), tags(tags), split(split), synopsis_source(synopsisSource) {}

    void imprimirPelicula() const {
        std::cout << "IMDB_ID: " << imdb_id << std::endl;
        std::cout << "Title: " << title << std::endl;
        std::cout << "Synopsis: " << plot_synopsis << std::endl;
        std::cout << "Split: " << split << std::endl;
        std::cout << "Synopsis Source: " << synopsis_source << std::endl;
        std::cout << "Tags: ";
        for (const std::string& tag : tags) {
            std::cout << "["<< tag << "] ";
        }
        std::cout << std::endl;
    }

    void imprimirPreview() const {
        std::cout << "==================================================\n";
        std::cout << "IMDB_ID: " << imdb_id << std::endl;
        std::cout << "Title: " << title << std::endl;
        if (plot_synopsis.size() > 100) {
            std::cout << "Synopsis: " << plot_synopsis.substr(0, 96) << "..." << std::endl;
        } else {
            std::cout << "Synopsis: " << plot_synopsis << std::endl;
        }
        std::cout << "Split: " << split << std::endl;
        std::cout << "Synopsis Source: " << synopsis_source << std::endl;
        std::cout << "Tags: ";
        for (const std::string& tag : tags) {
            std::cout << "["<< tag << "] ";
        }
        std::cout << "\n";
        std::cout << "==================================================\n";
    }
};

#endif
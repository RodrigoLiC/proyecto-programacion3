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
          const std::vector<std::string> &tags, const std::string &split, const std::string &synopsisSource) :
            imdb_id(imdbId), title(title), plot_synopsis(plotSynopsis), tags(tags), split(split),
            synopsis_source(synopsisSource) {}
};

class DisplayMovie {
protected:
    const Movie &movie;

public:
    DisplayMovie(const Movie &movie) : movie(movie) {}
    virtual void display() const = 0;
};

class FullDisplayMovie : public DisplayMovie {
public:
    FullDisplayMovie(const Movie &movie) : DisplayMovie(movie) {}

    void display() const override {
        std::cout << "IMDB_ID: " << movie.imdb_id << std::endl;
        std::cout << "Title: " << movie.title << std::endl;
        std::cout << "Synopsis: " << movie.plot_synopsis << std::endl;
        std::cout << "Split: " << movie.split << std::endl;
        std::cout << "Synopsis Source: " << movie.synopsis_source << std::endl;
        std::cout << "Tags: ";
        for (const std::string &tag : movie.tags) {
            std::cout << "[" << tag << "] ";
        }
        std::cout << std::endl;
    }
};

class PreviewDisplayMovie : public DisplayMovie {
public:
    PreviewDisplayMovie(const Movie &movie) : DisplayMovie(movie) {}

    void display() const override {
        std::cout << "==================================================\n";
        std::cout << "IMDB_ID: " << movie.imdb_id << std::endl;
        std::cout << "Title: " << movie.title << std::endl;
        if (movie.plot_synopsis.size() > 100) {
            std::cout << "Synopsis: " << movie.plot_synopsis.substr(0, 96) << "..." << std::endl;
        } else {
            std::cout << "Synopsis: " << movie.plot_synopsis << std::endl;
        }
        std::cout << "Split: " << movie.split << std::endl;
        std::cout << "Synopsis Source: " << movie.synopsis_source << std::endl;
        std::cout << "Tags: ";
        for (const std::string &tag : movie.tags) {
            std::cout << "[" << tag << "] ";
        }
        std::cout << "\n";
    }
};

class MovieFactory {
public:
    enum DisplayType {
        FULL,
        PREVIEW
    };

    static void displayMovie(DisplayType type, const Movie &movie) {
        std::unique_ptr<DisplayMovie> displayMovie;
        switch (type) {
            case FULL: {
                displayMovie = std::make_unique<FullDisplayMovie>(movie);
                break;
            }
            case PREVIEW: {
                displayMovie = std::make_unique<PreviewDisplayMovie>(movie);
                break;
            }
            default:
                std::cerr << "Unknown display type" << std::endl;
                return;
        }
        displayMovie->display();
    }
};


#endif
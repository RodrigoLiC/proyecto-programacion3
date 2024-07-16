//src/headers/movie.h
#ifndef PROYECTO_PROGRAMACION3_MOVIE_H
#define PROYECTO_PROGRAMACION3_MOVIE_H

#include <string>
#include <vector>
#include <iostream>

using namespace std;

class Movie {
public:
    string imdb_id;
    string title;
    string plot_synopsis;
    vector<string> tags;
    string split;
    string synopsis_source;

    Movie(const string &imdbId, const string &title, const string &plotSynopsis,
          const vector<string> &tags, const string &split, const string &synopsisSource) :
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
        cout << "IMDB_ID: " << movie.imdb_id << endl;
        cout << "Title: " << movie.title << endl;
        cout << "Synopsis: " << movie.plot_synopsis << endl;
        cout << "Split: " << movie.split << endl;
        cout << "Synopsis Source: " << movie.synopsis_source << endl;
        cout << "Tags: ";
        for (const string &tag : movie.tags) {
            cout << "[" << tag << "] ";
        }
        cout << endl;
    }
};

class PreviewDisplayMovie : public DisplayMovie {
public:
    PreviewDisplayMovie(const Movie &movie) : DisplayMovie(movie) {}

    void display() const override {
        cout << "==================================================\n";
        cout << "IMDB_ID: " << movie.imdb_id << endl;
        cout << "Title: " << movie.title << endl;
        if (movie.plot_synopsis.size() > 100) {
            cout << "Synopsis: " << movie.plot_synopsis.substr(0, 96) << "..." << endl;
        } else {
            cout << "Synopsis: " << movie.plot_synopsis << endl;
        }
        cout << "Split: " << movie.split << endl;
        cout << "Synopsis Source: " << movie.synopsis_source << endl;
        cout << "Tags: ";
        for (const string &tag : movie.tags) {
            cout << "[" << tag << "] ";
        }
        cout << "\n";
    }
};

class MovieFactory {
public:
    enum DisplayType {
        FULL,
        PREVIEW
    };

    static void displayMovie(DisplayType type, const Movie &movie) {
        unique_ptr<DisplayMovie> displayMovie;
        switch (type) {
            case FULL: {
                displayMovie = make_unique<FullDisplayMovie>(movie);
                break;
            }
            case PREVIEW: {
                displayMovie = make_unique<PreviewDisplayMovie>(movie);
                break;
            }
            default:
                cerr << "Unknown display type" << endl;
                return;
        }
        displayMovie->display();
    }
};


#endif
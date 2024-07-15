#ifndef PROYECTO_PROGRAMACION3_USER_H
#define PROYECTO_PROGRAMACION3_USER_H

#include <vector>
#include <string>
#include <iostream>
#include "database.h"

class User {
private:
    std::vector<int> likedMovies;
    std::vector<int> watchLaterMovies;

public:
    void likeMovie(int movieIndex) {
        likedMovies.push_back(movieIndex);
        std::cout << "Movie added to liked list.\n";
    }

    void addWatchLater(int movieIndex) {
        watchLaterMovies.push_back(movieIndex);
        std::cout << "Movie added to watch later list.\n";
    }

    void showLikedMovies(Database* db) const {
        std::cout << "Liked Movies:\n";
        for (int index : likedMovies) {
            MovieFactory::displayMovie(MovieFactory::FULL,db->getMovies()[index]);
        }
    }

    void showWatchLaterMovies(Database* db) const {
        std::cout << "Watch Later Movies:\n";
        for (int index : watchLaterMovies) {
            MovieFactory::displayMovie(MovieFactory::FULL,db->getMovies()[index]);
        }
    }
};

#endif

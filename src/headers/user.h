// src/headers/user.h
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

    bool isLikedMovie(int movieIndex) const {
        for (int index : likedMovies) {
            if (index == movieIndex) {
                return true;
            }
        }
        return false;
    }

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
            MovieFactory::displayMovie(MovieFactory::FULL, db->getMovies()[index]);
        }
    }

    void showWatchLaterMovies(Database* db) const {
        std::cout << "Watch Later Movies:\n";
        for (int index : watchLaterMovies) {
            MovieFactory::displayMovie(MovieFactory::FULL, db->getMovies()[index]);
        }
    }

    void showRecommendations(Database* db) const {
        std::unordered_set<std::string> likedTags;
        std::vector<Movie> movies = db->getMovies();
        std::cout << "Collecting tags from liked movies...\n";
        for (int index: likedMovies) {
            std::vector<std::string> tags = db->getMovies()[index].tags;
            for (auto tag: tags) {
                likedTags.insert(tag);
            }
        }

        std::cout << "Finding movies with similar tags...\n";
        std::vector<int> recommendedMovies;
        for (int i = 0; i < movies.size(); ++i) {
            if (isLikedMovie(i)) {
                continue;
            }
            for (auto tag: movies[i].tags) {
                if (likedTags.find(tag) != likedTags.end()) {
                    recommendedMovies.push_back(i);
                    break;
                }
            }
            if(recommendedMovies.size() > 5) {
                break;
            }
        }

        std::cout << "Here are some movies you may like:\n";
        for (int i = 0; i < recommendedMovies.size(); ++i) {
            MovieFactory::displayMovie(MovieFactory::PREVIEW, movies[recommendedMovies[i]]);
        }
        std::cout << "Going back to menu...\n";
    }
};

#endif // PROYECTO_PROGRAMACION3_USER_H

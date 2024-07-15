//src/headers/movie_factory.h
#ifndef PROYECTO_PROGRAMACION3_MOVIE_FACTORY_H
#define PROYECTO_PROGRAMACION3_MOVIE_FACTORY_H

#include "movie.h"

class MovieFactory {
public:
    static Movie createMovie(const std::string& imdbId, const std::string& title, const std::string& plotSynopsis,
                             const std::vector<std::string>& tags, const std::string& split, const std::string& synopsisSource) {
        return Movie(imdbId, title, plotSynopsis, tags, split, synopsisSource);
    }
};

#endif
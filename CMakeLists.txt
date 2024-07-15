cmake_minimum_required(VERSION 3.27)
project(proyecto_programacion3)

set(CMAKE_CXX_STANDARD 14)

add_executable(proyecto_programacion3 src/main.cpp
        src/headers/trie.h
        src/headers/database.h
        src/headers/search.h
        src/headers/ui.h
        src/headers/utility.h
        src/headers/load.h
        src/headers/movie.h)
//src/main.cpp
#include <iostream>
#include <fstream>
#include <string>
#include "headers/database.h"
#include "headers/search.h"
#include "headers/trie.h"
#include "headers/ui.h"
#include "headers/utility.h"
#include "headers/load.h"

int main() {
    Database* db = Database::getInstance();
    std::string trieFile = "../datasets/trie_data.txt";

    std::ifstream infile(trieFile);
    if (!infile.good()) {
        std::cout << "No existing trie file found. Loading data and generating trie..." << std::endl;
        load_data();
        db->generateTrie();
        db->saveTrieToFile(trieFile);
    } else {
        load_data();
        std::cout << "Loading trie from file..." << std::endl;
        db->loadTrieFromFile(trieFile);
    }

    std::string s;
    MovieSearchCommand searchCommand;
    while (s != "exit") {
        std::string input;
        std::cout << "\nIngrese parte de la pelicula que desea buscar: ";
        getline(std::cin, input);

        std::vector<int> indexes = searchCommand.execute(input, db);

        if (indexes.empty()) {
            std::cout << "No movies found for the given prefix." << std::endl;
        } else {
            for (int i = 0; i < 5 && i < indexes.size(); i++) {
                db->getMovies()[indexes[i]].imprimirPreview();
            }
            std::cout << "\n\n";
        }
    }

    return 0;
}
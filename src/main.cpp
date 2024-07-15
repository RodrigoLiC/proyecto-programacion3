//src/main.cpp
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "headers/database.h"
#include "headers/search.h"
#include "headers/ui.h"
#include "headers/load.h"
#include "headers/user.h"


int main() {
    Database* db = Database::getInstance();
    std::string trieFile = "../datasets/trie_data.txt";

    std::ifstream infile(trieFile);
    if (!infile.good()) {
        load_data();
        std::cout << "No existing trie file found. Loading data and generating trie..." << std::endl;
        db->generateTrie();
        db->saveTrieToFile(trieFile);
    } else {
        load_data();
        std::cout << "Loading trie from file..." << std::endl;
        db->loadTrieFromFile(trieFile);
    }



    User user;
    MovieSearchCommand searchCommand;

    while (true) {
        MainMenu mainMenu;
        mainMenu.display();
        mainMenu.handleInput(user, db);
    }

//
//    while (true) {
//        showMenu(user, db);
//
//        std::string input;
//        std::cout << "\nIngrese parte de la pelicula que desea buscar: ";
//        getline(std::cin, input);
//
//        std::vector<int> indexes = searchCommand.execute(input, db);
//
//        if (indexes.empty()) {
//            std::cout << "No movies found for the given prefix." << std::endl;
//        } else {
//            if (movieSelectionMenu(indexes, db, user)) {
//                continue; // Return to main menu
//            }
//        }
//    }

    return 0;
}
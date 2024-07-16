//src/main.cpp
#include <iostream>
#include <fstream>
#include <string>

#include "headers/database.h"
#include "headers/search.h"
#include "headers/ui.h"
#include "headers/load.h"
#include "headers/user.h"


int main() {
    Database* db = Database::getInstance();
    string trieFile = "../datasets/trie_data.txt";

    ifstream infile(trieFile);
    if (!infile.good()) {
        load_data();
        cout << "No existing trie file found. Loading data and generating trie..." << endl;
        db->generateTrie();
        db->saveTrieToFile(trieFile);
    } else {
        load_data();
        cout << "Loading trie from file..." << endl;
        db->loadTrieFromFile(trieFile);
    }


    User user;
    MovieSearchCommand searchCommand;

    while (true) {
        MainMenu mainMenu;
        mainMenu.display();
        mainMenu.handleInput(user, db);
    }

    return 0;
}
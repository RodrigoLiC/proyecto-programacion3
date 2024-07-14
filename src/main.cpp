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
    string trieFile = "../datasets/trie_data.txt";

    ifstream infile(trieFile);
    if (!infile.good()) { // Verifica si el archivo no existe o no es accesible
        cout << "No existing trie file found. Loading data and generating trie..." << endl;
        load_data(); // Cargar datos desde el CSV
        db->generateTrie(); // Generar el Trie
        db->saveTrieToFile(trieFile); // Guardar el Trie en el archivo
    } else {
        load_data();
        cout << "Loading trie from file..." << endl;
        db->loadTrieFromFile(trieFile); // Cargar el Trie desde el archivo
    }

    string s = "";
    while (s != "exit") {
        string input;
        cout << "\nIngrese parte de la pelicula que desea buscar: ";
        getline(cin, input);

        vector<int> indexes = searchMovie(input, db);


        if (indexes.empty()) {
            cout << "No movies found for the given prefix." << endl;
        } else {
            // imprimir primeros 5 resultados
            for (int i = 0; i < 5 && i < indexes.size(); i++) {
                db->getMovies()[indexes[i]].imprimirPreview();
            }
            cout << "\n\n";
        }
    }

    return 0;
}
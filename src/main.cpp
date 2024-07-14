#include <iostream>
#include <fstream>
#include <string>
#include "headers/database.h"
#include "headers/trie.h"
#include "headers/load.h"

int main() {
    Database* db = Database::getInstance();
    string trieFile = "../datasets/trie_data.txt"; // Especifica la ruta del archivo

    // Cargar datos y generar el Trie si no existe el archivo
    ifstream infile(trieFile);
    if (!infile.good()) { // Verifica si el archivo no existe o no es accesible
        cout << "No existing trie file found. Loading data and generating trie..." << endl;
        load_data(); // Cargar datos desde el CSV
        db->generateTrie(); // Generar el Trie
        db->saveTrieToFile(trieFile); // Guardar el Trie en el archivo
    } else {
        load_data(); // Cargar datos desde el CSV
        cout << "Loading trie from file..." << endl;
        db->loadTrieFromFile(trieFile); // Cargar el Trie desde el archivo
    }

    string s = "";
    while (s != "exit") {
        cout << "Ingrese el string de la pelicula que desea buscar: ";
        cin >> s;
        vector<int> indexes = db->getTrie().getMovieIndices(s);

        if (indexes.empty()) {
            cout << "No movies found for the given prefix." << endl;
        } else {
            // imprimir primeros 5 resultados
            for (int i = 0; i < 5 && i < indexes.size(); i++) {
                db->getMovies()[indexes[i]].imprimirPreview();
            }
        }
    }

    return 0;
}

#include <iostream>
#include "headers/database.h"
#include "headers/trie.h"
#include "headers/load.h"
#include <fstream>

int main() {
    Database* db = Database::getInstance();
    string trieFile = "../datasets/trie_data.dat"; // Nombre del archivo donde se almacena el Trie

    // Cargar datos y generar el Trie si no existe el archivo
    ifstream infile(trieFile);
    if (!infile.good()) { // Verifica si el archivo no existe o no es accesible
        load_data(); // Cargar datos desde el CSV
        db->generateTrie(); // Generar el Trie
        db->saveTrieToFile(trieFile); // Guardar el Trie en el archivo
    } else {
        db->loadTrieFromFile(trieFile); // Cargar el Trie desde el archivo
    }

    string s = "";
    while (s != "exit") {
        cout << "Ingrese el string de la pelicula que desea buscar: ";
        cin >> s;
        vector<int> indexes = db->getTrie().getMovieIndices(s);

        // imprimir primeros 10 resultados
        for (int i = 0; i < 5 && i < indexes.size(); i++) {
            db->getMovies()[indexes[i]].imprimirPreview();
        }
    }

    return 0;
}

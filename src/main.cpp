#include <iostream>
#include "headers/database.h"
#include "headers/search.h"
#include "headers/trie.h"
#include "headers/ui.h"
#include "headers/utility.h"
#include "headers/load.h"


int main() {
    load_data();
    Database* db = Database::getInstance();
    db->generateTrie();

//    Trie trie;
//    trie.insert("bark", 1);
//    trie.insert("start", 2);
//    trie.insert("stark", 3);
//    trie.insert("story", 4);
//    trie.insert("artist", 5);

//    string s = "";
//    while(s != "exit"){
//        cout << "Ingrese el string de la pelicula que desea buscar: ";
//        cin >> s;
//        vector<int> a= trie.getMovieIndices(s);
//        for (auto i : a){
//            cout << i << endl;
//        }
//    }


    string s = "";
    while(s != "exit"){
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





#include <iostream>
#include "headers/database.h"
#include "headers/search.h"
#include "headers/trie.h"
#include "headers/ui.h"
#include "headers/utility.h"
#include "headers/load.h"
#include "headers/mastarde.h"

int main() {
    load_data();
    Database* db = Database::getInstance();
    db->generateTrie();

    string opcion;
    interfaz();
    cin >> opcion;

    MasTarde<Movie> EnEspera;

    if (opcion == "1"){
        string s = "";
        string v = "";
        while(s != "exit"){
            cout << "Ingrese el string de la pelicula que desea buscar: ";
            cin >> s;
            if (s == "exit")
                break;
            vector<int> indexes = db->getTrie().getMovieIndices(s);

            // imprimir primeros 10 resultados
            for (int i = 0; i < 5 && i < indexes.size(); i++) {
                db->getMovies()[indexes[i]].imprimirPreview();
            }
            cout << "Quisiera agregar alguna pelicula en Ver mas tarde? (y/n): ";
            cin >> v;
            if (v == "y"){
                cout << "Escriba el titulo de la pelicula: ";
            }
        }
    }
    else if (opcion == "2"){ // Esto seria para donde se vean los me gusta
        MisLikes();
    }
    else if (opcion == "3"){ // Y esto en ver mas tarde
        VMT();
    }

    return 0;
}



//Trie trie;
//trie.insert("bark", 1);
//trie.insert("start", 2);
//trie.insert("stark", 3);
//trie.insert("story", 4);
//trie.insert("artist", 5);
//
//string s = "";
//while(s != "exit"){
//cout << "Ingrese el string de la pelicula que desea buscar: ";
//cin >> s;
//trie.printMovieIndices(s);
//}
//

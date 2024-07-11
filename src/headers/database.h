#ifndef PROYECTO_PROGRAMACION3_DATABASE_H
#define PROYECTO_PROGRAMACION3_DATABASE_H

#include <vector>

using namespace std;

/** Entidad que representa una película. @n
 * Estructura: @n@n
 * - imdb_id: Identificador de la película en la base de datos de IMDB. @n@n
 * - title: Título de la película. @n@n
 * - plot_synopsis: Sinopsis de la película. @n@n
 * - tags: Lista de etiquetas asociadas a la película. @n@n
 * - split: División de la película en el conjunto de entrenamiento o prueba. @n@n
 * - synopsis_source: Fuente de la sinopsis de la película.
 **/
struct Movie {
    string imdb_id;
    string title;
    string plot_synopsis;
    vector<string> tags;
    string split;
    string synopsis_source;
public:
    Movie(const string &imdbId, const string &title, const string &plotSynopsis,
          const vector<string> &tags, const string &split, const string &synopsisSource):
          imdb_id(imdbId),
          title(title),
          plot_synopsis(plotSynopsis),
          tags(tags),
          split(split),
          synopsis_source(synopsisSource) {}

    void imprimirPelicula() {
        cout << "IMDB_ID: " << imdb_id << endl;
        cout << "Title: " << title << endl;
        cout << "Synopsis: " << plot_synopsis << endl;
        cout << "Split: " << split << endl;
        cout << "Synopsis Source: " << synopsis_source << endl;
        cout << "Tags: ";
        for (const string& tag : tags) {
            cout << tag << ", ";
        }
        cout << endl;
    }
    void imprimirPreview() {
        cout << "===============\n";
        cout << "IMDB_ID: " << imdb_id << endl;
        cout << "Title: " << title << endl;
        if (plot_synopsis.size() > 100) {
            cout << "Synopsis: " << plot_synopsis.substr(0, 96) << "..." << endl;
        } else {
            cout << "Synopsis: " << plot_synopsis << endl;
        }
        cout << "Split: " << split << endl;
        cout << "Synopsis Source: " << synopsis_source << endl;
        cout << "Tags: ";
        for (const string& tag : tags) {
            cout << tag << ", ";
        }
        cout << endl;
    }
};


#endif
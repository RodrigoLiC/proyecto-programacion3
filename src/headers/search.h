#ifndef PROYECTO_PROGRAMACION3_SEARCH_H
#define PROYECTO_PROGRAMACION3_SEARCH_H

vector<int> searchMovie(const string& input,Database* db){
    istringstream iss(input);
    vector<vector<int>> searchIndexes;
    string word;
    while (iss >> word) {
        searchIndexes.push_back(db->getTrie().getMovieIndices(word));
    }


//    for (int i = 0; i < searchIndexes.size(); i++) {
//        cout << "index: ";
//        for (int j = 0; j < searchIndexes[i].size(); j++) {
//            cout << searchIndexes[i][j] << " ";
//        }
//        cout << endl;
//    }

    vector<int> intersection;
    if (!searchIndexes.empty()) {
        // Start with the indices from the first word
        intersection = searchIndexes[0];

        // Find intersection with indices from subsequent words
        for (size_t i = 1; i < searchIndexes.size(); ++i) {
            vector<int> currentIndices = searchIndexes[i];
            unordered_set<int> commonIndices;

            // Insert currentIndices into unordered_set for fast lookup
            for (int index : intersection) {
                commonIndices.insert(index);
            }

            // Find common indices between current set and common set
            vector<int> newIntersection;
            for (int index : currentIndices) {
                if (commonIndices.count(index) > 0) {
                    newIntersection.push_back(index);
                }
            }

            // Update intersection to newIntersection
            intersection = newIntersection;
        }
    }

    return intersection;
}


//vector<int> indexes = db->getTrie().getMovieIndices(s);

#endif
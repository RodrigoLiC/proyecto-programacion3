#ifndef PROYECTO_PROGRAMACION3_TRIE_H
#define PROYECTO_PROGRAMACION3_TRIE_H

#include <iostream>
#include <vector>
#include <unordered_set>

using namespace std;

struct TrieNode {
    TrieNode* childNode[26];
    unordered_set<int> movieIndices;
    char value;

    TrieNode(char value) : value(value){

        for (int i = 0; i < 26; i++) {
            childNode[i] = NULL;
        }
    }
};

class Trie {
private:
    TrieNode* root;

public:
    Trie() {
        root = new TrieNode(' ');
    }

    void insert(const string& word, int index) {
        for (int i = 0; i < word.size(); i++) {
            insertPrefix(word.substr(i), index);
        }
    }


    void insertPrefix(const string& word, int index) {
        TrieNode* current = root;

        for (char c : word) {
            int i = c - 'a';
            if (current->childNode[i] == nullptr) {
                current->childNode[i] = new TrieNode(c);
            }
            current = current->childNode[i];
            current->movieIndices.insert(index);
        }
    }

    TrieNode* getRoot(){
        return root;
    }

    vector<int> getMovieIndices(const string& word) {
        TrieNode* current = root;

        for (char c : word) {
            int i = c - 'a';
            if (current->childNode[i] == nullptr) {
                // If the path for the word does not exist in the Trie
                cout << "No movies found for prefix: " << word << endl;
                vector<int> indices;
                return indices;
            }
            current = current->childNode[i];
        }
        vector<int> indices(current->movieIndices.begin(), current->movieIndices.end());
        return indices;
    }

};


#endif
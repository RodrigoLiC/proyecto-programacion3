#ifndef PROYECTO_PROGRAMACION3_TRIE_H
#define PROYECTO_PROGRAMACION3_TRIE_H

#include <iostream>
#include <vector>
#include <unordered_set>

using namespace std;

struct TrieNode {
    TrieNode* childNode[26];
    vector<int> movieIndices;
    unordered_set<int> movieIndicesSet;

    TrieNode(){
        for(auto & i : childNode) {
            i = nullptr;
        }
    }

    ~TrieNode(){
        for(auto & i : childNode) {
            delete i;
        }
    }
};

class Trie {
private:
    TrieNode* root;

public:
    Trie() {
        root = new TrieNode();
    }

    void insertPrefix(const string& word, int index) {
        TrieNode* current = root;

        for (char c : word) {
            int i = c - 'a';
            if (current->childNode[i] == nullptr) {
                current->childNode[i] = new TrieNode();
            }
            current = current->childNode[i];

            // MAX SIZE
            if (current->movieIndicesSet.size() > 100){
                continue;
            }
            else {
                if(current->movieIndicesSet.count(index) == 0){
                    current->movieIndices.push_back(index);
                    current->movieIndicesSet.insert(index);
                }
            }
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
                cout << "No movies found for prefix: " << word << endl;
                vector<int> indices;
                return indices;
            }
            current = current->childNode[i];
        }

        vector<int> vec = current->movieIndices;
        return vec;
    }

};


#endif
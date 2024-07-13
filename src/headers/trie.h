#ifndef PROYECTO_PROGRAMACION3_TRIE_H
#define PROYECTO_PROGRAMACION3_TRIE_H

#include <iostream>
#include <vector>
#include <unordered_set>
#include <mutex>

using namespace std;

struct TrieNode {
    TrieNode* childNode[26];
    unordered_set<int> movieIndices;
    mutex nodeMutex;

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
            lock_guard<mutex> lock(current->nodeMutex);
            if (current->childNode[i] == nullptr) {
                current->childNode[i] = new TrieNode();
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
                cout << "No movies found for prefix: " << word << endl;
                vector<int> indices;
                return indices;
            }
            current = current->childNode[i];
        }

        vector<int> res(current->movieIndices.begin(), current->movieIndices.end());
        return res;
    }
};


#endif
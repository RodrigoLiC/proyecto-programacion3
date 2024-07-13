#ifndef PROYECTO_PROGRAMACION3_TRIE_H
#define PROYECTO_PROGRAMACION3_TRIE_H

#include <iostream>
#include <vector>
#include <unordered_set>
#include <fstream>

using namespace std;

struct TrieNode {
    TrieNode* childNode[26];
    vector<int> movieIndices;
    unordered_set<int> movieIndicesSet;

    TrieNode() {
        for (auto &i : childNode) {
            i = nullptr;
        }
    }

    ~TrieNode() {
        for (auto &i : childNode) {
            delete i;
        }
    }
};

class Trie {
private:
    TrieNode* root;

    void saveTrieNode(TrieNode* node, ofstream& file) {
        if (!node) return;
        for (int i = 0; i < 26; i++) {
            if (node->childNode[i]) {
                file.put('1');
                saveTrieNode(node->childNode[i], file);
            } else {
                file.put('0');
            }
        }
        size_t size = node->movieIndices.size();
        file.write(reinterpret_cast<const char*>(&size), sizeof(size));
        for (int index : node->movieIndices) {
            file.write(reinterpret_cast<const char*>(&index), sizeof(index));
        }
    }

    TrieNode* loadTrieNode(ifstream& file) {
        TrieNode* node = new TrieNode();
        for (int i = 0; i < 26; i++) {
            char c;
            file.get(c);
            if (c == '1') {
                node->childNode[i] = loadTrieNode(file);
            } else {
                node->childNode[i] = nullptr;
            }
        }
        size_t size;
        file.read(reinterpret_cast<char*>(&size), sizeof(size));
        node->movieIndices.resize(size);
        for (size_t i = 0; i < size; i++) {
            int index;
            file.read(reinterpret_cast<char*>(&index), sizeof(index));
            node->movieIndices[i] = index;
            node->movieIndicesSet.insert(index);
        }
        return node;
    }

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
            if (current->movieIndicesSet.size() > 100) {
                continue;
            } else {
                if (current->movieIndicesSet.count(index) == 0) {
                    current->movieIndices.push_back(index);
                    current->movieIndicesSet.insert(index);
                }
            }
        }
    }

    TrieNode* getRoot() {
        return root;
    }

    vector<int> getMovieIndices(const string& word) {
        TrieNode* current = root;
        for (char c : word) {
            int i = c - 'a';
            if (current->childNode[i] == nullptr) {
                return vector<int>();
            }
            current = current->childNode[i];
        }
        return current->movieIndices;
    }

    void saveTrie(const string& filename) {
        ofstream file(filename, ios::binary);
        if (!file.is_open()) {
            cerr << "Failed to open file for saving Trie." << endl;
            return;
        }
        saveTrieNode(root, file);
        file.close();
    }

    void loadTrie(const string& filename) {
        ifstream file(filename, ios::binary);
        if (!file.is_open()) {
            cerr << "Failed to open file for loading Trie." << endl;
            return;
        }
        root = loadTrieNode(file);
        file.close();
    }
};

#endif // PROYECTO_PROGRAMACION3_TRIE_H

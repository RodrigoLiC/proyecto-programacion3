//src/headers/trie.h
#ifndef PROYECTO_PROGRAMACION3_TRIE_H
#define PROYECTO_PROGRAMACION3_TRIE_H

#include <vector>
#include <unordered_set>
#include <fstream>
#include <sstream>
#include <map>
#include <mutex>

#include "utility.h"

struct TrieNode {
    TrieNode* childNode[26]{};
    vector<int> movieIndices;
    unordered_set<int> movieIndicesSet;
    mutex nodeMutex;

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

    void collectWords(TrieNode* node, const string& word, map<string, vector<int>>& wordMap) {
        if (!node) return;
        if (!node->movieIndices.empty()) {
            wordMap[word] = node->movieIndices;
        }
        for (int i = 0; i < 26; i++) {
            if (node->childNode[i]) {
                collectWords(node->childNode[i], word + char('a' + i), wordMap);
            }
        }
    }

public:
    Trie() : root(new TrieNode()) {}

    void insertPrefix(const string& word, int index) {
        TrieNode* current = root;
        for (char c : word) {
            int i = c - 'a';
            lock_guard<mutex> lock(current->nodeMutex);
            if (current->childNode[i] == nullptr) {
                current->childNode[i] = new TrieNode();
            }
            current = current->childNode[i];
            if (current->movieIndicesSet.size() > 100000) {
                continue;
            } else {
                if (current->movieIndicesSet.count(index) == 0) {
                    current->movieIndices.push_back(index);
                    current->movieIndicesSet.insert(index);
                }
            }
        }
    }

    void insertWord(const string& word, int index) {
        TrieNode* current = root;
        for (char c : word) {
            int i = c - 'a';
            lock_guard<mutex> lock(current->nodeMutex);
            if (current->childNode[i] == nullptr) {
                current->childNode[i] = new TrieNode();
            }
            current = current->childNode[i];
        }
        lock_guard<mutex> lock(current->nodeMutex);
        if (current->movieIndicesSet.count(index) == 0) {
            current->movieIndices.push_back(index);
            current->movieIndicesSet.insert(index);
        }
    }

    TrieNode* getRoot() const {
        return root;
    }

    vector<int> getMovieIndices(const string& word) const {
        TrieNode* current = root;
        string parsed_word = toAlphabet(word);
        for (char c : parsed_word) {
            int i = c - 'a';
            if (current->childNode[i] == nullptr) {
                cout << "No movies found for prefix: " << parsed_word << endl;
                return vector<int>();
            }
            current = current->childNode[i];
        }
        return current->movieIndices;
    }

    void saveTrie(const string& filename) {
        ofstream file(filename);
        if (!file.is_open()) {
            cerr << "Failed to open file for saving Trie." << endl;
            return;
        }

        map<string, vector<int>> wordMap;
        collectWords(root, "", wordMap);

        for (const auto& pair : wordMap) {
            file << pair.first << "<";
            for (size_t i = 0; i < pair.second.size(); ++i) {
                file << pair.second[i];
                if (i != pair.second.size() - 1) {
                    file << ",";
                }
            }
            file << "\n";
        }
        file.close();
    }

    void loadTrie(const string& filename) {
        ifstream file(filename);
        if (!file.is_open()) {
            cerr << "Failed to open file for loading Trie." << endl;
            return;
        }

        string line;
        int count = 0;
        cout << "Words loaded (chunks of 50k):\n";
        while (getline(file, line)) {
            if (line.empty()) continue;
            size_t pos = line.find('<');
            string word = line.substr(0, pos);
            string indicesStr = line.substr(pos + 1);
            stringstream ss(indicesStr);
            string indexStr;
            while (getline(ss, indexStr, ',')) {
                int index = stoi(indexStr);
                insertWord(word, index);
            }
            count++;
            if (count % 50000 == 0) {
                cout << "|";
            }
        }
        file.close();
    }
};

#endif
//src/headers/trie.h
#ifndef PROYECTO_PROGRAMACION3_TRIE_H
#define PROYECTO_PROGRAMACION3_TRIE_H

#include <vector>
#include <unordered_set>
#include <fstream>
#include <sstream>
#include <map>
#include <mutex>

struct TrieNode {
    TrieNode* childNode[26]{};
    std::vector<int> movieIndices;
    std::unordered_set<int> movieIndicesSet;
    std::mutex nodeMutex;

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

    void collectWords(TrieNode* node, const std::string& word, std::map<std::string, std::vector<int>>& wordMap) {
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

    void insertPrefix(const std::string& word, int index) {
        TrieNode* current = root;
        for (char c : word) {
            int i = c - 'a';
            std::lock_guard<std::mutex> lock(current->nodeMutex);
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

    void insertWord(const std::string& word, int index) {
        TrieNode* current = root;
        for (char c : word) {
            int i = c - 'a';
            std::lock_guard<std::mutex> lock(current->nodeMutex);
            if (current->childNode[i] == nullptr) {
                current->childNode[i] = new TrieNode();
            }
            current = current->childNode[i];
        }
        std::lock_guard<std::mutex> lock(current->nodeMutex);
        if (current->movieIndicesSet.count(index) == 0) {
            current->movieIndices.push_back(index);
            current->movieIndicesSet.insert(index);
        }
    }

    TrieNode* getRoot() const {
        return root;
    }

    std::vector<int> getMovieIndices(const std::string& word) const {
        TrieNode* current = root;
        for (char c : word) {
            int i = c - 'a';
            if (current->childNode[i] == nullptr) {
                std::cout << "No movies found for prefix: " << word << std::endl;
                return std::vector<int>();
            }
            current = current->childNode[i];
        }
        return current->movieIndices;
    }

    void saveTrie(const std::string& filename) {
        std::ofstream file(filename);
        if (!file.is_open()) {
            std::cerr << "Failed to open file for saving Trie." << std::endl;
            return;
        }

        std::map<std::string, std::vector<int>> wordMap;
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

    void loadTrie(const std::string& filename) {
        std::ifstream file(filename);
        if (!file.is_open()) {
            std::cerr << "Failed to open file for loading Trie." << std::endl;
            return;
        }

        std::string line;
        while (getline(file, line)) {
            if (line.empty()) continue;
            size_t pos = line.find('<');
            std::string word = line.substr(0, pos);
            std::string indicesStr = line.substr(pos + 1);
            std::stringstream ss(indicesStr);
            std::string indexStr;
            while (getline(ss, indexStr, ',')) {
                int index = std::stoi(indexStr);
                insertPrefix(word, index);
            }
        }
        file.close();
    }
};

#endif
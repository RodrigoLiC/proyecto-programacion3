#ifndef PROYECTO_PROGRAMACION3_TRIE_H
#define PROYECTO_PROGRAMACION3_TRIE_H


struct TrieNode {
    // pointer array for child nodes of each node
    TrieNode* childNode[26];

    // Used for indicating ending of string
    bool wordEnd;

    TrieNode()
    {
        wordEnd = false;
        for (int i = 0; i < 26; i++) {
            childNode[i] = NULL;
        }
    }
};

#endif
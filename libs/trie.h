// Trie Header

#ifndef TRIE_H
#define TRIE_H

#include <iostream>
#include "dag.h"

using namespace std;

const int ALPHABET_SIZE = 36;

class TrieNode {
    private:
        TrieNode* children[ALPHABET_SIZE];
        DAGNode* person;

    public:
        TrieNode();

    friend class Trie;
};

class Trie {
    private:
        TrieNode* root;

        int getIndex(char chr);

    public:
        Trie();

        void insert(const string& value, DAGNode* person);

        DAGNode* search(const string& value);
};

#endif
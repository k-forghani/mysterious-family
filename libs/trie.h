// Trie Header

#ifndef TRIE_H
#define TRIE_H

#include <iostream>
#include "dag.h"

using namespace std;

const int ALPHABET_SIZE = 36;

class DAGNode;

class TrieNode {
    private:
        TrieNode* children[ALPHABET_SIZE];
        DAGNode* person;

    public:
        TrieNode();

        ~TrieNode();

        bool hasNoChildren();

    friend class Trie;
};

class Trie {
    private:
        TrieNode* root;

        int getIndex(char chr);

        TrieNode* removeHelper(TrieNode* node, const string& value, int depth);

    public:
        Trie();

        void insert(const string& value, DAGNode* person);

        void remove(const string& value);

        DAGNode* search(const string& value);
};

#endif
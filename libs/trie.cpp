// Trie Implementation

#include <iostream>
#include "trie.h"

using namespace std;

#pragma region TrieNode

    TrieNode::TrieNode() : person(nullptr) {
        for (int i = 0; i < ALPHABET_SIZE; i++) {
            children[i] = nullptr;
        }
    }

    TrieNode::~TrieNode() {

    }

    bool TrieNode::hasNoChildren() {
        for (int i = 0; i < ALPHABET_SIZE; ++i) {
            if (this->children[i] != nullptr) {
                return false;
            }
        }
        return true;
    }

#pragma endregion

#pragma region Trie

    int Trie::getIndex(char chr) {
        if (isdigit(chr)) {
            return chr - '0' + 26;
        } else {
            return chr - 'a';
        }
    }

    TrieNode* Trie::removeHelper(TrieNode* node, const string& value, DAGNode*& person, int depth) {
        if (node == nullptr) {
            return nullptr;
        }

        if (depth == value.length()) {
            person = node->person;
            node->person = nullptr;

            if (node->hasNoChildren()) {
                delete node;
                return nullptr;
            }

            return nullptr;
        } else {
            int index = getIndex(value[depth]);
            node->children[index] = removeHelper(node->children[index], value, person, depth + 1);
        }

        if (node->hasNoChildren() && node->person == nullptr && depth > 0) {
            delete node;
            return nullptr;
        }

        return node;
    }

    Trie::Trie() {
        root = new TrieNode();
    }

    void Trie::insert(const string& value, DAGNode* person) {
        TrieNode* current = root;
        for (char ch : value) {
            int index = getIndex(ch);
            if (!current->children[index]) {
                current->children[index] = new TrieNode();
            }
            current = current->children[index];
        }
        current->person = person;
    }

    DAGNode* Trie::remove(const string& value) {
        DAGNode* person = nullptr;
        root = removeHelper(root, value, person, 0);
        return person;
    }

    DAGNode* Trie::search(const string& value) {
        TrieNode* current = root;

        for (char chr : value) {
            int index = getIndex(chr);
            if (!current->children[index]) {
                return nullptr;
            }
            current = current->children[index];
        }
        return current->person;
    }

    void Trie::getAllLeaves(TrieNode* node, vector<DAGNode*>& result) {
        if (!node) {
            return;
        }

        if (node->person) {
            result.push_back(node->person);
        }

        for (int i = 0; i < ALPHABET_SIZE; i++) {
            getAllLeaves(node->children[i], result);
        }
    }

    vector<DAGNode*> Trie::getAllLeaves() {
        vector<DAGNode*> result;
        getAllLeaves(root, result);
        return result;
    }


#pragma endregion
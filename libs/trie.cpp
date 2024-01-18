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

#pragma endregion

#pragma region Trie

    int Trie::getIndex(char chr) {
        if (isdigit(chr)) {
            return chr - '0' + 26;
        } else {
            return chr - 'a';
        }
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

#pragma endregion
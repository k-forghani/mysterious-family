// Directed Acyclic Graph Header

#ifndef DAG_H
#define DAG_H

#include <iostream>
#include <vector>
#include "trie.h"

using namespace std;

class DAGNode {
    private:
        string id;
        DAGNode* father;
        DAGNode* mother;
        vector<DAGNode*> children;

    public:
        DAGNode(string id);

        ~DAGNode();

        DAGNode* getFather() const;

        DAGNode* getMother() const;

        void linkToParents(DAGNode* father, DAGNode* mother);

        void linkChild(DAGNode* target);

        void unlinkChild(DAGNode* target);

        bool isSourceNode();
};

class DAG {
    private:
        vector<DAGNode*> sourceNodes;

    public:
        DAG();

        DAGNode* newNode(string id, DAGNode* father = nullptr, DAGNode* mother = nullptr);

        void deleteNode(DAGNode* target);
};

#endif
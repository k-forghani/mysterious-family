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

    public:
        vector<DAGNode*> children;
        
        DAGNode(string id);

        ~DAGNode();

        DAGNode* getFather() const;

        DAGNode* getMother() const;

        string getID() const;

        void linkToParents(DAGNode* father, DAGNode* mother);

        void linkChild(DAGNode* target);

        void unlinkChild(DAGNode* target);

        bool searchInChildren(string target, bool recursively = false);

        void getMostDistanceFromChildren(int& distance) const;

        bool isSourceNode();

        void getAncestors(vector<DAGNode*>& ancestors);

        void traverseUpTo(DAGNode*& breakNode, vector<DAGNode*> nodes);
};

class DAG {
    private:
        vector<DAGNode*> sourceNodes;

    public:
        DAG();

        DAGNode* newNode(string id, DAGNode* father = nullptr, DAGNode* mother = nullptr);

        void deleteNode(DAGNode* target);

        DAGNode* findLowestCommonAncesotor(DAGNode* firstNode, DAGNode* secondNode);
};

#endif
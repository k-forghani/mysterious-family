// Directed Acyclic Graph Header

#ifndef DAG_H
#define DAG_H

#include <iostream>
#include <vector>
#include <unordered_set>
#include "trie.h"

using namespace std;

class DAGNode {
    private:
        string id;
        string name;
        DAGNode* father;
        DAGNode* mother;

    public:
        vector<DAGNode*> children;
        
        DAGNode(string id, string name = "");

        void destruct(unordered_set<DAGNode*>& visitedNodes);

        DAGNode* getFather() const;

        DAGNode* getMother() const;

        vector<DAGNode*> getChildren() const;

        string getID() const;

        string getName() const;

        bool isSourceNode() const;

        void linkToParents(DAGNode* father, DAGNode* mother);

        void linkChild(DAGNode* target);

        void unlinkChild(DAGNode* target);

        bool searchInChildren(string target, bool recursively = false);

        void getMostDistanceFromChildren(int& distance) const;

        void getAncestors(vector<DAGNode*>& ancestors);

        void traverseUpTo(DAGNode*& breakNode, vector<DAGNode*> nodes);

        DAGNode* findFarthestNode();
};

class DAG {
    private:
        vector<DAGNode*> sourceNodes;

    public:
        DAG();

        DAGNode* createNode(string id, string name = "", DAGNode* father = nullptr, DAGNode* mother = nullptr);

        vector<string> deleteNode(DAGNode* target);

        DAGNode* findLowestCommonAncesotor(DAGNode* firstNode, DAGNode* secondNode);

        pair<DAGNode*, DAGNode*> getLongestRelationship();
};

#endif
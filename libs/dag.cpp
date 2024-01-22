// Directed Acyclic Graph Implementation

#include <iostream>
#include <vector>
#include <algorithm>
#include "dag.h"

using namespace std;

#pragma region DAGNode

    DAGNode::DAGNode(string id) : id(id) {
        father = mother = nullptr;
    }

    DAGNode::~DAGNode() {
        if (father)
            father -> unlinkChild(this);
        
        if (mother)
            mother -> unlinkChild(this);

        for (auto &&child : children) {
            delete child;
        }
    }

    DAGNode* DAGNode::getFather() const {
        return father;
    }

    DAGNode* DAGNode::getMother() const {
        return mother;
    }

    string DAGNode::getID() const {
        return id;
    }

    void DAGNode::linkToParents(DAGNode* father, DAGNode* mother) {
        this -> father = father;
        this -> mother = mother;

        if (this -> father)
            this -> father -> linkChild(this);

        if (this -> mother)
            this -> mother -> linkChild(this);
    }

    void DAGNode::linkChild(DAGNode* target) {
        if (target)
            children.push_back(target);
    }

    void DAGNode::unlinkChild(DAGNode* target) {
        auto cursor = children.begin();
        auto end = children.end();

        while (cursor != end) {
            if (*cursor == target) {
                children.erase(cursor);
                break;
            } else {
                cursor++;
            }
        }
    }

    bool DAGNode::searchInChildren(string target, bool recursively) {
        bool isFound = false;

        for (auto &&child : children) {
            if (child->getID() == target) {
                isFound = true;
                break;
            }
            if (recursively)
                isFound = isFound || child->searchInChildren(target, true);
        }

        return isFound;
    }

    void DAGNode::getMostDistanceFromChildren(int& distance) const {
        int dist = 0;
        for (auto &&child : children) {
            int temp;
            child->getMostDistanceFromChildren(temp);
            if (temp > dist)
                dist = temp;
        }
        distance = dist;
        if (!children.empty())
            distance++;
    }

    void DAGNode::getAncestors(vector<DAGNode*>& ancestors) {
        if (father) {
            ancestors.push_back(father);
            ancestors.push_back(mother);
        }
        
        if (father) {
            father->getAncestors(ancestors);
            mother->getAncestors(ancestors);
        }
    }

    void DAGNode::traverseUpTo(DAGNode*& breakNode, vector<DAGNode*> nodes) {
        if (count(nodes.begin(), nodes.end(), this) > 0) {
            breakNode = this;
            return;
        }
        
        if (father) {
            father->traverseUpTo(breakNode, nodes);
            mother->traverseUpTo(breakNode, nodes);
        }
    }

    bool DAGNode::isSourceNode() {
        return father == nullptr && mother == nullptr;
    }

#pragma endregion

#pragma region DAG

    DAG::DAG() {

    }

    DAGNode* DAG::newNode(string id, DAGNode* father, DAGNode* mother) {
        DAGNode* node = new DAGNode(id);
        node->linkToParents(father, mother);

        if (!father && !mother) {
            sourceNodes.push_back(node);
        }

        return node;
    }

    void DAG::deleteNode(DAGNode* target) {
        auto cursor = sourceNodes.begin();
        auto end = sourceNodes.end();

        while (cursor != end) {
            if (*cursor == target) {
                cursor = sourceNodes.erase(cursor);
                break;
            } else {
                cursor++;
            }
        }

        delete target;
    }

    DAGNode* DAG::findLowestCommonAncesotor(DAGNode* firstNode, DAGNode* secondNode) {
        if (!firstNode || !secondNode)
            return nullptr;

        vector<DAGNode*> firstNodeParents;

        firstNode->getAncestors(firstNodeParents);

        DAGNode* lca = nullptr;

        secondNode->traverseUpTo(lca, firstNodeParents);

        return lca;
    }

#pragma endregion
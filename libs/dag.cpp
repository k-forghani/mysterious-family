// Directed Acyclic Graph Implementation

#include <iostream>
#include <vector>
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


#pragma endregion
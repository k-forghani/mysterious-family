// Directed Acyclic Graph Implementation

#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_set>
#include <queue>
#include "dag.h"

using namespace std;

#pragma region DAGNode

    DAGNode::DAGNode(string id, string name) : id(id), name(name) {
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

    vector<DAGNode*> DAGNode::getChildren() const {
        return children;
    }

    string DAGNode::getID() const {
        return id;
    }

    string DAGNode::getName() const {
        return name;
    }

    bool DAGNode::isSourceNode() const {
        return father == nullptr && mother == nullptr;
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

    DAGNode* DAGNode::findFarthestNode() {
        unordered_set<DAGNode*> visitedNodes;
        queue<pair<DAGNode*, int>> nodesQueue;

        nodesQueue.push({this, 0});
        visitedNodes.insert(this);

        DAGNode* farthestNode = this;
        int maxDistance = 0;

        while (!nodesQueue.empty()) {
            auto current = nodesQueue.front();
            nodesQueue.pop();

            vector<DAGNode*> neighbors;

            neighbors.push_back(current.first->getFather());
            neighbors.push_back(current.first->getMother());

            for (auto &&child : current.first->getChildren()) {
                neighbors.push_back(child);
            }

            for (auto neighbor : neighbors) {
                if (neighbor && visitedNodes.find(neighbor) == visitedNodes.end()) {
                    nodesQueue.push(
                        make_pair(neighbor, current.second + 1)
                    );
                    visitedNodes.insert(neighbor);

                    if (current.second + 1 > maxDistance) {
                        maxDistance = current.second + 1;
                        farthestNode = neighbor;
                    }
                }
            }
        }

        return farthestNode;
    }

#pragma endregion

#pragma region DAG

    DAG::DAG() {

    }

    DAGNode* DAG::createNode(string id, string name, DAGNode* father, DAGNode* mother) {
        DAGNode* node = new DAGNode(id, name);
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

    pair<DAGNode*, DAGNode*> DAG::getLongestRelationship() {
        if (sourceNodes.empty()) {
            return make_pair(nullptr, nullptr);
        }

        DAGNode* startNode = sourceNodes[0];

        DAGNode* firstNode = startNode->findFarthestNode();

        DAGNode* secondNode = firstNode->findFarthestNode();

        return make_pair(firstNode, secondNode);
    }

#pragma endregion
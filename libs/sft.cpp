// Secure Family Tree Implementation

#include <iostream>
#include <map>
#include <jsoncpp/json/json.h>
#include "sft.h"

using namespace std;


#pragma region SFT

    SFT::SFT () : count(0) {
        trie = new Trie();
        dag = new DAG();
    }

    void SFT::addPerson (string name, string fatherID, string motherID) {
        string id = name;

        DAGNode* father = trie->search(fatherID);
        DAGNode* mother = trie->search(motherID);

        DAGNode* person = dag->newNode(id, father, mother);

        trie->insert(id, person);

        count++;
    }

    bool SFT::findPerson (string id) {
        DAGNode* person = trie->search(id);
        return person != nullptr;
    }

    void SFT::deletePerson (string id) {
        DAGNode* person = trie->remove(id);
        dag->deleteNode(person);
        count--;
    }

    int SFT::getPersonsCount () {
        return count;
    }

    bool SFT::isAncestor (string ancestor, string child) {
        DAGNode* ancestorObject = trie->search(ancestor);
        if (ancestorObject)
            return ancestorObject->searchInChildren(child, true);
        return false;
    }

    bool SFT::areSiblings (string firstPerson, string secondPerson) {
        DAGNode* firstPersonObject = trie->search(firstPerson);

        if (firstPersonObject) {
            return firstPersonObject->getFather()->searchInChildren(secondPerson) || firstPersonObject->getMother()->searchInChildren(secondPerson);
        }

        return false;
    }

    bool SFT::haveExtendedRelationship (string firstPerson, string secondPerson) {
        DAGNode* firstPersonObject = trie->search(firstPerson);
        DAGNode* secondPersonObject = trie->search(secondPerson);

        if (!firstPersonObject || !secondPersonObject) {
            return false;
        }
        
        if (firstPersonObject->searchInChildren(secondPerson, true) || secondPersonObject->searchInChildren(firstPerson, true)) {
            return false;
        }

        DAGNode* lca = dag->findLowestCommonAncesotor(firstPersonObject, secondPersonObject);

        return lca != nullptr;
    }

    string SFT::getLowsetCommonAncestor (string firstPerson, string secondPerson) {
        DAGNode* firstPersonObject = trie->search(firstPerson);
        DAGNode* secondPersonObject = trie->search(secondPerson);
        DAGNode* lca = dag->findLowestCommonAncesotor(firstPersonObject, secondPersonObject);
        if (lca)
            return lca->getID();
        else
            return "";
    }

    int SFT::getMostDistanceFromChildren (string person) {
        DAGNode* personObject = trie->search(person);

        int distance;
        personObject->getMostDistanceFromChildren(distance);

        return distance;
    }

    pair<string, string> SFT::getMostDistantRelationship () {
        pair<DAGNode*, DAGNode*> farthestNodes = dag->getMostDistantRelationship();

        if (!farthestNodes.first || !farthestNodes.second) {
            return make_pair("", "");
        }

        return make_pair(
            farthestNodes.first->getID(),
            farthestNodes.second->getID()
        );
    }

    string SFT::toJSON() const {
        vector<DAGNode*> nodes = trie->getAllLeaves();
        
        Json::Value json;

        Json::Value jsonNodes;
        Json::Value jsonEdges;

        Json::Value jsonData;
        jsonData["data"] = "";

        for (auto &&node : nodes) {
            Json::Value jsonNode;
            jsonNode["id"] = node->getID();
            jsonNode["name"] = node->getID();
            jsonData["data"] = jsonNode;
            jsonNodes.append(jsonData);
            
            for (auto &&child : node->children) {
                Json::Value jsonEdge;
                jsonEdge["source"] = node->getID();
                jsonEdge["target"] = child->getID();
                jsonData["data"] = jsonEdge;
                jsonEdges.append(jsonData);
            }
        }

        json["nodes"] = jsonNodes;
        json["edges"] = jsonEdges;
        
        Json::StreamWriterBuilder writer;
        string jsonString = Json::writeString(writer, json);

        return jsonString;
    }

#pragma endregion
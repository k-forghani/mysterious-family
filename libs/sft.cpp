// Secure Family Tree Implementation

#include <iostream>
#include <map>
#include <jsoncpp/json/json.h>
#include "sft.h"
#include "sha256.h"

using namespace std;

#pragma region SFT

    string SFT::encrypt(string value) const {
        if (value.empty()) {
            return "";
        }

        SHA256 sha256;
        sha256.update(value);
        std::array<uint8_t, 32> digest = sha256.digest();
        return SHA256::toString(digest);
    }

    SFT::SFT(bool doesEncrypt) : count(0), doesEncrypt(doesEncrypt) {
        trie = new Trie();
        dag = new DAG();
    }

    SFT::~SFT() {
        delete trie;
        delete dag;
    }

    string SFT::addPerson(string id, string fatherID, string motherID, string name) {
        if (fatherID == motherID) {
            return "";
        }

        if (doesEncrypt) {
            id = encrypt(id);
            name = encrypt(name);
            fatherID = encrypt(fatherID);
            motherID = encrypt(motherID);
        }

        if (id.empty()) {
            return "";
        }

        DAGNode* father = nullptr;
        DAGNode* mother = nullptr;

        if (!fatherID.empty()) {
            father = trie->search(fatherID);
            if (!father) {
                return "";
            }
        }

        if (!motherID.empty()) {
            mother = trie->search(motherID);
            if (!mother) {
                return "";
            }
        }

        if (trie->search(id)) {
            return "";
        }

        DAGNode* person = dag->createNode(id, name, father, mother);

        trie->insert(id, person);

        count++;

        return id;
    }

    bool SFT::findPerson(string id) {
        if (doesEncrypt) {
            id = encrypt(id);
        }

        DAGNode* person = trie->search(id);
        return person != nullptr;
    }

    void SFT::deletePerson(string id) {
        if (doesEncrypt) {
            id = encrypt(id);
        }

        DAGNode* person = trie->remove(id);

        if (!person) {
            return;
        }
        
        vector<string> toDeleteNodes = dag->deleteNode(person);

        for (auto &&nodeID : toDeleteNodes) {
            trie->remove(nodeID);
        }
        
        count--;
    }

    int SFT::getPersonsCount() {
        return count;
    }

    bool SFT::isAncestor(string ancestor, string child) {
        if (doesEncrypt) {
            ancestor = encrypt(ancestor);
            child = encrypt(child);
        }

        DAGNode* ancestorObject = trie->search(ancestor);
        if (ancestorObject)
            return ancestorObject->searchInChildren(child, true);
        return false;
    }

    bool SFT::areSiblings(string firstPerson, string secondPerson) {
        if (doesEncrypt) {
            firstPerson = encrypt(firstPerson);
            secondPerson = encrypt(secondPerson);
        }

        DAGNode* firstPersonObject = trie->search(firstPerson);

        if (firstPersonObject) {
            DAGNode* father = firstPersonObject->getFather();
            DAGNode* mother = firstPersonObject->getMother();
            return (father && father->searchInChildren(secondPerson)) || (mother && mother->searchInChildren(secondPerson));
        }

        return false;
    }

    bool SFT::haveExtendedRelationship(string firstPerson, string secondPerson) {
        if (doesEncrypt) {
            firstPerson = encrypt(firstPerson);
            secondPerson = encrypt(secondPerson);
        }

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

    string SFT::getLowsetCommonAncestor(string firstPerson, string secondPerson) {
        if (doesEncrypt) {
            firstPerson = encrypt(firstPerson);
            secondPerson = encrypt(secondPerson);
        }

        DAGNode* firstPersonObject = trie->search(firstPerson);
        DAGNode* secondPersonObject = trie->search(secondPerson);
        DAGNode* lca = dag->findLowestCommonAncesotor(firstPersonObject, secondPersonObject);
        if (lca)
            return lca->getID();
        else
            return "";
    }

    int SFT::getMostDistanceFromChildren(string person) {
        if (doesEncrypt) {
            person = encrypt(person);
        }

        DAGNode* personObject = trie->search(person);

        if (!personObject) {
            return -1;
        }

        int distance;
        personObject->getMostDistanceFromChildren(distance);

        return distance;
    }

    pair<string, string> SFT::getLongestRelationship() {
        pair<DAGNode*, DAGNode*> farthestNodes = dag->getLongestRelationship();

        if (!farthestNodes.first || !farthestNodes.second) {
            return make_pair("", "");
        }

        return make_pair(
            farthestNodes.first->getID(),
            farthestNodes.second->getID()
        );
    }

    string SFT::toJSON(bool oneline) const {
        vector<DAGNode*> nodes = trie->getAllLeaves();
        
        Json::Value json;

        Json::Value jsonNodes;
        Json::Value jsonEdges;

        Json::Value jsonData;
        jsonData["data"] = "";

        for (auto &&node : nodes) {
            Json::Value jsonNode;
            jsonNode["id"] = node->getID();
            jsonNode["name"] = node->getName();
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
        
        if (oneline) {
            writer["indentation"] = "";
        }

        string jsonString = Json::writeString(writer, json);

        return jsonString;
    }

#pragma endregion
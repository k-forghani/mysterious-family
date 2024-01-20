// Secure Family Tree Implementation

#include <iostream>
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

        DAGNode* person = new DAGNode(id);

        person->linkToParents(father, mother);

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
        return ancestorObject->searchInChildren(child);
    }

    bool SFT::areSiblings (string firstPerson, string secondPerson) {
        return false;
    }

    bool SFT::haveExtendedRelationship (string firstPerson, string secondPerson) {
        return false;
    }

    string SFT::getLowsetCommonAncestor (string firstPerson, string secondPerson) {
        return "";
    }

    int SFT::getMostDistanceFromChildren (string person) {
        return 0;
    }

    pair<string, string> SFT::getMostDistantRelationship () {
        return make_pair("", "");
    }


#pragma endregion
// Secure Family Tree Implementation

#include <iostream>
#include "sft.h"

using namespace std;


#pragma region SFT

    SFT::SFT () {
        trie = new Trie();
        dag = new DAG();
    }

    void SFT::addPerson (string name, string fatherID, string motherID) {
        string id = name;

        DAGNode* father = trie->search(fatherID);
        DAGNode* mother = trie->search(motherID);

        DAGNode* person = new DAGNode(id);

        person->linkToParents(father, mother);

        trie -> insert(id, person);
    }

    bool SFT::findPerson (string id) {
        return false;
    }

    void SFT::deletePerson (string id) {

    }

    int SFT::getPersonsCount () {
        return 0;
    }

    bool SFT::isParent (string parent, string child) {
        return false;
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
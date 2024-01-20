// Secure Family Tree Header

#ifndef SFT_H
#define SFT_H

#include <iostream>
#include "dag.h"
#include "trie.h"

class SFT {
    private:
        Trie* trie;
        DAG* dag;

        int count;

    public:
        SFT();

        void addPerson(string name, string fatherID = "", string motherID = "");

        bool findPerson(string id);

        void deletePerson(string id);

        int getPersonsCount();

        bool isAncestor(string ancestor, string child);

        bool areSiblings(string firstPerson, string secondPerson);

        bool haveExtendedRelationship(string firstPerson, string secondPerson);

        string getLowsetCommonAncestor(string firstPerson, string secondPerson);

        int getMostDistanceFromChildren(string person);

        pair<string, string> getMostDistantRelationship();
};

#endif
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

    public:
        SFT();

        void addPerson(string id);

        bool findPerson(string id);

        void deletePerson(string id);

        int getPersonsCount();

        bool isParent(string parent, string child);

        bool areSiblings(string firstPerson, string secondPerson);

        bool haveExtendedRelationship(string firstPerson, string secondPerson);

        string getLowsetCommonAncestor(string firstPerson, string secondPerson);

        int getMostDistanceFromChildren(string person);

        pair<string, string> getMostDistantRelationship();
};

#endif SFT_H
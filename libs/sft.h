// Secure Family Tree Header

#ifndef SFT_H
#define SFT_H

#include <iostream>
#include "dag.h"
#include "trie.h"
#include "sha256.h"

class SFT {
    private:
        Trie* trie;
        DAG* dag;

        bool doesEncrypt;
        int count;

        string encrypt(string value) const;

    public:
        SFT(bool doesEncrypt = false);

        ~SFT();

        string addPerson(string id, string fatherID = "", string motherID = "", string name = "");

        bool findPerson(string id);

        bool deletePerson(string id);

        int getPersonsCount();

        bool isAncestor(string ancestor, string child);

        bool areSiblings(string firstPerson, string secondPerson);

        bool haveExtendedRelationship(string firstPerson, string secondPerson);

        string getLowsetCommonAncestor(string firstPerson, string secondPerson);

        int getMostDistanceFromChildren(string person);

        pair<string, string> getLongestRelationship();

        string toJSON(bool oneline = true) const;
};

#endif
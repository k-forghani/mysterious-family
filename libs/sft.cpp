// Secure Family Tree Implementation

#include <iostream>
#include "sft.h"

using namespace std;


SFT::SFT () {

}

void SFT::addPerson (string id) {

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

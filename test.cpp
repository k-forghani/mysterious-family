#include <iostream>
#include "libs/hashes.h"
#include "libs/sft.h"

using namespace std;

int main () {
    // Hashing

    SHA256 sha256;
    sha256.update("Kazem Forghani");
    std::array<uint8_t, 32> digest = sha256.digest();
    string hashed = SHA256::toString(digest);
    cout << hashed << endl;
    
    // Secure Family Tree
    
    SFT sft;
    sft.addPerson("1");
    cout << sft.findPerson("1") << endl;
    sft.deletePerson("1");
    cout << sft.findPerson("1") << endl;
    sft.addPerson("1");
    sft.addPerson("2");
    sft.addPerson("121", "1", "2");
    sft.addPerson("122", "1", "2");
    sft.addPerson("123", "1", "2");
    sft.addPerson("3");
    sft.addPerson("4");
    sft.addPerson("341", "3", "4");
    sft.addPerson("1213411", "121", "341");
    sft.addPerson("5");
    sft.addPerson("6");
    sft.addPerson("561", "5", "6");
    sft.addPerson("1235611", "123", "561");
    cout << "getPersonsCount: " << sft.getPersonsCount() << endl;
    cout << "isAncestor: " << sft.isAncestor("3", "341") << endl;
    cout << "areSiblings: " << sft.areSiblings("121", "123") << endl;
    cout << "getMostDistanceFromChildren: " << sft.getMostDistanceFromChildren("1") << endl;
    cout << "getLowsetCommonAncestor: " << sft.getLowsetCommonAncestor("1235611", "1213411") << endl;
    

    return 0;
}
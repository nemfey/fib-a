#include "DHashing.hh"
#include <iostream>
#include <string>
#include <unistd.h>
using namespace std;

// PRIVATE FUNCTIONS
unsigned int DHashing::hash1(string key) {
    unsigned int hashVal = 0;

    for(int i=0; i<key.size(); i++) {
        hashVal = (37*hashVal + key[i]) % size;
    }

    return hashVal;
}

unsigned int DHashing::hash2(string key) {
    int hashVal = 0;

    for(int i=0; i<key.size(); i++) {
        hashVal = (29*hashVal + key[i]) % 7;
    }

    // mod prime number smaller than table size
    unsigned int index = 7 - (hashVal%7);
    return index;
}

// PUBLIC FUNCTIONS 
void DHashing::insert(const pair<string,bool>& key)
{
    int posh1 = hash1(key.first);
    int posh2 = hash2(key.first);
    int index = 0;
    bool posFound = false;

    //Encontar la pos adecuada con la fórmula Posición final = pos(Hashing 1) + i * pos(hashing 2)
    //Iterando con la i
    for (int i=1; i<=size and !posFound; ++i) {
        index = (posh1 + i*posh2) % size;
        if(hashTable[index].first=="-" or hashTable[index]==key) {
            posFound = true;
        }
    }
    
    if(posFound) hashTable[index] = key;
    else cout << "No se ha podido poner la key" << endl;
}

bool DHashing::searchPrefixWord(const string key)
{
    int posh1 = hash1(key);
    int posh2 = hash2(key);
    int index = 0;
    bool posFound = false;

    for (int i=1; i<=size and !posFound; ++i) {
        index = (posh1 + i*posh2) % size;
        posFound = (hashTable[index].first==key);
    }
    
    return posFound;
}

bool DHashing::searchFinalWord(const string key)
{
    int posh1 = hash1(key);
    int posh2 = hash2(key);
    int index = 0;
    bool posFound = false;

    for (int i=1; i<=size and !posFound; ++i) {
        index = (posh1 + i*posh2) % size;
        posFound = (hashTable[index].first==key && hashTable[index].second);
    }
    
    return posFound;
}


int DHashing::getSize() {
    return size;
}
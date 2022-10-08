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

    //return offsetHash2;
}

// PUBLIC FUNCTIONS 
void DHashing::insert(string key)
{
    int offset = 1;
    int positions = 0;
    unsigned int index_h1 = hash1(key);
    unsigned int index_h2 = hash2(key);
    unsigned int index = index_h1;
    //cout << "INDEX: " << index << endl;
    while(hashTable[index] != "-" and hashTable[index] != key) {
        positions = offset++ * index_h2;
        cout << offset << endl;
        //offset++;
        index = (index_h1+positions) % size;
        //cout << "i: " << index << ", occup: " << hashTable[index] << endl;
        //usleep(100000);
    }

    cout << "in position " << index << " word " << key << endl;
    hashTable[index] = key;
   /*
    unsigned int hashKey = hash1(key);
    //unsigned int stepSz = hash2(key);
    unsigned int stepSz = hash2();
    while(hashTable[hashKey] != "-" and hashTable[hashKey] != key) {
        hashKey = (hashKey + stepSz) % size;
        cout << "i: " << hashKey << ", occup: " << hashTable[hashKey] << endl;
        usleep(100000);
    }
    cout << "in position " << hashKey << " word " << key << endl;
    hashTable[hashKey] = key;
    */
    
}
/*
unsigned int DHashing::search(string key)
{
    int offset = 2;
    int index_h1 = hash1(key);
    int index_h2 = hash2(key);
    int index = index_h1;
    while(hashTable[index] != "-" or hashTable[index] != key) {
        int positions = offset * index_h2;
        offset++;
        index = (index_h1+positions) % size;
    }

    return index;
}
*/
int DHashing::getSize() {
    return size;
}

void DHashing::setOffsetHash2(int offset) {
    offsetHash2 = offset;
}
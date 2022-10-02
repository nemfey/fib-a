#include "Trie.hh"
#include <iostream>
#include <string>
using namespace std;
 
// Define the character size
#define CHAR_SIZE 128
 
// Iterative function to insert a key into a Trie
void Trie::insert(string key)
{
    // start from the root node
    Trie* curr = this;
    string s = "";
    for (int i = 0; i < key.length(); i++)
    {
        s.push_back(key[i]);
        if(curr->children.find(s) == curr->children.end()) {
            curr->children.insert({s,new Trie()});
        }
        curr = curr->children.find(s)->second;
        s = ""; // insert only char
    }
    // mark the current node as a leaf
    curr->isLeaf = true;
}

bool Trie::search(string key)
{
    // start from the root node
    Trie* curr = this;
    string s = "";
    for (int i = 0; i < key.length(); i++)
    {
        s.push_back(key[i]);

        if(curr->children.find(s) != curr->children.end()) {
            curr = curr->children.find(s)->second;
            s = "";
        }
    }
    // mark the current node as a leaf
    return curr->isLeaf;
}

bool Trie::existChildrenWithKey(string key) {
    Trie* curr = this;
    return (curr->children.find(key) != curr->children.end());
}

Trie* Trie::nodeWithKey(string key) {
    Trie* curr = this;
    return curr->children.find(key)->second;
}

void Trie::patricia() {
    //Trie* curr = this;
    // ...
}
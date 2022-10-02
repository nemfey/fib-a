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
/*
// Recursive function to delete a key in the Trie
bool Trie::deletion(Trie*& curr, string key)
{
    // return if Trie is empty
    if (curr == nullptr) {
        return false;
    }
 
    // if the end of the key is not reached
    if (key.length())
    {
        unsigned char c = key[0];
        // recur for the node corresponding to the next character in the key
        // and if it returns true, delete the current node (if it is non-leaf)
 
        if (curr != nullptr &&
            curr->character[c] != nullptr &&
            deletion(curr->character[c], key.substr(1)) &&
            curr->isLeaf == false)
        {
            if (!haveChildren(curr))
            {
                delete curr;
                curr = nullptr;
                return true;
            }
            else {
                return false;
            }
        }
    }
 
    // if the end of the key is reached
    if (key.length() == 0 && curr->isLeaf)
    {
        // if the current node is a leaf node and doesn't have any children
        if (!haveChildren(curr))
        {
            // delete the current node
            delete curr;
            curr = nullptr;
 
            // delete the non-leaf parent nodes
            return true;
        }
 
        // if the current node is a leaf node and has children
        else {
            // mark the current node as a non-leaf node (DON'T DELETE IT)
            curr->isLeaf = false;
 
            // don't delete its parent nodes
            return false;
        }
    }
 
    return false;
}

Trie* Trie::nodeOf(string key)
{
    // return false if Trie is empty
    //if (this == nullptr) {
    //    return false;
    //}
    
    Trie* curr = this;
    for (int i = 0; i < key.length(); i++)
    {
        unsigned char c = key[i];
        // go to the next node
        curr = curr->character[c];
 
        // if the string is invalid (reached end of a path in the Trie)
        if (curr == nullptr) {
            return nullptr;
        }
    }
 
    // return true if the current node is a leaf and the
    // end of the string is reached
    return curr;
}

void Trie::patricia() {

}
*/
#include <iostream>
#include <string>
#include <map>

using namespace std;

// Define the character size
#define CHAR_SIZE 128

class Trie {
    public:
        //string word;
        bool isLeaf;
        map<string,Trie*> children;
        //Trie* character[CHAR_SIZE];
    
        // Constructor
        Trie()
        {
            this->isLeaf = false;
            //this->children;
        }

        void insert(string);
        bool search(string);
        bool existChildrenWithKey(string);
        Trie* nodeWithKey(string);

        //bool deletion(Trie*&, string);
        //void patricia();
};

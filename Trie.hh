#include <iostream>
#include <string>
#include <map>

using namespace std;

class Trie {
    private:
        int numberChildren();
    
    public:
        string word;
        bool isCompleteWord;
        map<string,Trie*> children;
        //Trie* character[CHAR_SIZE];
    
        // Constructor
        Trie()
        {
            word = "";
            this->isCompleteWord = false;
            //this->children;
        }

        void insert(string);
        bool search(string);
        bool existChildrenWithKey(string);
        Trie* nodeWithKey(string);
        void patricia();

        //bool deletion(Trie*&, string);
        //void patricia();
};

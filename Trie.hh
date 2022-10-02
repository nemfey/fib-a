#include <iostream>

using namespace std;

// Define the character size
#define CHAR_SIZE 128

typedef vector<char> Row;
typedef vector<Row> Matrix;
typedef vector<pair<int,int>> PosChars;
typedef vector<bool> BoolRow;
typedef vector<BoolRow> BoolMatrix;

class Trie {
    
    bool isLeaf;
    Trie* character[CHAR_SIZE];
 
    // Constructor
    Trie()
    {
        this->isLeaf = false;
 
        for (int i = 0; i < CHAR_SIZE; i++) {
            this->character[i] = nullptr;
        }
    }
 
    void insert(string);
    bool deletion(Trie*&, string);
    bool search(string);
    bool haveChildren(Trie const*);
};

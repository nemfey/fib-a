#include <iostream>
#include <string>
#include <vector>

using namespace std;

class DHashing {
    private:
        unsigned int hash1(string);
        unsigned int hash2(string);
        int size;
    
    public:
        vector<pair<string,bool>> hashTable;
    
        // Constructor
        DHashing(int n)
        {
            size = n;
            hashTable = vector<pair<string,bool>>(n,make_pair("-",false));
        }

        void insert(const pair<string,bool>&);
        bool searchPrefixWord(const string);
        bool searchFinalWord(const string);
        int getSize();
};

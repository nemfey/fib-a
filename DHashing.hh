#include <iostream>
#include <string>
#include <vector>

using namespace std;

class DHashing {
    private:
        unsigned int hash1(string);
        unsigned int hash2(string);
        int size;
        int offsetHash2;
    
    public:
        vector<string> hashTable;
    
        // Constructor
        DHashing(int n)
        {
            size = n;
            hashTable = vector<string>(n,"-");
        }

        void insert(string);
        unsigned int search(string);
        int getSize();
        void setOffsetHash2(int);
};

#ifndef BLOOM_FILTER
#define BLOOM_FILTER

#include <vector>
#include <string>

using namespace std;


class BloomFilter {
    
    private:
        //dictionary size
        int n;
        //false positive probability
        float p;
        //number of bits
        int m; 
        vector<unsigned char> mask;
        //number of hash functions
        int k;
        
        int charToInt(char a);
        int fHash(int base, int exponent, int mod);
        
    public:
        BloomFilter(int n2, float p2);
        void insertWord(const string& word);
        int search(const string& auxWord, int cont);
        void print(int i);
        int size();
};

#endif

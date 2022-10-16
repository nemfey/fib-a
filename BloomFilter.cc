#include "BloomFilter.hh"
#include <iostream>
#include <cmath>
#include <string>

using namespace std;

vector<int> primeElevatedNumbers = {31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97, 101, 103, 107, 109, 113, 127, 131, 197, 139};

vector<unsigned char> bitMask = {0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80, 0x00};

//private functions

int BloomFilter::stringToInt(const string& word) {
    
    int num = 0, wordSize = word.size();
    
    for (int i = 0; i < wordSize; i++) {
        
        num = 37*num + int(word[i]);
        num = num % m;
    }
    return num;
}

//exponenciació ràpida (O(logn))
int BloomFilter::fHash0(int base, int exponent) {
    
    if (exponent == 0) {
        
        return 1;
    }
    
    unsigned int pow = fHash0(base, exponent/2);
    if (exponent%2 == 0) pow *= pow;
    else pow *= pow * base;
    pow = pow % m;
    return pow;
}

int BloomFilter::fHash1(int prime, const string& word) {
    
    int num = 0;
    
    for (int i = 0; i < word.size(); i++) {
        
        num = prime*num + word[i];
        num = num % m;
    }
    return num;
}

int BloomFilter::fHash2(int prime, int sNum) {
    
    unsigned int num = 0;
    
    for (int i = 0; i < 4; i++) {
        
        num = ((num<<prime)+num)^sNum;
        num = num % m;
    }
    return num;
}

int BloomFilter::fHash3(int prime, int sNum) {
    
    unsigned int num = 0;
    
    for (int i = 0; i < 3; i++) {
        
        num = ((num<<prime)-num)+sNum;
        num = num & num;
        num = num % m;
    }
    return num;
}

int BloomFilter::fHash4(int prime, int sNum) {
    
    unsigned int num = 0;
    
    for (int i = 0; i < 5; i++) {
        
        num = ((num<<prime)+num)-sNum;
        num = num | num;
        num = num % m;
    }
    return num;
}

//public functions

BloomFilter::BloomFilter() {}

BloomFilter::BloomFilter(int n2, float p2) {
    
    n = n2;
    p = p2;
    float aux = (n * log(p)) / log(1 / pow(2, log(2)));
    m = ceil(aux);
    mask = vector<unsigned char>(ceil(aux/8),0x0);
    k = floor((m / n) * log(2));
    if (k == 0) k=1;
}

void BloomFilter::insertWord(const string& word) {
    
    //int numWord = stringToInt(word);
    int numHash, posMask, posBit;
    int j = 0;
    
    for(int i = 0; i < 1; i++, j++) {
        
        if (j == primeElevatedNumbers.size()) j = 0;
        /*if (i % 5 == 0) numHash = fHash0(primeElevatedNumbers[j], numWord);
        else if (i % 5 == 1) numHash = fHash1(primeElevatedNumbers[j], numWord);
        else if (i % 5 == 2) numHash = fHash2(primeElevatedNumbers[j], numWord);
        else if (i % 5 == 3) numHash = fHash3(primeElevatedNumbers[j], numWord);
        else numHash = fHash4(primeElevatedNumbers[j], numWord);*/
        numHash = fHash1(primeElevatedNumbers[j], word);
        posMask = numHash / 8;
        posBit = numHash % 8;
        mask[posMask] = mask[posMask] | bitMask[posBit];
    }
}

int BloomFilter::search(const string& auxWord) {
    
    //int numWord = stringToInt(auxWord);
    int numHash, posMask, posBit;
    int j = 0;
    
    for(int i = 0; i < 1; i++, j++) {
        
        if (j == primeElevatedNumbers.size()) j = 0;
        /*if (i % 5 == 0) numHash = fHash0(primeElevatedNumbers[j], numWord);
        else if (i % 5 == 1) numHash = fHash1(primeElevatedNumbers[j], numWord);
        else if (i % 5 == 2) numHash = fHash2(primeElevatedNumbers[j], numWord);
        else if (i % 5 == 3) numHash = fHash3(primeElevatedNumbers[j], numWord);
        else numHash = fHash4(primeElevatedNumbers[j], numWord);*/
        numHash = fHash1(primeElevatedNumbers[j], auxWord);
        posMask = numHash / 8;
        posBit = numHash % 8;
        if((mask[posMask] & bitMask[posBit])==bitMask[8]) return 0;
    }
    return 1;
}

void BloomFilter::print (int i) {
    
    cout << int(mask[i]) << endl;
}

int BloomFilter::size() {
    
    return mask.size();
}

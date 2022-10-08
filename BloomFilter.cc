#include "BloomFilter.hh"
#include <iostream>
#include <cmath>
#include <string>

using namespace std;

vector<int> primeElevatedNumbers = {3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43};
vector<int> primeModNumbers = {104551, 104561, 104579, 104593, 104597, 104623, 104639, 104651, 104659, 104677, 104681, 104683, 104693, 104701, 104707, 104711, 104717, 104723, 104729};

vector<unsigned char> bitMask = {0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80};

//private functions

int BloomFilter::charToInt(char a) {
    
    int nA = int(a);
    return nA;
}

//exponenciació ràpida (O(logn))
int BloomFilter::fHash(int base, int exponent, int mod) {
    
    if (exponent == 0) {
        
        return 1;
    }
    
    unsigned int pow = fHash(base, exponent/2, mod);
    if (exponent%2 == 0) pow *= pow;
    else pow *= pow * base;
    pow = pow % mod;
    return pow;
}

//public functions

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
    
    int wordSize = word.size();
    int countChar = 0;
    int numChar, numHash, posMask, posBit;
    int j = 0, l = 0;
    
    for(int i = 0; i < k; i++, countChar++, j++, l++) {
        
        if (countChar == wordSize) countChar = 0;
        numChar = charToInt(word[countChar]);
        if (j == primeElevatedNumbers.size()) j = 0;
        if (l == primeModNumbers.size()) l = 0;
        numHash = fHash(primeElevatedNumbers[j], numChar, primeModNumbers[l]);
        posMask = (numHash * m / primeModNumbers[l]) / 8;
        posBit = int((numHash * m / primeModNumbers[l])) % 8;
        mask[posMask] = mask[posMask] | bitMask[posBit];
    }
}

int BloomFilter::search(const string& auxWord, int cont) {
    
    cout << "auxWord " << auxWord << " cont " << cont << endl;
    int auxWordSize = auxWord.size();
    cout << "auxWordSize " << auxWordSize << endl;
    int countChar = cont;
    cout << "countChar " << countChar << endl;
    int numChar, numHash, posMask, posBit;
    int j = cont % primeElevatedNumbers.size(), l = cont % primeModNumbers.size();
    cout << "j " << j << " l " << l << endl;
    
    for(int i = cont; i < k; i++, countChar++, j++, l++) {
        
        if (countChar == auxWordSize) countChar = 0;
        numChar = charToInt(auxWord[countChar]);
        if (j == primeElevatedNumbers.size()) j = 0;
        if (l == primeModNumbers.size()) l = 0;
        numHash = fHash(primeElevatedNumbers[j], numChar, primeModNumbers[l]);
        posMask = (numHash * m / primeModNumbers[l]) / 8;
        posBit = int((numHash * m / primeModNumbers[l])) % 8;
        if(!(mask[posMask] & bitMask[posBit])) {
            
            if (i > cont) return 1;
            return 0;
        }
    }
    return 2;
}

void BloomFilter::print (int i) {
    
    cout << int(mask[i]) << endl;
}

int BloomFilter::size() {
    
    return mask.size();
}

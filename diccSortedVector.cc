#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <vector>
#include <algorithm>
#include "wordSearch.hh"

using namespace std;

// words must have 20 positions
void chooseWordsFromDict(vector<string>& dictionary, vector<string>& words) {
    int dicSize = dictionary.size();
    vector<int> positionsToChoose(dicSize);
    for(int i=0; i<dicSize; ++i) positionsToChoose[i] = i;
    
    for(int i=0; i<20; ++i) {
        int r = rand() % (dicSize-i);
        words[i] = dictionary[r];

        swap(dictionary[r], dictionary[dicSize - (i+1)]);
    }
}

int main() {
    
    srand(time(NULL));
    
    vector<string> dictionary = {"abuela","arbol","bocata","bocina","son","buenas","coche","noche","silla",
                                  "carbon","electro","iman","tapon","persiana","ventana","booleano","mesa",
                                  "lapiz","mono","estuche","coco","palmeta","barco","avion","empirico"};
    vector<string> words(20);
    chooseWordsFromDict(dictionary,words);
    
    int n = rand() % 11 + 10;
    WordSearch wordSearch(n);
    
    // always 20 words to search
    for (int i = 0; i < 20; i++) {
        
        wordSearch.addWord(words[i]);
    }

    //aqui la sopa ya estaria creada y solo tocaria buscar las palabras
    wordSearch.print();
}

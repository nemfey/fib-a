#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <vector>
#include "wordSearch.hh"

using namespace std;

int main() {
    
    srand(time(NULL));
    
    int n = rand() % 11 + 10;
    WordSearch wordSearch(n);
    
    vector<string> words = {"joan","pol","victor","mario"};
    int nWords = words.size();
    for (int i = 0; i < nWords; i++) {
        
        wordSearch.addWord(words[i]);
    }
    //aqui la sopa ya estaria creada y solo tocaria buscar las palabras
}

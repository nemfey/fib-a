#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <vector>
#include "wordSearch.hh"

using namespace std;

int main() {
    
    srand(time(NULL));
    
    //int n = rand() % 11 + 10;
    int n = 5;
    WordSearch wordSearch(n);
    
    //vector<string> words = {"JOAN","POL","VICTOR","MARIO", "AMARILLO", "COCHE", "JUEGO", "NATILLA"};
    vector<string> words = {"aaaaa","bbbbb","ccccc","ddddd","eeeee","fffff"};
    int nWords = words.size();
    for (int i = 0; i < nWords; i++) {
        
        wordSearch.addWord(words[i]);
    }

    //aqui la sopa ya estaria creada y solo tocaria buscar las palabras
    wordSearch.print();
}

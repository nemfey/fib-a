#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <vector>
#include <algorithm>
#include <list>
#include "wordSearch.hh"

using namespace std;

typedef pair<string,PosChars> Result;

// words must have 20 positions
void chooseWordsFromDict(vector<string> dictionary, vector<string>& words) {
    
    int dicSize = dictionary.size();
    vector<int> positionsToChoose(dicSize);
    for(int i=0; i<dicSize; ++i) positionsToChoose[i] = i;
    
    for(int i=0; i<20; ++i) {
        int r = rand() % (dicSize-i);
        words[i] = dictionary[r];

        swap(dictionary[r], dictionary[dicSize - (i+1)]);
    }
}

int dichotomousSearch(const string& auxWord, const vector<string>& dictionary, int left, int right) {
    
    if (left > right) return 0;
    int m = (left + right) / 2;
    if (auxWord < dictionary[m]) {
        
        //prefix the same
        if(dictionary[m].find(auxWord) == 0) return 1;
        return dichotomousSearch(auxWord, dictionary, left, m - 1);
    }
    else if (auxWord > dictionary[m]) return dichotomousSearch(auxWord, dictionary, m + 1, right);
    //word found
    return 2;
}

//recursive call
void searchingWordsRec(const vector<string>& dictionary, WordSearch& wordSearch, int n, int i, int j, list<Result>& result, BoolMatrix& visited, string& currentWord) {
    
    if(not visited[i][j]) {
        
        visited[i][j] = true;
        string auxWord = currentWord;
        auxWord.push_back(wordSearch.toChar(i,j));
        int exists = dichotomousSearch(auxWord, dictionary, 0, dictionary.size());
        if (exists == 0) return;
        //else if (exists == 2)
    }
}

//first call to recursive searching words
void searchingWords(const vector<string>& dictionary, WordSearch& wordSearch, int n, int i, int j, list<Result>& result) {
    
    BoolMatrix visited(n, BoolRow(n, false));
    string w = "";
    searchingWordsRec(dictionary, wordSearch, n, i, j, result, visited, w);
}

int main() {
    
    srand(time(NULL));
    
    vector<string> dictionary = {"ABUELO", "ARBOL", "BALON", "BICICLETA", "COLILLA", "CHORRA", "DICCIONARIO", "DORMIR", "ELECTIRCO", "ESPANYA", "FAROLA", "FUENTE", "GATO", "GORILA", "HELICOPTERO", "HORMIGA", "IGUALAR", "ISLAM", "JUEGO", "JORDAN", "KIWI", "KILO", "LIBRA", "LIMON", "MONEDA", "MESA", "NORIA", "NUBE", "ORIFICIO", "OLER", "PALOMA", "PUEBLO", "QUESO", "QUERER", "RUIDO", "RUEGO", "SORIA", "SUERTE", "TIRAR", "TITAN", "UVA", "UMBRAL", "VACACIONES", "VOLVER", "WATERPOLO", "WIKI", "XAVI", "XINO", "YOGUR", "YAYO", "ZEBRA", "ZAPATO"};
    vector<string> words(20);
    
    sort(dictionary.begin(), dictionary.end());
    
    chooseWordsFromDict(dictionary,words);
    
    int n = rand() % 16 + 10;
    WordSearch wordSearch(n);
    
    // always 20 words to search
    for (int i = 0; i < 20; i++) {
        
        wordSearch.addWord(words[i]);
    }

    sort(words.begin(), words.end());
    int wordsSize = words.size();
    for (int i = 0; i < wordsSize; i++) cout << words[i] << "  ";
    cout << endl << endl;
    //aqui la sopa ya estaria creada y solo tocaria buscar las palabras
    wordSearch.print();
    
    list<Result> result;
    for(int i = 0; i < n; i++) {
        
        for(int j = 0; j < n; j++) {
            
            searchingWords(dictionary, wordSearch, n, i, j, result);
        }
    }
}

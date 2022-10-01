#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <vector>
#include <algorithm>
#include "wordSearch.hh"

using namespace std;

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
}

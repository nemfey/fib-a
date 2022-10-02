#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <vector>
#include <algorithm>
#include <list>
#include "wordSearch.hh"
#include "Trie.hh"

using namespace std;

//                  NO N NE E SE S SO O
vector<int> dirI = {-1,0,1,1,1,0,-1,-1};
vector<int> dirJ = {-1,-1,-1,0,1,1,1,0};

typedef pair<string,PosChars> Result;


void chooseWordsFromDictionary(vector<string> dictionary, vector<string>& words) {
    
    int dicSize = dictionary.size();
    vector<int> positionsToChoose(dicSize);
    for(int i=0; i<dicSize; ++i) positionsToChoose[i] = i;
    
    for(int i=0; i<20; ++i) {
        int r = rand() % (dicSize-i);
        words[i] = dictionary[r];

        swap(dictionary[r], dictionary[dicSize - (i+1)]);
    }
}

//recursive call
void searchingWordsRec(WordSearch& wordSearch, BoolMatrix& visited, Trie*& dictionary, list<Result>& result, PosChars& auxPos, string partialWord, string finalWord, int i, int j) {   
    if(not visited[i][j]) {
        visited[i][j] = true;
        // creamos string auxiliar para ver si el nuevo prefijo existe
        //string auxWord = partialWord;
        //auxWord.push_back(wordSearch.toChar(i,j)); // partial word + current char(i,j)
        partialWord.push_back(wordSearch.toChar(i,j));
        // coche coca
        // coc  -> he
        //      -> ca
        // c+o+c+h+e

        //Posiciones que se verán después
        int auxI, auxJ;
        
        // Comprobamos si existe la palabra completa en el diccionario
        // int exists = dichotomousSearch(auxWord, dictionary, 0, dictionary.size()-1);
        if (dictionary->search(partialWord)) {
            auxPos.push_back({i,j});
            finalWord.push_back(wordSearch.toChar(i,j));
            result.push_back({finalWord,auxPos});
            cout << "final: " << finalWord << " ended (" << i << "," << j << ")" << endl;
        }
        else if(dictionary->existChildrenWithKey(partialWord)) {
            auxPos.push_back({i,j});
            Trie* childrenDictionary = dictionary->nodeWithKey(partialWord);
            // recursive call
            for(int k = 0; k < 8; k++) {         
                auxI = i + dirI[k];
                auxJ = j + dirJ[k];
                string resetWord = "";
                string someFinalWord = finalWord;
                someFinalWord.push_back(wordSearch.toChar(i,j));
                if(wordSearch.posOk(auxI,auxJ)) {
                    searchingWordsRec(wordSearch, visited, childrenDictionary, result, auxPos, resetWord, someFinalWord, auxI, auxJ);
                }
            }
            auxPos.pop_back();
        }
        //else if prefijo de alguna key patricia

        //    ->  e->s->p->a   -> nya
        //                  -> t
        //                          ->ula
        //                           ->illa
        //espa              t       
        partialWord.pop_back();
        visited[i][j] = false;
    }
}

// First call to recursive searching words
void searchingWords(Trie*& dictionary, WordSearch& wordSearch, int i, int j, list<Result>& result) {
    BoolMatrix visited(wordSearch.getSize(), BoolRow(wordSearch.getSize(), false));
    string finalWord, partialWord = "";
    PosChars auxPos;
    searchingWordsRec(wordSearch, visited, dictionary, result, auxPos, partialWord, finalWord, i, j);
}

int main() {
    srand(time(NULL));
    
    vector<string> dictionary = {"ABUELO", "ARBOL", "BALON", "BICICLETA", "COLILLA", "CHORRA", "DICCIONARIO", "DORMIR", "ELECTIRCO", "ESPANYA", "FAROLA", "FUENTE", "GATO", "GORILA", "HELICOPTERO", "HORMIGA", "IGUALAR", "ISLAM", "JUEGO", "JORDAN", "KIWI", "KILO", "LIBRA", "LIMON", "MONEDA", "MESA", "NORIA", "NUBE", "ORIFICIO", "OLER", "PALOMA", "PUEBLO", "QUESO", "QUERER", "RUIDO", "RUEGO", "SORIA", "SUERTE", "TIRAR", "TITAN", "UVA", "UMBRAL", "VACACIONES", "VOLVER", "WATERPOLO", "WIKI", "XAVI", "XINO", "YOGUR", "YAYO", "ZEBRA", "ZAPATO"};
    //sort(dictionary.begin(), dictionary.end());    
    vector<string> words(20);
    chooseWordsFromDictionary(dictionary,words);
    
    // Initialize the word search
    int n = rand() % 16 + 10;
    WordSearch wordSearch(n);   
    for (int i = 0; i < 20; i++) {
        wordSearch.addWord(words[i]);
    }

    int wordsSize = words.size();
    for (int i = 0; i < wordsSize; i++) cout << words[i] << "  ";
    cout << endl << endl;
    // Word search created
    wordSearch.print();

    // Initialize the trie with words from dictionary
    Trie* trie = new Trie();
    for (int i = 0; i < dictionary.size(); ++i) {
        trie->insert(dictionary[i]);
    }
    
    // Find all the words
    list<Result> wordsFound;
    for(int i = 0; i < n; i++) {      
        for(int j = 0; j < n; j++) {           
            searchingWords(trie, wordSearch, i, j, wordsFound);
        }
    }
    
    // Print words found in the word search
    cout << endl << "WORDS FOUND:" << endl;
    list<Result>::const_iterator it;
    for(it = wordsFound.begin(); it!= wordsFound.end(); ++it) {       
        Result r = *it;
        cout << r.first << " -> ";
        int vsize = r.second.size();
        for (int i = 0; i < vsize; i++) {            
            cout << '{' << r.second[i].first << ',' << r.second[i].second << "} (" << wordSearch.toChar(r.second[i].first,r.second[i].second) << ")";
            //cout << wordSearch.toChar(r.second[i].first,r.second[i].second) << " ";
            if(i != vsize -1) cout << " , ";
        }
        cout << endl;   
    }
}

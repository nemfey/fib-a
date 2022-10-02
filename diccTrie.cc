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

// convertir diccionario a trie
// aplicar patricia al trie
// backtracking
//      caso base: si palabra intermedia == palabra hoja -> return palabra
//      sino:
//            repetir:
//              mira si mi letra (o palabra hasta el momento formada)
//                  forma parte del valor de un nodo vecino
//                   -> si: vamos al vecino y lo mismo
//                   -> sino: siguiente letra vecina (i,j)
//                              si ninguna letra (auxiliar de visitados) backtracking se encarga :)

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
void searchingWordsRec(Trie*& dictionary, WordSearch& wordSearch, int i, int j, list<Result>& result, BoolMatrix& visited, string partialWord, string finalWord, PosChars& auxPos) {
    
    if(not visited[i][j]) {
        visited[i][j] = true;
        // creamos string auxiliar para ver si el nuevo prefijo existe
        string auxWord = partialWord;
        auxWord.push_back(wordSearch.toChar(i,j)); // partial word + current char(i,j)
        
        //Posiciones que se verán después
        int auxI, auxJ;
        
        // Comprobamos si existe la palabra completa en el diccionario
        // int exists = dichotomousSearch(auxWord, dictionary, 0, dictionary.size()-1);
        if (dictionary->search(auxWord)) {
            auxPos.push_back({i,j});
            finalWord.push_back(wordSearch.toChar(i,j));
            result.push_back({finalWord,auxPos});
            // llamada recursiva
            /*
            for(int k = 0; k < 8; k++) {         
                auxI = i + dirI[k];
                auxJ = j + dirJ[k];
                if(wordSearch.posOk(auxI,auxJ)) searchingWordsRec(dictionary, wordSearch, auxI, auxJ, result, visited, auxWord, auxPos);
            }
            auxPos.pop_back();
            */
        }
        else if(dictionary->existChildrenWithKey(auxWord)) {
            auxPos.push_back({i,j});
            Trie* childrenDictionary = dictionary->nodeWithKey(auxWord);
            //llamada recursiva
            for(int k = 0; k < 8; k++) {         
                auxI = i + dirI[k];
                auxJ = j + dirJ[k];
                string resetWord = "";
                string someFinalWord = finalWord;
                someFinalWord.push_back(wordSearch.toChar(i,j));
                if(wordSearch.posOk(auxI,auxJ)) searchingWordsRec(childrenDictionary, wordSearch, auxI, auxJ, result, visited, resetWord, someFinalWord, auxPos);
            }
            auxPos.pop_back();
            //actualizar dictionary -> dic->children.find(auxword) y reset palabra
        }
        //else if prefijo de alguna key patricia

        //    ->  e->s->p->a   -> nya
        //                  -> t
        //                          ->ula
        //                           ->illa
        //espa              t       

        visited[i][j] = false;
    }
}

//first call to recursive searching words
void searchingWords(Trie*& dictionary, WordSearch& wordSearch, int n, int i, int j, list<Result>& result) {
    
    BoolMatrix visited(n, BoolRow(n, false));
    string finalWord = "";
    string partialWord = ""; // partial word
    PosChars auxPos; // ???
    searchingWordsRec(dictionary, wordSearch, i, j, result, visited, partialWord, finalWord, auxPos);
}

int main() {
    
    srand(time(NULL));
    
    vector<string> dictionary = {"ABUELO", "ARBOL", "BALON", "BICICLETA", "COLILLA", "CHORRA", "DICCIONARIO", "DORMIR", "ELECTIRCO", "ESPANYA", "FAROLA", "FUENTE", "GATO", "GORILA", "HELICOPTERO", "HORMIGA", "IGUALAR", "ISLAM", "JUEGO", "JORDAN", "KIWI", "KILO", "LIBRA", "LIMON", "MONEDA", "MESA", "NORIA", "NUBE", "ORIFICIO", "OLER", "PALOMA", "PUEBLO", "QUESO", "QUERER", "RUIDO", "RUEGO", "SORIA", "SUERTE", "TIRAR", "TITAN", "UVA", "UMBRAL", "VACACIONES", "VOLVER", "WATERPOLO", "WIKI", "XAVI", "XINO", "YOGUR", "YAYO", "ZEBRA", "ZAPATO"};
    sort(dictionary.begin(), dictionary.end());
    
    vector<string> words(20);
    chooseWordsFromDict(dictionary,words);
    
    // create empty wordSearch
    int n = rand() % 16 + 10;
    WordSearch wordSearch(n);   
    // initialize the wordSearch
    for (int i = 0; i < 20; i++) {
        wordSearch.addWord(words[i]);
    }

    int wordsSize = words.size();
    for (int i = 0; i < wordsSize; i++) cout << words[i] << "  ";
    cout << endl << endl;
    //aqui la sopa ya estaria creada y solo tocaria buscar las palabras
    wordSearch.print();

    //Mutate dictionary into Trie
    Trie* trieDictionary = new Trie();
    for (int i = 0; i < dictionary.size(); ++i) {
        trieDictionary->insert(dictionary[i]);
    }
    /*
    cout << trieDictionary->search("E") << endl;
    cout << trieDictionary->existChildrenWithKey("E") << endl;
    cout << trieDictionary->search("ESPANYA") << endl;
    cout << trieDictionary->existChildrenWithKey("ESPANYA") << endl;
    */

    
    list<Result> result; // words found
    for(int i = 0; i < n; i++) {      
        for(int j = 0; j < n; j++) {           
            searchingWords(trieDictionary, wordSearch, n, i, j, result);
        }
    }
    
    cout << endl << "WORDS FOUND" << endl << "------------------------------------------------------------" << endl;
    list<Result>::const_iterator it;
    for(it = result.begin(); it!= result.end(); ++it) {
        
        Result r = *it;
        cout << r.first << " -> ";
        int vsize = r.second.size();
        for (int i = 0; i < vsize; i++) {
            
            cout << '{' << r.second[i].first << ',' << r.second[i].second << "}";
            if(i != vsize -1) cout << " , ";
        }
        cout << endl;
        
    }
}

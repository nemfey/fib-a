#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <vector>
#include <algorithm>
#include <list>
#include "wordSearch.hh"

using namespace std;

// Define the character size
#define CHAR_SIZE 128

//                  NO N NE E SE S SO O
vector<int> dirI = {-1,0,1,1,1,0,-1,-1};
vector<int> dirJ = {-1,-1,-1,0,1,1,1,0};

typedef pair<string,PosChars> Result;

class Trie
{
public:
    bool isLeaf;
    Trie* character[CHAR_SIZE];
 
    // Constructor
    Trie()
    {
        this->isLeaf = false;
 
        for (int i = 0; i < CHAR_SIZE; i++) {
            this->character[i] = nullptr;
        }
    }
 
    void insert(string);
    bool deletion(Trie*&, string);
    bool search(string);
    bool haveChildren(Trie const*);
};
 
// Iterative function to insert a key into a Trie
void Trie::insert(string key)
{
    // start from the root node
    Trie* curr = this;
    for (int i = 0; i < key.length(); i++)
    {
        unsigned char c = key[i];
        // create a new node if the path doesn't exist
        if (curr->character[c] == nullptr) {
            curr->character[c] = new Trie();
        }
 
        // go to the next node
        curr = curr->character[c];
    }
 
    // mark the current node as a leaf
    curr->isLeaf = true;
}
 
// Iterative function to search a key in a Trie. It returns true
// if the key is found in the Trie; otherwise, it returns false
bool Trie::search(string key)
{
    // return false if Trie is empty
    /*
    if (this == nullptr) {
        return false;
    }
    */
    Trie* curr = this;
    for (int i = 0; i < key.length(); i++)
    {
        unsigned char c = key[i];
        // go to the next node
        curr = curr->character[c];
 
        // if the string is invalid (reached end of a path in the Trie)
        if (curr == nullptr) {
            return false;
        }
    }
 
    // return true if the current node is a leaf and the
    // end of the string is reached
    return curr->isLeaf;
}
 
// Returns true if a given node has any children
bool Trie::haveChildren(Trie const* curr)
{
    for (int i = 0; i < CHAR_SIZE; i++)
    {
        if (curr->character[i]) {
            return true;    // child found
        }
    }
 
    return false;
}
 
// Recursive function to delete a key in the Trie
bool Trie::deletion(Trie*& curr, string key)
{
    // return if Trie is empty
    if (curr == nullptr) {
        return false;
    }
 
    // if the end of the key is not reached
    if (key.length())
    {
        unsigned char c = key[0];
        // recur for the node corresponding to the next character in the key
        // and if it returns true, delete the current node (if it is non-leaf)
 
        if (curr != nullptr &&
            curr->character[c] != nullptr &&
            deletion(curr->character[c], key.substr(1)) &&
            curr->isLeaf == false)
        {
            if (!haveChildren(curr))
            {
                delete curr;
                curr = nullptr;
                return true;
            }
            else {
                return false;
            }
        }
    }
 
    // if the end of the key is reached
    if (key.length() == 0 && curr->isLeaf)
    {
        // if the current node is a leaf node and doesn't have any children
        if (!haveChildren(curr))
        {
            // delete the current node
            delete curr;
            curr = nullptr;
 
            // delete the non-leaf parent nodes
            return true;
        }
 
        // if the current node is a leaf node and has children
        else {
            // mark the current node as a non-leaf node (DON'T DELETE IT)
            curr->isLeaf = false;
 
            // don't delete its parent nodes
            return false;
        }
    }
 
    return false;
}

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
void searchingWordsRec(const vector<string>& dictionary, WordSearch& wordSearch, int i, int j, list<Result>& result, BoolMatrix& visited, string& currentWord, PosChars& auxPos) {
    
    if(not visited[i][j]) {
        
        visited[i][j] = true;
        //creamos string auxiliar para ver si el nuevo prefijo existe
        string auxWord = currentWord;
        auxWord.push_back(wordSearch.toChar(i,j));
        int exists = dichotomousSearch(auxWord, dictionary, 0, dictionary.size()-1);
        int auxI, auxJ;
        // existe la palabra entera
        if (exists == 2) {
            
            auxPos.push_back({i,j});
            result.push_back({auxWord,auxPos});
            //llamada recursiva
            for(int k = 0; k < 8; k++) {
                
                auxI = i + dirI[k];
                auxJ = j + dirJ[k];
                if(wordSearch.posOk(auxI,auxJ)) searchingWordsRec(dictionary, wordSearch, auxI, auxJ, result, visited, auxWord, auxPos);
            }
            auxPos.pop_back();
        }
        //existe el prefijo
        else if (exists == 1){
            
            auxPos.push_back({i,j});
            for(int k = 0; k < 8; k++) {
                
                auxI = i + dirI[k];
                auxJ = j + dirJ[k];
                if(wordSearch.posOk(auxI,auxJ)) searchingWordsRec(dictionary, wordSearch, auxI, auxJ, result, visited, auxWord, auxPos);
            }
            auxPos.pop_back();
        }
        visited[i][j] = false;
    }
}

//first call to recursive searching words
void searchingWords(const vector<string>& dictionary, WordSearch& wordSearch, int n, int i, int j, list<Result>& result) {
    
    BoolMatrix visited(n, BoolRow(n, false));
    string w = "";
    PosChars auxPos;
    searchingWordsRec(dictionary, wordSearch, i, j, result, visited, w, auxPos);
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
    /*
    list<Result> result;
    for(int i = 0; i < n; i++) {
        
        for(int j = 0; j < n; j++) {
            
            searchingWords(dictionary, wordSearch, n, i, j, result);
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
    */
}

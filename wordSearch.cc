#include "wordSearch.hh"
#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

typedef vector<bool> BoolRow;
typedef vector<BoolRow> BoolMatrix;

//                  NO N NE E SE S SO O
vector<int> diri = {-1,0,1,1,1,0,-1,-1};
vector<int> dirj = {-1,-1,-1,0,1,1,1,0};

//Funciones privadas

bool WordSearch::posOk(int posi, int posj, char c) {
    
    if (posi < 0 or posj < 0 or posi >= wordSearch.size() or posj >= wordSearch.size()) return false;
    if (wordSearch[posi][posj] == '*' or wordSearch[posi][posj] == c) return true;
    return false;
}

bool WordSearch::posRepeated(int posi, int posj, const PosChars& posChars) {
    
    for (auto pos: posChars) {
        
        if (pos.first == posi and pos.second == posj) return true;
    }
    return false;
}

//empiezo a poner letras desde la última para que el problema de borrarlas si no hay hueco sea más facil
bool WordSearch::addWordRec(int posi, int posj, const string& word, int n, PosChars& posChars) {
    
    if (!posOk(posi, posj, word[n]) or posRepeated(posi, posj, posChars)) return false;
    //última letra de la palabra
    if (n == word.size() - 1) {
        
        wordSearch[posi][posj] = word[n];
        return true;
    }
    posChars[n] = {posi,posj};
    //dirVisited[8] es el contador para ver si ya se han mirado las 8 direcciones
    vector<int> dirVisited(9,0);
    bool charFitted = false;
    int dir;
    do {
        
        dir = rand() % 8;
        //hasta encontrar una dirección que no se ha usado
        while (dirVisited[dir] == 1) dir = rand() % 8;
        dirVisited[dir] = 1;
        ++dirVisited[8];
        charFitted = addWordRec(posi + diri[dir], posj + dirj[dir], word, n + 1, posChars);
    }
    while(!charFitted and dirVisited[8] < 8);
    if (charFitted) {
        
        wordSearch[posi][posj] = word[n];
        return true;
    }
    return false;
}

//Funciones públicas

WordSearch::WordSearch(int n) {
    
    wordSearch = Matrix(n, Row(n,'*'));
}

void WordSearch::addWord(const string& word) {
    
    int posi, posj;
    bool wordFitted = false;
    //no se me ocurre otra forma de comprobar si la posición ya se ha mirado
    //también doy por hecho de que habrá algun sitio por donde empezar
    //si no habría que usar otra EdD más para controlar eso zzz
    BoolMatrix posTried(wordSearch.size(), BoolRow(wordSearch.size(),false));
    do {
        
        posi = rand() % wordSearch.size();
        posj = rand() % wordSearch.size();
        if (!posTried[posi][posj]) {
            
            //vector del tamaño de la palabra para tener ordenados cual es la posi y posj de la ultima letra de la palabra añadida
            PosChars posChars(word.size(), {-1,-1});
            wordFitted = addWordRec(posi, posj, word, 0, posChars);
            posTried[posi][posj] = true;
        }
    }
    while(!wordFitted);
}

void WordSearch::print() {
    
    int randomChar;
    for (auto row: wordSearch) {
        
        for (auto c: row) {
            
            if (c == '*') {
                
                randomChar = rand() % 26 + 65;
                cout << " " << char(randomChar);
            }
            else cout << " " << c;
        }
        cout << endl;
    }
}

#include "wordSearch.hh"
#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

<<<<<<< HEAD
typedef vector<bool> BoolRow;
typedef vector<BoolRow> BoolMatrix;
=======

typedef vector<bool> BoolRow;
typedef vector<BoolRow> BoolMatrix;

//typedef vector<bool> BoolRow;
//typedef vector<BoolRow> BoolMatrix;
>>>>>>> victor

//                  NO N NE E SE S SO O
vector<int> diri = {-1,0,1,1,1,0,-1,-1};
vector<int> dirj = {-1,-1,-1,0,1,1,1,0};

// Funciones privadas

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

// empiezo a poner letras desde la ultima para que el problema de borrarlas si no hay hueco sea mas facil
bool WordSearch::addWordRec(int posi, int posj, const string& word, int i, PosChars& posChars) {
    
    if (!posOk(posi, posj, word[i]) or posRepeated(posi, posj, posChars)) return false;
    // ultima letra de la palabra
    if (i == word.size() - 1) {
        
        wordSearch[posi][posj] = word[i];
        return true;
    }

    posChars[i] = {posi,posj};
    // dirVisited[8] es el contador para ver si ya se han mirado las 8 direcciones
    vector<int> dirVisited(9,0);
    bool charUsed = false;
    int dir;
    do {
        
        dir = rand() % 8;
        // hasta encontrar una direccion que no se ha usado
        while (dirVisited[dir] == 1) dir = rand() % 8;
        dirVisited[dir] = 1;
        ++dirVisited[8];
        charUsed = addWordRec(posi + diri[dir], posj + dirj[dir], word, i + 1, posChars);
    }
    while(!charUsed and dirVisited[8] < 8);

    if (charUsed) {
        
        wordSearch[posi][posj] = word[i];
        return true;
    }
    return false;
}

// Funciones publicas

WordSearch::WordSearch(int n) {
    
    wordSearch = Matrix(n, Row(n,'*'));
}

void WordSearch::addWord(const string& word) {
    
    int posi, posj;
    bool wordPlaced = false;
    // no se me ocurre otra forma de comprobar si la posicion ya se ha mirado
    // tambien doy por hecho de que habra algun sitio por donde empezar
    // si no habria que usar otra EdD mas para controlar eso zzz
    int n = wordSearch.size();
<<<<<<< HEAD
    int posToTry = n*n;
    BoolMatrix posTried(n, BoolRow(n,false));
=======
    BoolMatrix posTried(n, BoolRow(n,false));
    int posToTry = n * n;
>>>>>>> victor
    do {
        posi = rand() % n;
        posj = rand() % n;
        if (!posTried[posi][posj]) {
            
            // vector del tamano de la palabra para tener ordenados cual es la posi y posj de la ultima letra de la palabra anadida
            PosChars posChars(word.size(), {-1,-1});
            wordPlaced = addWordRec(posi, posj, word, 0, posChars);
            posTried[posi][posj] = true;
            --posToTry;
        }
    }
    while(!wordPlaced and posToTry>0);

<<<<<<< HEAD
    if(posToTry == 0) cout << "WORD " << word << " WAS IMPOSSIBLE TO PLACE" << endl;
=======
    if(posToTry==0) cout << "WORD " << word << " WAS IMPOSSIBLE TO PLACE" << endl;
>>>>>>> victor
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

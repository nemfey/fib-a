#include "wordSearch.hh"
#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

WordSearch::WordSearch(int n) {
    
    wordSearch = Matrix(n, Row(n,'*'));
}

bool WordSearch::pos_ok(int posi, int posj, char c) {
    
    if (posi < 0 or posj < 0 or posi >= wordSearch.size() or posj >= wordSearch.size()) return false;
    if (wordSearch[posi][posj] == '*' or wordSearch[posi][posj] == c) return true;
    return false;
}

void WordSearch::addWord(const string& word){
    
    int posi, posj;
    bool wordFitted = false;
    while (not wordFitted) {
        
        do {
        
            posi = rand() % wordSearch.size();
            posj = rand() % wordSearch.size();
        }
        while(!pos_ok(posi,posj, word[0]));
        
    }
}

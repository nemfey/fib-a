#ifndef WORD_SEARCH
#define WORD_SEARCH

#include <vector>
#include <string>

using namespace std;

typedef vector<char> Row;
typedef vector<Row> Matrix;
typedef vector<pair<int,int>> PosChars;

class WordSearch {
    
    private:
        
        Matrix wordSearch;
        
        bool posOk(int posi, int posj, char c);
        
        bool posRepeated(int posi, int posj, const PosChars& posChars);
        
        bool addWordRec(int posi, int posj, const string& word, int n, PosChars& posChars);
        
        
    public:
        
        //constructora de la sopa de letras
        WordSearch(int n);
        
        void addWord(const string& word);
        
        void print();
};

#endif

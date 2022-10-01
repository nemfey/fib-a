#ifndef WORD_SEARCH
#define WORD_SEARCH

#include <vector>
#include <string>

using namespace std;

typedef vector<char> Row;
typedef vector<Row> Matrix;
typedef vector<pair<int,int>> PosChars;
typedef vector<bool> BoolRow;
typedef vector<BoolRow> BoolMatrix;

//                  NO N NE E SE S SO O
vector<int> diri = {-1,0,1,1,1,0,-1,-1};
vector<int> dirj = {-1,-1,-1,0,1,1,1,0};

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
        
        char toChar(int i, int j);
};

#endif

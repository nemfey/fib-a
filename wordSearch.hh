#ifndef WORD_SEARCH
#define WORD_SEARCH

#include <vector>
#include <string>

using namespace std;

typedef vector<char> Row;
typedef vector<Row> Matrix;

class WordSearch {
    
    private:
        
        Matrix wordSearch;
        
        bool pos_ok(int posi, int posj, char c);
        
    public:
        
        //constructora de la sopa de letras
        WordSearch(int n);
        
        void addWord(const string& word);
};

#endif

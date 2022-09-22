#include <iostream>
#include <stdlib.h>
#include <vector>
#include <string>

using namespace std;

typedef vector<char> Row;
typedef vector<Row> Matrix;

//                  NO N NE E SE S SO O
vector<int> diri = {-1,0,1,1,1,0,-1,-1};
vector<int> dirj = {-1,-1,-1,0,1,1,1,0};

/*
bool pos_ok(const Matrix& matrix, int posi, int posj, int dir, char nextchar) {
    // check out of boundaries position
    if(posi+diri[dir]>=matrix.size() || posj+dirj[dir]>=matrix.size() ||
        posi+diri[dir]<0 || posj+dirj[dir]<0) return false;

    char charpos = matrix[posi+diri[dir]][posj+dirj[dir]];
    return (charpos=='*' || charpos==nextchar);
}
*/

bool pos_ok (const Matrix &matrix, int posi, int posj, int dir, char nextchar) {
    int n = matrix.size();
    return (posi+diri[dir] >= 0 && posi+diri[dir] < n &&
            posj+dirj[dir] >= 0 && posj+dirj[dir] < n &&
            (matrix[posi+diri[dir]][posj+dirj[dir]] == '*' || matrix[posi+diri[dir]][posj+dirj[dir]] == nextchar));
} 

// n is matrix size (nxn)
// words are 20 words to add in the matrix randomly
Matrix initialize(int n, vector<string> words) {
    Matrix matrix = Matrix(n, Row(n,'*'));

    int nwords = words.size();
    for(int x=0; x<nwords; ++x) {
        string word = words[x]; // word to add
        int posi, posj;
        
        do {
            posi = rand()%n;
            posj = rand()%n;
        }
        while(matrix[posi][posj]!='*');

        matrix[posi][posj] = word[0]; // first letter added

        int wordlength = word.size();
        for(int y=1; y<wordlength; ++y) {
            vector<bool> directions_used(8,false);
            int dir;
            do {
                dir = rand()%8; // next direction
                while(directions_used[dir]) {
                    dir = rand()%8;
                }
            }
            while(!pos_ok(matrix,posi,posj,dir,word[y]));
            
            posi += diri[dir];
            posj += dirj[dir];
            matrix[posi][posj] = word[y];
        }
    }


    return matrix;
}

int main() {
    srand(time(NULL));
    
    int n = 10;
    vector<string> words = {"joan","pol","victor","mario","DDADDDDDDDAD"};
    Matrix matrix = initialize(n,words);

    for(int i=0; i<n; ++i) {
        for(int j=0; j<n; ++j) {
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }
}
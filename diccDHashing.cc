#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <vector>
#include <algorithm>
#include <list>
#include "wordSearch.hh"
#include "DHashing.hh"
using namespace std;

//                  NO N NE E SE S SO O
vector<int> dirI = {-1,0,1,1,1,0,-1,-1};
vector<int> dirJ = {-1,-1,-1,0,1,1,1,0};

typedef pair<string,PosChars> Result;

// words must have 20 positions
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

// Recursive call
void searchDictionaryWordsRec(WordSearch& wordSearch, BoolMatrix& visited, DHashing& dictionary, list<Result>& result, PosChars& auxPos, string partialWord, string finalWord, int i, int j) {   
    if(not visited[i][j]) {
        visited[i][j] = true;
        partialWord.push_back(wordSearch.toChar(i,j));

        // check wether if words exists in dictionary
        if (dictionary.searchFinalWord(partialWord)) {
            auxPos.push_back({i,j});
            finalWord.push_back(wordSearch.toChar(i,j));
            result.push_back({finalWord,auxPos});
            auxPos.pop_back();
        }
        else if(dictionary.searchPrefixWord(partialWord)) {
            auxPos.push_back({i,j});
            int nexti, nextj;
            for(int k = 0; k < 8; k++) {         
                nexti = i + dirI[k];
                nextj = j + dirJ[k];
                finalWord.push_back(wordSearch.toChar(i,j));
                if(wordSearch.posOk(nexti,nextj)) {
                    searchDictionaryWordsRec(wordSearch, visited, dictionary, result, auxPos, partialWord, finalWord, nexti, nextj);
                }
                finalWord.pop_back();
            }
            auxPos.pop_back();
        }
        partialWord.pop_back();
        visited[i][j] = false;
    }
}

// first call to recursive searching words
void searchingWords(WordSearch& wordSearch, DHashing& dictionary, int n, int i, int j, list<Result>& result) {
    
    BoolMatrix visited(n, BoolRow(n, false));
    string w = "";
    PosChars auxPos;
    searchDictionaryWordsRec(wordSearch, visited, dictionary, result, auxPos, w, w, i, j);
}

int main() {
    srand(time(NULL));
    
    vector<string> dictionary;
    string w;
    while(cin>>w) {
        dictionary.push_back(w);
    }
    
    vector<string> words(20);
    chooseWordsFromDictionary(dictionary,words);
    
    // initialize the word search
    int n = rand() % 16 + 10;
    WordSearch wordSearch(n);   
    for (int i = 0; i < 20; i++) {
        wordSearch.addWord(words[i]);
    }

    int wordsSize = words.size();
    for (int i = 0; i < wordsSize; i++) cout << words[i] << "  ";
    cout << endl << endl;

    // word search created
    wordSearch.print();

    // initialization started
    
    int len = 0;
    for(int i=0; i<dictionary.size(); ++i) len += dictionary[i].size();
    DHashing dHashing = DHashing(len);

    for(int i=0; i<dictionary.size(); ++i) {
        int wSize = dictionary[i].size();
        string w = "";
        for(int j=0; j<wSize; ++j) {
            w.push_back(dictionary[i][j]);
            pair<string,bool> p = make_pair(w,j==wSize-1);
            dHashing.insert(p);
        }
    }

    // initialization ended

    // finding started

    list<Result> wordsFound;
    for(int i = 0; i < n; i++) {    
        for(int j = 0; j < n; j++) {     
            searchingWords(wordSearch, dHashing, n, i, j, wordsFound);
        }
    }

    // finding ended
    
    // print words found in the word search
    cout << endl << "WORDS FOUND: " << wordsFound.size() << endl;
    
    list<Result>::const_iterator it;
    for(it = wordsFound.begin(); it!= wordsFound.end(); ++it) {       
        Result r = *it;
        cout << r.first << " -> ";
        int vsize = r.second.size();
        for (int i = 0; i < vsize; i++) {            
            cout << '{' << r.second[i].first << ',' << r.second[i].second << "} (" << wordSearch.toChar(r.second[i].first,r.second[i].second) << ")";
            if(i != vsize -1) cout << " , ";
        }
        cout << endl;   
    }
    cout << endl << "Words found: " << wordsFound.size() << endl;
}

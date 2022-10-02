OPCIONS = -D_GLIBCXX_DEBUG -O2 -Wall -Wextra -Werror -Wno-sign-compare -std=c++11

diccTrie.exe: diccTrie.o wordSearch.o 
	g++ -o diccTrie.exe diccTrie.o wordSearch.o 

diccTrie.o: diccTrie.cc wordSearch.hh 
	g++ -c diccTrie.cc $(OPCIONS)

diccSortedVector.exe: diccSortedVector.o wordSearch.o 
	g++ -o diccSortedVector.exe diccSortedVector.o wordSearch.o 

diccSortedVector.o: diccSortedVector.cc wordSearch.hh 
	g++ -c diccSortedVector.cc $(OPCIONS)

wordSearch.o: wordSearch.cc wordSearch.hh
	g++ -c wordSearch.cc $(OPCIONS)

clean:
	rm *.exe
	rm *.o

#include "trie.hpp"
#include <stdlib.h>  
#include <sstream>

int main()
{
	SuffixTree A;




	// parse input lines until I find newline
	for(std::string line; std::getline(std::cin, line) && line.compare(""); ) {
	 	std::stringstream ss(line);
	    std::string string_weight;
	    ss >> string_weight;
	    int weight = std::stoi(string_weight);
	    // I am just going to put these words into a vector
	    // you probably want to put them in your trie
	    std::vector<std::string> words;
	    for(std::string word; ss >> word;) {
	    	words.push_back(word);
	    }
	    A.add(words, weight);
	    // don't forget to do something with the weight
	}
	// parse query line
	std::string query;
	std::getline(std::cin, query);
	std::stringstream sss(query);

	std::vector<std::string> queryWords;
	for(std::string w; sss >> w;){
		queryWords.push_back(w);
	}

	A.printChildren(queryWords);
	A.printMaxDegreeNode();

	return 0;
	}

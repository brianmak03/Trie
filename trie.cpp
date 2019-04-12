#include "trie.hpp"

void SuffixTree::add(vector<string> sentence, int sentenceWeight){
	int length = sentence.size();
	node* it = &root;
	
	for(int i=0; i<length; i++){
	  
		if (it->children.count(sentence[i]) == 0){
			it->numChildren++;
			it->children[sentence[i]] = new node;
			it->children[sentence[i]]->word = sentence[i];
		        if(it->numChildren > maxDegree && i>0){
			  maxDegree = it->numChildren;
			  maxWord = it->word;
			}
		}
		it = it->children[sentence[i]];
	}
	it->weight = sentenceWeight;

}

void SuffixTree::printChildren(vector<string> searchTerm){
	int length = searchTerm.size();
	map<int, string> subTree;
	map<int, string> subsubTree;
	node* it = &root;
	node* buffit;

	for(int i=0; i<length; i++){
		if(it->children.count(searchTerm[i])==0){
		  cout<<"No valid completion"<<endl;
		  return;
		}
		it = it->children[searchTerm[i]];
	}

	for(map<string, node*>::iterator subit = it->children.begin(); subit != it->children.end(); ++subit){
		buffit = subit->second;
		subsubTree = getSubTree(buffit);
		for(map<int, string>::iterator subsubit = subsubTree.begin(); subsubit != subsubTree.end(); ++subsubit){
			subTree[subsubit->first] = subsubit->second;
		}
	}

	for(map<int, string>::reverse_iterator rit = subTree.rbegin(); rit != subTree.rend(); ++rit){
	  cout<<rit->second<<endl;
	}

}

map<int,string> SuffixTree::getSubTree(node* start){
	map<int,string> subtree;
	map<int,string> subsubtree;
	node* bufferit;

	//case 1: no children (weight >=0 too?)
	if(start->children.size() == 0){
		subtree[start->weight] = start->word;
		return subtree;
	}

	//case 2: weight < 0 (type map::iterator != node*)
	else{
		for(map<string, node*>::iterator subIt = start->children.begin(); subIt != start->children.end(); ++subIt){
			bufferit = subIt->second;
			subsubtree = getSubTree(bufferit);
			for(map<int, string>::iterator subsubIt = subsubtree.begin(); subsubIt != subsubtree.end(); ++subsubIt){
				subtree[subsubIt->first] = start->word + " " + subsubIt->second;
			}
		}

		//case 3: weight >= 0 and has children
		if(start->weight >= 0){
			subtree[start->weight] = start->word;
		}

		return subtree;
	}
}

void SuffixTree::printMaxDegreeNode(){
  if(maxDegree > 0){
    cout<<maxWord<<" "<<maxDegree<<endl;
  }
}




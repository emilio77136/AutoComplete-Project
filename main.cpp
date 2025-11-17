#include <iostream>
#include <string>
#include <vector>
using namespace std;



//========= TRIE NODE =========
struct TrieNode{ 

	TrieNode* next[26];
	bool endFlag;

	TrieNode();
};


//======== TRIE CLASS =======
class Trie{
private: 
	TrieNode* root;
	int key = 'a';

	bool deleteHelper(TrieNode* node, const string& word, int depth);
	void suggestHelper(TrieNode* node, string prefix, vector<string>& list);

public:
	Trie();
	
	void insertWord(const string& word);
	bool searchWord(const string& word);
	void deleteWord(const string& word);
	vector<string> suggestWords(const string& prefix);
};

//========= MAIN ========
int main(){
return 0;
}



//========= FUNCTIONS ==========

TrieNode::TrieNode(){
	endFlag = false;
	for(int i = 0; i < 26; i++){
		next[i] = nullptr;
	}
}

Trie::Trie(){
	root = new TrieNode();
}


//-----INSERT-----

void Trie::insertWord(const string& word){
	TrieNode* current = root;
	for(char ch : word){
		int idx = ch - key;
		if(!current->next[idx]){
		 current->next[idx] = new TrieNode();
		}
	current = current->next[idx];
	}
	current->endFlag = true;
}


//-----SEARCH-----
bool Trie:: searchWord(const string& word){
	TrieNode* current = root;

	for(char ch : word){
	 int idx = ch - key;
		if(!current->next[idx]){
		return false;
		}
	current = current->next[idx];
	}
	return current->endFlag;
}


//-----DELETE WORD-----
void Trie::deleteWord(const string& word){
	if(searchWord(word)){
	  deleteHelper(root, word, 0);
	  cout << word << "' removed.\n";
	}else{
	  cout << "Word not found.\n";
	}

}

//-----DELETE HELPER-----
bool Trie::deleteHelper(TrieNode* node, const string& word, int depth){
if(!node){
  return false;
}

	if(depth == (int)word.size()){
	  if(!node->endFlag){
	    return false;
	  }

	node->endFlag = false;

	for(int i = 0; i < 26; i++){
	  if(node->next[i]){
	    return false;
	  }
	}

	reutrn true;
	}

	int idx = word[depth] - key;

	if(deleteHelper(node->next[idx], word,depth + 1)){
	  delete node->next[idx];
	  node->next[idx] = nullptr;

	  if(!node->endFlag){
	    for(int i =0; i < 26; i++){
	 	 return false;
		}
	  return true;
	    }
	}
	return false;
}


//-----SUGGEST WORD-----
vector<string> Trie:: suggestWords(const string& prefix){
	TrieNode* current = root;
	vector<string> results;
	
	for(char ch : prefix){
	  int idx = ch - key;
	  if(!current->next[idx]){
	      return results;
	    }
	current = current->next[idx];
	}
suggestHelper(current, prefix, results);
return results;

}


//-----SUGGEST HELPER-----
void Trie::suggestHelper(TrieNode* node, string prefix, vector<string>& list){
  if(node->endFlag){
    list.push_back(prefix);
  }

  for(int i = 0; i < 26; i++){
      if(node->next[i]){
	 suggestHelper(node->next[i], prefix + char(key +i),list);
	}
  }
}

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






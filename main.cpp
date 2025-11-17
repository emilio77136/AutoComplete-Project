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

	Trie autoComplete;
	
	autoComplete.insertWord("cat");
	autoComplete.insertWord("car");
	autoComplete.insertWord("cart");
	autoComplete.insertWord("dog");
	autoComplete.insertWord("dove");
	autoComplete.insertWord("door");

	int choice;
	string input;

	do{
		cout << "\n-----AUTOCOMPLETE MENU-----\n";
		cout << "1. Insert Word \n";
		cout << "2. Search Word \n";
		cout << "3. Delete Word \n";
		cout << "4. AutoComplete Suggest \n";
		cout << "5. Exit \n";
		cout << "Enter choice: ";
		cin >> choice;

		switch(choice){
			case 1:
			cout << "Enter word: ";
			cin >> input;
			autoComplete.insertWord(input);
			cout << "Inserted. \n";
			break;
			
			case 2:
			cout << "Enter word: ";
			cin >> input;
			cout << (autoComplete.searchWord(input) ? "Found.\n" : "Not Found. \n");
			break;

			case 3:	
			cout << "Enter word: ";
			cin >> input;
			autoComplete.deleteWord(input);
			break;

			case 4:
			cout << "Enter prefix: ";
			cin >> input;
			{
			  vector<string> out = autoComplete.suggestWords(input);
			  if(out.empty()){
				cout << "No suggestions. \n";
			    }else{
				cout << "Suggestions: \n";
				for(auto& s : out){
				 cout << " - " << s << "\n";
				}
			    }
			}
			break;

			case 5: 
			cout << "Goodbye! \n";
			break;
			
			default: 
			cout << "Invalid choice. \n";
		}

		}while(choice != 5);

return 0;	
};



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
bool Trie::searchWord(const string& word){
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

	return true;
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

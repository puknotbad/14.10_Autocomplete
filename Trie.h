#pragma once
#include <iostream>

#define ALPHABET_SIZE 26 //eng

// Структура узла дерева
struct TrieNode
{
	struct TrieNode* children[ALPHABET_SIZE];
	// isEndOfWord - true, если ключ является концом слова
	bool isEndOfWord;
	int nWords = 0; // the number of prefixes containing this node in the trie
};

class Trie
{
	TrieNode* getNewNode(void);
	TrieNode* _root;

public:
	Trie(){
		_root = getNewNode();
	}

	~Trie() {};

	TrieNode* getRoot();
	void insert(TrieNode* root, std::string& key);

	bool search(struct TrieNode* root, std::string key);

	bool isEmpty(TrieNode* root);

	TrieNode* remove(TrieNode* root, std::string key, int depth);

	void findMinPrefixes(TrieNode* root, char buf[], int ind, std::string& res); 

	std::string searchWordByPrefix(std::string prefix);
	std::string completeWordByPrefix(std::string prefix);


};


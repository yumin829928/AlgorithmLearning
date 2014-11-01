// prefix.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <string>
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

void shortestPrefix1(char** words, int size) {
	vector<string> vWords;
	for (int i = 0; i < size; ++i) {
		vWords.push_back(string(words[i]));
	}

	sort(vWords.begin(), vWords.end());
	int prevDiff = -1;
	for (int i = 0; i < size - 1; ++i) {
		int minLength = min(vWords[i].size(), vWords[i+1].size());
		int j = 0;
		for (; j < minLength; ++j) {
			if (vWords[i][j] != vWords[i+1][j]) {
				break;
			}
		}

		if (j == minLength) {
			cout << vWords[i] << ": " << vWords[i] << endl;
		}
		else {
			int minPrefix = max(prevDiff, j);
			cout << vWords[i] << ": " << vWords[i].substr(0, minPrefix + 1) << endl;
		}
		prevDiff = j;
	}

	cout << vWords[size-1] << ": " << vWords[size-1].substr(0, prevDiff + 1) << endl;
}

struct TrieNode {
	int count;
	TrieNode* children[26];

	TrieNode() {
		count = 0;
		memset(&children[0], 0, sizeof(TrieNode*) * 26);
	}
};

class TrieTree {
public:
	TrieTree() {
		root = NULL;
	}

	int getTotalCount() {
		return root == NULL ? 0: root->count;
	}

	void add(string str) {
		if (root == NULL) {
			root = new TrieNode();
		}
		TrieNode* branch = root;
		branch->count++;
		for (int i = 0; i < str.size(); ++i) {
			int index = str[i] - 'a';
			if (branch->children[index] == NULL) {
				branch->children[index] = new TrieNode();
			}
			branch = branch->children[index];
			branch->count++;
		}
	}

	string shortestPrefix(string str) {
		TrieNode* branch = root;
		int i = 0;
		for (; i < str.size(); ++i) {
			branch = branch->children[str[i]-'a'];
			if (branch->count == 1) {
				break;
			}
		}

		if (i == str.size()) {
			return str;
		}
		else {
			return str.substr(0, i+1);
		}
	}

private:
	TrieNode* root;
};

int _tmain(int argc, _TCHAR* argv[])
{
	char *words[] = {"zebra", "dog", "duck", "dove", "frog", "franch", "fly", "zoo", "great"};

	cout << "###Shortest prefix by sorting###" << endl;
	shortestPrefix1(words, sizeof(words)/sizeof(char*));

	TrieTree trie;
	for (int i = 0; i < sizeof(words)/sizeof(char*); ++i) {
		trie.add(words[i]);
	}

	cout << "\n###Shortest prefix by Trie tree###" << endl;
	for (int i = 0; i < sizeof(words)/sizeof(char*); ++i) {
		cout << words[i] << ": " << trie.shortestPrefix(words[i]) << endl;
	}
	cout << "Total number of strings = " << trie.getTotalCount() << endl;

	return 0;
}
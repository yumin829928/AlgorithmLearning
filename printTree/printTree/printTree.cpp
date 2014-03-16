// printTree.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <vector>
#include <stack>
using namespace std;

struct TreeNode {
	int val;
	TreeNode *left;
	TreeNode *right;
	TreeNode(int value) {val = value; left = right = NULL;}
};

void printVector(vector<int> &v) {
	for (int i = 0; i < v.size(); ++i) {
		cout << v[i] << " ";
	}
	cout << endl;
}

void printPathsRecursive(TreeNode *root, vector<int> &path) {
	if (root == NULL) {
		return;
	}

	path.push_back(root->val);
	if (root->left == NULL && root->right == NULL) {
		printVector(path);
	}
	else {
		if (root->left != NULL) {
			printPathsRecursive(root->left, path);
		}
		if (root->right != NULL) {
			printPathsRecursive(root->right, path);
		}
	}
	path.pop_back();
}

void printPathsIterative(TreeNode *root) {
    if (root == NULL) {
        return;
    }
    
	TreeNode *prev = NULL;
    vector<int> path;
    stack<TreeNode*> nodes;
    while (root != NULL || !nodes.empty()) {
        while (root != NULL) {
            nodes.push(root);
            path.push_back(root->val);
            root = root->left;
        }
        if (!nodes.empty()) {
            root = nodes.top();
            if (root->right == NULL || root->right == prev) {
				if (root->left == NULL && root->right == NULL) {
					printVector(path);
				}
                nodes.pop();
				path.pop_back();
				prev = root;
                root = NULL;
            }
            else {
                root = root->right;
            }
        }
    }
}

void printLevel(TreeNode *root, int level) {
	if (root == NULL || level < 1) {
		return;
	}

	if (level == 1) {
		cout << root->val << " ";
		return;
	}

	printLevel(root->left, level - 1);
	printLevel(root->right, level - 1);
}

int getDepth(TreeNode *root) {
	if (root == NULL) {
		return 0;
	}

	int ldepth = getDepth(root->left);
	int rdepth = getDepth(root->right);
	return (max(ldepth, rdepth) + 1);
}

void printTreeByLevel(TreeNode *root) {
	int levels = getDepth(root);
	for (int i = 1; i <= levels; ++i) {
		printLevel(root, i);
		cout << endl;
	}
}

int _tmain(int argc, _TCHAR* argv[])
{
	TreeNode *root = new TreeNode(1);
	root->left = new TreeNode(2);
	root->left->left = new TreeNode(3);
	root->left->right = new TreeNode(5);
	root->right = new TreeNode(4);
	root->right->right = new TreeNode(6);
	root->right->right->left = new TreeNode(7);
	root->right->right->left->right = new TreeNode(9);
	root->right->right->right = new TreeNode(8);

	cout << "Print tree paths by iterative method: " << endl;
	printPathsIterative(root);

	cout << "Print tree paths by recursive method: " << endl;
	vector<int> path;
	printPathsRecursive(root, path);

	cout << "Print tree by level: " << endl;
	printTreeByLevel(root);

	return 0;
}


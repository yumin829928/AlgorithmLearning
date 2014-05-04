//

#include "stdafx.h"
#include "tree.h"
#include <iostream>
using namespace std;

// Private functions go here
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

// Public functions go here
void printTreeByLevel(TreeNode *root) {
	int levels = getDepth(root);
	for (int i = 1; i <= levels; ++i) {
		printLevel(root, i);
		cout << endl;
	}
}
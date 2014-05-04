// bst.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "tree.h"
#include <iostream>
using namespace std;

TreeNode* joinLists(TreeNode *first, TreeNode *second) {
	if (first == NULL) {
		return second;
	}
	if (second == NULL) {
		return first;
	}

	TreeNode *firstTail = first->left;
	TreeNode *secondTail = second->left;
	firstTail->right = second;
	second->left = firstTail;
	first->left = secondTail;
	secondTail->right = first;

	return first;
}

TreeNode *convertBSTToList(TreeNode *root) {
	if (root == NULL) {
		return NULL;
	}

	TreeNode *small = convertBSTToList(root->left);
	TreeNode *big = convertBSTToList(root->right);

	root->left = root;
	root->right = root;
	TreeNode *head = joinLists(small, root);
	head = joinLists(head, big);

	return head;
}

TreeNode *constructBST(int *a, int start, int end) {
	if (a == NULL || start > end) {
		return NULL;
	}

	int mid = (start + end) / 2;
	TreeNode *root = new TreeNode(a[mid]);
	root->left = constructBST(a, start, mid - 1);
	root->right = constructBST(a, mid + 1, end);
	
	return root;
}

void printList(TreeNode *head, bool inverse) {
	if (head == NULL) {
		return;
	}

	cout << head->val << " ";
	if (inverse) {
		TreeNode *cur = head->left;
		while (cur != head && cur != NULL) {
			cout << cur->val << " ";
			cur = cur->left;
		}
	}
	else {
		TreeNode *cur = head->right;
		while (cur != head && cur != NULL) {
			cout << cur->val << " ";
			cur = cur->right;
		}
	}
	cout << endl;
}

void convertBSTToListTest() {
	int a[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
	TreeNode *root = constructBST(a, 0, sizeof(a)/sizeof(int) - 1);
	printTreeByLevel(root);

	TreeNode *head = convertBSTToList(root);
	cout << "The increasing list is: " << endl;
	printList(head, false);
	cout << "The decreasing list is: " << endl;
	printList(head->left, true);
}

int _tmain(int argc, _TCHAR* argv[])
{
	convertBSTToListTest();

	return 0;
}


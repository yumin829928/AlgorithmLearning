// Tree definition

struct TreeNode {
	int val;
	TreeNode *left;
	TreeNode *right;
	TreeNode(int value) {val = value; left = right = NULL;}
};

void printTreeByLevel(TreeNode *root);
#include<iostream>

using namespace std;


struct TreeNode {
	int val;
	struct TreeNode *left;
	struct TreeNode *right;

	TreeNode(int x) :
	val(x), left(NULL), right(NULL) {
	}
};

class Solution {
public:
	TreeNode *prev = NULL;
	TreeNode *first;
	void fun(TreeNode * node)
	{
		node->left = prev;
		if (prev != NULL){
			prev->right = node;
		}
		else{
			first = node;
		}
		prev = node;
	}
	void Inorder(TreeNode *root){
		if (root == NULL){
			return;
		}

		Inorder(root->left);
		fun(root);
		Inorder(root->right);
	}
	TreeNode* Convert(TreeNode* pRootOfTree)
	{
		first = NULL;
		Inorder(pRootOfTree);

		return first;
	}
};

// A B D # E # # C # F

#include<assert.h>
/**
* Definition for a binary tree node.
* struct TreeNode {
*     int val;
*     struct TreeNode *left;
*     struct TreeNode *right;
* };
*/


struct TreeNode* buildTree(int* preorder, int preorderSize, int* inorder, int inorderSize){
	assert(preorderSize == inorderSize);
	if (preorderSize == 0){
		return NULL;
	}

	//从前序遍历中找到根结点
	int rootValue = preorder[0];
	//根据根的值，在中序遍历中找到其下标
	int rindex = -1;
	for (int i = 0; i < inorderSize; i++){
		//假设树的结点不重复
		if (inorder[i] == rootValue){
			rindex = i;
		}
	}
	assert(rindex != -1);

	//创建根
	struct TreeNode* root = (struct TreeNode *)malloc(sizeof(struct TreeNode));
	root->val = rootValue;
	//创建左子树
	root->left = buildTree(preorder + 1, rindex, inorder, rindex);
	//创建右子树
	root->right = buildTree(
		preorder + 1 + rindex,
		preorderSize - 1 - rindex,
		inorder + rindex + 1,
		inorderSize - rindex - 1);

	return root;
}
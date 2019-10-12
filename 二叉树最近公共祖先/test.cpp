#include<iostream>

using namespace std;

 //Definition for a binary tree node.
 struct TreeNode {
     int val;
     TreeNode *left;
     TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 };

class Solution {
public:
	TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
		if (root == nullptr || root == p || root == q)
		{
			return root;
		}
		TreeNode* left = lowestCommonAncestor(root->left, p, q);
		TreeNode* right = lowestCommonAncestor(root->right, p, q);

		return left == nullptr ? right : (right == nullptr ? left : root);

	}
};

//查找

struct TreeNode *Find(struct TreeNode * root, int val)
{
	if (root == NULL){
		return NULL;
	}

	if (root->val == val){
		return root;
	}

	struct TreeNode *left = Find(root->left, val);
	if (r != NULL){
		//左子树找到了，不需要去右子树找到
		return r;
	}
	
	//左子树没找到，去右子树找
	struct TreeNode *right = Find(root->right, val);
	if (right != NULL){
		return right;
	}
	else
	{
		return NULL;
	}
}
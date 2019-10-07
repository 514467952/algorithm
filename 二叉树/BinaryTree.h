#pragma once
#include<stdio.h>
#include<malloc.h>
typedef struct Node{
	int val;
	struct Node *left;
	struct Node *right;
};

//前序遍历
void preorder(Node *root){
	if (root == NULL){
		return;
	}

	printf("%d", root->val); //根
	preorder(root->left);    //左
	preorder(root->right);	//右
}

void inorder(Node *root){
	if (root == NULL){
		return;
	}

	inorder(root->left);    //左
	printf("%d", root->val); //根
	inorder(root->right);   //右
}

Node * buyNode(int val){
	Node *node = (Node *)malloc(sizeof(Node));
	node->val = val;
	node->left = node->right = NULL;
	return node;
}


//int *array;
//int size;
//
//
//void _preordertraversal(struct treenode *root){
//	if (root == null){
//		return;
//	}
//
//	处理根结点
//	array[size++] = root->val;
//	_preordertraversal(root->left);
//	_preordertraversal(root->right);
//}
//
//
//int* preordertraversal(struct treenode* root, int* returnsize){
//	array = (int *)malloc(sizeof(int)* 100 * 1000);
//	size = 0;
//
//	_preordertraversal(root);
//
//	*returnsize = size;
//	return array;
//}


//判读子树

bool isSameTree(struct TreeNode *p, struct TreeNode *q)
{
	if (p == NULL && q == NULL){
		return true;
	}
	if (p == NULL || q == NULL){
		return false;
	}

	return q->val == p->val
		&&isSameTree(q->left, p->left)
		&& isSameTree(q->right, p->right);
}

bool preorderTraversal(struct TreeNode *root, struct TreeNode *t){

	//bool root_ret ;
	if (root == NULL){
		return false;
	}

	//根
	if (root->val == t->val && isSameTree(root, t)){
		return true;
	}

	//左
	bool left = preorderTraversal(root->left, t);
	if (left == true){
		return true;
	}
	//右
	bool right = preorderTraversal(root->right, t);

	return  left || right;
}

bool isSubtree(struct TreeNode* s, struct TreeNode* t){
	if (t == NULL){
		return true;
	}

	return preorderTraversal(s, t);
}

//二叉树最大深度
/**
* Definition for a binary tree node.
* struct TreeNode {
*     int val;
*     struct TreeNode *left;
*     struct TreeNode *right;
* };
*/


int maxDepth(struct TreeNode* root){
	if (root == NULL){
		return 0;
	}

	int left = maxDepth(root->left);
	int right = maxDepth(root->right);

	return (left > right ? left : right) + 1;
}


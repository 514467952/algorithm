#define _CRT_SECURE_NO_WARNINGS

#include<stdlib.h>
#include<stdio.h>
#include<malloc.h>
#include<string.h>
#include<iostream>
using namespace std;
typedef struct  TreeNode
{
	struct TreeNode *left;
	struct TreeNode *right;

	char val;
}TreeNode;

typedef struct Result{
	TreeNode * root; //构建的树的根结点
	int used;      //构建过程中用掉的val个数
} Result;


//char * tree2str_array;
//int tree2str_size;
//void  _tree2str(TreeNode *root)
//{
//	if (root == NULL){
//		return ;
//	}
//	tree2str_array[tree2str_size++] = '(';
//	tree2str_array[tree2str_size++] = root->val;
//
//	if (root->left == NULL){
//		tree2str_array[tree2str_size++] = '(';
//		tree2str_array[tree2str_size++] = ')';
//	}
//	else
//	{
//		_tree2str(root->left);
//	}
//	_tree2str(root->right);
//	tree2str_array[tree2str_size++] = ')';
//
//}
//
//char * tree2str(TreeNode *root)
//{
//	//根不打印
//	if (root == NULL)
//	{
//		return;
//	}
//	tree2str_array = (char *)malloc(sizeof(char)* 100 * 10000);
//	tree2str_size = 0;
//
//	tree2str_array[tree2str_size++] = root->val;
//	if (root->left == NULL){
//		tree2str_array[tree2str_size++] = '(';
//		tree2str_array[tree2str_size++] = ')';
//	}
//	else
//	{
//		_tree2str(root->left);
//	}
//	_tree2str(root->right);
//
//	tree2str_array[tree2str_size] = '\0';
//	return tree2str_array;
//}

class Solution {
public:
	string tree2str(TreeNode* t) {
		if (t == nullptr)
			return "";
		stringstream ss;
		function<void(TreeNode*)> helper = [&ss, &helper](TreeNode* t){
			ss << t->val;
			if (t->left == nullptr){
				if (t->right != nullptr){
					ss << "()(";
					helper(t->right);
					ss << ')';
				}
			}
			else if (t->right == nullptr){
				ss << '(';
				helper(t->left);
				ss << ')';
			}
			else{
				ss << '(';
				helper(t->left);
				ss << ")(";
				helper(t->right);
				ss << ')';
			}
		};
		helper(t);
		string s;
		ss >> s;
		return s;
	}
};

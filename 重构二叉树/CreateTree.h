#define _CRT_SECURE_NO_WARNINGS

#include<stdlib.h>
#include<stdio.h>
#include<malloc.h>
#include<string.h>
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

Result CreateTree(char preorder[], int size){
	if (size == 0){
		Result result;
		result.root = NULL;
		result.used = 0;
		return result;
	}

	char rootVal = preorder[0];
	if (rootVal == '#'){
		Result result;
		result.root = NULL;
		result.used = 1;    //'#'号在数组中也占一个位置
		return result;
	}

	//根的过程
	TreeNode * root = (TreeNode *)malloc(sizeof(TreeNode));
	root->val = rootVal;
	root->left = root->right = NULL;

	//左子树
	Result left_result = CreateTree(preorder + 1, size - 1);

	//右子树
	Result right_result = CreateTree(preorder + 1 + left_result.used, size - 1 - left_result.used);

	root->left = left_result.root;
	root->right = right_result.root;

	Result result;
	result.root = root;
	result.used = 1 + left_result.used + right_result.used;
	return result;
}


void InorderTraversal(TreeNode * root){
	if (root == NULL){
		return;
	}

	InorderTraversal(root->left);
	printf("%c", root->val);
	InorderTraversal(root->right);
}

//求二叉树中所有结点的个数
void TreeSize(TreeNode *root, int *size){
	if (root == NULL){
		return;
	}

	(*size)++;
	TreeSize(root->left,size);
	TreeSize(root->right,size);

}

//递推的思想
int TreeSize2(TreeNode *root){
	if (root == NULL){
		return 0;
	}

	return 1 + TreeSize2(root->left) + TreeSize2(root->right);
}



//求叶子结点个数
void LeafSize(TreeNode *root, int *leaf_size){
	if (root == NULL){
		return;
	}
	if (root->left == NULL && root->right == NULL){
		leaf_size++;
	}

	LeafSize(root->left, leaf_size);
	LeafSize(root->right, leaf_size);
}

//递推_叶子结点
int LeafSize2(TreeNode *root){
	if (root == NULL){
		return 0;
	}

	if (root->left == NULL && root->right == NULL){
		return 1;
	}

	return LeafSize2(root->left) + LeafSize2(root->right);
}


//求第k层结点个数
//左子树已知第K-1层结点个数left
//右子树第K-1层结点个数 right
/* 求第K层结点个数
	left + right
	终止条件 ： 
	空树   return 0

 */

int LevelK(TreeNode *root, int k)
{
	if (root == NULL)
	{
		return 0;
	}

	//这里不是空树
	if (k == 1){
		return 1;
	}

	return LevelK(root->left, k - 1) + LevelK(root->right, k - 1);

}

//查找val = x的值
/*1. 先看根的val
  2. 在根不是我们要找的情况下，去左子树继续查找
  3. 在左子树中也没有找到，继续去右子树中查找
  4. 空树 return NULL
*/
TreeNode *Find(TreeNode *root, char x){
	if (root == NULL){
		return NULL;
	}
	//根
	if (root->val == x){
		return root;
	}
	//左子树不为空就在左子树找
	TreeNode *result = Find(root->left, x);
	if (result != NULL){
		return result;
	}

	//左子树没找到
	//如果右子树没找到，那么整个树都找不到
	return Find(root->right, x);

}


void TestCreateTree()
{
	char *preorder="abc##de#g##f###";
	//scanf("%s", preorder);
	int size = strlen(preorder);

	Result result = CreateTree(preorder, size);

	int node_size = 0;
	TreeSize(result.root, &node_size);
	printf("结点个数:%d\n", node_size);



	InorderTraversal(result.root);
}

//层序遍历
#include<queue>
void LevelorderTraversal(TreeNode *root)
{

	if (root == NULL){
		return;
	}

	std::queue<TreeNode *>qu;

	qu.push(root);

	while (!qu.empty())
	{
		TreeNode *front = qu.front();
		qu.pop();
		printf("%c", front->val);
		//如果有左孩子
		if (front->left != NULL){
			qu.push(front->left);
		}
		//如果有右孩子
		if (front->right != NULL){
			qu.push(front->right);
		}
	}
}

//判断二叉树是否为完全二叉树
bool IsCompleteBinaryTree(TreeNode *root)
{
	if (root == NULL){
		return true;
	}
	std::queue<TreeNode *>qu;
	qu.push(root);

	while (1)
	{
		TreeNode *front = qu.front();
		qu.pop();
		if (front == NULL){
			//遇到空结点了
			break;
		}
		qu.push(front->left);
		qu.push(front->right);
	}
	//检查队列中是否还有非空结点
	while(!qu.empty()){
		TreeNode *front = qu.front();
		qu.pop();
		if (front != NULL){
			return false;
		}
	}
	return true;

}


//


void Test()
{
	char *preorder = "abc##de#g##f###";
	//scanf("%s", preorder);
	int size = strlen(preorder);

	Result result = CreateTree(preorder, size);

	printf("中序遍历:\n");
	InorderTraversal(result.root);
	printf("\n");
	printf("层序遍历:\n");
	LevelorderTraversal(result.root);
	printf("\n");
}


//二叉树转化为前序字符串，如果右子树为空，可以省略
void _tree2str(TreeNode *root){
	if (root == NULL){
		return ;
	}

	printf("(");
	printf("%c", root->val);
	if (root->left == NULL){
		printf("()");
	}
	else
	{
		_tree2str(root->left);;
	}
	_tree2str(root->right);
	printf(")");
}

char * tree2str_array;

char * tree2str(TreeNode *root)
{
	if (root == NULL){
		return;
	}
	

	printf("%c", root->val);
	if (root->left == NULL){
		printf("()");
	}
	else
	{
		_tree2str(root->left);
	}
	_tree2str(root->right);
}
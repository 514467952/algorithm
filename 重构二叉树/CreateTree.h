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
	TreeNode * root; //���������ĸ����
	int used;      //�����������õ���val����
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
		result.used = 1;    //'#'����������Ҳռһ��λ��
		return result;
	}

	//���Ĺ���
	TreeNode * root = (TreeNode *)malloc(sizeof(TreeNode));
	root->val = rootVal;
	root->left = root->right = NULL;

	//������
	Result left_result = CreateTree(preorder + 1, size - 1);

	//������
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

//������������н��ĸ���
void TreeSize(TreeNode *root, int *size){
	if (root == NULL){
		return;
	}

	(*size)++;
	TreeSize(root->left,size);
	TreeSize(root->right,size);

}

//���Ƶ�˼��
int TreeSize2(TreeNode *root){
	if (root == NULL){
		return 0;
	}

	return 1 + TreeSize2(root->left) + TreeSize2(root->right);
}



//��Ҷ�ӽ�����
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

//����_Ҷ�ӽ��
int LeafSize2(TreeNode *root){
	if (root == NULL){
		return 0;
	}

	if (root->left == NULL && root->right == NULL){
		return 1;
	}

	return LeafSize2(root->left) + LeafSize2(root->right);
}


//���k�������
//��������֪��K-1�������left
//��������K-1������� right
/* ���K�������
	left + right
	��ֹ���� �� 
	����   return 0

 */

int LevelK(TreeNode *root, int k)
{
	if (root == NULL)
	{
		return 0;
	}

	//���ﲻ�ǿ���
	if (k == 1){
		return 1;
	}

	return LevelK(root->left, k - 1) + LevelK(root->right, k - 1);

}

//����val = x��ֵ
/*1. �ȿ�����val
  2. �ڸ���������Ҫ�ҵ�����£�ȥ��������������
  3. ����������Ҳû���ҵ�������ȥ�������в���
  4. ���� return NULL
*/
TreeNode *Find(TreeNode *root, char x){
	if (root == NULL){
		return NULL;
	}
	//��
	if (root->val == x){
		return root;
	}
	//��������Ϊ�վ�����������
	TreeNode *result = Find(root->left, x);
	if (result != NULL){
		return result;
	}

	//������û�ҵ�
	//���������û�ҵ�����ô���������Ҳ���
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
	printf("������:%d\n", node_size);



	InorderTraversal(result.root);
}

//�������
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
		//���������
		if (front->left != NULL){
			qu.push(front->left);
		}
		//������Һ���
		if (front->right != NULL){
			qu.push(front->right);
		}
	}
}

//�ж϶������Ƿ�Ϊ��ȫ������
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
			//�����ս����
			break;
		}
		qu.push(front->left);
		qu.push(front->right);
	}
	//���������Ƿ��зǿս��
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

	printf("�������:\n");
	InorderTraversal(result.root);
	printf("\n");
	printf("�������:\n");
	LevelorderTraversal(result.root);
	printf("\n");
}


//������ת��Ϊǰ���ַ��������������Ϊ�գ�����ʡ��
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
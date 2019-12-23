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
	//�ж��ǲ�����ͬ����
	bool isSameTree(TreeNode* pRoot1, TreeNode* pRoot2)
	{

		if (pRoot2 == NULL) return true; //����������һ������������
		if (pRoot1 == NULL) return false;//����Ϊ�գ�����false
		if (pRoot2->val == pRoot1->val) {        //����ֵ��ȣ��ٿ�����������ֵ�ǲ�����ͬ
			return isSameTree(pRoot1->left, pRoot2->left)
				&& isSameTree(pRoot1->right, pRoot2->right);
		}
		else //����ͬ������false;
			return false;
	}

	//�ж��ǲ�������
	bool HasSubtree(TreeNode* pRoot1, TreeNode* pRoot2)
	{

		bool result = false;
		if (pRoot2 != nullptr &&pRoot1 != nullptr)
		{
			if (pRoot1->val == pRoot2->val)
				result = isSameTree(pRoot1, pRoot2); //�� �ж��Ը�Ϊ�׵����������Ƿ���ȫ��ͬ
			if (!result)                                //������ǣ�����������
				result = HasSubtree(pRoot1->left, pRoot2); //�� 
			if (!result)                                //��������
				result = HasSubtree(pRoot1->right, pRoot2); //��
		}
		return result;
	}
};
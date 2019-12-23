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
	//判断是不是相同的树
	bool isSameTree(TreeNode* pRoot1, TreeNode* pRoot2)
	{

		if (pRoot2 == NULL) return true; //空树是任意一个子树的子树
		if (pRoot1 == NULL) return false;//大树为空，返回false
		if (pRoot2->val == pRoot1->val) {        //根的值相等，再看左右子树的值是不是相同
			return isSameTree(pRoot1->left, pRoot2->left)
				&& isSameTree(pRoot1->right, pRoot2->right);
		}
		else //不相同，返回false;
			return false;
	}

	//判断是不是子树
	bool HasSubtree(TreeNode* pRoot1, TreeNode* pRoot2)
	{

		bool result = false;
		if (pRoot2 != nullptr &&pRoot1 != nullptr)
		{
			if (pRoot1->val == pRoot2->val)
				result = isSameTree(pRoot1, pRoot2); //根 判断以根为首的两颗子树是否完全相同
			if (!result)                                //如果不是，看看左子树
				result = HasSubtree(pRoot1->left, pRoot2); //左 
			if (!result)                                //看右子树
				result = HasSubtree(pRoot1->right, pRoot2); //右
		}
		return result;
	}
};
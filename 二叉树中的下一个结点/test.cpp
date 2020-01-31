
struct TreeLinkNode {
int val;
struct TreeLinkNode *left;
struct TreeLinkNode *right;
struct TreeLinkNode *next;
TreeLinkNode(int x) :val(x), left(NULL), right(NULL), next(NULL) {

}
};

class Solution {
public:
	TreeLinkNode* GetNext(TreeLinkNode* pNode)
	{
		if (pNode == nullptr)
			return NULL;

		TreeLinkNode* pNext = nullptr;
		//如果一个结点有右子树
		if (pNode->right != nullptr)
		{
			TreeLinkNode* pRight = pNode->right;
			//一直找到右子树中的最左边的结点
			while (pRight->left != nullptr)
			{
				pRight = pRight->left;
			}
			pNext = pRight;
		}
		//一个结点没有右子树并且是父结点的右子结点
		else if (pNode->next != nullptr)
		{
			TreeLinkNode* pCur = pNode;
			TreeLinkNode* Parent = pNode->next;
			//有父结点并且是父结点的右子结点
			while (Parent != nullptr && pCur == Parent->right)
			{
				pCur = Parent;
				Parent = Parent->next;
			}
			//下一个结点就为父结点的父结点
			pNext = Parent;
		}
		return pNext;
	}
};
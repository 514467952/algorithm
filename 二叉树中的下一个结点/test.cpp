
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
		//���һ�������������
		if (pNode->right != nullptr)
		{
			TreeLinkNode* pRight = pNode->right;
			//һֱ�ҵ��������е�����ߵĽ��
			while (pRight->left != nullptr)
			{
				pRight = pRight->left;
			}
			pNext = pRight;
		}
		//һ�����û�������������Ǹ��������ӽ��
		else if (pNode->next != nullptr)
		{
			TreeLinkNode* pCur = pNode;
			TreeLinkNode* Parent = pNode->next;
			//�и���㲢���Ǹ��������ӽ��
			while (Parent != nullptr && pCur == Parent->right)
			{
				pCur = Parent;
				Parent = Parent->next;
			}
			//��һ������Ϊ�����ĸ����
			pNext = Parent;
		}
		return pNext;
	}
};
#pragma once
#include<iostream>
using namespace std;

template<class T>
struct AVLTreeNode{

	AVLTreeNode(const T& data = T())
		:_pLeft(nullptr)
		, _pRight(nullptr)
		, _pParent(nullptr)
		, _data(data)
		, _bf(0)
	{}

	AVLTreeNode<T>* _pLeft;
	AVLTreeNode<T>* _pRight;
	AVLTreeNode<T>* _pParent;
	T _data;
	int _bf;  //当前结点的平衡因子
};

template<class T>
class AVLTree
{
	typedef AVLTreeNode<T> Node;
public:
	AVLTree()
		:_pRoot(nullptr)
	{}

	bool Insert(const T& data)
	{
		if (nullptr == _pRoot)
		{
			_pRoot = new Node(data);
			return true;
		}
		//非空
		//按照二叉搜索树的性质:找待插入结点在AVL树中的位置
		Node *pCur = _pRoot;
		Node *pParent = nullptr;
		while (pCur)
		{
			pParent = pCur;
			if (data < pCur->_data)
				pCur = pCur->_pLeft;
			else if (data>pCur->_data)
				pCur = pCur->_pRight;
			else
				return false;
		}

		//插入新结点
		pCur = new Node(data);
		if (data < pParent->_data)
			pParent->_pLeft = pCur;
		else
			pParent->_pRight = pCur;
		pCur->_pParent = pParent;


		//可能会导致pParent结点的平衡因子不满足AVL树的性质
		while (pParent)
		{
			//必须更新平衡因子
			//按左子树-右子树
			if (pCur == pParent->_pLeft)
				pParent->_bf--;
			else
				pParent->_bf++;


			if (0 == pParent->_bf)
				return true;
			else if (-1 == pParent->_bf || 1 == pParent->_bf){
				pCur = pParent;
				pParent = pCur->_pParent;
			}
			else
			{
				//双亲的平衡因子不满足AVL树的的性质
				//双亲的结点的平衡因子为:2 或者-2
				//需要对以双亲为根的二叉树进行旋转处理
				if (2 == pParent->_bf)		//双亲平衡因子和pcur的平衡因子是同号，用单旋
				{
					//右子树高
					if (1 == pCur->_bf)
						_RotateL(pParent);
					else
						_RotateRL(pParent);
				}
				else{
					//左子树高
					if (-1 == pCur->_bf)
						_RotateR(pParent);
					else
						_RotateLR(pParent);
				}
				break;
			}
			
		}
		return true;
	}

	void Inorder()
	{
		_Inorder(_pRoot);
	}


	bool IsVaildAVLTree()
	{
		return _IsVaildAVLTree(_pRoot);
	}

protected:

	bool _IsVaildAVLTree(Node *pRoot)
	{
		if (nullptr == pRoot)
			return true;

		int leftHeight = _Height(pRoot->_pLeft);
		int rightHeight = _Height(pRoot->_pRight);

		if (!(pRoot->_bf >= -1 && pRoot->_bf <= 1 && pRoot->_bf == rightHeight - leftHeight))
			return false;

		return _IsVaildAVLTree(pRoot->_pLeft) && _IsVaildAVLTree(pRoot->_pRight);
	}

	int _Height(Node *pRoot)
	{
		if (nullptr == pRoot)
			return 0;

		int leftHeight = _Height(pRoot->_pLeft);
		int rightHeight = _Height(pRoot->_pRight);

		return leftHeight > rightHeight ? leftHeight + 1 : rightHeight + 1;
	}

	void _Inorder(Node *pRoot)
	{
		if (pRoot)
		{
			_Inorder(pRoot->_pLeft);
			cout << pRoot->_data << " ";
			_Inorder(pRoot->_pRight);
		}
	}

	//右单旋
	void _RotateR(Node * pParent)
	{
		//第一步
		Node *pSubL = pParent->_pLeft; // pParent的左孩子 
		Node *pSubLR = pSubL->_pRight; //左子树的右孩子

		//旋转完成之后
		//更新孩子指针域
		pParent->_pLeft = pSubLR;
		if (pSubLR)
			pSubLR->_pParent = pParent;
		//第一步完

		//第二步
		pSubL->_pRight = pParent;
		//更新双亲指针域
		Node* pPParent = pParent->_pParent;
		pParent->_pParent = pSubL;
		pSubL->_pParent = pPParent;
		//第二步完

		//第三步
		//对pParent分情况:根结点||非根结点(pParent可能为其双亲的左||右孩子)
		if (nullptr == pPParent)
			_pRoot = pSubL;
		else
		{
			if (pParent == pPParent->_pLeft)
				pPParent->_pLeft = pSubL;
			else
				pPParent->_pRight = pSubL;
		}
		//第三步完

		//更新平衡因子
		pParent->_bf = pSubL->_bf = 0;
	}

	
	//左单旋
	void _RotateL(Node * pParent)
	{
		Node * pSubR = pParent->_pRight;
		Node * pSubRL = pSubR->_pLeft;

		//第一步
		pParent->_pRight = pSubRL;
		if (pSubRL)
			pSubRL->_pParent = pParent;
		//第一步完

		//第二步
		pSubR->_pLeft = pParent;
		Node * pPParent = pParent->_pParent;
		pSubR->_pParent = pPParent;
		pParent->_pParent = pSubR;
		//第二步完

		//第三步
		if (nullptr == pPParent)
			_pRoot = pSubR;
		else
		{
			if (pParent == pPParent->_pLeft)
				pPParent->_pLeft = pSubR;
			else
				pPParent->_pRight = pSubR;
		}
		//第三步完
		pParent->_bf = pSubR->_bf = 0;
	}

	//右左双旋
	void _RotateRL(Node * pParent)
	{
		Node *pSubR = pParent->_pRight;
		Node*pSubL = pSubR->_pLeft;
		int bf = pSubL->_bf;

		_RotateR(pParent->_pRight);
		_RotateL(pParent);

		if (-1 == bf)
			pSubR->_bf = 1;
		else if (1 == bf)
			pParent->_bf = -1;
	}

	//左右双旋
	void _RotateLR(Node *pParent)
	{
		Node* pSubL = pParent->_pLeft;
		Node* pSubLR = pSubL->_pRight;
		int bf = pSubLR->_bf;

		_RotateL(pParent->_pLeft);
		_RotateR(pParent);

		if (-1 == bf)
			pParent->_bf = 1;
		else if (1 == bf)
			pSubL->_bf = -1;
		
	}
private:
	Node *_pRoot;
};

void TestAVLTree()
{
	//int array[] = { 16, 3, 7, 11, 9, 26, 18, 14, 15 };
	int array[] = { 4, 2, 6, 1, 3, 5, 15, 7, 16, 14 };

	AVLTree<int>t;

	for (auto e : array)
		t.Insert(e);

	t.Inorder();
	printf("\n");

	if (t.IsVaildAVLTree())
	{
		cout << "t is vailed AVL Tree" << endl;
	}
	else
	{
		cout << "t is not vaild AVL Tree" << endl;
	}
}
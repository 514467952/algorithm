#pragma once


#include<iostream>
using namespace std;

template<class T>
struct BSTreeNode
{

	BSTreeNode(const T& data = T())  //初始化   T()默认值
		:_pLeft(nullptr)
		, _pRight(nullptr)
		, _data(data)
	{}


		BSTreeNode<T>* _pLeft;  //指向左子树
		BSTreeNode<T>* _pRight; //指向右子树
		T _data;
};

template<class T>
class BsTree
{
	typedef BSTreeNode<T>  Node;

public:
	BsTree()
		:_pRoot(nullptr)  //空树就是一颗二叉搜索树
	{}
	~BsTree()
	{
		_Destroy(_pRoot);
	}

	bool Insert(const T& data)
	{
		//空树--->直接插入
		if (_pRoot == nullptr)
		{
			_pRoot = new Node(data);
			return true;
		}

		//非空
		//找到待插入元素在二叉搜索树中的位置
		Node *pCur = _pRoot;
		Node *pParent = nullptr;
		while (pCur)
		{
			pParent = pCur;  //记录cur变化前的位置，就是记录cur的双亲
			if (data < pCur->_data)
			{
				pCur = pCur->_pLeft;
			}
			else if (data > pCur->_data)
				pCur = pCur->_pRight;
			else
			  return false;
		}

		//插入结点
		pCur = new Node(data);
		if (data < pParent->_data)
			pParent->_pLeft = pCur;
		else
			pParent->_pRight = pCur;

		return true;
	}
	//获取最左侧结点
	Node *LeftMost()
	{
		if (nullptr == _pRoot)
			return nullptr;

		Node *pCur = _pRoot;
		while (pCur->_pLeft)
			pCur = pCur->_pLeft;

		return pCur;
	}
	//获取最右侧结点
	Node *RightMost()
	{
		if(nullptr == _pRoot)
			return nullptr;

		Node *pCur = _pRoot;
		while (pCur->_pRight)
			pCur = pCur->_pRight;

		return pCur;
	}

	void InOrder()			//再封装一层是为了让用户方便，尽量不要让用户传参数
	{
		_InOrder(_pRoot);
	}

	//删除
	bool Delete(const T& data)
	{
		
		if (nullptr == _pRoot)
			return false;

		//找到待删除元素再二叉搜索树中的位置
		Node *pCur = _pRoot;
		Node *pParent = nullptr;
		while (pCur)
		{
			if (data < pCur->_data)
			{
				pParent = pCur;
				pCur = pCur->_pLeft;
			}
			else if (data>pCur->_data){
				pParent = pCur;
				pCur = pCur->_pRight;
			}
			else
				break;
		}

		//结点不存在
		if (nullptr == pCur)
			return false;

		//结点已经找到----分情况删除
		//1.左右孩子都不存在
		//2.只有左孩子
		//3.只有右孩子
		//4.左右孩子均存在
		Node *pDelNode = pCur;
		if (nullptr == pCur->_pRight)
		{
			// 叶子结点 || 只有左孩子
			if (nullptr == pParent)
			{
				_pRoot = pCur->_pLeft;
			}
			else
			{
				if (pCur == pParent->_pLeft)
					pParent->_pLeft = pCur->_pLeft;
				else
					pParent->_pRight = pCur->_pLeft;
			}
		}
		else if (nullptr == pCur->_pLeft)
		{
			// 只有右孩子
			if (nullptr == pParent)
				_pRoot = pCur->_pRight;
			else
			{
				if (pCur == pParent->_pLeft)
					pParent->_pLeft = pCur->_pRight;
				else
					pParent->_pRight = pCur->_pRight;
			}
		}
		else
		{
			//左右孩子均存在，不能直接删除，必须在其子树中找一个替代结点进行删除
			//方式一:在其左子树中找最大的结点---->最右侧的结点
			//方式二:在其右子树中找最小的结点---->最左侧的结点
			//在右子树中查找替代结点
			Node *pMostLeft = pCur->_pRight;
			pParent = pCur;
			while (pMostLeft->_pLeft){
				pParent = pMostLeft;  //每次变动前保存双亲
				pMostLeft = pMostLeft->_pLeft;
			}
			pCur->_data = pMostLeft->_data;

			//删除替代结点
			if (pMostLeft == pParent->_pLeft)
				pParent->_pLeft = pMostLeft->_pRight;
			else
				pParent->_pRight = pMostLeft->_pLeft;

			pDelNode = pMostLeft;
		}

		delete pDelNode;
		return true;
	}

	Node* Find(const T& data)
	{
		Node *pCur = _pRoot;
		Node *pParent = nullptr;
		while (pCur)
		{
			pParent = pCur;  //保存双亲
			if (data == pCur->_data)
				return pCur;
			else if (data < pCur->_data)
				pCur = pCur->_pLeft;
			else
				pCur = pCur->_pRight;
		}

		//走到这个位置，当前元素一定不存在
		return nullptr;
	}

	
private:

	void _InOrder(Node * pRoot)
	{
		if (pRoot){
			_InOrder(pRoot->_pLeft);
			cout << pRoot->_data << " ";
			_InOrder(pRoot->_pRight);
		}
		
	}

	void _Destroy(Node*& pRoot)
	{
		if (pRoot)
		{
			_Destroy(pRoot->_pLeft);
			_Destroy(pRoot->_pRight);
			delete pRoot;
			pRoot = nullptr;
		}
	}
private:
		Node *_pRoot;  //记录根结点 就是保存了整颗树
};

void TestBSTree()
{
	int a[] = { 5, 3, 4, 1, 7, 8, 2, 6, 0, 9 };
	BsTree<int>t;
	for (auto e : a)
		t.Insert(e);

	cout << t.LeftMost() << endl;
	cout << t.RightMost() << endl;
	t.InOrder();
	printf("\n");

	t.Delete(8);
	t.InOrder();
	printf("\n");

	t.Delete(0);
	t.InOrder();
	printf("\n");

	t.Delete(1);
	t.InOrder();
	printf("\n");

	t.Delete(5);
	t.InOrder();
	printf("\n");
}

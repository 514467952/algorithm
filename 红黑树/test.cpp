#if 0
#pragma once

enum COLOR{RED,BLACK};


template<class T>
struct RBTreeNode
{
	RBTreeNode(const T& data = T(), COLOR color = RED)
		:_pLeft(nullptr)
		, _pRight(nullptr)
		, _pParent(nullptr)
		, _data(_data)
		, _color(color)
	{}

	RBTreeNode<T>* _pLeft;
	RBTreeNode<T>* _pRight;
	RBTreeNode<T>* _pParent;
	T _data;
	COLOR _color;
};

template<class T>
class RBTree
{
	typedef RBTreeNode<T>Node;
public:
	RBTree()
	{
		_pHead = new Node;
		_pHead->_pLeft = _pHead;
		_pHead->_pRight = _pHead;
	}

	bool Insert(const T& data)
	{
		Node*& pRoot = GetRoot();
		//空树
		if (nullptr == pRoot){
			pRoot = new Node(data);
			pRoot->_pParent = _pHead;
			_pHead->_pLeft = pRoot;
			_pHead->_pRight = pRoot;
			return true;
		}
		else
		{
			//不是空树
			//1.按照二叉搜索树的性质找到待插入结点在红黑树中的位置
			Node* pCur = pRoot;
			Node* pParent = nullptr;
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

			//2.插入新的结点
			pCur = new Node(data);
			if (data < pParent->_data)
				pParent->_pLeft = pCur;
			else
				pParent->_pRight = pCur;
			pCur->_pParent = pParent;

			//检测：新结点插入后，是否有连在一起的红色结点
			if (RED == pParent->_color)
			{

			}
		}

		pRoot->_color = BLACK;
		_pHead->_pLeft = LeftMost();
		_pHead->_pRight = RightMost();
	}

	Node* LeftMost()
	{
		Node * pCur = GetRoot();
	}
protected:
	Node* &GetRoot()
	{
		return _pHead->_pParent;
	}
protected:
	Node * _pHead;

};
#endif
#include"RBTree.h"


int main()
{
	TestRBTree();

	system("pause");
	return 0;
}
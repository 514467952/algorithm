#pragma once
enum COLOR{ RED, BLACK };
#include<algorithm>
#include<iostream>
using namespace std;
template<class T>
struct RBTreeNode
{
	RBTreeNode(const T& data = T(), COLOR color = RED)
	:_pLeft(nullptr)
	, _pRight(nullptr)
	, _pParent(nullptr)
	, _data(data)
	, _color(color)
	{}
	RBTreeNode<T>* _pLeft;
	RBTreeNode<T>* _pRight;
	RBTreeNode<T>* _pParent;
	T _data;
	COLOR _color;
};

//红黑树的迭代器
template<class T>
struct RBTreeIterator
{
	typedef RBTreeNode<T>Node;
	typedef RBTreeIterator<T> Self;
public:
	RBTreeIterator(Node* pNode = nullptr)
		:_pNode(pNode)
	{}
	//具有指针操作
	T& operator*()
	{
		return _pNode->_data;//找值
	}
	T* operator->()
	{
		return &(operator*());
	}

	//可以移动
	Self& operator++()
	{
		Increament();
		return *this;
	}
	Self operator++(int)
	{
		Self temp(*this);
		Increament(); //往后走一步
		return temp;
	}
	Self& operator--()
	{
		DeIncreament();
		return *this;
	}
	Self operator--(int)
	{
		Self temp(*this);
		DeIncreament();
		return temp;
	}
	bool operator==(const Self& s)const
	{
		return _pNode == s._pNode;
	}
	bool operator!=(const Self& s)const
	{
		return _pNode != s._pNode;
	}
private:
	void Increament()
	{
		if (_pNode->_pRight)  //右子树存在
		{
			_pNode = _pNode->_pRight;
			while (_pNode->_pLeft)
				_pNode = _pNode->_pLeft;
		}
		else
		{
			//比_pNode大的元素可能在它的双亲中
			Node* pParent = _pNode->_pParent;
			while (_pNode == pParent->_pRight)
			{
				_pNode = pParent;
				pParent = _pNode->_pParent;
			}
			//根结点没有右子树&&迭代器在根结点的位置
			if (_pNode->_pRight!=pParent)
				_pNode = pParent; //把pNode放到双亲的位置
		}
	}
	void DeIncreament()
	{
		if (_pNode->_pParent->_pParent == _pNode&& RED == _pNode->_color)
		{
			_pNode = _pNode->_pRight;
		}
		else if (_pNode->_pLeft)
		{
			//如果左子树存在，应该在左子树中找最大的结点
			_pNode = _pNode->_pLeft;
			while (_pNode->_pRight)
				_pNode = _pNode->_pRight;
		}
		else
		{
			//向上找
			Node* pParent = _pNode->_pParent;
			while (_pNode == pParent->_pLeft)
			{
				_pNode = pParent;
				pParent = _pNode->_pParent;
			}
			//begin不可能再减
			_pNode = pParent;
		}
	}
private:
	Node* _pNode;
};

template<class T,class KOFV>
class RBTree
{
	typedef RBTreeNode<T> Node;
public:
	typedef RBTreeIterator<T> iterator;

public:
	RBTree()
		:_size(0)
	{
		_pHead = new Node;
		_pHead->_pLeft = _pHead;
		_pHead->_pRight = _pHead;
		//构造里已经将双亲给成空
	}
	iterator begin()
	{
		return iterator(_pHead->_pLeft);
	}
	iterator end()
	{
		return iterator(_pHead);
	}

	pair<iterator,bool> Insert(const T&data)
	{
		Node*& pRoot = GetRoot(); //必须以引用的方式进行接受
		Node* pNewNode = nullptr;
		if (nullptr == pRoot) //树为空,创建根结点
		{
			pNewNode = pRoot = new Node(data, BLACK);
			pRoot->_pParent = _pHead;//只有一个结点，head就是根节点的双亲
		}
		else
		{
			//说明树已经不为空了
			//1.按照二叉搜索树的性质找到带插入结点在红黑树的位置
			Node* pCur = pRoot;
			Node* pParent = nullptr;
			while (pCur)
			{
				pParent = pCur;//标记双亲位置
				if (KOFV()(data) < KOFV()(pCur->_data))
					pCur = pCur->_pLeft;
				else if (KOFV()(data) > KOFV()(pCur->_data))
					pCur = pCur->_pRight;
				else
					//相同不插入
					return make_pair(iterator(pCur),false);
			}
			//2. 插入新结点
			pNewNode = pCur = new Node(data);
			if (KOFV()(data) < KOFV()(pParent->_data))
				pParent->_pLeft = pCur;
			else
				pParent->_pRight = pCur;
			//3. 更新双亲位置
			pCur->_pParent = pParent;
			//以上没错
			//4.检测:是否新结点插入后连在一起的红色结点
			while (pParent != _pHead && RED == pParent->_color)
			{
				Node* granderFather = pParent->_pParent;
				if (pParent == granderFather->_pLeft)
				{
					//叔叔结点在右侧
					Node* uncle = granderFather->_pRight;
					//情况一:叔叔结点存在，且为红
					if (uncle && RED == uncle->_color)
					{
						pParent->_color = BLACK;
						uncle->_color = BLACK;
						granderFather->_color = RED;
						pCur = granderFather;
						pParent = pCur->_pParent;
					}
					//以上没问题
					else
					{
						//情况三
						if (pCur == pParent->_pRight) //情况三
						{
							//转变成情况二
							RotateLeft(pParent);
							swap(pParent, pCur);
						}
						//情况二
						pParent->_color = BLACK;
						granderFather->_color = RED;
						RotateRight(granderFather);
					}
					//以上没问题
				}
				else
				{
					//叔叔结点在左侧
					Node* uncle = granderFather->_pLeft;
					//情况一的反情况
					if (uncle && uncle->_color == RED)
					{
						pParent->_color = BLACK;
						uncle->_color = BLACK;
						granderFather->_color = RED;
						pCur = granderFather;
						pParent = pCur->_pParent;
					}
					//以上没问题
					else
					{
						//情况三的反情况
						if (pCur == pParent->_pLeft)	/**/
						{
							//情况三的反情况变成情况二的反情况
							RotateRight(pParent);
							swap(pParent, pCur);
						}
						//情况二反情况处理
						pParent->_color = BLACK;
						granderFather->_color = RED;
						RotateLeft(granderFather);
					}
					//以上没问题
				}
			}
		}
		//5.调整头结点的左右指针域
		//保证根节点是黑色
		++_size;
		pRoot->_color = BLACK;
		_pHead->_pLeft = LeftMost();
		_pHead->_pRight = RightMost();
		return make_pair(iterator(pNewNode), true);
	}

	iterator Find(const T& data)const
	{
		Node* pCur = _pHead->_pParent;
		while (pCur)
		{
			if (KOFV()(data) == KOFV()(pCur->_data))
				return iterator(pCur);
			else if (KOFV()(data) < KOFV()(pCur->_data))
				pCur = pCur->_pLeft;
			else
				pCur = pCur->_pRight;
		}
		return end();
	}

	void InOrder()
	{
		_InOrder(GetRoot());
	}

	//检测红黑树
	bool IsValidRBTree()
	{
		Node* pRoot = GetRoot();
		if (nullptr == pRoot)
			return true;
		if (pRoot->_color != BLACK)
		{
			cout << "违反性质2：根结点颜色必须为黑色" << endl;
			return false;
		}
		//获取一条路径中结点的个数
		size_t blackCount = 0; //基准值
		Node* pCur = pRoot;
		while (pCur)
		{
			if (pCur->_color == BLACK)
				blackCount++;
			pCur = pCur->_pLeft;
		}
		size_t pathBlack = 0; //每条路径中的黑色结点个数
		return _IsValidRBTree(pRoot, blackCount, pathBlack);
	}

	bool Empty()const
	{
		return nullptr = _pHead->_pParent;
	}
	size_t Size()const
	{
		return _size;
	}
protected:
	bool _IsValidRBTree(Node* pRoot, size_t blackCount, size_t pathBlack)
	{
		if (nullptr == pRoot)
			return true;
		if (pRoot->_color == BLACK)
			pathBlack++;
		//检测性质3
		Node* pParent = pRoot->_pParent;
		if (pParent != _pHead && pParent->_color == RED&&pRoot->_color == RED)
		{
			cout << "违反性质3:不能有连在一起的红色结点" << endl;
			return false;
		}

		if (nullptr == pRoot->_pLeft&&nullptr == pRoot->_pRight)
		{
			//一条路径到叶子
			if (blackCount != pathBlack)
			{
				cout << "违反了性质4：每条路径中黑色结点个数必须相同" << endl;
				return false;
			}
		}
		return _IsValidRBTree(pRoot->_pLeft, blackCount, pathBlack) &&
			_IsValidRBTree(pRoot->_pRight, blackCount, pathBlack);
	}
	Node* LeftMost()
	{
		//得到根节点
		Node* pRoot = GetRoot();
		if (nullptr == pRoot)
			return _pHead;
		Node* pCur = pRoot;
		//找到最左侧结点
		while (pCur->_pLeft)
			pCur = pCur->_pLeft;
		return pCur;
	}
	Node* RightMost()
	{
		//得到根节点
		Node* pRoot = GetRoot();
		if (nullptr == pRoot)
			return _pHead;
		Node* pCur = pRoot;
		//找到最右侧结点
		while (pCur->_pRight)
			pCur = pCur->_pRight;
		return pCur;
	}

	void RotateLeft(Node* pParent)
	{
		Node* pSubR = pParent->_pRight;
		Node* pSubRL = pSubR->_pLeft;

		pParent->_pRight = pSubRL;
		if (pSubRL)
			pSubRL->_pParent = pParent;

		pSubR->_pLeft = pParent;
		Node* pPParent = pParent->_pParent;
		pParent->_pParent = pSubR;
		pSubR->_pParent = pPParent;

		if (pPParent == _pHead)
			GetRoot() = pSubR;
		else
		{
			if (pPParent->_pLeft == pParent)
				pPParent->_pLeft = pSubR;
			else
				pPParent->_pRight = pSubR;
		}
	}
	void RotateRight(Node* pParent)
	{
		Node* pSubL = pParent->_pLeft;
		Node* pSubLR = pSubL->_pRight;

		pParent->_pLeft = pSubLR;
		if (pSubLR)
			pSubLR->_pParent = pParent;

		pSubL->_pRight = pParent;
		Node* pPParent = pParent->_pParent;
		pParent->_pParent = pSubL;
		pSubL->_pParent = pPParent;

		//pParent是根结点
		if (pPParent == _pHead)
			GetRoot() = pSubL;
		else
		{
			//非根结点
			if (pPParent->_pLeft == pParent)
				pPParent->_pLeft = pSubL;
			else
				pPParent->_pRight = pSubL;
		}
	}

	Node*& GetRoot()  //head是new出来的，head存在parent一定存在，按引用方式返回没有问题
	{
		//得到根节点，也就是头结点的下一个结点
		return _pHead->_pParent;
	}

	void _InOrder(Node* pRoot)
	{
		if (pRoot)
		{
			_InOrder(pRoot->_pLeft);
			cout << pRoot->_data << " ";
			_InOrder(pRoot->_pRight);
		}
	}
private:
	Node* _pHead;
	size_t _size; //记录红黑树中有效结点的个数
};
struct KeyValue
{
	int operator()(int data)
	{
		return data;
	}
};

void TestRBTree()
{
	int array[] = { 16, 3, 7, 11, 9, 26, 18, 14, 15 };
	RBTree<int,KeyValue>t;
	for (auto e : array)
		t.Insert(e);

	t.InOrder();
	if (t.IsValidRBTree())
	{
		cout << "t is vaild rbTree" << endl;
	}
	else
		cout << "t is not vaild rbTree" << endl;

	//RBTree<int>::iterator it = t.begin();
	auto it = t.begin();
	while (it != t.end())
	{
		cout << *it << " ";
		++it;
	}
	cout << endl;
}

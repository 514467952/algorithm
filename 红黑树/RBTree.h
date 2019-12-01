#pragma once
enum COLOR{RED,BLACK};
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

template<class T>
class RBTree
{
	typedef RBTreeNode<T> Node;
public:
	RBTree()
	{
		_pHead = new Node;
		_pHead->_pLeft = _pHead;
		_pHead->_pRight = _pHead;
		//�������Ѿ���˫�׸��ɿ�
	}
	bool Insert(const T&data)
	{
		Node*& pRoot = GetRoot(); //���������õķ�ʽ���н���
		if (nullptr == pRoot) //��Ϊ��,���������
		{
			pRoot = new Node(data,BLACK);
			pRoot->_pParent = _pHead;//ֻ��һ����㣬head���Ǹ��ڵ��˫��
			_pHead->_pLeft = pRoot; //�ı�����ָ����
			_pHead->_pRight = pRoot;
			return true;
		}
		else
		{
			//˵�����Ѿ���Ϊ����
			//1.���ն����������������ҵ����������ں������λ��
			Node* pCur = pRoot;
			Node* pParent = nullptr;
			while (pCur)
			{
				pParent = pCur;//���˫��λ��
				if (data < pCur->_data)
					pCur = pCur->_pLeft;
				else if (data > pCur->_data)
					pCur = pCur->_pRight;
				else
					//��ͬ������
					return false;
			}
			//2. �����½��
			pCur = new Node(data);
			if (data < pParent->_data)
				pParent->_pLeft = pCur;
			else
				pParent->_pRight = pCur;
			//3. ����˫��λ��
			pCur->_pParent = pParent;
			//����û��
			//4.���:�Ƿ��½����������һ��ĺ�ɫ���
			while (pParent!=_pHead && RED == pParent->_color)
			{
				Node* granderFather = pParent->_pParent;
				if (pParent == granderFather->_pLeft)
				{
					//���������Ҳ�
					Node* uncle = granderFather->_pRight;
					//���һ:��������ڣ���Ϊ��
					if (uncle && RED == uncle->_color)
					{
						pParent->_color = BLACK;
						uncle->_color = BLACK;
						granderFather->_color = RED;
						pCur = granderFather;
						pParent = pCur->_pParent;
					}
					//����û����
					else
					{
						//�����
						if (pCur == pParent->_pRight) //�����
						{
							//ת��������
							RotateLeft(pParent);
							swap(pParent, pCur);
						}
						//�����
						pParent->_color = BLACK;
						granderFather->_color = RED;
						RotateRight(granderFather);
					}
					//����û����
				}
				else
				{
					//�����������
					Node* uncle = granderFather->_pLeft;
					//���һ�ķ����
					if (uncle && uncle->_color == RED)
					{
						pParent->_color = BLACK;
						uncle->_color = BLACK;
						granderFather->_color = RED;
						pCur = granderFather;
						pParent = pCur->_pParent;
					}
					//����û����
					else
					{
						//������ķ����
						if (pCur == pParent->_pLeft)	/**/
						{
							//������ķ�������������ķ����
							RotateRight(pParent);
							swap(pParent, pCur);
						}
						//��������������
						pParent->_color = BLACK;
						granderFather->_color = RED;
						RotateLeft(granderFather);
					}
					//����û����
				}
			}
		}
		//5.����ͷ��������ָ����
		//��֤���ڵ��Ǻ�ɫ
		pRoot->_color = BLACK;
		_pHead->_pLeft = LeftMost();
		_pHead->_pRight = RightMost();
		return true;
	}

	void InOrder()
	{
		_InOrder(GetRoot());
	}

	//�������
	bool IsValidRBTree()
	{
		Node* pRoot = GetRoot();
		if (nullptr == pRoot)
			return true;
		if (pRoot->_color != BLACK)
		{
			cout << "Υ������2���������ɫ����Ϊ��ɫ" << endl;
			return false;
		}
		//��ȡһ��·���н��ĸ���
		size_t blackCount = 0; //��׼ֵ
		Node* pCur = pRoot;
		while (pCur)
		{
			if (pCur->_color == BLACK)
				blackCount++;
			pCur = pCur->_pLeft;
		}
		size_t pathBlack = 0; //ÿ��·���еĺ�ɫ������
		return _IsValidRBTree(pRoot, blackCount,pathBlack);
	}
protected:
	bool _IsValidRBTree(Node* pRoot, size_t blackCount, size_t pathBlack)
	{
		if (nullptr == pRoot)
			return true;
		if (pRoot->_color == BLACK)
			pathBlack++;
		//�������3
		Node* pParent = pRoot->_pParent;
		if (pParent != _pHead && pParent->_color == RED&&pRoot->_color == RED)
		{
			cout << "Υ������3:����������һ��ĺ�ɫ���" << endl;
			return false;
		}

		if (nullptr == pRoot->_pLeft&&nullptr == pRoot->_pRight)
		{
			//һ��·����Ҷ��
			if (blackCount != pathBlack)
			{
				cout << "Υ��������4��ÿ��·���к�ɫ������������ͬ" << endl;
				return false;
			}
		}
		return _IsValidRBTree(pRoot->_pLeft, blackCount, pathBlack) &&
			_IsValidRBTree(pRoot->_pRight, blackCount, pathBlack);
	}
	Node* LeftMost()
	{
		//�õ����ڵ�
		Node* pRoot = GetRoot();
		if (nullptr == pRoot)
			return _pHead;
		Node* pCur = pRoot;
		//�ҵ��������
		while (pCur->_pLeft)
			pCur = pCur->_pLeft;
		return pCur;
	}
	Node* RightMost()
	{
		//�õ����ڵ�
		Node* pRoot = GetRoot();
		if (nullptr == pRoot)
			return _pHead;
		Node* pCur = pRoot;
		//�ҵ����Ҳ���
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

		//pParent�Ǹ����
		if (pPParent == _pHead)
			GetRoot() = pSubL;
		else
		{
			//�Ǹ����
			if (pPParent->_pLeft == pParent)
				pPParent->_pLeft = pSubL;
			else
				pPParent->_pRight = pSubL;
		}
	}

	Node*& GetRoot()  //head��new�����ģ�head����parentһ�����ڣ������÷�ʽ����û������
	{
		//�õ����ڵ㣬Ҳ����ͷ������һ�����
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
};

void TestRBTree()
{
	int array[] = { 16, 3, 7, 11, 9, 26, 18, 14, 15 };
	RBTree<int>t;
	for (auto e : array)
		t.Insert(e);

	t.InOrder();
	if (t.IsValidRBTree())
	{
		cout << "t is vaild rbTree" << endl;
	}
	else
		cout << "t is not vaild rbTree" << endl;
}

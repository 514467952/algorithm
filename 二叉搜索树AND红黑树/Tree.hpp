#pragma once


#include<iostream>
using namespace std;

template<class T>
struct BSTreeNode
{

	BSTreeNode(const T& data = T())  //��ʼ��   T()Ĭ��ֵ
		:_pLeft(nullptr)
		, _pRight(nullptr)
		, _data(data)
	{}


		BSTreeNode<T>* _pLeft;  //ָ��������
		BSTreeNode<T>* _pRight; //ָ��������
		T _data;
};

template<class T>
class BsTree
{
	typedef BSTreeNode<T>  Node;

public:
	BsTree()
		:_pRoot(nullptr)  //��������һ�Ŷ���������
	{}
	~BsTree()
	{
		_Destroy(_pRoot);
	}

	bool Insert(const T& data)
	{
		//����--->ֱ�Ӳ���
		if (_pRoot == nullptr)
		{
			_pRoot = new Node(data);
			return true;
		}

		//�ǿ�
		//�ҵ�������Ԫ���ڶ����������е�λ��
		Node *pCur = _pRoot;
		Node *pParent = nullptr;
		while (pCur)
		{
			pParent = pCur;  //��¼cur�仯ǰ��λ�ã����Ǽ�¼cur��˫��
			if (data < pCur->_data)
			{
				pCur = pCur->_pLeft;
			}
			else if (data > pCur->_data)
				pCur = pCur->_pRight;
			else
			  return false;
		}

		//������
		pCur = new Node(data);
		if (data < pParent->_data)
			pParent->_pLeft = pCur;
		else
			pParent->_pRight = pCur;

		return true;
	}
	//��ȡ�������
	Node *LeftMost()
	{
		if (nullptr == _pRoot)
			return nullptr;

		Node *pCur = _pRoot;
		while (pCur->_pLeft)
			pCur = pCur->_pLeft;

		return pCur;
	}
	//��ȡ���Ҳ���
	Node *RightMost()
	{
		if(nullptr == _pRoot)
			return nullptr;

		Node *pCur = _pRoot;
		while (pCur->_pRight)
			pCur = pCur->_pRight;

		return pCur;
	}

	void InOrder()			//�ٷ�װһ����Ϊ�����û����㣬������Ҫ���û�������
	{
		_InOrder(_pRoot);
	}

	//ɾ��
	bool Delete(const T& data)
	{
		
		if (nullptr == _pRoot)
			return false;

		//�ҵ���ɾ��Ԫ���ٶ����������е�λ��
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

		//��㲻����
		if (nullptr == pCur)
			return false;

		//����Ѿ��ҵ�----�����ɾ��
		//1.���Һ��Ӷ�������
		//2.ֻ������
		//3.ֻ���Һ���
		//4.���Һ��Ӿ�����
		Node *pDelNode = pCur;
		if (nullptr == pCur->_pRight)
		{
			// Ҷ�ӽ�� || ֻ������
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
			// ֻ���Һ���
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
			//���Һ��Ӿ����ڣ�����ֱ��ɾ��������������������һ�����������ɾ��
			//��ʽһ:�����������������Ľ��---->���Ҳ�Ľ��
			//��ʽ��:����������������С�Ľ��---->�����Ľ��
			//���������в���������
			Node *pMostLeft = pCur->_pRight;
			pParent = pCur;
			while (pMostLeft->_pLeft){
				pParent = pMostLeft;  //ÿ�α䶯ǰ����˫��
				pMostLeft = pMostLeft->_pLeft;
			}
			pCur->_data = pMostLeft->_data;

			//ɾ��������
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
			pParent = pCur;  //����˫��
			if (data == pCur->_data)
				return pCur;
			else if (data < pCur->_data)
				pCur = pCur->_pLeft;
			else
				pCur = pCur->_pRight;
		}

		//�ߵ����λ�ã���ǰԪ��һ��������
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
		Node *_pRoot;  //��¼����� ���Ǳ�����������
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

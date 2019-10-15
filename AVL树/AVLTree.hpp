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
	int _bf;  //��ǰ����ƽ������
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
		//�ǿ�
		//���ն���������������:�Ҵ���������AVL���е�λ��
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

		//�����½��
		pCur = new Node(data);
		if (data < pParent->_data)
			pParent->_pLeft = pCur;
		else
			pParent->_pRight = pCur;
		pCur->_pParent = pParent;


		//���ܻᵼ��pParent����ƽ�����Ӳ�����AVL��������
		while (pParent)
		{
			//�������ƽ������
			//��������-������
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
				//˫�׵�ƽ�����Ӳ�����AVL���ĵ�����
				//˫�׵Ľ���ƽ������Ϊ:2 ����-2
				//��Ҫ����˫��Ϊ���Ķ�����������ת����
				if (2 == pParent->_bf)		//˫��ƽ�����Ӻ�pcur��ƽ��������ͬ�ţ��õ���
				{
					//��������
					if (1 == pCur->_bf)
						_RotateL(pParent);
					else
						_RotateRL(pParent);
				}
				else{
					//��������
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

	//�ҵ���
	void _RotateR(Node * pParent)
	{
		//��һ��
		Node *pSubL = pParent->_pLeft; // pParent������ 
		Node *pSubLR = pSubL->_pRight; //���������Һ���

		//��ת���֮��
		//���º���ָ����
		pParent->_pLeft = pSubLR;
		if (pSubLR)
			pSubLR->_pParent = pParent;
		//��һ����

		//�ڶ���
		pSubL->_pRight = pParent;
		//����˫��ָ����
		Node* pPParent = pParent->_pParent;
		pParent->_pParent = pSubL;
		pSubL->_pParent = pPParent;
		//�ڶ�����

		//������
		//��pParent�����:�����||�Ǹ����(pParent����Ϊ��˫�׵���||�Һ���)
		if (nullptr == pPParent)
			_pRoot = pSubL;
		else
		{
			if (pParent == pPParent->_pLeft)
				pPParent->_pLeft = pSubL;
			else
				pPParent->_pRight = pSubL;
		}
		//��������

		//����ƽ������
		pParent->_bf = pSubL->_bf = 0;
	}

	
	//����
	void _RotateL(Node * pParent)
	{
		Node * pSubR = pParent->_pRight;
		Node * pSubRL = pSubR->_pLeft;

		//��һ��
		pParent->_pRight = pSubRL;
		if (pSubRL)
			pSubRL->_pParent = pParent;
		//��һ����

		//�ڶ���
		pSubR->_pLeft = pParent;
		Node * pPParent = pParent->_pParent;
		pSubR->_pParent = pPParent;
		pParent->_pParent = pSubR;
		//�ڶ�����

		//������
		if (nullptr == pPParent)
			_pRoot = pSubR;
		else
		{
			if (pParent == pPParent->_pLeft)
				pPParent->_pLeft = pSubR;
			else
				pPParent->_pRight = pSubR;
		}
		//��������
		pParent->_bf = pSubR->_bf = 0;
	}

	//����˫��
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

	//����˫��
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
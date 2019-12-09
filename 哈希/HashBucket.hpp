#pragma once
#include<iostream>
#include<sstream>
#include<string>
#include"Common.h"
using namespace std;
//��ɢ��:һ������ļ���---������ͬ��ϣ��ַ��Ԫ�طŵ�ͬһ��������
#include<vector>
//��ϣ��Ľ��
template<class T>
struct HashNode
{
	HashNode(const T&data = T())
	:_pNext(nullptr)
	, _data(data)
	{}
	HashNode<T>* _pNext;
	T _data;
};

template<class T>
struct DefD2INIT
{
	const T& operator()(const T& data)
	{
		return data;
	}
};

struct Str2INT
{
	size_t operator()(const string& s)
	{
		return (size_t)s.c_str();
	}
};
template<class T,class DTOINT = DefD2INIT<T>>
class hashbucket
{
	typedef HashNode<T> Node;
	typedef hashbucket<T, DTOINT> Self;
public:
	hashbucket(size_t capacity)
		:_table(GetNextPrime(capacity))
		, _size(0)
	{}

	~hashbucket()
	{
		Clear();
	}

	bool Insert(const T& data)
	{

		//����
		_CheckCapacity();
		//ͨ����ϣ���������ϣ��Ͱ��
		size_t bucketNo = HashFunc(data);

		Node* pCur = _table[bucketNo];
		while (pCur)
		{
			if (data == pCur->_data)
				return false;
			pCur = pCur->_pNext;
		}
		pCur = new Node(data);
		pCur->_pNext = _table[bucketNo];
		_table[bucketNo] = pCur;
		_size++;
		return true;
	}

	bool Erase(const T&data)
	{
		//�������ĸ�����
		size_t bucketNo = HashFunc(data);

		//����������Ԫ��
		Node* pCur = _table[bucketNo];
		Node* pPrev = nullptr;
		while (pCur)
		{
			if (data == pCur->_data)
			{
				//����ɾ��
				if (pCur == _table[bucketNo])
					_table[bucketNo] = pCur->_pNext;
				else
					pPrev->_pNext = pCur->_pNext;
				delete pCur;
				--_size;
				return true;
			}
			else
			{
				pPrev = pCur;
				pCur = pCur->_pNext;
			}
		}
		return false;
	}
	Node* Find(const T& data)
	{
		size_t bucketNo = HashFunc(data);

		Node* pCur = _table[bucketNo];
		while (pCur)
		{
			if (pCur->_data == data)
				return pCur;
			pCur = pCur->_pNext;
		}
		return nullptr;
	}

	size_t Size()const
	{
		return _size;
	}

	bool Empty()const
	{
		return 0 == _size;
	}

	void Clear()
	{
		for (size_t bucketNo = 0; bucketNo < _table.capacity(); ++bucketNo)
		{
			Node* pCur = _table[bucketNo];

			while (pCur)
			{
				_table[bucketNo] = pCur->_pNext;
				delete pCur;
				pCur = _table[bucketNo];
			}
		}
	}

	void Swap( Self& ht)
	{
		_table.swap(ht._table);
		swap(_size, ht._size);
	}
	void _CheckCapacity()
	{
		if (_size == _table.capacity())
		{
			//�µĹ�ϣͰ
			Self newHT(GetNextPrime( _table.capacity() ));

			//���ɹ�ϣͰ�еĽ�����¹�ϣͰ�н��а���
			for (size_t i = 0; i < _table.capacity(); ++i)
			{
				Node* pCur = _table[i];

				//��i��Ͱ�е����н����Ƶ��¹�ϣͰ��
				while (pCur)
				{
					//��pCur����table��i���Ƴ���
					_table[i] = pCur->_pNext;

					//��pCur���뵽�¹�ϣͰ��
					size_t bucketNo = newHT.HashFunc(pCur->_data);

					//����ͷ�巨
					pCur->_pNext = newHT._table[bucketNo];
					newHT._table[bucketNo] = pCur;
					newHT._size++;
					_size--;

					pCur = _table[i];
				}
			}
			//��Ͱ�;�Ͱ���н���
			this->Swap(newHT);
		}
	}

	void PrintHashBucket()
	{
		for (int i = 0; i < _table.capacity(); ++i)
		{
			Node* pCur = _table[i];
			cout << "table[" << i << "]:";
			while (pCur)
			{
				cout << pCur->_data << "-->";
				pCur = pCur->_pNext;
			}
			cout << "NULL" << endl;
		}
	}
private:
	size_t HashFunc(const T&data)
	{
		//T:��������������---���ܲ�������
		return DTOINT ()(data) % _table.capacity();
	}
private:
	vector<Node*> _table;//ÿһ��������׵�ַ
	size_t _size;  //��ǰ��ϣͰ����˶��ٸ�Ԫ��
};

void TestHashBucket()
{
	hashbucket<int>ht(10);
	ht.Insert(1);
	ht.Insert(5);
	ht.Insert(15);
	ht.Insert(23);
	ht.Insert(24);
	ht.Insert(28);
	ht.Insert(25);
	ht.Insert(20);
	ht.Insert(29);
	ht.Insert(19);
	cout << ht.Size() << endl;
	//ht.PrintHashBucket();
	ht.Insert(11);
	//ht.PrintHashBucket();
	ht.Erase(5);
	ht.PrintHashBucket();
	cout << endl;
	ht.Erase(25);
	ht.PrintHashBucket();
}

void TestHashBucket1()
{
	hashbucket<string,Str2INT>ht(10);
	ht.Insert("hello");
	ht.Insert("11111");
	ht.Insert("���");
	cout << ht.Size() << endl;
	ht.PrintHashBucket();
}


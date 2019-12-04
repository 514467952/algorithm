#pragma once
#include"RBTree.h"

namespace bite
{
	//ֻ��Ҫ��װһ�������
	template<class K>
	class set
	{
		typedef K ValueType;

		struct KeyOfValue
		{
			const K& operator()(const ValueType & data)
			{
				return data;
			}
		};

	public:
		//�������п��ܽ�iterator���ɾ�̬��Ա����������
		typename typedef RBTree<ValueType, KeyOfValue>::iterator iterator;
		//��ȷ�ĸ��߱�����iterator ʱ������е�һ������
	public:
		set()
			:_t()
		{}
		iterator begin()
		{
			return _t.begin();
		}
		iterator end()
		{
			return _t.end();
		}
		pair<iterator, bool> insert(const ValueType&data)
		{
			return _t.Insert(data);
		}
		size_t size()const
		{
			return _t.Size();
		}
		bool Empty()const
		{
			return _t.Empty();
		}

		iterator find(const K& key)
		{
			return  _t.Find(key);
		}

	private:
		RBTree<ValueType, KeyOfValue> _t;
	};
}
#include<string>
#include<iostream>
using namespace std;
void TestSet()
{
	bite::set<std::string>m;
	m.insert("2222");
	m.insert("11111");
	m.insert("11111");

	cout << m.size() << endl;
	for (auto e : m)
		cout << e << endl;
	cout << endl;
}
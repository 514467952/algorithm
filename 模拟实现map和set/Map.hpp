#pragma once
#include"RBTree.h"

namespace bite
{
	//ֻ��Ҫ��װһ�������
	template<class K, class V>
	class map
	{
		typedef pair<K, V> ValueType;

		struct KeyOfValue
		{
			const K& operator()(const ValueType & data)
			{
				return data.first;
			}
		};

	public:
		//�������п��ܽ�iterator���ɾ�̬��Ա����������
		typename typedef RBTree<ValueType, KeyOfValue>::iterator iterator;
		//��ȷ�ĸ��߱�����iterator ʱ������е�һ������
	public:
		map()
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
			return  _t.Find(make_pair(key,V()));
		}

		V& operator[](const K& key)
		{
			return (*(_t.Insert(ValueType(key, V()))).first).second;
		}
	private:
		RBTree<ValueType,KeyOfValue> _t;
	};
}

#include<string>
#include<iostream>
using namespace std;
void TestMap()
{
	bite::map<std::string, std::string>m;
	m.insert(pair<std::string,std::string>("2222","11111"));
	m.insert(make_pair("1111","1111"));

	m["0000"] = "0000";
	cout << m.size() << endl;
	for (auto e : m)
		cout << e.first << " " << e.second << endl;
	cout << endl;
}
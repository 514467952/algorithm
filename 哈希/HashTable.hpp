#pragma once
#include<iostream>
using namespace std;

#include<vector>
enum State{ EMPTY, EXIST, DELETE };

template<class T, bool IsLine = true>
class hashtable
{
	struct Elem  //存储的元素类型
	{	
		Elem()
		:_state(EMPTY)
		{}
		T _data;
		State _state;
	};
public:
	hashtable(size_t capacity)
		:_table(capacity)
		, _size(0)
		,_total(0)
	{}

	bool Insert(const T&data)
	{
		//检测哈希空间是否充足
		_CheckCapacity();
		//1.通过哈希函数计算哈希地址
		size_t hashAddr = HashFunc(data);

		size_t i = 0;//二次探测中的第几次探测
		//2.检测位置是否可以存储
		while(_table[hashAddr]._state != EMPTY)
		{
			//检测该位置元素是否有效&&是否为待插入元素
			if (EXIST == _table[hashAddr]._state&&data == _table[hashAddr]._data)
			{
				return false;//元素已经存在，不进行插入
			}
			//发生哈希冲突
			if (IsLine)
			{
				DetectiveLine(hashAddr);
			}
			else
			{
				++i;
				DetectiveTwice(hashAddr,i);
			}
		}
		//3.插入元素
		_table[hashAddr]._data = data;
		_table[hashAddr]._state = EXIST;
		_size++;
		_total++;
		return true;
	}

	int Find(const T&data)
	{
		size_t hashAddr = HashFunc(data);
		size_t i = 0;
		while (_table[hashAddr]._state != EMPTY)
		{
			if (EXIST == _table[hashAddr]._state&&
				data == _table[hashAddr]._data)
			{
				return hashAddr;
			}

			//发生哈希冲突
			if (IsLine)
			{
				DetectiveLine(hashAddr);
			}
			else
			{
				++i;
				DetectiveTwice(hashAddr,i);
			}
		}
		return -1;
	}

	bool Erase(const T&data)
	{
		int ret = Find(data);
		if (-1 != ret)
		{
			_table[ret]._state = DELETE;
			--_size;
			return true;
		}
		return false;
	}

	size_t Size()const
	{
		return _size;
	}

	void Swap(hashtable<T,IsLine>& ht)
	{
		_table.swap(ht._table);
		swap(_size, ht._size);
		swap(_total, ht._total);
	}
private:
	size_t HashFunc(const T&data)
	{
		return data%_table.capacity();
	}

	//线性探测
	void DetectiveLine(size_t&hashAddr)
	{
		hashAddr += 1;
		if (hashAddr == _table.capacity())
			hashAddr = 0;
	}
	//二次探测
	void DetectiveTwice(size_t& hashAddr, size_t i)
	{
		hashAddr = hashAddr + 2 * i + 1;
		if (hashAddr >= _table.capacity())
			hashAddr %= _table.capacity();
	}
	//扩容
	void  _CheckCapacity()
	{
		if (_total * 10 / _table.capacity() >= 7)
		{
			//新的哈希表
			hashtable<T,IsLine>newHT(_table.capacity() * 2);
			//奖旧哈希表中有效元素搬移到新的哈希表中
			//注意:已经删除的元素不用搬移
			for (size_t i = 0; i < _table.capacity(); ++i)
			{
				if (_table[i]._data == EXIST)
					newHT.Insert(_table[i]._data);
			}
			Swap(newHT);
		}
	}
private:
	vector<Elem>_table; //状态表格
	size_t _size;	//哈希表中有效元素的个数
	size_t _total; //哈希表中元素的个数:存在和删除(为了保证哈希表中数据的唯一性，删除位置不能插入元素)
};

void TestHashTable()
{
	hashtable<int>ht(10);
	ht.Insert(1);
	ht.Insert(23);
	ht.Insert(78);
	ht.Insert(13);
	ht.Insert(19);
	ht.Insert(29);
	
	cout << ht.Size() << endl;
	int ret = ht.Find(23);
	if (-1 != ret)
	{
		cout << "23元素存在" << endl;
	}
	else
	{
		cout << "23元素不存在" << endl;
	}
	ht.Erase(23);
	ret = ht.Find(23);
	if (-1 != ret)
	{
		cout << "23元素存在" << endl;
	}
	else
	{
		cout << "23元素不存在" << endl;
	}
	ret = ht.Find(13);
	if (-1 != ret)
	{
		cout << "13元素存在" << endl;
	}
	else
	{
		cout << "13元素不存在" << endl;
	}
}


#if 0
// 哈希函数采用处理余数法，被模的key必须要为整形才可以处理，此处提供将key转化为整形的方法
// 整形数据不需要转化
template<class T>
class DefHashF
{
public:
	size_t operator()(const T& val)
	{
		return val;
	}
};
// key为字符串类型，需要将其转化为整形
class Str2Int
{
public:
	size_t operator()(const string& str)
	{
		return BKDRHash(str.c_str());
	}
	size_t BKDRHash(const char * str)
	{
		unsigned int seed = 131; // 31 131 1313 13131 131313
		unsigned int hash = 0;
		while (*str)
		{
			hash = hash * seed + (*str++);
		}
		return (hash & 0x7FFFFFFF);
	}
};
// 为了实现简单，此哈希表中我们将比较直接与元素绑定在一起
template<class K, class V, class HF>
class HashTable
{
	// ……
private:
	size_t HashFunc(const K& key)
	{
		return HF()(key) % _ht.capacity();
	}
};
#endif
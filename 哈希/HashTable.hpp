#pragma once
#include<iostream>
using namespace std;

#include<vector>
enum State{ EMPTY, EXIST, DELETE };

template<class T, bool IsLine = true>
class hashtable
{
	struct Elem  //�洢��Ԫ������
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
		//����ϣ�ռ��Ƿ����
		_CheckCapacity();
		//1.ͨ����ϣ���������ϣ��ַ
		size_t hashAddr = HashFunc(data);

		size_t i = 0;//����̽���еĵڼ���̽��
		//2.���λ���Ƿ���Դ洢
		while(_table[hashAddr]._state != EMPTY)
		{
			//����λ��Ԫ���Ƿ���Ч&&�Ƿ�Ϊ������Ԫ��
			if (EXIST == _table[hashAddr]._state&&data == _table[hashAddr]._data)
			{
				return false;//Ԫ���Ѿ����ڣ������в���
			}
			//������ϣ��ͻ
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
		//3.����Ԫ��
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

			//������ϣ��ͻ
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

	//����̽��
	void DetectiveLine(size_t&hashAddr)
	{
		hashAddr += 1;
		if (hashAddr == _table.capacity())
			hashAddr = 0;
	}
	//����̽��
	void DetectiveTwice(size_t& hashAddr, size_t i)
	{
		hashAddr = hashAddr + 2 * i + 1;
		if (hashAddr >= _table.capacity())
			hashAddr %= _table.capacity();
	}
	//����
	void  _CheckCapacity()
	{
		if (_total * 10 / _table.capacity() >= 7)
		{
			//�µĹ�ϣ��
			hashtable<T,IsLine>newHT(_table.capacity() * 2);
			//���ɹ�ϣ������ЧԪ�ذ��Ƶ��µĹ�ϣ����
			//ע��:�Ѿ�ɾ����Ԫ�ز��ð���
			for (size_t i = 0; i < _table.capacity(); ++i)
			{
				if (_table[i]._data == EXIST)
					newHT.Insert(_table[i]._data);
			}
			Swap(newHT);
		}
	}
private:
	vector<Elem>_table; //״̬���
	size_t _size;	//��ϣ������ЧԪ�صĸ���
	size_t _total; //��ϣ����Ԫ�صĸ���:���ں�ɾ��(Ϊ�˱�֤��ϣ�������ݵ�Ψһ�ԣ�ɾ��λ�ò��ܲ���Ԫ��)
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
		cout << "23Ԫ�ش���" << endl;
	}
	else
	{
		cout << "23Ԫ�ز�����" << endl;
	}
	ht.Erase(23);
	ret = ht.Find(23);
	if (-1 != ret)
	{
		cout << "23Ԫ�ش���" << endl;
	}
	else
	{
		cout << "23Ԫ�ز�����" << endl;
	}
	ret = ht.Find(13);
	if (-1 != ret)
	{
		cout << "13Ԫ�ش���" << endl;
	}
	else
	{
		cout << "13Ԫ�ز�����" << endl;
	}
}


#if 0
// ��ϣ�������ô�������������ģ��key����ҪΪ���βſ��Դ����˴��ṩ��keyת��Ϊ���εķ���
// �������ݲ���Ҫת��
template<class T>
class DefHashF
{
public:
	size_t operator()(const T& val)
	{
		return val;
	}
};
// keyΪ�ַ������ͣ���Ҫ����ת��Ϊ����
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
// Ϊ��ʵ�ּ򵥣��˹�ϣ�������ǽ��Ƚ�ֱ����Ԫ�ذ���һ��
template<class K, class V, class HF>
class HashTable
{
	// ����
private:
	size_t HashFunc(const K& key)
	{
		return HF()(key) % _ht.capacity();
	}
};
#endif
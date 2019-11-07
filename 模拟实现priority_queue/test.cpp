#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;

namespace bite
{
	template<class T ,class Container = vector<T>,class Compare = less<T>>
	class priority_queue
	{
	public:
		priority_queue()
			:c()
		{}

		template<class Iterator>
		priority_queue(Iterator first, Iterator last)
			: c(first,last)
		{
			//��c�е�Ԫ�ص����ɶѵĽṹ
			size_t count = c.size();
			//������һ����Ҷ�ӽ��
			int root = (count - 2) / 2;
			for (; root >= 0; root--)
				AdjustDown(root);
		}

		void push(const T& data)
		{
			c.push_back(data);
			AdjustUp(c.size() - 1);
		}

		void pop()
		{
			if (empty())
				return;
			swap(c.front(), c.back());
			c.pop_back();
			AdjustDown(0);
		}

		size_t size()const
		{
			return c.size();
		}

		bool empty()const
		{
			return c.empty();
		}

		//�Ѷ�Ԫ�ز������޸ģ���Ϊ�Ѷ�Ԫ���޸Ŀ��ܻ��ƻ��ѵ�����
		const T& top() const
		{
			return c.front();
		}
	private:
		void AdjustDown(int parent)
		{
			int child = parent * 2 + 1;
			while (child < c.size())
			{
				//����parentΪ�������������нϴ�ĺ���
				if (child + 1 < c.size() && com(c[child], c[child + 1]))
					child += 1;
				
				//���˫���Ƿ��������
				if (com(c[parent] , c[child]))
				{
					swap(c[child], c[parent]);
					parent = child;
					child = parent * 2 + 1;
				}
				else
					return;
			}
		}

		void AdjustUp(int child)
		{
			int parent = (child - 1) / 2;

			while (child)
			{
				if (com(c[parent] , c[child]))
				{
					swap(c[child], c[parent]);
					child = parent;
					parent = (child - 1) / 2;

				}
				else
				{
					return;
				}
			}
		}
	private:
		Container c;	//�洢��ʽ
		Compare com;  //�ȽϷ�ʽ
	};

}


//void AdjustDown(int array[], int size, int root)
//{
//	if (array == NULL)
//		return;
//
//	int left = 2 * root + 1;
//	if (left >= size)
//		return;
//
//	int right = 2 * root + 2;
//	int min = left;
//	if (right < size&& array[right] < array[min])
//		min = right;
//
//	if (array[root] < array[min])
//		return;
//
//	swap(array[root], array[min]);
//
//	root = min;
//}



#include<functional>
int main()
{
	int array[] = { 8, 1, 9, 3, 6, 4, 5, 0, 2, 7 };
	bite::priority_queue<int>q(array, array + sizeof(array) / sizeof(array[0]));
	cout << q.top() << endl;


	bite::priority_queue<int, vector<int>,less<int>>q2;
	q2.push(5);
	q2.push(0);
	q2.push(9);
	q2.push(3);
	q2.push(4);
	system("pause");
	return 0;
}
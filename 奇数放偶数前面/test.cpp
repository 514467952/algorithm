#include<iostream>
#include<vector>
using namespace std;
void reOrderArray(vector<int> &array) {
	int size = array.size();
	while (size--)
	{
		bool flag = false;
		for (int i = 0; i<array.size() - 1; ++i)
		{
			//利用冒泡排序，保证相对有序
			if (array[i] % 2 == 0 && array[i + 1] % 2 == 1)
			{
				swap(array[i], array[i + 1]);
				flag = true;
			}
		}
		if (!flag)
		{
			return; //回到while循环，一次循环后最后面的偶数放到最后一位，缩小范围继续循环
		}
	}
}
int main()
{
	vector<int> v = { 1, 2, 3, 4, 5, 6, 7 };
	reOrderArray(v);
	system("pause");
	return 0;
}
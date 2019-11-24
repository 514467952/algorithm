#include <iostream>
#include <algorithm>
using namespace std;

/*����ÿһ����������Լ���ͣ�����sqrt��С��Χ*/
bool IsPerfect(int num)
{
	int sum = 1;
	for (int i = 2; i < sqrt(num); ++i)
	{
		if (num%i == 0)
		{
			sum += i;
			if (num / i != i) //��ʾ����ƽ������������Լ����Ҫ��
				sum += num / i;
		}
	}

	if (num == sum)
		return true;
	else
		return false;
}

int main()
{
	int n;
	while (cin >> n)
	{
		int count = 0;
		if (n<0 || n>500000) //�쳣�������-1
			return -1;
		else
		{
			for (int i = 2; i < n; ++i)
			{
				if (IsPerfect(i))
					++count;
			}
			cout << count << endl;
		}
	}
	return 0;
}
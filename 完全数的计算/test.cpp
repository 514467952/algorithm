#include <iostream>
#include <algorithm>
using namespace std;

/*遍历每一个数，求其约数和，可用sqrt缩小范围*/
bool IsPerfect(int num)
{
	int sum = 1;
	for (int i = 2; i < sqrt(num); ++i)
	{
		if (num%i == 0)
		{
			sum += i;
			if (num / i != i) //表示不是平方，所以两个约数都要加
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
		if (n<0 || n>500000) //异常情况返回-1
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
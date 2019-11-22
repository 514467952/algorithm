
/*
*/
#include <iostream>
#include <algorithm>
using namespace std;

/*从最低位开始，n&1判断当前位是否为1
*	如果是1，++count，更新maxsize；
*	如果是0，count归0；
*	n向左移位来比较下一位
*/
int main()
{
	int n;
	while (cin >> n)
	{
		int count = 0, maxsize = 0;
		while (n)
		{
			if (n & 1)
			{
				count++;
				maxsize = max(maxsize, count);
			}
			else
				count = 0;
			n = n >> 1;
		}

		cout << maxsize << endl;
	}
	return 0;
}



/*
*/
#include <iostream>
#include <algorithm>
using namespace std;

/*�����λ��ʼ��n&1�жϵ�ǰλ�Ƿ�Ϊ1
*	�����1��++count������maxsize��
*	�����0��count��0��
*	n������λ���Ƚ���һλ
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


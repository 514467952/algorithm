/*
������32λ����n��m�����д�㷨��m�Ķ�������λ���뵽n�Ķ����Ƶĵ�j����iλ,
���ж����Ƶ�λ���ӵ�λ������λ����0��ʼ��

����������int n��int m��ͬʱ����int j��int i�����������������뷵�ز������������֤n�ĵ�j����iλ��Ϊ�㣬
��m�Ķ�����λ��С�ڵ���i-j+1��

*/


#include <iostream>
using namespace std;

/*m����jλ���ٽ��л�����n|m*/
typedef class BinInsert {
public:
	int binInsert(int n, int m, int j, int i) {
		m <<= j;
		return n | m;
	}
}BI;

int main()
{
	BI b;
	int n, m, j, i;
	while (cin >> n >> m >> j >> i)
		cout << b.binInsert(n, m, j, i) << endl;
	return 0;
}


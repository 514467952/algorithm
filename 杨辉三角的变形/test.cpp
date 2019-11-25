#include<iostream>
#include<vector>
using namespace std;

vector<vector<int>> CreadeTriangle(int n) {
	//����һ����ά���飬���ҽ���ά�����������Ϊn��������Ϊ2*n+1��ȫ����ʼ��Ϊ0
	vector<vector<int>> v(n, vector<int>(2 * n + 1, 0));
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < 2 * i + 1; ++j) {
			//��һ���к͵�һ��ȫΪ1
			if (i == 0)
				v[i][j] = 1;
			else if (j == 0)
				v[i][j] = 1;
			//�ڶ���ֻ�����������
			else if (j == 1)
				v[i][j] = v[i - 1][j] + v[i - 1][j - 1];
			else
				v[i][j] = v[i - 1][j] + v[i - 1][j - 1] + v[i - 1][j - 2];
		}
	}
	return v;
}

//����������ǵĵ�n�еĵ�һ��ż��������+1
int GetEven(int n) {
	//����һ��n�е��������
	vector<vector<int>> v = CreadeTriangle(n);
	//����������ǵĵ�n�еĵ�һ��ż��������+1
	for (int i = 0; i < 2 * n - 1; ++i) {
		if (v[n - 1][i] % 2 == 0)
			return (i + 1);
	}
	return -1;
}
int main() {
	int n;
	while (cin >> n) {
		cout << GetEven(n) << endl;
	}
	return 0;
}

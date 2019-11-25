#include<iostream>
#include<vector>
using namespace std;

vector<vector<int>> CreadeTriangle(int n) {
	//创建一个二维数组，并且将二维数组的行设置为n，列设置为2*n+1，全部初始化为0
	vector<vector<int>> v(n, vector<int>(2 * n + 1, 0));
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < 2 * i + 1; ++j) {
			//第一个行和第一列全为1
			if (i == 0)
				v[i][j] = 1;
			else if (j == 0)
				v[i][j] = 1;
			//第二列只有两个数相加
			else if (j == 1)
				v[i][j] = v[i - 1][j] + v[i - 1][j - 1];
			else
				v[i][j] = v[i - 1][j] + v[i - 1][j - 1] + v[i - 1][j - 2];
		}
	}
	return v;
}

//返回杨辉三角的第n行的第一个偶数的索引+1
int GetEven(int n) {
	//创建一个n行的杨辉三角
	vector<vector<int>> v = CreadeTriangle(n);
	//返回杨辉三角的第n行的第一个偶数的索引+1
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

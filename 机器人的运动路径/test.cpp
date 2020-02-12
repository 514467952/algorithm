#include<iostream>
using namespace std;
class Solution {
public:
	//求一个数字的数位之和
	int GetSum(int num)
	{
		int sum = 0;
		while (num>0)
		{
			sum += num % 10;
			num /= 10;
		}
		return sum;
	}
	//判断当前数字格子机器能否达到
	bool Judge(int threshold, int row, int col, int rows, int cols, bool* visited)
	{
		if (row >= 0 && row<rows && col >= 0 && col<cols  // 数组没有越界
			&& GetSum(row) + GetSum(col) <= threshold  //行坐标和列坐标数位之和小于等于k的格子
			&& !visited[row*cols + col])  //当前格子没有被判断过
		{
			return true;
		}
		return false;
	}
	//判断的总体函数
	int check(int threshold, int rows, int cols, int row, int col, bool* visited)
	{
		int count = 0;
		if (Judge(threshold, row, col, rows, cols, visited))
		{
			visited[row*cols + col] = true; //标记此格子经历过
			count = 1 + check(threshold, rows, cols, row - 1, col, visited)
				+ check(threshold, rows, cols, row, col - 1, visited)
				+ check(threshold, rows, cols, row + 1, col, visited)
				+ check(threshold, rows, cols, row, col + 1, visited);
		}
		return count;
	}

	int movingCount(int threshold, int rows, int cols)
	{
		if (threshold<0 || rows <= 0 || cols <= 0)
		{
			return 0;
		}

		bool * visited = new bool[rows*cols];
		for (int i = 0; i< rows*cols; ++i)
		{
			visited[i] = false;
		}
		int count = check(threshold, rows, cols, 0, 0, visited);

		delete[]visited;
		return count;
	}
};
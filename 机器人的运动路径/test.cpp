#include<iostream>
using namespace std;
class Solution {
public:
	//��һ�����ֵ���λ֮��
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
	//�жϵ�ǰ���ָ��ӻ����ܷ�ﵽ
	bool Judge(int threshold, int row, int col, int rows, int cols, bool* visited)
	{
		if (row >= 0 && row<rows && col >= 0 && col<cols  // ����û��Խ��
			&& GetSum(row) + GetSum(col) <= threshold  //���������������λ֮��С�ڵ���k�ĸ���
			&& !visited[row*cols + col])  //��ǰ����û�б��жϹ�
		{
			return true;
		}
		return false;
	}
	//�жϵ����庯��
	int check(int threshold, int rows, int cols, int row, int col, bool* visited)
	{
		int count = 0;
		if (Judge(threshold, row, col, rows, cols, visited))
		{
			visited[row*cols + col] = true; //��Ǵ˸��Ӿ�����
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
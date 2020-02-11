class Solution {
public:
	bool hasPath(char* matrix, int rows, int cols, char* str)
	{
		if (matrix == NULL || rows<1 || cols<1 || str == NULL) return false;
		//二维数组表示每个字符是否被查找过
		bool *flag = new bool[rows*cols];
		memset(flag, false, rows*cols);
		for (int i = 0; i<rows; i++)
		{
			for (int j = 0; j<cols; j++)
			{
				if (haha(matrix, rows, cols, i, j, str, 0, flag))
				{
					return true;
				}
			}
		}
		delete[] flag;
		return false;
	}
	/*参数说明*/
	bool haha(char* matrix, int rows, int cols, int i, int j, char* str, int k, bool* flag)
	{
		//因为是一维数组存放二维的值，index值就是相当于二维数组的（i，j）在一维数组的下标
		int index = i * cols + j;
		//flag[index]==true,说明被访问过了，那么也返回true;
		if (i<0 || i >= rows || j<0 || j >= cols
			|| matrix[index] != str[k] //表示当前与目标不匹配
			|| flag[index] == true)    //表示被访问过
			return false;
		//字符串已经查找结束，说明找到该路径了
		if (str[k + 1] == '\0')
			return true;

		flag[index] = true;//标记访问过  

		//向四个方向进行递归查找,向左，向右，向上，向下查找
		if (haha(matrix, rows, cols, i - 1, j, str, k + 1, flag)
			|| haha(matrix, rows, cols, i + 1, j, str, k + 1, flag)
			|| haha(matrix, rows, cols, i, j - 1, str, k + 1, flag)
			|| haha(matrix, rows, cols, i, j + 1, str, k + 1, flag))
		{
			return true;
		}
		//如果上下左右都不符合，则标记为错误，重新开始寻找
		flag[index] = false;
		return false;
	}
};
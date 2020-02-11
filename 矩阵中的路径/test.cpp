class Solution {
public:
	bool hasPath(char* matrix, int rows, int cols, char* str)
	{
		if (matrix == NULL || rows<1 || cols<1 || str == NULL) return false;
		//��ά�����ʾÿ���ַ��Ƿ񱻲��ҹ�
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
	/*����˵��*/
	bool haha(char* matrix, int rows, int cols, int i, int j, char* str, int k, bool* flag)
	{
		//��Ϊ��һά�����Ŷ�ά��ֵ��indexֵ�����൱�ڶ�ά����ģ�i��j����һά������±�
		int index = i * cols + j;
		//flag[index]==true,˵�������ʹ��ˣ���ôҲ����true;
		if (i<0 || i >= rows || j<0 || j >= cols
			|| matrix[index] != str[k] //��ʾ��ǰ��Ŀ�겻ƥ��
			|| flag[index] == true)    //��ʾ�����ʹ�
			return false;
		//�ַ����Ѿ����ҽ�����˵���ҵ���·����
		if (str[k + 1] == '\0')
			return true;

		flag[index] = true;//��Ƿ��ʹ�  

		//���ĸ�������еݹ����,�������ң����ϣ����²���
		if (haha(matrix, rows, cols, i - 1, j, str, k + 1, flag)
			|| haha(matrix, rows, cols, i + 1, j, str, k + 1, flag)
			|| haha(matrix, rows, cols, i, j - 1, str, k + 1, flag)
			|| haha(matrix, rows, cols, i, j + 1, str, k + 1, flag))
		{
			return true;
		}
		//����������Ҷ������ϣ�����Ϊ�������¿�ʼѰ��
		flag[index] = false;
		return false;
	}
};
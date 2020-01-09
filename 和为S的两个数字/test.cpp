#include<vector>
#include<iostream>
using namespace std;
class Solution {
public:
	vector<int> FindNumbersWithSum(vector<int> array, int sum) {
		vector<int> res;
		int i = 0;
		int j = array.size() - 1;
		//���ԽԶ�˻�ԽС,һ���ҵ�һ�����ݾ�ֱ�ӷ�����������һ��
		while (i<j)
		{
			if (array[i] + array[j] == sum)
			{
				res.push_back(array[i]);
				res.push_back(array[j]);
				break;
			}
			while (i<j&&array[i] + array[j]>sum)
				--j;
			while (i<j&&array[i] + array[j]<sum)
				++i;
		}
		return res;
	}
};

int main()
{
	return 0;
}
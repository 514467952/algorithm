#include<vector>
#include<iostream>
using namespace std;
class Solution {
public:
	vector<int> FindNumbersWithSum(vector<int> array, int sum) {
		vector<int> res;
		int i = 0;
		int j = array.size() - 1;
		//相差越远乘积越小,一但找到一组数据就直接返回无需找下一组
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
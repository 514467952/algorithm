#include<algorithm>
#include<iostream>
#include<vector>

using namespace std;
class Solution {
public:
	int maxArea(vector<int>& height) {
		int length = height.size();
		int left = 0;
		int right = length - 1;
		int temp = 0;
		int res = 0; //保存结果
		while (left<right)
		{
			//两条边中最短的
			temp = min(height[left], height[right]);
			res = max(res, (right - left)*temp);
			//如果最短的边是左边，则left++,否则right++
			if (temp == height[left])
			{
				left++;
			}
			else
			{
				right--;
			}
		}
		return res;
	}
};

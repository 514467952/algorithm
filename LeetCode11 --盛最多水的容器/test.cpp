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
		int res = 0; //������
		while (left<right)
		{
			//����������̵�
			temp = min(height[left], height[right]);
			res = max(res, (right - left)*temp);
			//�����̵ı�����ߣ���left++,����right++
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

#include<iostream>
using namespace std;
#include<vector>
class Solution {
public:
	int GetNumberOfK(vector<int> data, int k) {
		//sort(data.begin(),data.end());
		int j = 0;
		for (int i = 0; i<data.size(); ++i)
		{
			if (data[i] == k)
			{
				j = i;
				break;
			}
		}
		int count = 0;
		for (; j<data.size(); ++j)
		{
			if (data[j] != k)
				break;
			count++;
		}
		return count;
	}
};
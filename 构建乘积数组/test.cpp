#include<iostream>
#include<vector>

using namespace std;
class Solution {
public:
	vector<int> multiply(const vector<int>& A) {
		vector<int> res;
		int length1 = A.size();
		if (length1 == 0)
			return res;
		res.push_back(1);
		for (int i = 1; i<length1; ++i)
			res.push_back(res[i - 1] * A[i - 1]);
		double temp = 1;
		for (int i = length1 - 1; i >= 0; --i)
		{
			res[i] = res[i] * temp;
			temp *= A[i];
		}

		return res;
	}
};
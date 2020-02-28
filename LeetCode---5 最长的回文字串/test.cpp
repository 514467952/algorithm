class Solution {
public:
	string longestPalindrome(string s) {
		int n = s.size();
		//记录字符串是否为回文字符串
		vector<vector<bool>> array(n, vector<bool>(n));
		string res = "";//记录结果返回
		int length = 0; //记录长度，比较出最长的回文子串
		if (n == 0)
			return s;
		if (n == 1)
			return s;
		//如果是两个字符，则返回第一个字符
		res = s[0];
		//外层循环有边界
		for (int right = 0; right<n; ++right)
		{
			//内层循环左边界
			for (int left = right; left >= 0; --left)
			{
				//判断是否为回文字串
				if (s[left] == s[right] //两头相等
					&& (right - left <= 2 //长度小于等于3，并且两头相等比为回文串
					|| array[left + 1][right - 1]) //去掉两头，中间也是回文串才是回文串
					)
				{
					//标记left~right该区间为回文串
					array[left][right] = true;
					if (right - left>length)  //如果回文串长度大于之前记录的长度，则记录该串
					{
						res = s.substr(left, right - left + 1);
						length = right - left; //记录新长度
					}
				}
			}
		}
		return res;
	}
};
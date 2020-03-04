class Solution {
public:
	string longestCommonPrefix(vector<string>& strs) {
		string res = "";
		if (strs.empty())
			return res;
		char ch;
		for (int i = 0;; ++i)
		{
			if (i<strs[0].size())
				ch = strs[0].at(i);
			else
				return res;

			for (auto& e : strs)
			{
				if (i < e.size() && ch == e[i]) //什么也不干，因为通过筛选
					;
				else
					//没通过，直接返回
					return res;
			}
			//加上每回通过的
			res += ch;
		}
		return res;
	}
};

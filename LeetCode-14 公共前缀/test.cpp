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
				if (i < e.size() && ch == e[i]) //ʲôҲ���ɣ���Ϊͨ��ɸѡ
					;
				else
					//ûͨ����ֱ�ӷ���
					return res;
			}
			//����ÿ��ͨ����
			res += ch;
		}
		return res;
	}
};

class Solution {
public:
	string longestPalindrome(string s) {
		int n = s.size();
		//��¼�ַ����Ƿ�Ϊ�����ַ���
		vector<vector<bool>> array(n, vector<bool>(n));
		string res = "";//��¼�������
		int length = 0; //��¼���ȣ��Ƚϳ���Ļ����Ӵ�
		if (n == 0)
			return s;
		if (n == 1)
			return s;
		//����������ַ����򷵻ص�һ���ַ�
		res = s[0];
		//���ѭ���б߽�
		for (int right = 0; right<n; ++right)
		{
			//�ڲ�ѭ����߽�
			for (int left = right; left >= 0; --left)
			{
				//�ж��Ƿ�Ϊ�����ִ�
				if (s[left] == s[right] //��ͷ���
					&& (right - left <= 2 //����С�ڵ���3��������ͷ��ȱ�Ϊ���Ĵ�
					|| array[left + 1][right - 1]) //ȥ����ͷ���м�Ҳ�ǻ��Ĵ����ǻ��Ĵ�
					)
				{
					//���left~right������Ϊ���Ĵ�
					array[left][right] = true;
					if (right - left>length)  //������Ĵ����ȴ���֮ǰ��¼�ĳ��ȣ����¼�ô�
					{
						res = s.substr(left, right - left + 1);
						length = right - left; //��¼�³���
					}
				}
			}
		}
		return res;
	}
};
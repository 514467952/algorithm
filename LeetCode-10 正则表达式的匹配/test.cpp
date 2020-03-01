class Solution {
public:
	bool isMatch(string s, string p) {
		//����������
		if (p.length() == 0)
			return s.length() == 0;
		//��һ���ַ�ƥ��
		bool match = (s.length() > 0 && (s.at(0) == p.at(0) || p.at(0) == '.'));
		//�������
		if (p.length() > 1 && p.at(1) == '*'){
			//ƥ��0��,����p�е��������ַ���������s�����ƶ�һ������ƥ��
			return isMatch(s, p.substr(2)) || (match && isMatch(s.substr(1), p));
		}
		else {
			//һ�����
			return match && isMatch(s.substr(1), p.substr(1));
		}
	}
};

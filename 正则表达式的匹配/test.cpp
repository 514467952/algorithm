class Solution {
public:
	bool match(char* str, char* pattern)
	{
		if (*str == '\0'&& *pattern == '\0')
			return true;
		if (*str != '\0' && *pattern == '\0')
			return false;

		//������ʽ����һ���ַ�����*
		//��������
		//�жϵ�ǰ�Ƿ���Ȼ���ֻҪ���ʽΪ.����ƥ����ַ�����Ϊ��
		//Ȼ�󷵻�str+,pattern+1�ж���һ��
		if (*(pattern + 1) != '*'){
			if (*str == *pattern || *str != '\0'&& *pattern == '.')
				return match(str + 1, pattern + 1);
			else
				return false;
		}
		//������һ���ַ�Ϊ'*'
		else{
			if (*str == *pattern || *str != '\0' && *pattern == '.')
				return match(str, pattern + 2) || match(str + 1, pattern);
			else
				return match(str, pattern + 2);
		}

	}
};
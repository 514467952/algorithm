class Solution {
public:
	bool match(char* str, char* pattern)
	{
		if (*str == '\0'&& *pattern == '\0')
			return true;
		if (*str != '\0' && *pattern == '\0')
			return false;

		//如果表达式的下一个字符不是*
		//正常处理
		//判断当前是否相等或者只要表达式为.并且匹配的字符串不为空
		//然后返回str+,pattern+1判断下一个
		if (*(pattern + 1) != '*'){
			if (*str == *pattern || *str != '\0'&& *pattern == '.')
				return match(str + 1, pattern + 1);
			else
				return false;
		}
		//否则下一个字符为'*'
		else{
			if (*str == *pattern || *str != '\0' && *pattern == '.')
				return match(str, pattern + 2) || match(str + 1, pattern);
			else
				return match(str, pattern + 2);
		}

	}
};
class Solution {
public:
	bool isMatch(string s, string p) {
		//代码完整性
		if (p.length() == 0)
			return s.length() == 0;
		//第一个字符匹配
		bool match = (s.length() > 0 && (s.at(0) == p.at(0) || p.at(0) == '.'));
		//特殊情况
		if (p.length() > 1 && p.at(1) == '*'){
			//匹配0个,跳过p中的这两个字符；或多个，s往后移动一个继续匹配
			return isMatch(s, p.substr(2)) || (match && isMatch(s.substr(1), p));
		}
		else {
			//一般情况
			return match && isMatch(s.substr(1), p.substr(1));
		}
	}
};

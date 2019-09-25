#include<iostream>
#include<string>
using namespace std;


int judge(string s1, string s2){
	string s;
	s = s1 + s1;		//把第一个字符串加两边，如果加后的大串当中能找到第二个字符串就可以
	int pos = 0;
	pos = s1.find(s2);
	if (pos == -1){
		return 0;
	}
	else {
		return 1;
	}

}


int main()
{
	string s1;
	string s2;
	long len1 = 0;
	long  len2 = 0;
	int ret = 0;
	cin >> len1;
	cin >> len2;
	cin >> s1;
	cin >> s2;
	len1 = s1.size();
	len2 = s2.size();
	if (len1 != len2){
		cout << "NO" << endl;
	}
	else{
		ret = judge(s1, s2);
		if (ret == 1)
			cout << "YES" << endl;
		else
			cout << "NO" << endl;
	}

	system("pause");
	return 0;
}

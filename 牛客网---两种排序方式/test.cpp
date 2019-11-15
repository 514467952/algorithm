#include<string.h>
#include<vector>
using namespace std;
int main(){

	int n;
	cin >> n;
	vector<string> s;

	for (int i = 0; i<n; ++i)
	{
		string s1;
		getline(cin, s1);
		s.push_back(s1);
	}

	int j = 0;
	//默认两个排序都可以
	bool flag = true;
	bool flag2 = true;
	while (j < n - 1)
	{
		if (s[j]> s[j + 1])
			flag = false; //代表不是根据字典序
		++j;
	}

	j = 0;
	while (j < n - 1)
	{
		if (s[j].size() > s[j + 1].size())//代表不是按字符串大小排序
			flag2 = false;
		++j;
	}


	//strcpy(char *dest, const char *src)
	if (flag && flag2)
		cout << "both";
	else if (flag)
		cout << "lexicographically";
	else if (flag2)
		cout << "lengths";
	else
		cout << "none";

	return 0;
}
#endif 

#include<iostream>
#include<string>
#include<string.h>
#include<vector>
#include<algorithm>
using namespace std;
int main(){

	int n;
	cin >> n;
	vector<string> s1;

	for (int i = 0; i<n; ++i)
	{
		string s5;
		getline(cin, s5);
		s1.push_back(s5);
	}

	//默认两个排序都可以
	bool flag = false;
	bool flag2 = false;

	vector<string> stemp(s1);
	sort(stemp.begin(), stemp.end());
	if (stemp == s1)
		flag = true;

	vector<int> length;
	for (int i = 0; i<s1.size(); ++i)
	{
		length.push_back(s1[i].length());
	}
	vector<int> stemp2(length);
	sort(stemp2.begin(), stemp2.end());
	if (stemp2 == length)
		flag2 = true;
	//strcpy(char *dest, const char *src)
	if (flag == true && flag2 == true)
		cout << "both";
	if (flag == true && flag2 == false)
		cout << "lexicographically";
	if (flag2 == true && flag == false)
		cout << "lengths";
	if (flag2 == false && flag == false)
		cout << "none";

	return 0;
}
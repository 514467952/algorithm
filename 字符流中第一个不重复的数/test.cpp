#include<iostream>
#include<map>
#include<string>
using namespace std;
class Solution
{
	map<char, int> m;
	string s;
public:
	//Insert one char from stringstream
	void Insert(char ch)
	{
		s += ch;
		m[ch]++;
	}
	//return the first appearence once char in current stringstream
	char FirstAppearingOnce()
	{
		for (auto e : s)
		{
			if (m[e] == 1)
				return e;
		}
		return '#';
	}

};
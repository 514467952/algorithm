#include<iostream>
using namespace std;
#include<string>
#include<map>

int main()
{
	string s1 = "google";

	map<char, int> mp;
	for (int i = 0; i < s1.size(); ++i)
		mp[s1[i]]++;
	for (int i = 0; i < s1.size(); ++i){
		if (mp[s1[i]] == 1)
			printf("%d\n",i);
	}

	system("pause");
	return 0;
}
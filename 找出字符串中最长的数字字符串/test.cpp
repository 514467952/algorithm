#include<iostream>
#include<string>
#include<vector>
using namespace std;

int main()
{

	string s1;
	cin >> s1;

	string s2;
	vector<string> v1;
	int i = 0;
	int cnt = 0;
	while (i < s1.size())
	{

		if ((s1[i] - '0') >= 1 && (s1[i] - '0') <= 9)
		{
			s2.push_back(s1[i]);
		}
		else{
			v1.push_back(s2);
			s2 = "";
		}
		++i;
	}
	v1.push_back(s2);

	int max = 0;
	for (int j = 1; j < v1.size(); ++j)
	{
		if (v1[j].size() > v1[max].size())
		{
			max = j;
		}
	}

	cout << v1[max] << endl;
	system("pause");
	return 0;
}
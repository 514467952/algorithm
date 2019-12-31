#include<iostream>
#include<algorithm>
using namespace std;

#include<string>

int main()
{
	string s("123");
	while (next_permutation(s.begin(), s.end()))
		cout << s<<endl;

	system("pause");
	return 0;
}
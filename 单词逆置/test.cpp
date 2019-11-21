#include<iostream>
#include<stack>
#include<string>
#include<vector>
using namespace std;

int main()
{
	string s;
	stack<string> sp;
	//一次让他输入一个单词
	while (cin >> s)
	{
		//每个单词依次入栈
		sp.push(s);
		//因为最后一个单词是以'.'为结尾的，若以判断一下，作为输入循环的退出
		if (*(s.rbegin()) == '.')
			break;
	}
	//打印第一个出栈单词
	cout << sp.top();
	sp.pop();
	//依次打印剩下的单词，注意有空格
	while (!sp.empty())
	{
		cout << " " << sp.top();
		sp.pop();
	}
	return 0;
}
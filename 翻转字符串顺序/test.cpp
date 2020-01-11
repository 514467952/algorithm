#include<iostream>
using namespace std;
#include<string>

string ReverseSentence(string str) {
	string res = "", tmp = "";
	for (unsigned int i = 0; i < str.size(); ++i){
		if (str[i] == ' ')
		{
			res = " " + tmp + res;
			tmp = "";
		}
		else
			tmp += str[i];
	}
	if (tmp.size())
		res = tmp + res;
	return res;
}

int main()
{
	string s1 = "I am a student.";
	ReverseSentence(s1);
	return 0;
}
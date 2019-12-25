#include<iostream>
#include<stack>
using namespace std;
class Solution {
	stack<int> s1;
	stack<int> s2; //minջ
public:
	void push(int value) {
		if (s1.empty())
		{
			s1.push(value);
			s2.push(value);
		}
		else
		{
			if (value < s1.top())
			{
				s1.push(value);
				s2.push(value);
			}
			else
			{
				s1.push(value);
				s2.push(s2.top());
			}
		}


	}
	void pop() {
		s1.pop();
		s2.pop();
	}
	int top() {
		return s1.top();
	}
	int min() {
		return s2.top();
	}
};
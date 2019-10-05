#include<iostream>
#include<stack>
using namespace std;
/*
class MinStack {
public:
	 initialize your data structure here. 
	MinStack() {

	}

	void push(int x) {
		left.push(x);
		int min;
		if (!right.empty() && right.top() <= x){
			 min = right.top();
		}
		else
		{
			min = x;
		}
		right.push(min);
	}

	void pop() {
		left.pop();
		right.pop();
	}

	int top() {
		return left.top();
	}

	int getMin() {
		return right.top();
	}

	stack<int> left;  //存正长的数据
	stack<int> right;  //存最小的数据
};
*/



class MinStack {
public:
	/** initialize your data structure here. */
	MinStack() {

	}

	void push(int x) {
		left.push(x);
		if (right.empty() || x <= right.top()){
			right.push(x);
		}
	}

	void pop() {
		int top = left.top();
		left.pop();
		if (top == right.top()){
			right.pop();
		}
	}

	int top() {
		return left.top();
	}

	int getMin() {
		return right.top();
		
	}

	stack<int> left;  //存正长的数据
	stack<int> right;  //存最小的数据
};
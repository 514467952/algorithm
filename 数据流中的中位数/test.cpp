
class Solution {
	priority_queue<int, vector<int>, less<int>> max;
	priority_queue<int, vector<int>, greater<int>> min;
public:
	void Insert(int num)
	{
		if (max.empty() || num <= max.top())
			max.push(num);
		else
			min.push(num);

		//保证两个堆的元素个数之差小于1
		if (max.size() == min.size() + 2)
		{
			min.push(max.top());
			max.pop();
		}
		if (max.size() + 1 == min.size())
		{
			max.push(min.top());
			min.pop();
		}
	}

	double GetMedian()
	{
		return max.size() == min.size() ? (max.top() + min.top()) / 2.0 : max.top();
	}
};
#include<iostream>
using namespace std;
#include<string>
#include<algorithm>
#include<vector>

/*对vector容器内的数据进行排序，按照 将a和b转为string后
若 a＋b<b+a  a排在在前 的规则排序,
如 2 21 因为 212 < 221 所以 排序后为 21 2
to_string() 可以将int 转化为string
*/ 
class Solution {
public:
	static bool cmp(int a, int b){
		string A = "";
		string B = "";
		A += to_string(a);
		A += to_string(b);
		B += to_string(b);
		B += to_string(a);

		return A<B;
	}
	string PrintMinNumber(vector<int> numbers) {
		string  answer = "";
		sort(numbers.begin(), numbers.end(), cmp);
		for (int i = 0; i<numbers.size(); i++){
			answer += to_string(numbers[i]);
		}
		return answer;
	}
};
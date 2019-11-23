
#include <iostream>
#include <algorithm>
#include <climits>
#include <vector>
using namespace std;

/*首先，要保证拿出至少一对匹配的手套
*	我们保证所有颜色都拿一只(在左右手套中选择数量相对较少的来拿所有颜色)
*		只需要用该边手套总数减去最少数量+1即可
*	然后另一边手套只需要拿一只就可以保证匹配
*其次，考虑某个颜色一边数量为0的情况
*	要把另一边相应颜色的手套数加进去*/
class Gloves {
public:
	int findMinimum(int n, vector<int> left, vector<int> right)
	{
		int count = 0, left_count = 0, right_count = 0, left_min = INT_MAX, right_min = INT_MAX;
		for (int i = 0; i < n; ++i)
		{
			if (left[i] == 0 || right[i] == 0) //如果某一边对应颜色数量为0，则加上另一边的数量
				count += left[i] + right[i];
			else
			{
				left_count += left[i]; //统计左边手套数
				right_count += right[i]; //统计右边手套数
				left_min = min(left_min, left[i]); //找出左边最小数量
				right_min = min(right_min, right[i]); //找出右边最小数量
			}
		}

		return count + min(left_count - left_min + 1, right_count - right_min + 1) + 1;
	}
};

int main()
{
	int n;
	while (cin >> n)
	{
		vector<int> left(n);
		vector<int> right(n);
		for (auto&e : left)
			cin >> e;
		for (auto&e : right)
			cin >> e;
		Gloves g;
		cout << g.findMinimum(n, left, right) << endl;
	}
	return 0;
}


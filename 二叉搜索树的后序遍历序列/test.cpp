#include<iostream>
#include<vector>
using namespace std;
class Solution {
public:
	bool VerifySquenceOfBST(vector<int> sequence) {
		int size = sequence.size(); //求出数组长度
		if (0 == size)                //为0返回
			return false;
		int i = 0;
		//去掉总根结点后，数组最后一个元素就是右子树的根结点，它的左子树都比它小，右子树都比它大
		//那么size再--，就到了右子树的右子树或者到左子树，上述条件仍然成立
		while (--size)
		{
			while (sequence[i++]<sequence[size]); //看左子树的值是不是都小于根结点
			while (sequence[i++]>sequence[size]); //右子树的值是不是都大于根结点

			if (i<size) //如果最后i还没有和size相同，返回错误
				return false;
			i = 0;
		}
		return true;
	}
};
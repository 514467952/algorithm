#include<iostream>
#include<vector>
using namespace std;
class Solution {
public:
	bool VerifySquenceOfBST(vector<int> sequence) {
		int size = sequence.size(); //������鳤��
		if (0 == size)                //Ϊ0����
			return false;
		int i = 0;
		//ȥ���ܸ������������һ��Ԫ�ؾ����������ĸ���㣬����������������С����������������
		//��ôsize��--���͵��������������������ߵ�������������������Ȼ����
		while (--size)
		{
			while (sequence[i++]<sequence[size]); //����������ֵ�ǲ��Ƕ�С�ڸ����
			while (sequence[i++]>sequence[size]); //��������ֵ�ǲ��Ƕ����ڸ����

			if (i<size) //������i��û�к�size��ͬ�����ش���
				return false;
			i = 0;
		}
		return true;
	}
};
#include<iostream>
#include<stack>
#include<string>
#include<vector>
using namespace std;

int main()
{
	string s;
	stack<string> sp;
	//һ����������һ������
	while (cin >> s)
	{
		//ÿ������������ջ
		sp.push(s);
		//��Ϊ���һ����������'.'Ϊ��β�ģ������ж�һ�£���Ϊ����ѭ�����˳�
		if (*(s.rbegin()) == '.')
			break;
	}
	//��ӡ��һ����ջ����
	cout << sp.top();
	sp.pop();
	//���δ�ӡʣ�µĵ��ʣ�ע���пո�
	while (!sp.empty())
	{
		cout << " " << sp.top();
		sp.pop();
	}
	return 0;
}
#include<iostream>
#include<string>
using namespace std;

//��from��to���ƶ�������help
void process(int N, string from, string to, string help)
{
	if (N == 1)
	{
		cout << "�ƶ� 1 " << "��" << from << "��" << to << endl;
	}
	else{
		process(N - 1, from, help, to);
		cout << "�ƶ� " << N << "��" << from << "��" << to<<endl;
		process(N - 1, help, to, from);
	}
}

int main()
{
	process(3,"��","��","��");
	system("pause");
	return 0;
}
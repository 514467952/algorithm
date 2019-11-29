#include<iostream>
#include<string>
using namespace std;

//把from往to上移动，借助help
void process(int N, string from, string to, string help)
{
	if (N == 1)
	{
		cout << "移动 1 " << "从" << from << "到" << to << endl;
	}
	else{
		process(N - 1, from, help, to);
		cout << "移动 " << N << "从" << from << "到" << to<<endl;
		process(N - 1, help, to, from);
	}
}

int main()
{
	process(3,"左","右","中");
	system("pause");
	return 0;
}
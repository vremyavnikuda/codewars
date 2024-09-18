#include <iostream>
using namespace std;

int main()
{
	int a, b;
	cin >> a >> b;
	if (a > b)
	{
		cout << "Победит Деннис";
	}
	else if (a < b)
	{
		cout << "Победит Бьёрн";
	}
	else if (a == b)
	{
		cout << "Победит дружба";
	}
}
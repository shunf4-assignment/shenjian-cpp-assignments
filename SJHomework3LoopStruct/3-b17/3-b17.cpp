/* 1652270 计算机2班 冯舜 */
#include <iostream>
using namespace std;

int main()
{
	int x;

	do
	{
		cout << "请输入 x 的值 (0-100)：" << endl;
		cin >> x;
		if (cin.rdstate() != ios_base::failbit) {
			if (x >= 0 && x <= 100)
				break;
		}
		else
		{
			//cin.sync();
			cin.clear();
			cin.ignore(numeric_limits<std::streamsize>::max() , '\n');
		}

	} while (1);

	cout << "x=" << x << endl;

	return 0;
}
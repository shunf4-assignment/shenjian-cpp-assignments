/* 1652270 计算机2班 冯舜 */
#include <iostream>
#include <iomanip>
using namespace std;


int main()
{
	bool lights[101] = { false };  //lights[0]没用
	int lightNum = 0;

	for (int personNo = 1; personNo <= 100; personNo++)
	{
		for (int lightNo = personNo; lightNo <= 100; lightNo += personNo)
		{
			lights[lightNo] = !lights[lightNo];
		}
	}

	cout << "操作之后还亮着的灯编号为：" << endl;

	for (int lightNo = 1; lightNo <= 100; lightNo += 1)
	{
		if (lights[lightNo])
		{
			cout << setw(5) << lightNo;
			lightNum++;
		}
		if ((lightNum - 1) % 10 == 9 )
			cout << endl;
	}
	return 0;
}

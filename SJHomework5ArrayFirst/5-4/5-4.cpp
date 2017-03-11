/* 1652270 计算机2班 冯舜 */
#include <iostream>
#include <iomanip>
using namespace std;

template <typename T>
void printArray(T array[], int arrayLength)
{
	for (int i = 0; i < arrayLength; i++)
		cout << "[" << setw(2) << i << "]->" << setw(3) << array[i] << " ";
	cout << endl;
}

template <typename T>
void sortArray(T arrayToBeSorted[], int arrayLength, bool lessToGreater = true)
{
	int maxThisTurn;
	T tempVar;
	for (int i = arrayLength - 1; i > 0; i--)
	{
		maxThisTurn = 0;
		for (int j = 1; j < i+1; j++)
		{
			if (((lessToGreater) ^ (arrayToBeSorted[maxThisTurn] > arrayToBeSorted[j])) && (arrayToBeSorted[maxThisTurn] != arrayToBeSorted[j]))
				maxThisTurn = j;
		}
		tempVar = arrayToBeSorted[maxThisTurn];
		arrayToBeSorted[maxThisTurn] = arrayToBeSorted[i];
		arrayToBeSorted[i] = tempVar;

	}
}

template <typename T>
int insertArray(T array[], int arrayLength, T x, bool lessToGreater = true) //此处的arrayLength是数据的长度，不是数组的长度（就是说不计留空的那个位置）
{
	int whereInsert = 0;
	for (int i = 0; i < arrayLength; i++)
	{
		if ((array[i] > x) ^ lessToGreater)
		{
			whereInsert = i + 1;
		}
	}
	for (int i = arrayLength - 1; i >= whereInsert; i--)
	{
		array[i + 1] = array[i];
	}
	array[whereInsert] = x;

	return whereInsert;
}

int main()
{
	//REINPUT:
	double x;
	double sortedArray[17] = { -4,-6,0.1,8,3,-2,-10,9,8,3,0,10,21,3,8,-3 };	//数组长度比已有数据多一位，便于插入后的偏移
	bool valid, lessToGreater = false;
	int sortedArrayLength = sizeof(sortedArray) / sizeof(sortedArray[0]);
	int whereInsert;
	sortedArrayLength -= 1;

	sortArray(sortedArray, sortedArrayLength, lessToGreater);
	cout << "插入前的数组如下：（按" << (lessToGreater ? "从小到大" : "从大到小") << "顺序排列）" << endl;
	printArray(sortedArray, sortedArrayLength);

	do
	{
		valid = true;
		cout << "请输入要插入这个数组的数（实数）：";
		cin >> x;

		if (!cin.good())
		{
			valid = false;
			cin.clear();
			cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
			continue;
		}

		if (x == INFINITY || x == -INFINITY)
		{
			valid = false;
			cout << "输入超出范围，请重新输入。" << endl;
			cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
			continue;
		}

	} while (!valid);

	whereInsert = insertArray(sortedArray, sortedArrayLength, x, lessToGreater);

	cout <<  x << " 插入了array[" << whereInsert << "],插入后的数组如下：（按" << (lessToGreater ? "从小到大" : "从大到小") << "顺序排列）" << endl;
	printArray(sortedArray, sortedArrayLength +1);

	cout << endl;
	//goto REINPUT;
	return 0;
}

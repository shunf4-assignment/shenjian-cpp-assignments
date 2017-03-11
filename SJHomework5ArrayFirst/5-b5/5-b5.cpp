/* 1652270 计算机2班 冯舜 */
#include <iostream>
#include <iomanip>
#include <fstream>
using namespace std;

template <typename T>
void printArrayInRank(T array[], int arrayLength)
{
	int sameLevel = 0;
	for (int i = 0; i < arrayLength; i++)
	{
		if (i == 0 || array[i] != array[i - 1])
		{
			sameLevel = i;
		}
		cout << array[i] << " " << sameLevel + 1 << endl;
	}
}

template <typename T>
void sortArray(T arrayToBeSorted[], int arrayLength, bool lessToGreater = true)
{
	int maxThisTurn;
	T tempVar;
	for (int i = arrayLength - 1; i > 0; i--)
	{
		maxThisTurn = 0;
		for (int j = 1; j < i + 1; j++)
		{
			if (((lessToGreater) ^ (arrayToBeSorted[maxThisTurn] > arrayToBeSorted[j])) && (arrayToBeSorted[maxThisTurn] != arrayToBeSorted[j]))
				maxThisTurn = j;
		}
		tempVar = arrayToBeSorted[maxThisTurn];
		arrayToBeSorted[maxThisTurn] = arrayToBeSorted[i];
		arrayToBeSorted[i] = tempVar;
	}
}


int main()
{
	//REINPUT:
	int scoreArray[1000];
	int currScore;
	bool lessToGreater = false;
	int scoreArrayLength;
	int i;
	ifstream f;
	f.open("score.dat", ios::in);
	if (f.is_open() == 0)
	{
		cout << "打开文件失败。" << endl;
		return -1;
	}

	for (i = 0; i < 1000; i++)
	{
		f >> currScore;
		if (!f.good())
		{
			cout << "输入数据失效。" << endl;
			return -1;
		}
		if (currScore == -1)
			break;
		if (currScore < 0 || currScore > 100)
		{
			cout << "输入数据超出范围。" << endl;
			return -1;
		}
		scoreArray[i] = currScore;
	}

	scoreArrayLength = i;
	sortArray(scoreArray, scoreArrayLength, lessToGreater);

	printArrayInRank(scoreArray, scoreArrayLength);

	return 0;
}

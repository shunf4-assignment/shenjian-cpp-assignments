/* 1652270 ¼ÆËã»ú2°à ·ëË´ */
#include <iostream>
#include <iomanip>
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
	double scoreArray[] = { 47,10,3,62,7,73,2,90,49,45,
		67,62,91,57,91,66,21,81,58,64,
		62,30,72,23,52,78,35,8,3,16,
		12,42,75,31,82,69,18,18,76,29,
		46,86,86,35,3,37,68,83,41,82,
		29,47,7,34,91,57,67,58,27};
	bool lessToGreater = false;
	int scoreArrayLength = sizeof(scoreArray) / sizeof(scoreArray[0]);

	sortArray(scoreArray, scoreArrayLength, lessToGreater);

	printArrayInRank(scoreArray, scoreArrayLength);

	return 0;
}

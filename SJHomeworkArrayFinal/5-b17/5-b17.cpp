/* 1652270 ¼ÆËã»ú2°à ·ëË´ */
#include <iostream>
#include <time.h>
using namespace std;
#define WIDTH 26
#define HEIGHT 10
#define MINE 50

template <typename T>
void shiftArr(T arr[], int removePos, int lastPos);

int main()
{
	
	int grid[WIDTH * HEIGHT];
	char map[HEIGHT][WIDTH];
	int mine[MINE];
	int thisRan, x, y;
	time_t t;
	time(&t);
	srand((unsigned int)t);

	for (int i = 0; i < WIDTH*HEIGHT; i++)
	{
		grid[i] = i;
		map[i / WIDTH][i % WIDTH] = '0';
	}
	for (int m = 0; m < MINE; m++)
	{
		thisRan = int(rand() / 32676. * (WIDTH * HEIGHT - m));
		mine[m] = grid[thisRan];
		shiftArr(grid, thisRan, (WIDTH * HEIGHT - m - 1));
		y = mine[m] / WIDTH;
		x = mine[m] % WIDTH;
		map[y][x] = '*';
		if (y > 0 && map[y - 1][x] != '*')
			map[y - 1][x]++;
		if (y < HEIGHT - 1 && map[y + 1][x] != '*')
			map[y + 1][x]++;
		if (x < WIDTH - 1 && map[y][x + 1] != '*')
			map[y][x + 1]++;
		if (x > 0 && map[y][x - 1] != '*')
			map[y][x - 1]++;

		if (y > 0 && x < WIDTH - 1 && map[y - 1][x + 1] != '*')
			map[y - 1][x + 1]++;
		if (y < HEIGHT - 1 && x < WIDTH - 1 && map[y + 1][x + 1] != '*')
			map[y + 1][x + 1]++;
		if (x > 0 && y < HEIGHT - 1 && map[y + 1][x - 1] != '*')
			map[y + 1][x - 1]++;
		if (x > 0 && y > 0 && map[y - 1][x - 1] != '*')
			map[y - 1][x - 1]++;
	}
	for (int j = 0; j < HEIGHT; j++)
	{
		for (int i = 0; i < WIDTH; i++)
			cout << map[j][i] << " ";
		cout << endl;
	}
	
	return 0;
}

template <typename T>
void shiftArr(T arr[], int removePos, int lastPos)
{
	for (int i = removePos; i < lastPos; i++)
	{
		arr[i] = arr[i + 1];
	}
}
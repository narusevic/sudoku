#include "sudoku.h"

void getRow(int* grid, int index, int* nums)
{
	int row = index / 9;
	int sum = 0;

	for (int x = 0; x < 9; x++)
	{
		*(nums + sum) = *(grid + row * 9 + x);
		sum++;
	}
}

void getColumn(int* grid, int index, int* nums)
{
	int row = index % 9;
	int sum = 0;

	for (int y = 0; y < 9; y++)
	{
		*(nums + sum) = *(grid + row + y * 9);
		sum++;
	}
}

void getGroup(int* grid, int index, int* nums)
{
	int groupRow = index / 27;
	int groupColumn = (index % 9) / 3;

	int sum = 0;
	for (int x = 0; x < 3; x++)
	{
		for (int y = 0; y < 3; y++)
		{
			*(nums + sum) = *(grid + groupRow * 27 + groupColumn * 3 + x * 9 + y);
			sum++;
		}
	}
}

int possibleNumbers(int* grid, int index/*, int* nums*/)
{
	int rowNums[9], colNums[9], groupNums[9];
	int current = *(grid + index);

	getRow(grid, index, rowNums);
	getColumn(grid, index, colNums);
	getGroup(grid, index, groupNums);

	int sum = 0;

	for (int d = 1; d < 10; d++)
	{
		for (int i = 0; i < 9; i++)
		{
			if (rowNums[i] == d || colNums[i] == d || groupNums[i] == d)
			{
				sum++;
				break;
			}
		}
	}

	return sum;
}

void erase(int* grid, int left)
{
	int sum = 81;
	for (int i = 0; i < 100000; i++)
	{
		int random = rand() % 81;

		cout << possibleNumbers(grid, random) << " " << random << endl;

		if (possibleNumbers(grid, random) >= 8 && *(grid + random) != 0)
		{
			*(grid + random) = 0;
			sum--;
		}

		if (left == sum)
		{
			return;
		}
	}
}

void switchLines(int* grid, int a, int b)
{
	for (int i = 0; i < 9; i++)
	{
		int temp = *(grid + b * 9 + i);
		*(grid + b * 9 + i) = *(grid + a * 9 + i);
		*(grid + a * 9 + i) = temp;
	}
}

void switchColumns(int* grid, int a, int b)
{
	for (int i = 0; i < 9; i++)
	{
		int temp = *(grid + i * 9 + b);
		*(grid + i * 9 + b) = *(grid + i * 9 + a);
		*(grid + i * 9 + a) = temp;
	}
}

void randomizeGrid(int* grid)
{
	for (int i = 0; i < 1000; i++)
	{
		int group = rand() % 3;
		int first = rand() % 3;
		int second = first;

		while (first == second)
		{
			second = rand() % 3;
		}

		if (i % 2 == 0)
		{
			switchLines(grid, group * 3 + first, group * 3 + second);
		}
		else
		{
			switchColumns(grid, group * 3 + first, group * 3 + second);
		}
	}
}

void generateSudoku(int* grid, int left)
{
	int start = 1;

	for (int i = 0; i < 9; i++)
	{
		for (int x = 0; x < 9; x++)
		{
			*(grid + i * 9 + x) = (start + x) % 9 + 1;
		}
		start += 3;

		if (i == 2)
		{
			start = 2;
		}

		if (i == 5)
		{
			start = 3;
		}
	}

	randomizeGrid(grid);
	erase(grid, left);
}

void printSudoku(int* grid)
{
	for (int i = 0; i < 9; i++)
	{
		for (int x = 0; x < 9; x++)
		{
			int value = *(grid + 9 * i + x);

			if (value == 0)
			{
				cout << "  ";
			}
			else
			{
				cout << value << " ";
			}
		}

		cout << "\n";
	}
}

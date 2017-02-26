#include "sudoku.h"

void replaceAll(std::string& str, const std::string& from, const std::string& to) 
{
    if(from.empty())
    {
        return;
    }
    
    size_t start_pos = 0;
    
    while((start_pos = str.find(from, start_pos)) != std::string::npos) 
    {
        str.replace(start_pos, from.length(), to);
        start_pos += to.length(); // In case 'to' contains 'from', like replacing 'x' with 'yx'
    }
}

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

//GENERATION

int notAvailableNumbers(int* grid, int index, int* nums)
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
                nums[sum] = d;
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
        int posNums[9];    
    
		if (notAvailableNumbers(grid, random, posNums) >= 8 && *(grid + random) != 0)
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

//END GENERATION

//IO

//option: 0 - cout; 1 - file
void printSudoku(int* grid, string name)
{
    ofstream fileOut (name.c_str());
    
    #define CSTREAM cout
    #define FSTREAM fileOut
    
    string border = "+-----+-----+-----+\n";
        
    for (int rg = 0; rg < 3; rg++)
	{
        (name == "" ? CSTREAM : FSTREAM) << border;
        
		for (int row = 0; row < 3; row++)
		{
            for (int col = 0; col < 3; col++)
            {
                int index = rg * 27 + row * 9 + col * 3;
                char value1 = grid[index] == 0 ? ' ' : grid[index] + 48;
                char value2 = grid[index + 1] == 0 ? ' ' : grid[index + 1] + 48;
                char value3 = grid[index + 2] == 0 ? ' ' : grid[index + 2] + 48;
                
                (name == "" ? CSTREAM : FSTREAM) << "|" << value1 << " " << value2 << " " << value3;                
            }
            
            (name == "" ? CSTREAM : FSTREAM) << "|\n";
        }
	}
    
    (name == "" ? CSTREAM : FSTREAM) << border;
}

void readSudokuFile(int* grid, string name)
{
    ifstream f (name.c_str());
    string content;
    
    int index = 0;
      
    while (getline(f, content))
    {
        replaceAll(content, "|", " ");   
        replaceAll(content, "+", "");   
        replaceAll(content, "-", "");   
        replaceAll(content, "  ", "0");   
        
        for (int i = 0; i < content.length(); i++)
        {                        
            if (content[i] > 47 && content[i] < 58)
            {
                grid[index] = content[i] - 48;
                index++;
            }   
        }
                
        while (index % 9 != 0)
        {
            grid[index] = 0;
            index++;
        }
    }
}

//END IO

//SOLVER

int availableNumbers(int grid[], int index, int nums[])
{
	int sum = notAvailableNumbers(grid, index, nums);

	if (sum == 9)
	{
		return 0;
	}

	int it = 0;
	int nums2[9];

	for (int d = 1; d < 10; d++)
	{
		if (d != nums[d - it])
		{
			nums2[it] = d;
			it++;
		}
	}

	nums = nums2;

	return 9 - sum;
}

void rmAvailableInputs(int availableInputs[][9], int index, int temp, int sizes[])
{
	int row = index / 9;
	int col = index % 9;
	int groupRow = index / 27;
	int groupColumn = (index % 9) / 3;
	for (int i = 0; i < 9; i++)
	{
		for (int x = 0; x < 9; x++)
		{
			if(availableInputs[row * 9 + i][x] == temp && sizes[row * 9 + i] != 0)
			{
				availableInputs[row * 9 + i][x] = 0;
				sizes[row * 9 + i]--;
			}
		}
	}

	for (int i = 0; i < 9; i++)
	{
		for (int x = 0; x < 9; x++)
		{
			if(availableInputs[i * 9 + col][x] == temp && sizes[i * 9 + col] != 0)
			{
				availableInputs[i * 9 + col][x] = 0;
				sizes[i * 9 + col]--;
			}
		}
	}

	for (int x = 0; x < 3; x++)
	{
		for (int y = 0; y < 3; y++)
		{
			for (int a = 0; a < 9; a++)
			{
				int groupIndex = groupRow * 27 + groupColumn * 3 + x * 9 + y;
				if(availableInputs[groupIndex][a] == temp && sizes[groupIndex] != 0)
				{
					availableInputs[groupIndex][a] = 0;
					sizes[groupIndex]--;
				}
			}
		}
	}
}

void recursion(int grid[], int availableInputs[][9], int sizes[])
{
	int minIndex;
	int minVariants = 9;

	for(int i = 0; i < 81; i++)
	{
		if (sizes[i] == 1)
		{
			cout << "size 1 " << i << "\n";
			int temp = 0;
			
			for (int d = 0; d < 9; d++)
			{
				if (availableInputs[i][d] > 0 && availableInputs[i][d] < 10)
				{
					temp = availableInputs[i][d];
					grid[i] = temp;
					cout << "TEEEEEEEEEEEEEEMP " << temp << " " << i <<"\n";
					sizes[i]--;
					break;
				}
			}

			for (int d = 0; d < 9; d++)
			{
				availableInputs[i][d] = 0;
			}

			rmAvailableInputs(availableInputs, i, temp, sizes);

			recursion(grid, availableInputs, sizes);
		}
		else if (minVariants > sizes[i])
		{
			minIndex = i;
			minVariants = sizes[i];
		}
	}
}

int solve(int grid[])
{
    int availableInputs[81][9];
    int sizes[81];
    
    for (int i = 0; i < 81; i++)
    {
        int posNums[9];
        int sum = availableNumbers(grid, i, posNums);
        
        for (int s = 0; s < sum; s++)
        {
            availableInputs[i][s] = posNums[s];
        }

        sizes[i] = sum;
    }

    recursion(grid, availableInputs, sizes);

    return 1;
}

//END SOLVER




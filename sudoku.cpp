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

void getRow(int grid[], int index, int nums[])
{
	int row = index / 9;
	int sum = 0;

	for (int x = 0; x < 9; x++)
	{
		int digit = grid[row * 9 + x];

		if (digit != 0)
		{
			nums[digit - 1]= digit;
			sum++;
		}
	}
}

void getColumn(int grid[], int index, int nums[])
{
	int row = index % 9;
	int sum = 0;

	for (int y = 0; y < 9; y++)
	{
		int digit = grid[y * 9 + row];

		if (digit != 0)
		{
			nums[digit - 1]= digit;
			sum++;
		}
	}
}

void getGroup(int grid[], int index, int nums[])
{
	int groupRow = index / 27;
	int groupColumn = (index % 9) / 3;

	int sum = 0;
	for (int x = 0; x < 3; x++)
	{
		for (int y = 0; y < 3; y++)
		{
			int digit = grid[groupRow * 27 + groupColumn * 3 + x * 9 + y];

			if (digit != 0)
			{
				nums[digit - 1]= digit;
				sum++;
			}
		}
	}
}

//GENERATION

int notAvailableNumbers(int grid[], int index, int nums[])
{
	fill_n(nums, 9, 0);
	int current = grid[index];

	getRow(grid, index, nums);
	getColumn(grid, index, nums);
	getGroup(grid, index, nums);

	int sum = 0;

	for (int i = 0; i < 9; i++)
	{
		if (nums[i] != 0)
		{
			sum++;
		}
	}	

	return sum;
}

void erase(int grid[], int left)
{
	int sum = 81;
	for (int i = 0; i < 100000; i++)
	{
		int random = rand() % 81;
        int posNums[9];    
    
		if (notAvailableNumbers(grid, random, posNums) >= 8 && grid[random] != 0)
		{
			grid[random] = 0;
			sum--;
		}

		if (left == sum)
		{
			return;
		}
	}
}

void switchLines(int grid[], int a, int b)
{
	for (int i = 0; i < 9; i++)
	{
		int temp = grid[b * 9 + i];
		grid[b * 9 + i] = grid[a * 9 + i];
		grid[a * 9 + i] = temp;
	}
}

void switchColumns(int grid[], int a, int b)
{
	for (int i = 0; i < 9; i++)
	{
		int temp = grid[i * 9 + b];
		grid[i * 9 + b] = grid[i * 9 + a];
		grid[i * 9 + a] = temp;
	}
}

void randomizeGrid(int grid[])
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

void generateSudoku(int grid[], int left)
{
	int start = 1;

	for (int i = 0; i < 9; i++)
	{
		for (int x = 0; x < 9; x++)
		{
			grid[i * 9 + x] = (start + x) % 9 + 1;
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
void printSudoku(int grid[], string name)
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

void readSudokuFile(int grid[], string name)
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

	for (int d = 0; d < 9; d++)
	{		
		if (nums[d] != 0)
		{
			nums[d] = 0;
		}
		else
		{
			nums[d] = d + 1;
		}
		cout << nums[d] << " ";
	}

	cout << index << " size: " << 9 - sum << endl;

	return 9 - sum;
}

void rmAvailableInputs(int availableInputs[][9], int index, int inputed, int sizes[])
{
	int row = index / 9;
	int col = index % 9;
	int groupRow = index / 27;
	int groupColumn = (index % 9) / 3;
	for (int i = 0; i < 9; i++)
	{
		int rowIndex = row * 9 + i;
		if (availableInputs[rowIndex][inputed] != 0)
		{
		cout << rowIndex << " ";
			availableInputs[rowIndex][inputed] = 0;
			sizes[rowIndex]--;
		}		
	}
			cout <<  " col ";

	for (int i = 0; i < 9; i++)
	{
		int colIndex = i * 9 + col;
		if (availableInputs[colIndex][inputed] != 0)
		{
		cout << colIndex << " ";
			availableInputs[colIndex][inputed] = 0;
			sizes[colIndex]--;
		}	
	}
			cout <<  " group ";

	for (int x = 0; x < 3; x++)
	{
		for (int y = 0; y < 3; y++)
		{
			int groupIndex = groupRow * 27 + groupColumn * 3 + x * 9 + y;	
			if (availableInputs[groupIndex][inputed] != 0)
			{	
			cout << groupIndex << " ";	
				availableInputs[groupIndex][inputed] = 0;
				sizes[groupIndex]--;
				cout << sizes[groupIndex];
			}
		}
	}
			cout <<  endl;		

}

void recursion(int grid[], int availableInputs[][9], int sizes[])
{
	int minIndex;
	int minVariants = 9;

	for(int i = 0; i < 81; i++)//goes through grid
	{
		if (sizes[i] == 1)//only one digit available with level 1 check
		{
			for (int d = 0; d < 9; d++)
			{				
				if (availableInputs[i][d] != 0)
				{
					cout << d + 1 << "\n";
					grid[i] = d + 1;
					availableInputs[i][d] = 0;
					sizes[i] = 0;

					rmAvailableInputs(availableInputs, i, d, sizes);
					recursion(grid, availableInputs, sizes);

					return;
				}
			}
		}

		if (sizes[i] > 1)
		{
			
		}
	}

	return;
}

int solve(int grid[])
{
    int availableInputs[81][9];
    int sizes[81];
    fill_n(sizes, 81, 0);

    for (int i = 0; i < 81; i++)
    {
    	fill_n(availableInputs[i], 9, 0);
    	if(grid[i] == 0)
    	{
	        int posNums[9];
	        int sum = availableNumbers(grid, i, availableInputs[i]);

	        sizes[i] = sum;    		
    	}
    }

    recursion(grid, availableInputs, sizes);

    return 1;
}

//END SOLVER




#include "sudoku.h"

int main()
{
	int* grid;
	grid = (int*)malloc(sizeof(int) * 81);
	int arr[9];
    
    int n = -1;
    
    while(n != 0)
    {
        printf("0 Close\n");
        printf("1 Generate sudoku\n");
        
        cin >> n;
        
        if (n == 1)
        {
            generateSudoku(grid, 40);
            printSudoku(grid);
        }
        
        printf("\n\n");
    }
	return 0;
}

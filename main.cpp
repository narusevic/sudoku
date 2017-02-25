#include "sudoku.h"

int main()
{
	int* grid;
	grid = (int*)malloc(sizeof(int) * 81);
	int arr[9];
    
    int n = -1;
    
    while(n != 0)
    {
        cout << "0 Close\n";
        cout << "1 Generate sudoku\n";
        cout << "2 Read sudoku from file\n";        
        cout << (n != -1 ? "3 Save sudoku to file\n" : "");        
        cout << (n != -1 ? "4 Print sudoku to file\n" : "");        
        cin >> n;
        
        if (n == 1)
        {
            generateSudoku(grid, 1);
        }
        if (n == 2)
        {
            string fileName;  
            cout << "Input file name:\n";  
            cin >> fileName;  
            
            readSudokuFile(grid, fileName);
        }
        if (n == 3)
        {
            if (n != -1)
            {            
                string fileName;
                cout << "Output file name:\n";  
                cin >> fileName;  
                if (fileName != "")
                {
                    printSudoku(grid, fileName);
                }  
                else
                {
                    cout << "Bad input:\n";                    
                }              
            }
        }
        if (n == 4)
        {
            if (n != -1)
            {                            
                printSudoku(grid);
            }
        }
        
        cout << "\n";
    }
	return 0;
}

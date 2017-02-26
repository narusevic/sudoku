#include "sudoku.h"

int main()
{
	//int* grid;
	//grid = (int*)malloc(sizeof(int) * 81);
    
    int grid[81];
	int arr[9];
    
    int n = -1;
    
    while(n != 0)
    {
        cout << "---------------------------------------------\n";
        cout << "0 Close\n";
        cout << "1 Generate sudoku\n";
        cout << "2 Read sudoku from file\n";        
        cout << (n != -1 ? "3 Print sudoku to file\n" : "");        
        cout << (n != -1 ? "4 Print sudoku to console\n" : "");        
        cout << (n != -1 ? "5 Solve sudoku\n" : "");   
        cout << "---------------------------------------------\nChoose: ";      
        cin >> n;
        
        if (n == 1)
        {
            generateSudoku(grid, 70);
            cout << "Generated sudoku.\n";
        }
        if (n == 2)
        {
            string fileName;  
            cout << "Input file name:\n";  
            cin >> fileName;  
            
            readSudokuFile(grid, fileName);
            cout << "Sudoku read.\n";
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
                    cout << "Sudoku printed to file.\n";                    
                }  
                else
                {
                    cout << "Bad input.\n";                    
                }              
            }
        }
        if (n == 4)
        {
            if (n != -1)
            {                 
                cout << "Sudoku:\n";           
                printSudoku(grid);
            }
        }
        if (n == 5)
        {
            if (n != -1)
            {                            
                int solved = solve(grid);
                
                if (solved == 1)
                {
                    cout << "Solved!\n";
                }
                else
                {
                    cout << "Impossible to solve!\n";                    
                }
            }
        }
        
        cout << "\n";
    }
	return 0;
}

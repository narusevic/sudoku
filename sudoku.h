// Sudoku, Lukas Narusevicius, 686 
#ifndef SUDOKU_H
#define SUDOKU_H

#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <fstream>
#include <string>

using namespace std;

void generateSudoku(int*, int);
void printSudoku(int*, string = "");
void readSudokuFile(int*, string);
int solve(int*);

#endif


//02-17 15-17h sudoku reading, planing, generator
//02-25 14-15h sudoku finishing generation
//02-25 19:30-21:50 IO
//02-26 05:30-


//find 

#include <stdio.h>

//Declaring the sudoku matrix globally.
int sudokuboard[9][9];

//Function to print sudoku board.
void printboard()
{
    int i,j;
    for(i=0;i<9;i++)
    {
        for(j=0;j<9;j++)
        {
            printf("%d   ",sudokuboard[i][j]);
        }
        printf("\n\n");
    }
}

//Function to check if all cells are assigned or not. If there is any unassigned cell then this function will change the values of row and column accordingly
int number_unassigned(int *row, int *column)
{
    int num_unassign = 0;
    int i,j;
    for(i=0;i<9;i++)
    {
        for(j=0;j<9;j++)
        {
            //cell is unassigned
            if(sudokuboard[i][j] == 0)
            {
                //changing the values of row and column
                *row = i;
                *column = j;
                //there is one or more unassigned cells
                num_unassign = 1;
                return num_unassign;
            }
        }
    }
    return num_unassign;
}

//Function to check if we can put a value in a paticular cell or not
int is_safe(int n, int r, int c)
{
    int i,j;
    //checking in row
    for(i=0;i<9;i++)
    {
        //there is a cell with same value
        if(sudokuboard[r][i] == n)
            return 0;
    }
    //checking column
    for(i=0;i<9;i++)
    {
        //there is a cell with the value equal to i
        if(sudokuboard[i][c] == n)
            return 0;
    }
    //checking sub matrix
    int row_start = (r/3)*3;
    int column_start = (c/3)*3;
    for(i=row_start;i<row_start+3;i++)
    {
        for(j=column_start;j<column_start+3;j++)
        {
            if(sudokuboard[i][j]==n)
                return 0;
        }
    }
    return 1;
}

//function to solve sudoku using backtracking
int sudoku_solver()
{
    int row;
    int column;
    //if all cells are assigned then the sudoku is already solved
    //pass by reference because number_unassigned will change the values of row and column
    if(number_unassigned(&row, &column) == 0)
        return 1;
    int n,i;
    //number between 1 to 9
    for(i=1;i<=9;i++)
    {
        //if we can assign i to the cell or not
        //the cell is matrix[row][column]
        if(is_safe(i, row, column))
        {
            sudokuboard[row][column] = i;
            //backtracking
            if(sudoku_solver())
                return 1;
            //if we can't proceed with this solution
            //reassign the cell
            sudokuboard[row][column]=0;
        }
    }
    return 0;
}

int main()
{
    printf("\n\nPress 0 for blank spaces in the sudoku\nNow Enter the sudoku:\n");
    for(int i=0;i<9;i++)
    {
        for(int j=0;j<9;j++)
        {
            scanf("%d",&sudokuboard[i][j]);
        }
    }
    if (sudoku_solver())
        printboard();
    else
        printf("No solution.\n");
    return 0;
}
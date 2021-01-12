#include <stdio.h>
#include <stdlib.h>

#define N 9

void print(int arr[N][N])
{
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
			printf("%d |",arr[i][j]);

		printf("\n");
	}
}

int isvalid(int mat[N][N], int row, int col, int num)
{
	
	// Check if we find the same number in the similar row then we return 0
	for (int x = 0; x <= 8; x++)
		if (mat[row][x] == num)
			return 0;

	// Check if we find the same number in the similar column then we return 0
	for (int x = 0; x <= 8; x++)
		if (mat[x][col] == num)
			return 0;

	// Check if we find the same number in the particular 3*3 matrix then we return 0
	int sRow = row - row % 3, 
				sCol = col - col % 3;

	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			if (mat[i + sRow][j + 
						sCol] == num)
				return 0;

	return 1;
}

int sol_Suduko(int mat[N][N], int row, int col)
{
	
	/*Check if we have reached the 8th row and 9th column (0 indexed matrix) then we are returning true to avoid further backtracking*/
	if (row == N - 1 && col == N)
		return 1;

	/*Check if column value becomes 9 , we move to next row and column start from 0*/
	if (col == N) 
	{
		row++;
		col = 0;
	}


	// if value >0 of the current position then we iterate for next column
	if (mat[row][col] > 0)
		return sol_Suduko(mat, row, col + 1);

	for (int num = 1; num <= N; num++) 
	{
		
		// Check if it is safe/valid  to place 
		// the num (1-9) in the
		// given row ,col then we move to next column
		if (isvalid(mat, row, col, num)==1) 
		{
			/* assigning the num in the 
			current (row,col)
			position of the grid
			and assuming our assined num 
			in the position
			is correct	 */
			mat[row][col] = num;
		
			// Checking for next possibility with next
			// column
			if (sol_Suduko(mat, row, col + 1) ==1)
				return 1;
		}
	
		// Removing the assigned num ,
		// since our assumption
		// was wrong , and we go for next 
		// assumption with
		// diff num value
		mat[row][col] = 0;
	}
	return 0;
}

int main()
{
	// 0 means unassigned cells
	int mat[N][N];
    for(int i=0 ; i<N ; i++)
    {
        for(int j=0 ; j<N ; j++)
        {
            scanf("%d",&mat[i][j]);
        }
    }

	if (sol_Suduko(mat, 0, 0)==1)
		print(mat);
	else
		printf("No solution exists \n Please Input a valid 9x9 sudoku!!!");

	return 0;
	

}

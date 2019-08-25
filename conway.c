/*
Helen Li
April 24, 2018
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//use 10x10 matrix
#define ROWS 10
#define COLUMNS 10

char nextGen (int row, int col, char currentGen[ROWS][COLUMNS])
{
	int liveNeighbors = 0;
	int i, j;

	for (i = row - 1; i <= row +1; i++)
	{
		for (j = col - 1; j <= col + 1; j++)
		{
			if (!(row == i && col == j))
			{
				if (i < 0 || i >= ROWS || j < 0 || j >= COLUMNS)
				{
					liveNeighbors = liveNeighbors;
				}
				else if (currentGen[i][j] == '0')
				{
					liveNeighbors = liveNeighbors;
				}
				else
				{
					liveNeighbors++;
				}
			}
		}
	}

	//a dead cell with exactly three alive neighbors becomes alive in the next gen
	if (currentGen[row][col] == '0')
	{
		if (liveNeighbors == 3)
		{
			return '1';
		}
		else
		{
			return '0';
		}
	}

	else
	{
		//an alive cell with fewer than two alive neighbors dies in the next gen
		//an alive cell with more than three neighbors also dies in the next gen
		if (liveNeighbors < 2 || liveNeighbors > 3)
		{
			return '0';
		}
		//an alive cell with exactly two or three alive neighbors stays alive in the next gen
		else
		{
			return '1';
		}
	}
}

int main (int argc, char *argv[])
{
	FILE *fp;
	int i, j;
	char s[21];
	char currentGen[ROWS][COLUMNS];

	fp = fopen(argv[2], "r");

	int rows = 0;
	while (fgets(s, 21, fp) != NULL)
	{
		int cols = 0;

		for (i = 0; i < 20; i++)
		{
			if (i < 20 && i % 2 == 0)
			{
				currentGen[rows][cols] = s[i];
				cols++;
			}
		}

		rows++;
	}

	fclose(fp);

	int numOfGen = atoi(argv[1]);
	int counter = 0;
	int row, col;
	char newGen[ROWS][COLUMNS];

	while (counter < numOfGen)
	{
		for (row = 0; row < ROWS; row++)
		{
			for (col = 0; col < COLUMNS; col++)
			{
				newGen[row][col] = nextGen(row, col, currentGen);
			}
		}

		for (row = 0; row < ROWS; row++)
		{
			for (col = 0; col < COLUMNS; col++)
			{
				currentGen[row][col] = newGen[row][col];
			}
		}

		counter++;
	}

	FILE *outFile;
	char outFileName[25];
	strcpy(outFileName, argv[2]);
	char ext[] = ".out";
	strcat(outFileName, ext);
	char space = ' ';

	outFile = fopen(outFileName, "w+");

	for (i = 0; i < ROWS; i++)
	{
		for (j = 0; j < COLUMNS; j++)
		{
			fprintf(outFile, "%c%c", currentGen[i][j], space);
		}

		fprintf(outFile, "\n");
	}

	fclose(outFile);

}

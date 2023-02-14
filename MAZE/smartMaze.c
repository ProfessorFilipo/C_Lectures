/***
**** S M A R T   M A Z E  ****
**** in this version, the fundations for creating a maze generating algorithm.
**** by the RetroModernProfessor (Professor Filipo) - filipomor.com
***/

#include <stdio.h>
#include <stdlib.h>
//#include <stdbool.h>

#define N      10	// mesh size (always squared)
#define TOP     1
#define BOTTOM  4
#define LEFT    8
#define RIGHT   2
// all walls open means a cell with ZERO value


void ResetMaze(int Maze[N][N], int celValue)
{
	int i, j;

	for (i = 0; i < N; i++)
	{
		for (j = 0; j < N; j++)
		{
			Maze[i][j] = celValue;
		}
	}

}

void ShowMazeValues(int Maze[N][N])
{
	// for testing purpouses only
	int i, j;

	for (i = 0; i < N; i++)
	{
		for (j = 0; j < N; j++)
		{
			printf(" %2d ", Maze[i][j]);
		}
		printf("\n");
	}

}

void ShowMaze(int Maze[N][N])
{

	int i, j;

	// for each line, we have to print 3 levels (top, botton and both sides of each cell)
	for (i = 0; i < N; i++)
	{

		// ##### TOP #####
		for (j = 0; j < N; j++)
		{
			// top (first line only)
			if (i == 0)
			{
				if ((Maze[i][j] & TOP) == TOP)
				{
					printf("+----");
				}
				else
				{
					printf("+    ");
				}
				if (j == (N - 1)) printf("+");
			}

			// top (second line on)
			if (i > 0)
			{
				if ((Maze[i - 1][j] & BOTTOM) == BOTTOM || (Maze[i][j] & TOP) == TOP)
				{
					printf("+----");
				}
				else
				{
					printf("+    ");
				}
				if (j == (N - 1)) printf("+");
			}
			
		}
		printf("\n");
		// FIM TOP

	    // #### both sides ####
		for (j = 0; j < N; j++)
		{

			char L = ' ';
			char R = ' ';

			// LEFT and RIGHT for the first column only
			if (j == 0)
			{
				if ((Maze[i][j] & LEFT) == LEFT)  L = '|';
				if ((Maze[i][j] & RIGHT) == RIGHT) R = '|';

				printf("%c    %c", L, R);
			}

			// LEFT and RIGHT for the last column only
			L = ' '; R = ' ';
			if (j == (N - 1))
			{
				if ((Maze[i][j] & LEFT) == LEFT)  L = '|';
				if ((Maze[i][j] & RIGHT) == RIGHT) R = '|';
				if ((Maze[i][j - 1] & RIGHT) == RIGHT) L = ' ';

				printf("%c   %c", L, R);
			}

			// LEFT and RIGHT for the intermediate columns only
			L = ' '; R = ' ';
			if (j > 0 && j < (N - 1))
			{
				// check the walls between two intermediate columns
				if ((Maze[i][j] & RIGHT) == RIGHT || (Maze[i][j + 1] & LEFT) == LEFT) L = '|';

				printf("    %c", L);

			}
			//printf("\n");
		}
		printf("\n");
			// fim both sides

		// #### BOTOM - last line only ####
		if (i == (N - 1))
		{
			for (j = 0; j < N; j++)
			{
				if ((Maze[i][j] & BOTTOM) == BOTTOM)
				{
					printf("+----");
				}
				else
				{
					printf("+    ");
				}
				if (j == (N - 1)) printf("+");
			}
			printf("\n");
		}

	}

}
		
	
void OpenWall(int Maze[N][N], int Line, int Column, int Wall)
{
	/*
	** set a wall as open, doing the same for its neighbour walls
	*/

	if ((Wall & TOP)   == TOP)    if (Line > 0) Maze[Line - 1][Column]         -= BOTTOM;
	if((Wall & BOTTOM) == BOTTOM) if (Line < (N - 1)) Maze[Line + 1][Column]   -= TOP;
	if((Wall & LEFT)   == LEFT)   if (Column > 0) Maze[Line][Column - 1]       -= RIGHT;
	if ((Wall & RIGHT) == RIGHT)  if (Column < (N - 1)) Maze[Line][Column + 1] -= LEFT;

	Maze[Line][Column] -= Wall;

}


int main()
{
	int Maze[N][N];

	ResetMaze(Maze, TOP + BOTTOM + LEFT + RIGHT);
	//OpenWall(Maze, 2, 2, RIGHT);
	//OpenWall(Maze, 2, 3, TOP);
	OpenWall(Maze, 4, 3, BOTTOM);
	OpenWall(Maze, 3, 3, BOTTOM);
	//OpenWall(Maze, 0, 5, TOP);
	OpenWall(Maze, 0, 0, LEFT);
	OpenWall(Maze, 5, 5, TOP+BOTTOM+LEFT+RIGHT);
	OpenWall(Maze, 1, 1, RIGHT+LEFT+TOP+BOTTOM);
	OpenWall(Maze, N-1, N-1, RIGHT + LEFT + TOP + BOTTOM);
	
	ShowMaze(Maze);
	ShowMazeValues(Maze);


	return (0);
}

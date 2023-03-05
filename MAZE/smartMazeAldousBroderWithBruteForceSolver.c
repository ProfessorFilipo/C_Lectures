/***
**** S M A R T   M A Z E  ****
**** in this version, the fundations for creating a maze generating algorithm.
**** Implementing the Aldous-Broder maze algorithm.
**** Maze solving using brute force.
**** by the RetroModernProfessor (Professor Filipo) - filipomor.com
***/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


#define N      15	// mesh size (always squared)

// NONE means no wall is closed, whilst ALL means all walls are closed
enum Walls { NONE = 0, TOP = 1, RIGHT = 2, BOTTOM = 4, LEFT = 8, ALL = 15};


void ResetMaze(int Maze[N][N], bool Visited[N][N], int celValue)
{
	int i, j;

	for (i = 0; i < N; i++)
	{
		for (j = 0; j < N; j++)
		{
			Maze[i][j] = celValue;
			Visited[i][j] = false;
		}
	}
} 

/*void ResetMaze(int Maze[N][N], int celValue)
{
	int i, j;

	for (i = 0; i < N; i++)
	{
		for (j = 0; j < N; j++)
		{
			Maze[i][j] = celValue;
		}
	}
} */


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

void ShowSolutionValues(bool Solution[N][N])
{
	// for testing purpouses only
	int i, j;

	for (i = 0; i < N; i++)
	{
		for (j = 0; j < N; j++)
		{
			printf(" %c ", Solution[i][j] ? '#' : '.');
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
				if ((Maze[i][j] & LEFT)  == LEFT)  L = '|';
				if ((Maze[i][j] & RIGHT) == RIGHT) R = '|';

				printf("%c    %c", L, R);
			}

			// LEFT and RIGHT for the last column only
			L = ' '; R = ' ';
			if (j == (N - 1))
			{
				if ((Maze[i][j] & LEFT)      == LEFT)  L = '|';
				if ((Maze[i][j] & RIGHT)     == RIGHT) R = '|';
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

void ShowMazeDetails(int Maze[N][N], bool Visited[N][N], int currCellLine, int currCellColumn, bool ClearScreen)
{
	if( ClearScreen) system("@cls||clear");
	
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
					printf("+---");
				}
				else
				{
					printf("+   ");
				}
				if (j == (N - 1)) printf("+");
			}

			// top (second line on)
			if (i > 0)
			{
				if ((Maze[i - 1][j] & BOTTOM) == BOTTOM || (Maze[i][j] & TOP) == TOP)
				{
					printf("+---");
				}
				else
				{
					//printf("+ = ");
					printf("+   ");
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
			char C = ' ';

			// cell content
			C = ' ';
			if (!Visited[i][j]) C = '*';
			if (i == currCellLine && j == currCellColumn) C = 'C';

			// LEFT and RIGHT for the first column only
			if (j == 0)
			{
				if ((Maze[i][j] & LEFT) == LEFT)  L = '|';
				if ((Maze[i][j] & RIGHT) == RIGHT) R = '|';

				printf("%c %c %c", L, C, R);
			}

			// LEFT and RIGHT for the last column only
			L = 0; R = ' ';
			if (j == (N - 1))
			{
				if ((Maze[i][j] & LEFT) == LEFT)  L = '|';
				if ((Maze[i][j] & RIGHT) == RIGHT) R = '|';
				if ((Maze[i][j - 1] & RIGHT) == RIGHT) L = 0;

				printf("%c %c %c", L, C, R);
			}

			// LEFT and RIGHT for the intermediate columns only
			L = ' '; R = ' '; /*C = '*'; */
			if (j > 0 && j < (N - 1))
			{
				// check the walls between two intermediate columns
				if ((Maze[i][j] & RIGHT) == RIGHT || (Maze[i][j + 1] & LEFT) == LEFT) L = '|';

				printf(" %c %c", C, L);

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
					printf("+---");
				}
				else
				{
					printf("+   ");
				}
				if (j == (N - 1)) printf("+");
			}
			printf("\n");
		}

	}

}

void ShowMazeSolution(int Maze[N][N], bool Solution[N][N], bool ClearScreen)
{
	if (ClearScreen) system("@cls||clear");

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
					printf("+---");
				}
				else
				{
					printf("+   ");
				}
				if (j == (N - 1)) printf("+");
			}

			// top (second line on)
			if (i > 0)
			{
				if ((Maze[i - 1][j] & BOTTOM) == BOTTOM || (Maze[i][j] & TOP) == TOP)
				{
					printf("+---");
				}
				else
				{
					//printf("+ = ");
					printf("+   ");
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
			char C = ' ';

			// cell content
			C = ' ';
			if (Solution[i][j]) C = '#';
			//if (i == currCellLine && j == currCellColumn) C = 'C';

			// LEFT and RIGHT for the first column only
			if (j == 0)
			{
				if ((Maze[i][j] & LEFT) == LEFT)  L = '|';
				if ((Maze[i][j] & RIGHT) == RIGHT) R = '|';

				printf("%c %c %c", L, C, R);
			}

			// LEFT and RIGHT for the last column only
			L = 0; R = ' ';
			if (j == (N - 1))
			{
				if ((Maze[i][j] & LEFT) == LEFT)  L = '|';
				if ((Maze[i][j] & RIGHT) == RIGHT) R = '|';
				if ((Maze[i][j - 1] & RIGHT) == RIGHT) L = 0;

				printf("%c %c %c", L, C, R);
			}

			// LEFT and RIGHT for the intermediate columns only
			L = ' '; R = ' '; /*C = '*'; */
			if (j > 0 && j < (N - 1))
			{
				// check the walls between two intermediate columns
				if ((Maze[i][j] & RIGHT) == RIGHT || (Maze[i][j + 1] & LEFT) == LEFT) L = '|';

				printf(" %c %c", C, L);

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
					printf("+---");
				}
				else
				{
					printf("+   ");
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

	if ((Wall & TOP) == TOP)
	{
		if (Line > 0)
		{
			Maze[Line - 1][Column] -= BOTTOM;
			if (Maze[Line - 1][Column] < 0) Maze[Line - 1][Column] = 0;
		}
	}
	if ((Wall & BOTTOM) == BOTTOM)
	{
		if (Line < (N - 1))
		{
			Maze[Line + 1][Column] -= TOP;
			if (Maze[Line + 1][Column] < 0) Maze[Line + 1][Column] = 0;
		}
	}
	if ((Wall & LEFT) == LEFT)
	{
		if (Column > 0)
		{
			Maze[Line][Column - 1] -= RIGHT;
			if (Maze[Line][Column - 1] < 0) Maze[Line][Column - 1] = 0;
		}
	}
	if ((Wall & RIGHT) == RIGHT)
	{
		if (Column < (N - 1))
		{
			Maze[Line][Column + 1] -= LEFT;
			if (Maze[Line][Column + 1] < 0)Maze[Line][Column + 1] = 0;
		}
	}

	Maze[Line][Column] -= Wall;
	if (Maze[Line][Column] < 0) Maze[Line][Column] = 0;

}

void PickupRandomCell(int Maze[N][N], int* Line, int* Column)
{
	// returns a random cell from the input maze
	*Line   = rand() % N;
	*Column = rand() % N;

}


void AldousBroderMaze(int Maze[N][N])
{
	enum Walls wall;
	bool Visited[N][N];
	int unvisitedCells; 
	int currentCellLine=-1, currentCellColumn=-1, neighCellLine=-1, neighCellColumn=-1;
	int guess=-1;
	int cont = 0;

	ResetMaze(Maze, Visited, ALL);
	//ResetMaze(Maze, ALL);
	//ResetMaze(Visited, 0);

	PickupRandomCell(Maze, &currentCellLine, &currentCellColumn);
	unvisitedCells = N * N;

	while (unvisitedCells > 0)
	{
		// pickup a random neighbour from the current cell
		bool found = false;
		while (!found)
		{
			// 0: UP
			// 1: DOWN
			// 2: LEFT
			// 3: RIGHT
			guess = rand() % 4;

			switch (guess)
			{
			case 0: // top
				if (currentCellLine > 0)
				{
					neighCellLine   = currentCellLine - 1;
					neighCellColumn = currentCellColumn;
					found = true;
					wall = TOP;
				}
				break;
			case 1: // DOWN
				if (currentCellLine < (N - 1))
				{
					neighCellLine   = currentCellLine + 1;
					neighCellColumn = currentCellColumn;
					found = true;
					wall = BOTTOM;
				}
				break;
			case 2: // LEFT
				if (currentCellColumn > 0)
				{
					neighCellLine = currentCellLine;
					neighCellColumn = currentCellColumn - 1;
					found = true;
					wall = LEFT;                                                               
				}
				break;
			case 3: // RIGHT
				if (currentCellColumn < (N - 1))
				{
					neighCellLine = currentCellLine;
					neighCellColumn = currentCellColumn + 1;
					found = true;
					wall = RIGHT;
				}
				break;
			default:
				break;
			}
			
		}

		if (!Visited[neighCellLine][neighCellColumn])
		{
			OpenWall(Maze, currentCellLine, currentCellColumn, wall);
			Visited[neighCellLine][neighCellColumn] = true;
			unvisitedCells--;
		}
		
		// debugging
		//system("cls");
		ShowMazeDetails(Maze, Visited,currentCellLine, currentCellColumn, true);
		//ShowMazeValues(Maze);
		printf("\ncont: %d\nunvisited cells: %d\nwall: %d\nneighCellLine:   %2d ::: \tcurrentCellLine:   %2d \nneighCellColumn: %2d ::: \tcurrentCellColumn: %2d\n\n", ++cont, unvisitedCells, wall, neighCellLine, currentCellLine, neighCellColumn, currentCellColumn);
		//Sleep(50);
		

		currentCellLine   = neighCellLine;
		currentCellColumn = neighCellColumn;


	}
}

bool IsValidPosition(int Line, int Column)
{
	//checks wether the position is within the maze
	if ((Line >= 0 && Line <= (N - 1)) && (Column >= 0 && Column <= (N - 1)))
	{
		return true;
	}

	return false;
}

bool MazeSolving(int Maze[N][N], bool Solution[N][N], int LineSource, int ColumnSource, int LineDest, int ColumnDest)
{

	// check if the destination was reached
	if (LineSource == LineDest && ColumnSource == ColumnDest)
	{
		Solution[LineSource][ColumnSource] = true;
		return true;
	}

	// is it a valid position?
	if (!IsValidPosition(LineSource, ColumnSource))
	{
		return false;
	}

	// is it already part of the path?
	if (Solution[LineSource][ColumnSource])
	{
		return false;
	}
	
	// marks current cell as part of the path
	Solution[LineSource][ColumnSource] = true;
	//ShowSolutionValues(Solution);
	ShowMazeSolution(Maze, Solution, true);
	printf("\n");
	Sleep(50);


	// tries north, if possible
	if (LineSource > 0)
	{
		// is the top wall open?
		if ((Maze[LineSource][ColumnSource] & TOP) != TOP)
		{
			if (MazeSolving(Maze, Solution, LineSource - 1, ColumnSource, LineDest, ColumnDest)) return true;
		}
	}

	// tries south, if possible
	if (LineSource < (N - 1))
	{
		// is the bottom wall open?
		if ((Maze[LineSource][ColumnSource] & BOTTOM) != BOTTOM)
		{
			if (MazeSolving(Maze, Solution, LineSource + 1, ColumnSource, LineDest, ColumnDest)) return true;
		}
	}

	// tries east, if possible
	if (ColumnSource < (N - 1))
	{
		// is the right wall open?
		if ((Maze[LineSource][ColumnSource] & RIGHT) != RIGHT)
		{
			if (MazeSolving(Maze, Solution, LineSource, ColumnSource + 1, LineDest, ColumnDest)) return true;
		}
	}

	// tries west, if possible
	if (ColumnSource > 0)
	{
		// is the left wall open?
		if ((Maze[LineSource][ColumnSource] & LEFT) != LEFT)
		{
			if (MazeSolving(Maze, Solution, LineSource, ColumnSource - 1, LineDest, ColumnDest)) return true;
		}
	}

	/*
	// move forward into x direction, if possible!
	if (MazeSolving(Maze, Solution, LineSource + 1, ColumnSource, LineDest, ColumnDest)) return true;

	// move forward into y direction
	if (MazeSolving(Maze, Solution, LineSource, ColumnSource + 1, LineDest, ColumnDest)) return true;
	*/

	// if none direction solved the problem, unmark current cell and return.
	Solution[LineSource][ColumnSource] = false;

	return false;
}

int main()
{
	int Maze[N][N];
	bool Solution[N][N];

	//ResetMaze(Maze, TOP + BOTTOM + LEFT + RIGHT);
	//OpenWall(Maze, 2, 2, RIGHT);
	//OpenWall(Maze, 2, 3, TOP);
	//OpenWall(Maze, 4, 3, BOTTOM);
	//OpenWall(Maze, 3, 3, BOTTOM);
	//OpenWall(Maze, 0, 5, TOP);
	//OpenWall(Maze, 0, 0, LEFT);
	//OpenWall(Maze, 5, 5, TOP+BOTTOM+LEFT+RIGHT);
	//OpenWall(Maze, 1, 1, RIGHT+LEFT+TOP+BOTTOM);
	//OpenWall(Maze, N-1, N-1, RIGHT + LEFT + TOP + BOTTOM);

	srand(time(NULL));

	//ResetMaze(Solution, 0);
	int i, j;
	for (i = 0; i < N; i++)
		for (j = 0; j < N; j++)
			Solution[i][j] = false;


	AldousBroderMaze(Maze);
	
	ShowMazeValues(Maze);
	ShowMaze(Maze);

	bool Solved = MazeSolving(Maze, Solution, 0, 0, N - 1, N - 1);
	//ShowMazeValues(Solution);
	if (Solved)
	{
		ShowMaze(Maze); printf("\n");
		ShowMazeSolution(Maze, Solution, false);
	}
	else
	{
		printf("\n::: There is no solution for tis maze! \n");
	}
	//ShowMaze(Solution);

	return (0);
}

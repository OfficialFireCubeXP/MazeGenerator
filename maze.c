// Using the DFS recursive method (Deph First Search)
// use scanf_s instead of scanf to avoid any error

#include <stdio.h>
#include <time.h>
#include <stdlib.h>

// Maze setup
#define WALL '#'
#define PATH ' ';

//Directions
#define UP 0
#define DOWN 1
#define LEFT 2
#define RIGHT 3

void ViewMaze(char **maze, int input)
{
	int i, j;
	printf("\n");

	for (i = 0; i < input; i++)
	{
		for (j = 0; j < input; j++)
		{
			printf("%c", maze[i][j]);
		}

		printf("\n");
	}
}

void GenerateMaze(char **maze, int input, int x, int y)
{
	int dir = rand() % 4; // random direction
	int trail = 1;

	maze[x][y] = PATH;
	system("cls");

	ViewMaze(maze, input);

	printf("\r\n");
	printf("Press Enter to continue...");

	getchar(); // Wait for user input (acceptance is the Enter key)

	while (trail <= 4)
	{
		if (trail <= 4 && dir == UP)
		{
			trail++;
			if (x - 2 >= 1 && maze[x - 2][y] == WALL)
			{
				maze[x - 1][y] = PATH;
				GenerateMaze(maze, input, x - 2, y);
			}
			dir++;
		}

		if (trail <= 4 && dir == DOWN)
		{
			trail++;
			if (x + 2 < input && maze[x + 2][y] == WALL)
			{
				maze[x + 1][y] = PATH;
				GenerateMaze(maze, input, x + 2, y);
			}
			dir++;
		}

		if (trail <= 4 && dir == LEFT)
		{
			trail++;
			if (y - 2 >= 1 && maze[x][y - 2] == WALL)
			{
				maze[x][y - 1] = PATH;
			}
			dir++;
		}

		if (trail <= 4 && dir == RIGHT)
		{
			trail++;
			if (y + 2 < input && maze[x][y + 2] == WALL)
			{
				maze[x][y + 1] = PATH;
				GenerateMaze(maze, input, x, y + 2);
			}
			dir++;
		}

		dir = UP;
	}
}

int main()
{
	char** maze;
	int n, input, i, j;

	srand((unsigned)time(NULL));

	do
	{
		system("cls");
		printf("Maze Generator\n");
		printf("Select Input Size 0-30\n");
		fflush(stdin);
		scanf_s("%d", &n);

	} while (n < 0 || n > 30);

	if (n == 0)
	{
		printf("#");
		getchar();

		return 0;
	}

	input = 2 * n + 1;

	maze = malloc(sizeof(char*) * input);
	if (!maze) return 1;

	for (i = 0; i < input; i++) {
		maze[i] = malloc(sizeof(char) * input);
		if (!maze[i]) {
			// free already allocated rows
			for (int k = 0; k < i; k++) free(maze[k]);
			free(maze);
			return 1;
		}
		for (j = 0; j < input; j++) maze[i][j] = WALL;
	}

	// choose start coordinates using separate variables
	int startX = 2 * (rand() % n) + 1;
	int startY = 2 * (rand() % n) + 1;

	GenerateMaze(maze, input, startX, startY);
	ViewMaze(maze, input);

	// free after generation
	for (i = 0; i < input; i++) free(maze[i]);
	free(maze);

	getchar();

	return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define Ns 10
#define HEIGHT 30
#define WIDTH  90

typedef struct star
{
	int  posX;
	int  posY;
	bool Visivel;
	
};

void RandomStars(struct star *Stars, int numberOfStars, int W, int H)
{
	int k;
	
	for(k=0; k < numberOfStars; k++)
	{
		Stars[k].posY    = rand() % H;
		Stars[k].posX    = rand() % W;
		Stars[k].Visivel = true;
	}
}

void ClearScreen(char *Screen)
{
	int k;
	memset(Screen, 0, sizeof(char)*HEIGHT*WIDTH);
	memset(Screen, 205, WIDTH); // top border
	memset(Screen + ((HEIGHT-1)*WIDTH), 205, WIDTH); // bottom border
	for(k=0; k<HEIGHT; k++) // side borders
	{
		Screen[k * WIDTH] = 186;
		Screen[k * WIDTH + (WIDTH-1)] = 186;
	}
	Screen[0] = 201; // top let corner
	Screen[WIDTH-1] = 187; // top right corner
	Screen[(HEIGHT-1)*WIDTH] = 200; // bottom left corner
	Screen[HEIGHT*WIDTH-1] = 188; //bottom right corner
	
}

void PrintScreen(char *Screen)
{
	int i, j;
	for(i=0; i<HEIGHT; i++)
	{
		for(j=0; j<WIDTH; j++)
		{
			printf("%c", Screen[i * WIDTH + j]);
		}
		printf("\n");
	}	
}

void StampStars(char *Screen, struct star *Stars)
{
	int k;
	for(k=0; k<Ns; k++)
	{
		if( Stars[k].Visivel )
		{
			Screen[Stars[k].posY * WIDTH + Stars[k].posX] = 178;
		}
	}
}

int main(int argc, char *argv[]) 
{
	int i,j,k;
	
	char *Screen = (char*)malloc(sizeof(char) * WIDTH * HEIGHT);
	if( Screen == NULL )
	{
		printf("\nErro alocando memoria!\n");
		exit( EXIT_FAILURE );
	}

	struct star *Stars = (struct star*)malloc(sizeof(struct star) * Ns);
	if(Stars == NULL)
	{
		printf("\nErro alocando memoria!\n");
		exit( EXIT_FAILURE );
	}
	
	RandomStars(Stars, Ns, WIDTH, HEIGHT );
	ClearScreen(Screen);
	StampStars(Screen, Stars);
	
	
	PrintScreen(Screen);
	
	/*for(i=0; i<Ns; i++)
	{
		printf("Star[%d]: \tX:%2d \tY:%2d \tVisible:%c\n", i, Stars[i].posX, Stars[i].posY, Stars[i].Visivel==0 ? 'N' : 'S');
	}*/

    system("pause");
	return 0;
}

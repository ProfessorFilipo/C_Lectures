/*
** Liga dois pontos dentro de uma matriz
** by Professor Filipo
** 12/mar/2020
*/

#include <stdio.h>
#include <stdbool.h>
#include <math.h>

#define N 20

void MostraM(char M[N][N])
{
	int i, j;

	for (i = 0; i < N; i++)
	{
		for (j = 0; j < N; j++)
		{
			printf(" %c ", M[i][j]);
		}
		printf("\n");
	}

}

int main()
{

	char M[N][N];
	int i, j;
	int Ax, Ay, Bx, By;
	float distancia = 0.0;
	float X = 0.0, Y = 0.0;
	float incX=0.0, incY=0.0;

	// "limpa" a matriz;
	for (i = 0; i < N; i++)
	{
		for (j = 0; j < N; j++)
		{
			M[i][j] = '.';
		}
	}

	//Pontos de Origem e Destino
	Ay = 0; By = 19;
	Ax = 5; Bx = 18;
	
	// calcula distancia entre os pontos e o incremento para cada iteração.
	distancia = abs(Bx - Ax) + abs(By - Ay);
	incX = abs(Bx - Ax) / distancia; if (Bx < Ax) incX *= -1;
	incY = abs(By - Ay) / distancia; if (By < Ay) incY *= -1;

	//printf("\n::: Distancia: %2f \n", distancia);
	//printf(":::incX: %f incY: %f \n", incX, incY);

	// imprime o caminho entre A e B na matriz.
	X = Ax; Y = Ay; 
	for (i = 0; i < distancia; i++)
	{
		X += incX;
		Y += incY;
		M[(int)Y][(int)X] = '*';
		//printf("X: %f Y: %f \n", X, Y);
	}

	M[Ay][Ax] = 'A';
	M[By][Bx] = 'B';

	MostraM(M);

	return(0);
}

#include <stdio.h>

#define N 5
#define M 5

int main()
{
	int i = 0;
	int linha, coluna;
	int Matriz[N][M];

	for (linha = 0; linha < N; linha++)
	{
		for (coluna = 0; coluna < M; coluna++)
		{
			Matriz[linha][coluna] = i++;
		}
	}

	for (linha = 0; linha < N; linha++)
	{
		for (coluna = 0; coluna < M; coluna++)
		{
			printf(" %2d ", Matriz[linha][coluna]);
		}
		printf("\n");
	}

}

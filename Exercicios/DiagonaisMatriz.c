#include <stdio.h>

#define N 5
#define M 5

void MostraMatriz(int Matriz[N][M])
{
	int linha, coluna;
	for (linha = 0; linha < N; linha++)
	{
		for (coluna = 0; coluna < M; coluna++)
		{
			printf(" %2d ", Matriz[linha][coluna]);
		}
		printf("\n");
	}

}

int main()
{
	int i = 0;
	int linha, coluna;
	int Matriz[N][M];

	for (linha = 0; linha < N; linha++)
	{
		for (coluna = 0; coluna < M; coluna++)
		{
			Matriz[linha][coluna] = 0;
		}
	}

	MostraMatriz(Matriz);

	for (i = 0; i < N; i++)
	{
		Matriz[i][i] = 1;
		Matriz[i][N - i - 1] = 1;
	}


	printf("\n");
	MostraMatriz(Matriz);
}

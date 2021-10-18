/*
** Multiplicação de Matrizes Quadradas (N x N)
**  com contagem do tempo de processamento
** Prof. Filipo Mór - filipomor.com
** 18 de outubro de 2021
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define N 1000


void MostraMatriz(int Altura, int Largura, int* M, char* Titulo)
{
    int L, C; //Linha e Coluna

    printf(" %s \n", Titulo);
    for(L = 0; L < Altura; L++)
    {
        for(C = 0; C < Largura; C++)
        {
            printf(" %2d ", M[L * Altura + C]);
        }
        printf("\n");
    }
}

void PreencheMatriz(int Altura, int Largura, int* M, int Valor)
{
    int L, C; //Linha e Coluna

    for(L = 0; L < Altura; L++)
    {
        for(C = 0; C < Largura; C++)
        {
            M[L * Altura + C] = Valor;
        }
        printf("\n");
    }
    printf("\n\n");

}

int main()
{

    int* Ma = (int*)malloc(sizeof(int) * N * N);
    if ( Ma == NULL )
    {
        printf("\nErro alocando memoria! \n");
        exit( EXIT_FAILURE );
    }

    int* Mb = (int)malloc(sizeof(int) * N * N);
    if ( Mb == NULL )
    {
        printf("\nErro alocando memoria! \n");
        exit( EXIT_FAILURE );
    }

    int* Mc = (int)malloc(sizeof(int) * N * N);
    if ( Mc == NULL )
    {
        printf("\nErro alocando memoria! \n");
        exit( EXIT_FAILURE );
    }

    PreencheMatriz(N, N, Ma, 1);
    PreencheMatriz(N, N, Mb, 3);
    PreencheMatriz(N, N, Mc, 0);

    //MostraMatriz(N, N, Ma, " Matriz A ");
    //MostraMatriz(N, N, Mb, " Matriz B ");
    //MostraMatriz(N, N, Mc, " Matriz C ");

    int L, C, K;
	clock_t timeCount;
    
	timeCount = clock();
	//C = A . B
    for(L=0; L<N; L++)
    {
        for(C=0; C<N; C++)
        {
            for(K=0; K<N; K++)
            {
                Mc[L * N + C] += Ma[L * N + K] * Mb[K * N + C];
            }
        }
    }
    timeCount = clock() - timeCount;
    double execTime = ((double)timeCount)/CLOCKS_PER_SEC;

    //MostraMatriz(N, N, Mc, " Matriz C ");
    
    printf("\nCalculation time: %f seconds\n", execTime);
    return 0;
}

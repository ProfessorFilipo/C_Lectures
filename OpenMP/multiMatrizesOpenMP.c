/*****************************************************************************************
 ***     M U L T I P L I C A C A O   D E    M A T R I Z E S    C O M     O P E N M P   ***
 *****************************************************************************************
 *** Prof. Filipo Mor - github.com/ProfessorFilipo                                     ***
 *****************************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int main()
{
    int N = 512; // tamanho da matriz (N x N) — aumente para testar desempenho
    long long **A, **B, **C;
    int i, j, k;

    // Alocação dinâmica das matrizes
    A = (long long**) malloc(N * sizeof(long long*));
    B = (long long**) malloc(N * sizeof(long long*));
    C = (long long**) malloc(N * sizeof(long long*));

    for (i = 0; i < N; i++)
    {
        A[i] = (long long*) malloc(N * sizeof(long long));
        B[i] = (long long*) malloc(N * sizeof(long long));
        C[i] = (long long*) malloc(N * sizeof(long long));
    }

    // Inicializa as matrizes com valores simples
    for (i = 0; i < N; i++)
    {
        for (j = 0; j < N; j++)
        {
            A[i][j] = i + j;
            B[i][j] = i - j;
            C[i][j] = 0;
        }
    }

    printf("Iniciando multiplicacao de matrizes %dx%d...\n\n", N, N);

    double start = omp_get_wtime();

    // Multiplicação paralela
    #pragma omp parallel private(i, j, k)
    {
        int thread_id = omp_get_thread_num();
        int n_threads = omp_get_num_threads();

        // Apenas uma thread (a 0) imprime o total
        #pragma omp single
        {
            printf("Numero total de threads criadas: %d\n\n", n_threads);
        }

        // Determina o intervalo de linhas que esta thread irá processar
        int chunk = N / n_threads;           // linhas por thread
        int resto = N % n_threads;           // se N não for múltiplo de n_threads
        int start_i, end_i;

        // Distribuição equilibrada considerando o resto
        if (thread_id < resto)
        {
            start_i = thread_id * (chunk + 1);
            end_i = start_i + (chunk + 1) - 1;
        }
        else
        {
            start_i = thread_id * chunk + resto;
            end_i = start_i + chunk - 1;
        }

        printf("Thread %2d -> processando linhas %3d ate %3d (%d linhas)\n",
               thread_id, start_i, end_i, end_i - start_i + 1);

        // Loop principal — cada thread calcula apenas seu intervalo
        for (i = start_i; i <= end_i; i++)
        {
            for (j = 0; j < N; j++)
            {
                long long soma = 0;
                for (k = 0; k < N; k++)
                {
                    soma += A[i][k] * B[k][j];
                }
                C[i][j] = soma;
            }
        }
    }

    double end = omp_get_wtime();
    printf("\nTempo total: %.6f segundos\n", end - start);

    // Exibe parte da matriz resultado (para N pequeno)
    if (N <= 8)
    {
        printf("\nMatriz resultado (C):\n");
        for (i = 0; i < N; i++)
        {
            for (j = 0; j < N; j++)
            {
                printf("%6lld ", C[i][j]);
            }
            printf("\n");
        }
    }

    // Libera memória
    for (i = 0; i < N; i++)
    {
        free(A[i]);
        free(B[i]);
        free(C[i]);
    }
    free(A);
    free(B);
    free(C);

    return 0;
}

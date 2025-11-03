/*****************************************************
 ***     Multiplicação de vetores com OpenMP      ***
 *****************************************************
 *** Prof. Filipo Mor - github.com/ProfessorFilipo ***
 *****************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int main() {
    int n = 100000000; // tamanho do vetor
    int *A, *B, *C;
    double start_time, end_time;
    int num_threads = 0;

    A = (int*) malloc(n * sizeof(int));
    B = (int*) malloc(n * sizeof(int));
    C = (int*) malloc(n * sizeof(int));

    if (A == NULL || B == NULL || C == NULL)
    {
        printf("Erro ao alocar memória!\n");
        return 1;
    }

    for (int i = 0; i < n; i++)
    {
        A[i] = i;
        B[i] = 2 * i;
    }

    start_time = omp_get_wtime();

#pragma omp parallel
    {
        int tid = omp_get_thread_num();
        int nthreads = omp_get_num_threads();

#pragma omp single
        {
            num_threads = nthreads;
            printf("Número de threads criadas: %d\n", num_threads);
        }

        // Cada thread calcula seu intervalo do laço for
#pragma omp for
        for (int i = 0; i < n; i++)
        {
            C[i] = A[i] * B[i];
        }

        // Determina quais índices esta thread processou
        int chunk = n / nthreads;
        int start_idx = tid * chunk;
        int end_idx = (tid == nthreads - 1) ? (n - 1) : (start_idx + chunk - 1);

#pragma omp critical
        {
            printf("Thread %d processou índices [%d .. %d]\n", tid, start_idx, end_idx);
        }
    }

    end_time = omp_get_wtime();

    printf("Multiplicação concluída em %.6f segundos.\n", end_time - start_time);

    for (int i = 0; i < 10; i++)
    {
        printf("C[%d] = %d\n", i, C[i]);
    }

    free(A);
    free(B);
    free(C);

    return 0;
}

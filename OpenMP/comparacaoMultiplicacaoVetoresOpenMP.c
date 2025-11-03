/*****************************************************
 ***     Multiplicação de vetores com OpenMP       ***
 *****************************************************
 *** comparando diferentes configuracoes           ***
 *****************************************************
 *** Prof. Filipo Mor - github.com/ProfessorFilipo ***
 *****************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

void multiply_vectors_sequential(int *A, int *B, int *C, int n)
{
    for (int i = 0; i < n; i++)
    {
        C[i] = A[i] * B[i];
    }
}

void multiply_vectors_parallel(int *A, int *B, int *C, int n, int num_threads, char *schedule_type)
{
    omp_set_num_threads(num_threads);

    // Escolhe o tipo de agendamento
    if (strcmp(schedule_type, "static") == 0)
    {
        #pragma omp parallel for schedule(static)
        for (int i = 0; i < n; i++)
            C[i] = A[i] * B[i];
    }
    else if (strcmp(schedule_type, "dynamic") == 0)
    {
        #pragma omp parallel for schedule(dynamic, 1000)
        for (int i = 0; i < n; i++)
            C[i] = A[i] * B[i];
    }
    else if (strcmp(schedule_type, "guided") == 0)
    {
        #pragma omp parallel for schedule(guided, 1000)
        for (int i = 0; i < n; i++)
            C[i] = A[i] * B[i];
    }
    else
    {
        // fallback para static
        #pragma omp parallel for schedule(static)
        for (int i = 0; i < n; i++)
            C[i] = A[i] * B[i];
    }
}

int main()
{
    int n = 100000000; // 100 milhões de elementos (ajuste conforme a capacidade do seu hardware)
    int *A, *B, *C;
    double t_seq, t_par, speedup;

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
        A[i] = i % 1000;
        B[i] = (i % 1000) + 1;
    }

    // Execução sequencial
    double start = omp_get_wtime();
    multiply_vectors_sequential(A, B, C, n);
    double end = omp_get_wtime();
    t_seq = end - start;

    printf("Tempo sequencial: %.6f s\n\n", t_seq);
    printf("Threads | Schedule | Tempo (s) | Speedup\n");
    printf("-------------------------------------------\n");

    // Testa diferentes números de threads
    int threads_list[] = {2, 4, 8, 12, 16};
    const char *schedules[] = {"static", "dynamic", "guided"};
    int nthreads = sizeof(threads_list) / sizeof(threads_list[0]);
    int nschedules = sizeof(schedules) / sizeof(schedules[0]);

    FILE *csv = fopen("resultados_openmp.csv", "w");
    fprintf(csv, "threads,schedule,tempo,speedup\n");

    for (int s = 0; s < nschedules; s++)
    {
        for (int t = 0; t < nthreads; t++)
        {
            int nt = threads_list[t];
            const char *sched = schedules[s];

            start = omp_get_wtime();
            multiply_vectors_parallel(A, B, C, n, nt, (char*)sched);
            end = omp_get_wtime();
            t_par = end - start;
            speedup = t_seq / t_par;

            printf("%7d | %8s | %9.4f | %.2fx\n", nt, sched, t_par, speedup);
            fprintf(csv, "%d,%s,%.6f,%.2f\n", nt, sched, t_par, speedup);
        }
    }

    fclose(csv);

    free(A);
    free(B);
    free(C);

    printf("\nResultados também salvos em 'resultados_openmp.csv'\n");

    return 0;
}

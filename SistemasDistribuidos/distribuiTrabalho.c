#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

#define N_FILHOS 3

int main() {
    int pipe_ida[2];     // Pai -> Filhos (Tarefas)
    int pipe_volta[2];   // Filhos -> Pai (Resultados)
    
    pipe(pipe_ida);
    pipe(pipe_volta);

    for (int i = 0; i < N_FILHOS; i++) {
        if (fork() == 0) {
            // --- ÁREA DO FILHO ---
            int tarefa_recebida;
            close(pipe_ida[1]);   // Filho não escreve na ida
            close(pipe_volta[0]); // Filho não lê da volta

            // Espera uma tarefa do pai
            read(pipe_ida[0], &tarefa_recebida, sizeof(int));
            
            int resultado = tarefa_recebida * 2;
            printf("FILHO %d: Recebi %d, calculando dobro: %d\n", i+1, tarefa_recebida, resultado);
            
            // Envia o resultado de volta
            write(pipe_volta[1], &resultado, sizeof(int));
            
            exit(0); // Filho termina aqui
        }
    }

    // --- ÁREA DO PAI (GERENTE) ---
    close(pipe_ida[0]);   // Pai não lê da ida
    close(pipe_volta[1]); // Pai não escreve na volta

    int tarefas[N_FILHOS] = {10, 20, 30};
    int total_consolidado = 0;

    // 1. Distribui o trabalho
    for (int i = 0; i < N_FILHOS; i++) {
        printf("PAI: Enviando valor %d para um filho...\n", tarefas[i]);
        write(pipe_ida[1], &tarefas[i], sizeof(int));
    }

    // 2. Coleta e consolida os resultados
    for (int i = 0; i < N_FILHOS; i++) {
        int res;
        read(pipe_volta[0], &res, sizeof(int));
        total_consolidado += res;
    }

    printf("\nPAI: Trabalho concluído! Soma total dos dobros: %d\n", total_consolidado);

    // Limpeza: espera todos os filhos terminarem
    for (int i = 0; i < N_FILHOS; i++) wait(NULL);

    return 0;
}


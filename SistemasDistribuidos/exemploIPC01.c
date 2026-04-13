#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>

int main() {
    int fd[2];          // "File Descriptors" para o nosso cano (pipe)
    pid_t pid;          // Variável para armazenar o ID do processo
    char mensagem[] = "Olá, meu filho! O código secreto é 42.";
    char buffer[100];   // Espaço para o filho guardar a mensagem recebida

    // 1. Criamos o cano (pipe) antes do processo se dividir
    if (pipe(fd) == -1) {
        perror("Erro ao criar o cano");
        return 1;
    }

    // 2. Criamos o processo filho (fork)
    pid = fork();

    if (pid < 0) {
        perror("Erro no fork");
        return 1;
    }

    if (pid > 0) {
        /* --- PROCESSO PAI (O MESTRE) --- */
        close(fd[0]); // Fecha a ponta de leitura (ele só quer falar)
        
        printf("PAI: Enviando segredo pelo cano...\n");
        write(fd[1], mensagem, strlen(mensagem) + 1);
        
        close(fd[1]); // Terminou de falar, fecha o cano
    } 
    else {
        /* --- PROCESSO FILHO (O APRENDIZ) --- */
        close(fd[1]); // Fecha a ponta de escrita (ele só quer ouvir)
        
        printf("FILHO: Esperando mensagem...\n");
        read(fd[0], buffer, sizeof(buffer));
        
        printf("FILHO: Eu ouvi o seguinte segredo: '%s'\n", buffer);
        
        close(fd[0]); // Terminou de ouvir, fecha o cano
        exit(0);
    }

    return 0;
}

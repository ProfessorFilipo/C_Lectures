#include <stdio.h>
#include <math.h>

// bizu pra funcao sleep compilar em ruindows e em linux
#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif

int main()
{

    // acerte aqui o contador decrescente em 3h40min15s
    int horas=3, minutos=40, segundos=15;

    // cria um contador contendo a quantidade total de segundos desejada para o contador decrescente.
    int cont = (horas*60*60) + (minutos*60) + segundos;

    while(cont>0)
    {
        int horasDisplay = floor(cont / 3600);
        int minutosDisplay = floor( (cont - (horasDisplay*3600)) / 60);
        int segundosDisplay = floor( cont % 60);

        printf(" %02d:%02d:%02d ::: %06d ==> contador 'real' para referencia! \n", horasDisplay, minutosDisplay, segundosDisplay, cont);

        cont--;

        Sleep(1000); // dorme um segundo

    }

    printf("\n feito!!!\n");
    return(0);
}

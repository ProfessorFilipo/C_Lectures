#include <stdio.h>

// bizu pra funcao sleep compilar em ruindows e em linux
#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif

int main()
{

    //int cont=0;
    int horas=0, minutos=0, segundos=0;
    
     // uma hora possui 3600 segundos (60s x 60min == 1h)
     while (1)
     {
        printf(" %02d:%02d:%02d \n", horas, minutos, segundos); // vou deixar a formatacao na tela por tua conta kkk

        segundos++; 
        if(segundos >= 60)
        {
            segundos=0;
            minutos++;
        }

        if(minutos >= 60)
        {
            minutos=0;
            horas++;
        }

        if(horas >=24)
        {
            horas=0;
        }

        Sleep(1000); // dorme 1 segundo

     }
     

}

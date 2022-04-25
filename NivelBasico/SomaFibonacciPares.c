#include <stdio.h>
#define limite 5

int main()
{
	int ant, prox, i, j, cont=0, soma=0;
	
	ant=0; prox=1;
	while( cont < limite )
	{
		int aux = ant + prox;
		ant = prox;
		prox = aux;
		
		printf(" %6d ",prox);
		
		if( prox % 2 == 0)
		{
			cont++;
			soma += prox;	
			printf(" * %2d", cont);
		}
		printf("\n");
	}
	printf("Soma dos primeiros %d numeros primos pares: %d\n", limite, soma);
}

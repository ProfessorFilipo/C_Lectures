/*
**  Preenche vetor com valores não repetidos
**  e ordena o vetor utilizando bubblesort
** ===========================================
** Prof. Filipo Mór - filipomor.com
** ===========================================
** 23 de Setembro de 2019
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define N 10


int main(int argc, char *argv[]) {
	
	int V[N];
	int i, posicao;
	bool achei = false;
	
	srand(time(NULL));
	
	// preenche o vetor com valores não repetidos
	posicao=0;
	while(posicao < N)
	{
		achei = false; 
		int nro = rand() % N;
		i = 0;
		while(i<posicao)
		{
			if(nro == V[i]) achei = true;
			i++;
		}
		
		if(!achei)
		{
			V[posicao] = nro;
			posicao++;
		}
		else printf("repetido: %d\n", nro);
	}
	
	printf("\nVetor ANTES da ordenação:\n");
	for(i=0; i<N; i++)
	{
		printf("V[%2d]: %2d\n", i, V[i]);
	}
	
	// ordena o vetor com bubblesort
	do
	{
		achei = false;
		for(i=0; i<(N-1); i++)
		{
			if(V[i] > V[i+1])
			{
				int aux = V[i];
				V[i]    = V[i+1];
				V[i+1]  = aux;
				achei   = true;
			}
		}
	}while(achei);

	printf("\nVetor DEPOIS da ordenação:\n");
	for(i=0; i<N; i++)
	{
		printf("V[%2d]: %2d\n", i, V[i]);
	}

	
	return 0;
}

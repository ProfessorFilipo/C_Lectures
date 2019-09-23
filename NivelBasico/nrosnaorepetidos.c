/*
**  Preenche vetor com valoresw não repetidos
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
	
	posicao=0;
	while(posicao < N)
	{
		achei = false;
		int nro = rand() % N;
		for(i=0; i<posicao; i++)
		//while(i<posicao)
		{
			if(nro == V[i]) achei = true;
			//i++;
		}
		
		if(!achei)
		{
			V[posicao] = nro;
			posicao++;
		}
		//else printf("repetido: %d\n", nro);
	}
	
	for(i=0; i<N; i++)
	{
		printf("V[%2d]: %2d\n", i, V[i]);
	}
	
	return 0;
}

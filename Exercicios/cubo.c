
/*
**************************************************************************
***********           E x e r c i c i o  d o  C U B O          ***********
**************************************************************************
** A ideia eh calcular a soma dos valores das celulas correspondentes   **
** as diagonais do cubo, considerando-se todos os cortes possiveis      **
** em angulos de 90 graus. Por exemplo, em um cubo 3x3x3, teremos       **
** três cortes na visão frontal, cada corte contendo uma diagonal       **
** principal e uma diagonal secundária. A mesma coisa ocorre nas        **
** visoes superior e lateral. Deve-se somar ao resultado, ainda,        **
** os valores das diagonais tridimensional do cubo, em um total         **
** de 4 diagonais possiveis nesta visão 3D.                             **
** o cubo deve ser sempre simetrico (altura = largura = profundidade)   **
**************************************************************************
** pode-se informar o valor da aresta por parametro de linha de comando.
** o valor padrao da aresta eh 3.
**************************************************************************
** Prof. Filipo Mor - www.filipomor.com - 22/oct/2019
**************************************************************************
*/


#include <stdio.h>
#include <stdlib.h>

void LimpaTela()
{
	// tentativa de limpar a tela tanto em Win
	// quanto em Linux. No console Win funcionou.
	// Falta testar no Linux.
	system("@cls||clear");
}

int idx(int L, int C, int P, int N)
{
	return (L * N + C + (N*N*P));
}

int ContaDigitos(int numero)
{
	// Quantos digitos possui o nro informado?
	int count=0;
	
	while( numero != 0 )
	{
		numero /= 10;
		count++;
	}
	
	return ( count );
}

void TabAutomatica(int P, int N)
{
	int w, k, tab = ContaDigitos( N * N * N) * 2;
	
	// espaçamento incremental no inicio da linha
	for(w=0; w<P; w++)	{ for(k=0; k<tab; k++) printf(" ");	}	
}

void TabNroLinha(int digitos)
{
	int k;
	for(k=0; k<(digitos+2); k++) printf(" "); // alinhamento nro da linha
}
void TelaInicial(int N, int *cubo)
{
	int digitos = ContaDigitos( N * N * N );
	int L, C, P, k, t, w, tab = digitos*2;
	
	LimpaTela();
	printf("##########################################################\n");	
	printf("######         E x e r c i c i o  C U B O           ######\n");	
	printf("##########################################################\n");	
	printf("##########################################################\n\n");
	printf("::: Assumindo N = %d\n\n", N);

	for(P=0; P<N; P++)
	{

		TabAutomatica(P, N);
		TabNroLinha(digitos);
		printf("::: P = %d\n", P);
		for(L=0; L<N; L++)
		{

			TabAutomatica(P, N);
		    TabNroLinha(digitos);
			for(C=0; C<N; C++) // linha superior
			{
				printf("+"); for(k=0;k<=(digitos+2); k++) printf("-");
			}
			printf("+\n");
			
			TabAutomatica(P, N);
			printf("%*d|", digitos+2, L);
			
			// imprime valores do cubo
			for(C=0; C<N; C++)
			{
				printf("%*d |", digitos+2, cubo[idx(L, C, P, N)]);
			}
			printf("\n");
			
		}

		TabAutomatica(P, N);
		TabNroLinha(digitos);
		for(C=0; C<N; C++)
		{
			printf("+"); for(k=0;k<=(digitos+2); k++) printf("-");
		}
		printf("+\n");

		TabAutomatica(P, N);
		TabNroLinha(digitos);		
		for(C=0; C<N; C++)
		{
			printf("%*d  ", digitos+2, C);
		}
		printf("\n\n");				
	}

	
}


int main(int argc, char *argv[]) 
{

	int N = 3;
	int k=0, cont = 0;
	int L=0, C=0, P=0; // Linha Coluna Profundidade

	// informou um valor para N ?
	if(argc == 2)
	{
		N = atoi(argv[1]);
	}

	int *cubo = (int*)malloc( N * N * N * sizeof(int));
	if ( cubo == NULL)
	{
		printf(":::: Erro alocando memoria para o cubo! \n");
		exit( EXIT_FAILURE );
	}
	
	// preenche o cubo
	for(P=0; P<N; P++)
		for(L=0; L<N; L++)
			for(C=0; C<N; C++)
				cubo[idx(L, C, P, N)] = ++cont;


	TelaInicial( N, cubo );
	
	int diagPrincipal=0, diagSecundaria=0;
	int D1=0, D2=0, D3=0, D4=0;
	// calcula soma das diagonais
	for(P=0; P<N; P++)
	{
		for(k=0; k<N; k++)
		{
			// Visao FRONTAL
			diagPrincipal  += cubo[idx(k, k, P, N)];
			diagSecundaria += cubo[idx(k, N-k-1, P, N)];
			
			//Visao SUPERIOR
			diagPrincipal  += cubo[idx(P,     k, N-k-1, N)];
			diagSecundaria += cubo[idx(P, N-k-1, N-k-1, N)];

			//Visao LATERAL
			diagPrincipal  += cubo[idx(k, P, N-k-1, N)]; //printf("L: %d C: %d P: %d Valor: %d\n",k, P, N-k-1, cubo[idx(k, P, N-k-1, N)]);
			diagSecundaria += cubo[idx(k, P,     k, N)];
		}
		
		//diagonais 3D
		D1 += cubo[idx(P,         P, P, N)];
		D2 += cubo[idx(P,     N-P-1, P, N)];
		D3 += cubo[idx(N-P-1,     P, P, N)];
		D4 += cubo[idx(N-P-1, N-P-1, P, N)];
	}

	printf("::: Considera todos os cortes.\nDiagonais Principais: %d\nDiagonais Secundarias: %d\n", diagPrincipal, diagSecundaria);
	printf("::: Diagonais 3D:\nD1: %d\nD2: %d\nD3: %d\nD4: %d\n", D1, D2, D3, D4);
	printf("::: Soma total: %d\n", diagPrincipal+diagSecundaria+D1+D2+D3+D4);

	return 0;
}

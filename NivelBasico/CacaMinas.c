#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>

#define _BOMBA_  -1
#define _OCULTA_  0
#define _MOSTRA_  1

bool CheatMode = false;

int idx(int Linha, int Coluna, int Largura)
{
	return ( Linha * Largura + Coluna );
}

char Menu()
{
    char resposta;
    while( true )
    {
        system("@cls||clear");
        printf("##################################################################\n");
        printf("#################    C A M P O   M I N A D O     #################\n");
        printf("##################################################################\n");
        printf(">>> Escolha a dificuldade: \n\n");
        printf("                 ( B )ebe Chorao \n");
        printf("                 ( J )a sou grande! \n");
        printf("                 ( P )esadelo \n");
        printf("           Quero ( S )air daqui! \n");
        scanf(" %c", &resposta);
        resposta = toupper(resposta);

        if( resposta == 'S' )
        {
            printf("Tchau!\n");
            exit(EXIT_SUCCESS);
        }

        if( resposta == 'B' ||
            resposta == 'J' ||
            resposta == 'P'  )
        {
            break;
        }

    }

    return ( resposta );

}

void LimpaTabuleiro(int *Tabuleiro, int N)
{
	int i, j;
	
	for(i=0; i < N; i++)
	{
		for(j=0; j < N; j++)
		{
			Tabuleiro[ idx(i, j, N) ] = _OCULTA_;
		}
	}
}

void ContaBombas(int *Tabuleiro, int N)
{
	int L, C, cont=0;
	
	for(L=0; L < N; L++)
	{
		for(C=0; C < N; C++)
		{
			if( Tabuleiro[idx(L, C, N)] != _BOMBA_ )
			{
				cont=0;
				if( L > 0 )                  if(Tabuleiro[idx(L-1,   C,   N)] == _BOMBA_) cont++;	// acima
				if( L < (N-1) )              if(Tabuleiro[idx(L+1,   C,   N)] == _BOMBA_) cont++;	// abaixo
				if( C < (N-1) )              if(Tabuleiro[idx(L,     C+1, N)] == _BOMBA_) cont++;	// direita
				if( C > 0 )                  if(Tabuleiro[idx(L,     C-1, N)] == _BOMBA_) cont++;	// esquerda
				if( L > 0 && C < (N-1) )     if(Tabuleiro[idx(L-1,   C+1, N)] == _BOMBA_) cont++;	// diag sup dir
				if( L > 0 && C > 0 )         if(Tabuleiro[idx(L-1,   C-1, N)] == _BOMBA_) cont++;	// diag sup esq
				if( L < (N-1) && C < (N-1) ) if(Tabuleiro[idx(L+1,   C+1, N)] == _BOMBA_) cont++;	// diag inf dir
				if( L < (N-1) && C > 0 )     if(Tabuleiro[idx(L+1,   C-1, N)] == _BOMBA_) cont++;	// diag inf esq
				
				Tabuleiro[ idx(L, C, N) ] = cont;
			}
		}
	}
}


void MostraTabuleiro(int *Tabuleiro, int *TabVisual, int N)
{
	int L, C;
	
	for(L=0; L < N; L++)
	{
		for(C=0; C < N; C++)
		{
			if( TabVisual[idx(L, C, N)] == _OCULTA_  && !CheatMode )
			{
				printf(" # ");
			}
			else
			switch( Tabuleiro[idx(L, C, N)] )
			{
				case _BOMBA_ : printf(" * "); break;
				case 0       : printf(" . "); break;
				default      : printf(" %d ", Tabuleiro[idx(L, C, N)] ); break;
			}
			
		}
		printf("\n");
	}
}

void PosicionaBombas(int *Tabuleiro, int N, int qtBombas)
{
	//
	// posiciona as bombas no tabuleiro, garantindo
	// que nunca existirao duas bombas na mesma
	// posicao simultaneamente.
	//
	
	LimpaTabuleiro(Tabuleiro, N);
	
	int bombasAlocadas=0, i=0;
	bool achei = false;
	
	while( bombasAlocadas < qtBombas )
	{
		achei = false;
		int nro = rand() % (N*N-1);
		
		if( Tabuleiro[ nro ] == _BOMBA_ )
		{
			achei = true;
		}
		
		if(!achei)
		{
			Tabuleiro[ nro ] = _BOMBA_;
			bombasAlocadas++;
		}

	}
	
}

int AbreEspacos(int* Tabuleiro, int* TabVisual, int N, int Y, int X)
{
	int cont = 0;
	
	if( Tabuleiro[idx(Y, X, N)] == 0 && 
	    TabVisual[idx(Y, X, N)] == _OCULTA_ )
	{
			TabVisual[idx(Y, X, N)] = _MOSTRA_;
			cont++;
			
			if( Y > 0 )                  if( TabVisual[idx(Y-1, X,   N)] == _OCULTA_ ) cont += AbreEspacos(Tabuleiro, TabVisual, Y-1, X,   N); // acima
			if( Y < (N-1) )              if( TabVisual[idx(Y+1, X,   N)] == _OCULTA_ ) cont += AbreEspacos(Tabuleiro, TabVisual, Y+1, X,   N); // abaixo
			if( X < (N-1) )              if( TabVisual[idx(Y,   X+1, N)] == _OCULTA_ ) cont += AbreEspacos(Tabuleiro, TabVisual, Y,   X+1, N); // direita
			if( X > 0 )                  if( TabVisual[idx(Y,   X-1, N)] == _OCULTA_ ) cont += AbreEspacos(Tabuleiro, TabVisual, Y,   X-1, N); // esquerda
			if( Y > 0 && X < (N-1) )     if( TabVisual[idx(Y-1, X+1, N)] == _OCULTA_ ) cont += AbreEspacos(Tabuleiro, TabVisual, Y-1, X+1, N); // diag sup dir
			if( Y > 0 && X > 0 )         if( TabVisual[idx(Y-1, X-1, N)] == _OCULTA_ ) cont += AbreEspacos(Tabuleiro, TabVisual, Y-1, X-1, N); // diag sup esq
			if( Y < (N-1) && X < (N-1) ) if( TabVisual[idx(Y+1, X+1, N)] == _OCULTA_ ) cont += AbreEspacos(Tabuleiro, TabVisual, Y+1, X+1, N); // diag inf dir
			if( Y < (N-1) && X > 0 )     if( TabVisual[idx(Y+1, X-1, N)] == _OCULTA_ ) cont += AbreEspacos(Tabuleiro, TabVisual, Y+1, X-1, N); // diag inf esq
			
	}
	
	return( cont );
}

/*
 * 			if( Y > 0 )                  cont += AbreEspacos(Tabuleiro, TabVisual, Y-1, X,   N); // acima
			if( Y < (N-1) )              cont += AbreEspacos(Tabuleiro, TabVisual, Y+1, X,   N); // abaixo
			if( X < (N-1) )              cont += AbreEspacos(Tabuleiro, TabVisual, Y,   X+1, N); // direita
			if( X > 0 )                  cont += AbreEspacos(Tabuleiro, TabVisual, Y,   X-1, N); // esquerda
			if( Y > 0 && X < (N-1) )     cont += AbreEspacos(Tabuleiro, TabVisual, Y-1, X+1, N); // diag sup dir
			if( Y > 0 && X > 0 )         cont += AbreEspacos(Tabuleiro, TabVisual, Y-1, X-1, N); // diag sup esq
			if( Y < (N-1) && X < (N-1) ) cont += AbreEspacos(Tabuleiro, TabVisual, Y+1, X+1, N); // diag inf dir
			if( Y < (N-1) && X > 0 )     cont += AbreEspacos(Tabuleiro, TabVisual, Y+1, X-1, N); // diag inf esq
*/

int main()
{

    char resposta = Menu();
    int N=10, qtBombas=5;
    
    switch( resposta )
    {
		case 'B': N = 10; qtBombas = 5;  break;
		case 'J': N = 20; qtBombas = 15; break;
		case 'P': N = 30; qtBombas = 80; break;
		default:  N = 10; qtBombas = 5;  break;
	}

	// Tabuleiro mantera as informacoes do conteudo das celulas.
	// 0       : celula vazia
	// _BOMBA_ : celula contem uma bomba
	// 1 a 8   : quantidade de bombas ao redor da celula.
	int *Tabuleiro = (int*)malloc(sizeof(int) * N * N);
	if(Tabuleiro == NULL)
	{
		printf(">>> Erro alocando memoria para o tabuleiro! :-( \n");
		exit(EXIT_FAILURE);
	}
	
	// TabVisual indica o status das celulas:
	// 0 : celula coberta (conteudo da celula eh oculto).
	// 1 : celula descoberta (mostra o seu conteudo na tela).
	int *TabVisual = (int*)malloc(sizeof(int) * N * N);
	if(TabVisual == NULL)
	{
		printf(">>> Erro alocando memoria para o tabuleiro! :-( \n");
		exit(EXIT_FAILURE);
	}

	PosicionaBombas(Tabuleiro, N, qtBombas);
	ContaBombas    (Tabuleiro, N);
	LimpaTabuleiro (TabVisual, N);
	int cont = AbreEspacos(Tabuleiro, TabVisual, 6, 6, N);
	printf("\n"); CheatMode=false;
	MostraTabuleiro(Tabuleiro, TabVisual, N);
	printf("\n"); CheatMode=true;
	MostraTabuleiro(Tabuleiro, TabVisual, N);
	
	printf("\n\n Celulas Abertas: %d \n", cont);
	
	
    return 0;
}

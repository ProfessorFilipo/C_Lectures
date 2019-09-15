
/*
**    Calcula MMC dos nros dados
** =================================
** Prof. Filipo Mór - filipomor.com
** =================================
** 15 de Setembro de 2019
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

bool EhPrimo(int nro)
{
	//
	// indica se o valor informado
	// é um nro primo.
	//
	bool Dividiu = false;
	int  Divisor = nro - 1;
	while( Divisor > 1 )
	{
		if(nro % Divisor-- == 0)
		{
			Dividiu = true;
			break;
		}
		//Divisor--;
	}
	
	return(!Dividiu);
}

int ProximoPrimo(int nro)
{
	// 
	// Busca o próximo nro
	// primo maior do que o
	// nro informado.
	//
	bool Achou = false;
	int i = nro + 1;
	
	while(!Achou)
	{
		if(EhPrimo(i))
		{
			Achou = true;
			break;
		}
		i++;
	}
		
	return(i);
}

int main(int argc, char *argv[]) 
{
	
	int       Tam = 6;
	int Valores[] = {15, 25, 70, 65, 125, 225};
	int         i = 0;
	int   Divisor = 2;
	int  Divisoes = Tam;
	int Resultado = 1;
	
	printf("\n\n\n *** Calcula MMC *** \n\n");
	
	while ( true )
	{
		// mostra os valores a serem divididos
		i = 0;
		while ( i < Tam )
		{
			printf(" \t%5d ", Valores[i]);
			i++;
		}
		
		// decide qual será o divisor utilizado.
		// este valor tem de ser um nro primo, sendo
		// no minimo igual a 2. Inicia a busca 
		// do valor do divisor.
		int contUm = 0; // quantos valores == 1 ?
		while ( true )
		{
			Divisoes = 0;
			i = 0;
			contUm = 0;
			while ( i < Tam )
			{
				// testa se valor a ser dividido é 
				// igual a UM.
				if( Valores[i] == 1)
				{
					contUm++;
				}
				
				// testa se há divisão possível.
				if( Valores[i] % Divisor == 0 )
				{
					Divisoes++;
				}
				i++;
			}
			if(Divisoes == 0 && ( contUm != Tam))			
			{
				// não houve nenhuma divisao. Busca o
				// próximo valor para o divisor.
				Divisor = ProximoPrimo(Divisor);
			}
			else break;
		}
		
		// atualiza os valores no vetor
		if( contUm == Tam) 
		{
			// todos os valores já são UM.
			// não precisa continuar a execução.
			printf("\n Resultado: %5d\n\n", Resultado);
			break;
		}
		else
		{
			// ainda temos valores maiores do que um.
			// deve seguir executando.
			Resultado *= Divisor;
			printf(" | %5d\n", Divisor);
			i = 0;
			while ( i < Tam )
			{
				if( Valores[i] % Divisor == 0)
				{
					Valores[i] = Valores[i] / Divisor;
				}
				i++;
			}			
		}

	}
	
	return 0;
}

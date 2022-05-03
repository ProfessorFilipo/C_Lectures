#include <stdio.h>

int Comprimento(char Texto[])
{
	int cont=0;
	while(Texto[cont] != '\0') cont++;
	return cont;
}

int ContaPalavras(char Texto[])
{
	int pos=0, cont=0, aux=0;
	while(Texto[pos] != '\0')
	{
		aux = 0;
		while(Texto[pos] == ' ' && Texto[pos] != '\0') pos++;
		while(Texto[pos] != ' ' && Texto[pos] != '\0') 
		{
			aux++;
			pos++;
		}
		if(aux > 0) cont++;
	}
	return cont;
}

int ContaPalavra(char Texto[], char Palavra[])
{
	int tamPalavra = Comprimento(Palavra);
	int contPalavra = 0;
	int i, pos = 0, aux=0;
	
	while (Texto[pos] != '\0')
	{
		if(Texto[pos] == Palavra[0])
		{
			// achou a primeira letra. as demais tb batem?
			for(i=0; i<tamPalavra; i++)
			{
				if(Texto[i+pos] == Palavra[i]) 
				{
					aux++;	
				} else break;
				printf("i: %d ::: %c %c\n", i, Texto[i+pos], Palavra[i]);
			}
			if(aux == tamPalavra) contPalavra++;
			aux=0;
		}
		pos++;
	}
	return contPalavra;
}

int main()
{
	//char Texto[] = "     este eh um texto de   exemplo contendo explicações    importantes. ";
	//char Texto[] = "Este eh um texto de exemplo contendo explicações importantes. contendo     ";
	char Texto[] = " abc 123 abc 123 abc abcabc    abc    123      ";
	
	char Palavra[] = "abc ";
	printf("Texto: %s \n", Texto);
	printf("tamanho: %d\n", Comprimento(Texto));
	printf("palavras: %d\n", ContaPalavras(Texto));
	printf(" '%s' aparece %d vezes. \n", Palavra, ContaPalavra(Texto, Palavra));
	
	return 0;
}

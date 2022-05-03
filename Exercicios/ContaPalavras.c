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


int main()
{
	//char Texto[] = "     este eh um texto de   exemplo contendo explicações    importantes. ";
	char Texto[] = "Este eh um texto de exemplo contendo explicações importantes.     ";
	//char Texto[] = "      ";
	
	printf("Texto: %s \n", Texto);
	printf("tamanho: %d\n", Comprimento(Texto));
	printf("palavras: %d\n", ContaPalavras(Texto));
	
	return 0;
}

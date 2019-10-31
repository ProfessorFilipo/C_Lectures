#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

struct Produto
{
	int Codigo;
	char DataCadastro[8];
	bool Ativo;
	char Nome[50];
	double Valor;
};

double SorteiaDouble(double min, double max) 
{
    double range = (max - min); 
    double div = RAND_MAX / range;
    return min + (rand() / div);
}

int SorteiaInt(int min, int max) 
{
    int range = (max - min); 
    int div = RAND_MAX / range;
    return min + (rand() / div);
}

int main(int argc, char *argv[]) 
{

	//
	// gerador de arquivos de dados para o trabalho de implementacao 1
	//
	int    qtRegistros=0, i=0;
	char   NomeArq[256];
	struct Produto P;
	
	printf("###########################################\n");
	printf("####    G E R A D O R  D E  D A D O S   ###\n");
	printf("###########################################\n");
	printf("::: Informe a quantidade de registros: ");
	scanf("%d", &qtRegistros);
	printf("\n::: Informe o nome do arquivo de destino: ");
	scanf("%s", &NomeArq);
	
	//printf("\n\n%d\n\n", SorteiaInt(1980, 2019));
	
	FILE *arqDestino = fopen(NomeArq, "wb");
	if(arqDestino == NULL)
	{
		printf("\n::: Erro abrindo arquivo de destino!");
		exit(EXIT_FAILURE);
	}
	
	for(i=1; i<=qtRegistros; i++)
	{
		P.Codigo = i*10;
		P.Valor = SorteiaDouble(1.0, 3999.99);
		sprintf(P.Nome, "Produto %2d", i );
		sprintf(P.DataCadastro, "%4d%02d%02d", SorteiaInt(1980,2010), SorteiaInt(1,12), SorteiaInt(1,30) );
		P.Ativo = true;
		
		printf("\nCodigo: %4d\n", P.Codigo);
		printf("Nome: %s \n", P.Nome);
		printf("Valor: %lf \n", P.Valor);
		printf("Data Cadastro: %.8s\n", P.DataCadastro);
		if(P.Ativo) printf("ativado\n");
		printf("Ativo: %s %d\n", (P.Ativo ? "SIM": "NAO"), P.Ativo);
	
		fwrite(&P, sizeof(struct Produto), 1, arqDestino);
	}

	fclose(arqDestino);

	// Le o arquivo e mostra o conteudo 
	FILE *arqDados = fopen(NomeArq, "rb");
	if(arqDados == NULL)
	{
		printf("\n::: Erro abrindo arquivo de dados!");
		exit(EXIT_FAILURE);
	}
	
	printf("\n>>>\n>>> Dados Lidos: \n>>>\n");
	while(!feof(arqDados))
	{
		fread(&P, sizeof(struct Produto), 1, arqDados);
		printf("\nCodigo: %4d\n", P.Codigo);
		printf("Nome: %s \n", P.Nome);
		printf("Valor: %lf \n", P.Valor);
		printf("Data Cadastro: %.8s\n", P.DataCadastro);
		printf("Ativo: %s %d\n", (P.Ativo ? "SIM": "NAO"), P.Ativo);		
	}
	fclose(arqDados);
	
	return 0;
}

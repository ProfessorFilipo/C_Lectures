#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct registro
{
    int Linha;
    int Coluna;
    struct registro* Proximo;
};

// é bacana tratar os nodos como um tipo de dados, dando um nome a este tipo.
typedef struct registro Nodo_t;

struct registro_Objeto
{
    int Quantidade;
    struct registro* Proximo;
    struct registro_Objeto* ProxObjeto;
};

typedef struct registro_Objeto NodoObjeto_t;


void MostraLista(Nodo_t* Nodo, int cont)
{
    if (Nodo != NULL)
    {
        printf("%3d ::: L: %2d ::: C: %2d\n", cont++, Nodo->Linha, Nodo->Coluna);
        MostraLista(Nodo->Proximo, cont);
    }
}

void MostraListaObjetos(NodoObjeto_t* ListaObjetos, int cont)
{
    int i, qtNodos;
    if (ListaObjetos != NULL)
    {
        Nodo_t* temp = ListaObjetos->Proximo;
        qtNodos = ListaObjetos->Quantidade;
        printf("\n::::::: Objeto %d \n", cont);
        for (i = 0; i < qtNodos; i++)
        {
            printf("::::L: %3d  C: %3d\n", temp->Linha, temp->Coluna);
            temp = temp->Proximo;
        }
    }
}

bool ExisteNodo(int Linha, int Coluna, Nodo_t* Lista)
{
    bool retorno = false;

    if (Lista == NULL)
    {
        retorno = false;
    }
    else if (Lista->Linha == Linha && Lista->Coluna == Coluna)
    {
        retorno = true;
    }
    else retorno = ExisteNodo(Linha, Coluna, Lista->Proximo);

    return retorno;
}

void InsereNodo(int Linha, int Coluna, Nodo_t* p)
{
    Nodo_t* NovoNodo = (Nodo_t*)malloc(sizeof(Nodo_t));
    if (NovoNodo == NULL)
    {
        printf("\nErro alocando memória!\n");
        exit(-1);
    }
    NovoNodo->Linha = Linha;
    NovoNodo->Coluna = Coluna;
    NovoNodo->Proximo = p->Proximo;
    p->Proximo = NovoNodo;
}

NodoObjeto_t* InsereNodoObjeto(NodoObjeto_t* ListaObjetos, Nodo_t* CabecaLista, int Quantidade)
{
    NodoObjeto_t* NovoObjeto = (NodoObjeto_t*)malloc(sizeof(NodoObjeto_t));
    if (NovoObjeto == NULL)
    {
        printf("\nErro alocando memoria!\n");
        exit(-1);
    }
    NovoObjeto->Quantidade = Quantidade;
    NovoObjeto->Proximo = CabecaLista->Proximo;
    NovoObjeto->ProxObjeto = ListaObjetos->ProxObjeto;
    ListaObjetos->ProxObjeto = NovoObjeto;

    return (NovoObjeto);
}

int SegueTrilha(int Linha, int Coluna, int* Matriz, int N, int M, Nodo_t* Lista)
{
    int qtInserida = 0;

    // posição prenchida ou já pesquisada anteriormente?
    if (Matriz[Linha * N + Coluna] != 1 || ExisteNodo(Linha, Coluna, Lista))
    {
        return 0;
    }

    // insere a posição na lista como ponto de partida para a pesquisa.
    InsereNodo(Linha, Coluna, Lista);
    qtInserida++;

    if (Linha - 1 >= 0) // acima
    {
        qtInserida += SegueTrilha(Linha - 1, Coluna, Matriz, N, M, Lista);
    }

    if (Linha + 1 <= N) //abaixo
    {
        qtInserida += SegueTrilha(Linha + 1, Coluna, Matriz, N, M, Lista);
    }

    if (Coluna - 1 >= 0) // esquerda
    {
        qtInserida += SegueTrilha(Linha, Coluna - 1, Matriz, N, M, Lista);
    }

    if (Coluna + 1 <= M) // direita
    {
        qtInserida += SegueTrilha(Linha, Coluna + 1, Matriz, N, M, Lista);
    }

    if (Linha + 1 <= N && Coluna + 1 <= M) // diagonal inferior direita
    {
        qtInserida += SegueTrilha(Linha + 1, Coluna + 1, Matriz, N, M, Lista);
    }

    if (Linha - 1 >= 0 && Coluna + 1 <= M) // diagonal superior direita
    {
        qtInserida += SegueTrilha(Linha - 1, Coluna + 1, Matriz, N, M, Lista);
    }

    if (Linha - 1 >= 0 && Coluna - 1 >= 0) // diagonal superior esquerda
    {
        qtInserida += SegueTrilha(Linha - 1, Coluna - 1, Matriz, N, M, Lista);
    }

    if (Linha + 1 <= N && Coluna - 1 >= 0) // diagonal inferior esquerda
    {
        qtInserida += SegueTrilha(Linha + 1, Coluna - 1, Matriz, N, M, Lista);
    }

    return qtInserida;
}

void MostraMatriz(int* Matriz, int N, int M)
{
    int i, j;

    for (i = 0; i < N; i++)
    {
        for (j = 0; j < M; j++)
        {
            printf(" %c", Matriz[i * N + j] ? 35 : 250);
        }
        printf("\n");
    }

}


int main(void)
{

    int Matriz[] = {
                0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 1,
                0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 1,
                1, 1, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0,
                0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 1, 1, 1, 1,
                0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0,
                0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0,
                0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 1, 0, 0, 0,
                0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0,
                0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0,
                0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 1, 0, 1,
                0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 1, 0,
                0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 1, 0, 0, 0,
                0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0,
                0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 1, 0, 0, 0,
                0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0,
                0, 0, 0, 1, 0, 1, 1, 1, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0,
                0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0,
                0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0
    };

    int N = 20, M = 20;

    // cria lista vazia
    Nodo_t* CabecaLista = (Nodo_t*)malloc(sizeof(Nodo_t));
    if (CabecaLista == NULL)
    {
        printf("\nErro alocando memoria!\n");
        return (-1);
    }
    CabecaLista->Linha = -1;
    CabecaLista->Coluna = -1;
    CabecaLista->Proximo = NULL;

    NodoObjeto_t* CabecaListaObjetos = (NodoObjeto_t*)malloc(sizeof(NodoObjeto_t));
    if (CabecaListaObjetos == NULL)
    {
        printf("\nErro alocando memória!\n");
        return(-1);
    }
    CabecaListaObjetos->Quantidade = -1;
    CabecaListaObjetos->Proximo = NULL;
    CabecaListaObjetos->ProxObjeto = NULL;

    int ultLinha = -1, ultColuna = -1;
    int Linha, Coluna, qt;
    int contObjetos = 0;

    for (Linha = 0; Linha < N; Linha++)
    {
        for (Coluna = 0; Coluna < M; Coluna++)
        {
            qt = SegueTrilha(Linha, Coluna, Matriz, N, M, CabecaLista);
            if (qt > 0)
            {
                //contObjetos++;
                //printf(" %d", qt);
                NodoObjeto_t* NovoObjeto = InsereNodoObjeto(CabecaListaObjetos, CabecaLista, qt);
                MostraListaObjetos(NovoObjeto, contObjetos++);
            }

        }
        //printf("\n");
    }
    printf("\n:::: %d objetos identificados na matriz!\n", contObjetos);
    ////int qt = SegueTrilha(13, 11, Matriz, N, M, CabecaLista);
    ////printf("\n %d nodos incluidos\n", qt);


    MostraMatriz(Matriz, N, M);
    MostraLista(CabecaLista, 0);


    return 0;
}

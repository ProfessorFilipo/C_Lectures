/****************************************
***  Jogo da Velha [ tic tac toe ]    ***
***  by The Retro Modern Professor    ***
***  07 de agosto de 2022             ***
*****************************************
***  versao 0.1 - IA "burra"          ***
*****************************************
**/

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

#define _Humano_   1
#define _IA_      -1
#define _Vazio_    0
#define _Empate_   8
#define _Ninguem_ 15

typedef struct Jogada_t
{
    int Linha;
    int Coluna;
} Jogada;

void clrscr()
{
    system("@cls||clear");
}

void InsereEspacos(int quantidade)
{
    int i;
    for(i=0; i<quantidade;i++) printf(" ");
}

void MostraTabuleiro(int Tabuleiro[3][3])
{
    int L, C;
    char posicao;

    InsereEspacos(15);
    printf("  1   2   3 \n");
    InsereEspacos(15);
    printf("-------------\n");    
    for(L=0; L<3; L++)
    {
        if(L>0) 
        {
            InsereEspacos(15);
            printf("------------\n");
        }
        
        InsereEspacos(12);
        printf(" %d |", L+1);
        for(C=0; C<3; C++)
        {
            switch (Tabuleiro[L][C])
            {
            case _IA_:
                posicao = 'X';
                break;
            case _Vazio_:
                posicao = '.';
                break;
            case _Humano_:
                posicao = 'O';
                break;
            default:
                posicao = ' ';
                break;
            };

            printf(" %c ", posicao);
            /*if(C<=1)*/ printf("|");
        }
        printf("\n");
    }
    InsereEspacos(15);
    printf("-------------\n");        
}

void Cabecalho()
{
    printf("*************************************************************\n");
    printf("*************************************************************\n");
    printf("***********        J O G O  D A  V E L H A        ***********\n");
    printf("*************************************************************\n");
    printf("*************************************************************\n");
    printf("*** by The Retro Modern Professor                         ***\n");
    printf("*** version 0.1 - dummy AI ::: 2022-aug-07                ***\n");
    printf("*************************************************************\n");
    printf("*************************************************************\n");

}

void LimpaTabuleiro(int Tabuleiro[3][3], int Valor)
{
    int L, C;
    for(L=0; L<3; L++)
    {
        for(C=0; C<3; C++)
        {
            Tabuleiro[L][C] = Valor;
        }
    }

}

void TelaPrincipal(int Tabuleiro[3][3], int Jogador)
{

    clrscr();
    Cabecalho();
    printf("\n");
    MostraTabuleiro(Tabuleiro);

}

Jogada LeJogada(int Tabuleiro[3][3])
{
    bool JogadaValida;
    char resposta[10];
    int resp;
    int contTentativas=0;
    Jogada jogadaLida;

    // Le a coluna desejada
    do
    {
        TelaPrincipal(Tabuleiro, _Humano_);

        JogadaValida = false; 
        if(contTentativas > 9) printf("\n Isto esta ficando realmente MUITO chato.... ");
        if(contTentativas > 5 && contTentativas < 10) printf("\n Qual o seu problema???? ");
        if(contTentativas > 0) printf("\n COLUNA invalida, tente novamente um valor entre [1, 2 OU 3]!\n");
        
        printf("\n ::: Informe a COLUNA [1, 2 OU 3]: ");
        gets(resposta);

        resp = atoi(resposta); //printf("\nResposta: %d \n", resp);
        if(resp == 1 || resp == 2 || resp == 3)
        {
            JogadaValida = true;
        }
        contTentativas++;

    } while (!JogadaValida);
    
    if(contTentativas >5) printf("\n Ufa!!! Finalmente, em.... :-/ \n");

    jogadaLida.Coluna = resp;
    contTentativas=0;
    JogadaValida = false;

    // Le a LINHA desejada
    do
    {
        JogadaValida = false;
        if(contTentativas > 0) TelaPrincipal(Tabuleiro, _Humano_);
        if(contTentativas > 9) printf("\n Isto esta ficando realmente MUITO chato.... ");
        if(contTentativas > 5 && contTentativas < 10) printf("\n Qual o seu problema???? ");
        if(contTentativas > 0) printf("\n LINHA invalida, tente novamente um valor entre [1, 2 OU 3]!\n");        

        printf("\n ::: Informe a LINHA [1, 2 OU 3]: ");
        gets(resposta);
        
        resp = atoi(resposta); //printf("\nResposta: %d \n", resp);
        if(resp == 1 || resp == 2 || resp == 3)
        {
            JogadaValida = true;
        }
        contTentativas++;

    } while (!JogadaValida);
    
    jogadaLida.Linha = resp;
    
    // os indices da matriz sempre iniciam com zero!
    jogadaLida.Linha--;
    jogadaLida.Coluna--;

    return jogadaLida;
}

bool PosicaoLivre(int Tabuleiro[3][3], Jogada jogada)
{
    bool retorno = false;

    if(Tabuleiro[jogada.Linha][jogada.Coluna] == _Vazio_) retorno = true;

    return retorno;
}

int PosicoesLivres(int Tabuleiro[3][3])
{
    int L, C, cont=0;

    for(L=0; L<3; L++)
    {
        for(C=0; C<3; C++)
        {
            if(Tabuleiro[L][C] == _Vazio_) cont++;
        }
    }

    //printf("\nPosicoes livres: %d \n", cont);
    return cont;
}

Jogada JogadaIA(int Tabuleiro[3][3])
{
    //
    // Nesta versão, simplesmente sorteia uma posicao
    // vazia do tabuleiro, sem a aplicacao de qualquer
    // tipo de heuristica.
    //
    Jogada jogadasLivres[9];
    int L, C, cont=0;

    for(L=0; L<3; L++)
    {
        for(C=0; C<3; C++)
        {
            if(Tabuleiro[L][C] == _Vazio_)
            {
                jogadasLivres[cont].Linha  = L;
                jogadasLivres[cont].Coluna = C;
                cont++;
            }
        }
    }

    int posicao = rand() % cont;
    //printf("::: Jogadas Livres: %d ::: jogada selecionada: %d :: L: %d  C: %d \n", cont, posicao, jogadasLivres[posicao].Linha, jogadasLivres[posicao].Coluna);

    return jogadasLivres[posicao];

}

int VerificaVitoria(int Tabuleiro[3][3])
{

    int JogadorVitorioso = _Ninguem_;

    // linhas
    if( (Tabuleiro[0][0] == Tabuleiro[0][1] && Tabuleiro[0][0] == Tabuleiro[0][2]) && Tabuleiro[0][0] != _Vazio_ ) { JogadorVitorioso = Tabuleiro[0][0]; /*printf("Vitorioso: 0 %d \n", JogadorVitorioso); */ }
    if( (Tabuleiro[1][0] == Tabuleiro[1][1] && Tabuleiro[1][0] == Tabuleiro[1][2]) && Tabuleiro[1][0] != _Vazio_ ) { JogadorVitorioso = Tabuleiro[1][0]; /*printf("Vitorioso: 1 %d \n", JogadorVitorioso); */ }
    if( (Tabuleiro[2][0] == Tabuleiro[2][1] && Tabuleiro[2][0] == Tabuleiro[2][2]) && Tabuleiro[2][0] != _Vazio_ ) { JogadorVitorioso = Tabuleiro[2][0]; /*printf("Vitorioso: 2 %d \n", JogadorVitorioso); */ }

    // colunas
    if( (Tabuleiro[0][0] == Tabuleiro[1][0] && Tabuleiro[0][0] == Tabuleiro[2][0]) && Tabuleiro[0][0] != _Vazio_ ) { JogadorVitorioso = Tabuleiro[0][0]; /*printf("Vitorioso: 3 %d \n", JogadorVitorioso); */ }
    if( (Tabuleiro[0][1] == Tabuleiro[1][1] && Tabuleiro[0][1] == Tabuleiro[2][1]) && Tabuleiro[0][1] != _Vazio_ ) { JogadorVitorioso = Tabuleiro[0][1]; /*printf("Vitorioso: 4 %d \n", JogadorVitorioso); */ }
    if( (Tabuleiro[0][2] == Tabuleiro[1][2] && Tabuleiro[0][2] == Tabuleiro[2][2]) && Tabuleiro[0][2] != _Vazio_ ) { JogadorVitorioso = Tabuleiro[0][2]; /*printf("Vitorioso: 5 %d \n", JogadorVitorioso); */ }

    // diagonal principal
    if( (Tabuleiro[0][0] == Tabuleiro[1][1] && Tabuleiro[0][0] == Tabuleiro[2][2]) && Tabuleiro[0][0] != _Vazio_ ) { JogadorVitorioso = Tabuleiro[0][0]; /*printf("Vitorioso: 6 %d \n", JogadorVitorioso); */ }

    // diagonal secundaria
    if( (Tabuleiro[0][2] == Tabuleiro[1][1] && Tabuleiro[0][2] == Tabuleiro[2][0]) && Tabuleiro[0][2] != _Vazio_ ) { JogadorVitorioso = Tabuleiro[0][2]; /*printf("Vitorioso: 7 %d \n", JogadorVitorioso); */ }

    if(JogadorVitorioso == _Ninguem_ && PosicoesLivres(Tabuleiro) == 0) JogadorVitorioso = _Empate_;
    //printf("Vitorioso: 10 %d \n", JogadorVitorioso);
    return JogadorVitorioso;
}

void DeclaraVitorioso(int Tabuleiro[3][3], int jogadorVitorioso)
{

        switch ( jogadorVitorioso )
        {
        case _Humano_:
            printf("\n::: Parabens, vc ganhou da maquina! ::: \n");
            MostraTabuleiro(Tabuleiro);
            exit(0);
            break;
        
        case _IA_:
            printf("\n::: Tudo bem, vc nao tinha como ganhar mesmo ;-) ::: \n");
            MostraTabuleiro(Tabuleiro);
            exit(0);
            break;

        case _Empate_:
            printf("\n::: Muito bem, vc conseguiu nao perder! ;-) ::: \n");
            MostraTabuleiro(Tabuleiro);
            exit(0);
            break;

        default:
            break;
        }

}

int main()
{

    int Tabuleiro[3][3];
    // -1 jogador X            ===> _IA_
    //  0 célula não utilizada ===> _Vazio_
    //  1 jogador O            ===> _Humano_
    
    srand(time(NULL));

    Jogada jogada;
    bool jogadaValida = false;

    LimpaTabuleiro(Tabuleiro, _Vazio_);

    // o computador sempre começa! ;-)
    Jogada jogadaIA = JogadaIA(Tabuleiro);
    Tabuleiro[jogadaIA.Linha][jogadaIA.Coluna] = _IA_;

    while( PosicoesLivres(Tabuleiro) > 0)
    {
        //printf("Posicoes Livres: %d \n", PosicoesLivres(Tabuleiro));

        do
        {
            jogadaValida = false;
            jogada = LeJogada(Tabuleiro);
            //printf("\nLinha: %d ::: Coluna: %d\n", jogada.Linha, jogada.Coluna);
            if(PosicaoLivre(Tabuleiro, jogada))
            {
                Tabuleiro[jogada.Linha][jogada.Coluna] = _Humano_;
                jogadaValida = true;
            } 

        } while (!jogadaValida);

        int vitorioso = VerificaVitoria(Tabuleiro);
        DeclaraVitorioso( Tabuleiro, vitorioso );

        // computador joga
        Jogada jogadaIA = JogadaIA(Tabuleiro);
        Tabuleiro[jogadaIA.Linha][jogadaIA.Coluna] = _IA_;
        vitorioso = VerificaVitoria(Tabuleiro);
        DeclaraVitorioso( Tabuleiro, vitorioso );

    }

    
    //MostraTabuleiro(Tabuleiro);

    return 0;
}

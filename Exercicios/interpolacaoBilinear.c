/*
** Interpolacao Bilinear em Matrizes quadradas com relacao 1:2
** Prof. Me. Filipo Mor
** https://www.filipomor.com
** https://github.com/ProfessorFilipo
** Setembro de 2022
*/
#include <stdio.h>
#include <stdlib.h>

void LimpaMatriz(int *M, int N)
{
    int L, C;
    for(L=0; L<N; L++)
    {
        for(C=0; C<N; C++)
        {
            M[L*N+C] = 0;
        }

    }

}

void MostraMatriz(int *M, int N, char *Titulo)
{
    printf("\n::: %s :::\n", Titulo);
    int L, C;
    for(L=0; L<N; L++)
    {
        for(C=0; C<N; C++)
        {
            switch(M[L*N+C])
            {
                case 0: printf(" ."); break;
                case 1: printf(" #"); break;
            }
        }
        printf("\n");
    }

}


void Zoom(int *M, int *W, int N)
{

    // interpolacao bilinear
    // considera a relacao M com W sempre como sendo 1:2
    int Rv = 2, Rh = 2; // Relacao Vertical e Relacao Horizontal
    int L, C;
    for(L=0; L<N; L++)
    {
        for(C=0; C<N; C++)
        {

            // avalia a media para cada celula da matriz maior.
            // caso a media seja < 0.5, mantem em ZERO. senao, sobre para 1.
            int ibL, ibC, limV, limH, valor;
            float mediaH = (float)M[L*N+C] / (float)Rh;
            float mediaV = (float)M[L*N+C] / (float)Rv;

            for(ibL = L * Rv; ibL < (L*Rv+Rv); ibL++)
            {
                for(ibC = C * Rh; ibC < (C*Rh+Rh); ibC++)
                {
                    valor = 1;
                    if( (mediaV + mediaH)/2.0 < 0.5)
                    {
                        valor = 0;
                    }
                    W[ibL * N * Rv + ibC] = valor;
                }
            }
        }
    }
}


int main()
{

    int M[6][6] = { {0, 0, 0, 0, 0, 0},
                    {0, 1, 1, 1, 1, 0}, 
                    {0, 1, 1, 0, 1, 0}, 
                    {0, 1, 0, 1, 1, 0}, 
                    {0, 1, 1, 1, 1, 0}, 
                    {0, 0, 0, 0, 0, 0} };

    int W[6*2][6*2];
    LimpaMatriz(W, 6*2);

    MostraMatriz(M, 6, "Original");
    Zoom(M, W, 6);
    MostraMatriz(W, 6*2, "Nova");

    return(0);
}

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

void trocaValores(int *X, int *Y)
{
	int aux = *X;
	*X = *Y;
	*Y = aux;
}

int main()
{

	int A, B, C;

	printf("Informe 3 inteiros: ");
	scanf("%d %d %d", &A, &B, &C);


	if (A > B) trocaValores(&A, &B);
	if (A > C) trocaValores(&A, &C);
	if (B > C) trocaValores(&B, &C);

	printf("\nValores informados: %d :: %d :: %d\n", A, B, C);

	return(0);
}

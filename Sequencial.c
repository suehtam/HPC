#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>
#define TAMANHO 10000
int main()
{
    int vetor[TAMANHO];
    int i, soma = 0;
    for (i = 0; i < TAMANHO; i++)
    {
        vetor[i] = rand() % 100;
        soma += vetor[i];
    }
    printf("Soma dos elementos sequencial = %d\n", soma);
}
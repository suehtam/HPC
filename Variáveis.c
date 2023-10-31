#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <math.h>
#include <string.h>
#include <omp.h>
// number of threads
#define T 8
#define STRIDE 32
void calc_diferenca(int **matriz, int linha, int coluna, int tam, int *dif, int *valor_maior, int *valor_menor)
{
    int aux_dif = 0;
    int i, j;
    *dif = 0;
    for (i = linha - 1; i <= linha + 1; i++)
    {
        for (j = coluna - 1; j <= coluna + 1; j++)
        {
            if ((i >= 0 && i < tam) && (j >= 0 && j < tam) && (i != linha || j != coluna))
            {
                aux_dif = abs(matriz[linha][coluna] - matriz[i][j]);
                if (aux_dif > *dif)
                {
                    *dif = aux_dif;
                    if (matriz[linha][coluna] > matriz[i][j])
                    {
                        *valor_maior = matriz[linha][coluna];
                        *valor_menor = matriz[i][j];
                    }
                    else
                    {
                        *valor_maior = matriz[i][j];
                        *valor_menor = matriz[linha][coluna];
                    }
                }
            }
        }
    }
    return;
}
int main(int argc, char **argv)
{
    omp_set_num_threads(4);
    int tam, seed, i, j;
    int **matriz;
    int dif_aux, valor_maior_aux, valor_menor_aux;
    int diferenca_global = INT_MIN, valor_maior_global, valor_menor_global;
    int
        diferenca_local[T * STRIDE],
        valor_maior_local[T * STRIDE], valor_menor_local[T * STRIDE];
    double wtime;
    if (argc != 3)
    {
        printf("Wrong arguments. Please use arguments <amount_of_elements>
        <seed_for_rand> \n");
        exit(-1);
    }
    tam = atoi(argv[1]);
    seed = atoi(argv[2]);
    matriz = ((int **)malloc(tam * sizeof(int *)));
    for (i = 0; i < tam; i++)
    {
        matriz[i] = ((int *)malloc(tam * sizeof(int)));
    }
    srand(seed); // setting starting point to rand();
    #pragma omp parallel for private(i, j, dif_aux, valor_maior_aux, valor_menor_aux) shared(matriz, tam, diferenca_local, valor_maior_local, valor_menor_local)
    for (i = 0; i < tam; i++)
    {
        for (j = 0; j < tam; j++)
        {
            int my_id = omp_get_thread_num();
            calc_diferenca(matriz, i, j, tam, &dif_aux, &valor_maior_aux,
                        &valor_menor_aux);
            if (diferenca_local[my_id * STRIDE] < dif_aux)
            {
                diferenca_local[my_id * STRIDE] = dif_aux;
                valor_maior_local[my_id * STRIDE] = valor_maior_aux;
                valor_menor_local[my_id * STRIDE] = valor_menor_aux;
            }
        } // end second for
    } // end first for
    
    wtime = omp_get_wtime();
    #pragma omp parallel for reduction(max : diferenca_global) reduction(min : valor_maior_global, valor_menor_global)
    for (i = 0; i < T; i++)
    {
        if (diferenca_global < diferenca_local[i * STRIDE])
        {
            diferenca_global = diferenca_local[i * STRIDE];
            valor_maior_global = valor_maior_local[i * STRIDE];
            valor_menor_global = valor_menor_local[i * STRIDE];
        }
    } // end for

    wtime = omp_get_wtime() - wtime;
    printf("Elapsed wall clock time = %.5f\n\n", wtime);
    printf("%d %d \n", valor_maior_global, valor_menor_global);
    fflush(0);
    for (i = 0; i < tam; i++)
    {
        free(matriz[i]);
    }
    free(matriz);
    return (0);
}
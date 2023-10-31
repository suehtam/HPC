#include <stdio.h>
#include <omp.h>

// Função que define a curva f(x) = x² + 1
double f(double x) {
    return x * x + 1;
}

// Função que calcula a integral de f(x) no intervalo [a,b] usando a regra do trapézio com n subintervalos
double trapezio(double a, double b, int n) {
    double h = (b - a) / n; // Largura dos subintervalos
    double area = 0.0; // Área total
    int i; // Índice do laço

    // Cria uma região paralela com um número de threads igual ao número de núcleos disponíveis
    #pragma omp parallel
    {
        // Divide o laço for entre os threads da região paralela
        #pragma omp parallel for
        for (i = 0; i < n; i++) {
            // Calcula a área do i-ésimo trapézio
            double x1 = a + i * h;
            double x2 = a + (i + 1) * h;
            double ai = (f(x1) + f(x2)) * h / 2.0;

            // Atualiza a área total de forma atômica, evitando condições de corrida
            #pragma omp atomic
            area += ai;
        }
    }

    return area;
}

int main() {
    double a = 0.0; // Limite inferior da integral
    double b = 1.0; // Limite superior da integral
    int n = 1000000; // Número de subintervalos

    // Calcula e imprime o valor aproximado da integral
    double area = trapezio(a, b, n);
    printf("A integral de f(x) no intervalo [%.2f, %.2f] é aproximadamente %.6f\n", a, b, area);

    return 0;
}
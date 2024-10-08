#include <stdio.h>

// Función Iterativa
void calcularPiIterativo(int n, double* pi) {
    double sum = 0.0;
    int sign = 1;
    for (int i = 0; i < n; i++) {
        sum += sign * (1.0 / (2 * i + 1));
        sign = -sign;
    }
    *pi = 4 * sum;
}

// Función Recursiva
void calcularPiRecursivo(int n, int i, double* sum, int sign) {
    if (i >= n) {
        return;
    }
    *sum += sign * (1.0 / (2 * i + 1));
    calcularPiRecursivo(n, i + 1, sum, -sign);
}

int main() {
    int iteraciones;
    double piIterativo = 0.0;
    double piRecursivo = 0.0;

    printf("Ingrese el número de iteraciones: ");
    scanf("%d", &iteraciones);

    // función iterativa
    calcularPiIterativo(iteraciones, &piIterativo);

    // función recursiva
    calcularPiRecursivo(iteraciones, 0, &piRecursivo, 1);
    piRecursivo *= 4;

    printf("El valor de pi (iterativo) es: %.15lf\n", piIterativo);
    printf("El valor de pi (recursivo) es: %.15lf\n", piRecursivo);

    return 0;
}

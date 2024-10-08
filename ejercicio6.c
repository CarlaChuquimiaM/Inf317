#include <stdio.h>

#define MAX_TERMS 100

void calcularFibonacci(int n, int fib[]) {
    if (n >= 1) fib[0] = 0;
    if (n >= 2) fib[1] = 1;

    for (int i = 2; i < n; i++) {
        fib[i] = fib[i - 1] + fib[i - 2];
    }
}

int main() {
    int n;
    int fib[MAX_TERMS];
    printf("Cantidad de terminos: ");
    scanf("%d", &n);
    if (n > MAX_TERMS) {
        printf("El número de términos debe ser menor o igual a %d\n", MAX_TERMS);
        return 1;
    }
    calcularFibonacci(n, fib);
    printf("Términos de Fibonacci:\n");
    for (int i = 0; i < n; i++) {
        printf("%d \n", fib[i]);
    }
    printf("\n");

    return 0;
}

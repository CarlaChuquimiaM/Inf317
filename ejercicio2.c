#include "stdio.h"

int suma(int a, int b) {
    return a + b;
}

// Función para restar dos números
int resta(int a, int b) {
    return a - b;
}
int multiplicacion(int a, int b) {
    return a*b;
}
int division(int a, int b) {
    if (b == 0) {
        printf("Error, no se puede dividir entre cero.\n");
        return -1;
    }
    return a/b;
}


int main() {
    int num1, num2;

    printf("Ingrese el primer numero: ");
    scanf("%d", &num1);

    printf("Ingrese el segundo numero: ");
    scanf("%d", &num2);

    // Suma
    printf("La suma es: %d\n", suma(num1, num2));

    // Resta
    printf("La resta es: %d\n", resta(num1, num2));

    // Multiplicacion
    printf("La multiplicación es: %d\n", multiplicacion(num1, num2));

    // Division
    printf("La division es: %d\n", division(num1, num2));


}

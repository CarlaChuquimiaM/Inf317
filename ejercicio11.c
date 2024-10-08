#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

#define n 13

void suma_pares(int *A, int *B, int *C) {
    for (int i = 0; i < n; i += 2)
        C[i] = A[i] + B[i];
}

void suma_impares(int *A, int *B, int *C) {
    for (int i = 1; i < n; i += 2)
        C[i] = A[i] + B[i];
}

int main(int argc, char **argv)
{
    int proc, maq;
    int A[n] = {5, 6, 7, 8, 9, 8, 7, 6, 5, 4, 3, 2, 1};
    int B[n] = {5, 4, 3, 2, 1, 8, 7, 6, 5, 4, 2, 1, 0};
    int C[n] = {0};

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &proc);
    MPI_Comm_size(MPI_COMM_WORLD, &maq);

    if (proc == 1) {
        suma_impares(A, B, C);
        MPI_Send(C, n, MPI_INT, 0, 0, MPI_COMM_WORLD);
    }
    else if (proc == 2) {
        suma_pares(A, B, C);
        MPI_Send(C, n, MPI_INT, 0, 0, MPI_COMM_WORLD);
    }
    else if (proc == 0) {
        int C_par[n] = {0};
        int C_impar[n] = {0};

        MPI_Recv(C_impar, n, MPI_INT, 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

        MPI_Recv(C_par, n, MPI_INT, 2, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

        for (int i = 0; i < n; i++) {
            C[i] = C_par[i] + C_impar[i];
        }
        printf("La suma es:\n");
        for (int i = 0; i < n; i++)
            printf("%d ", C[i]);
    }
    MPI_Finalize();
    return 0;
}

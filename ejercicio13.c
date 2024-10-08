#include <mpi.h>
#include <stdio.h>
#include <string.h>

#define n 6
#define max 100

int main(int argc, char **argv) {
    int proc, maq;
    char vector[n][max] = {
        "cadena1", "cadena2", "cadena3", "cadena4", "cadena5","cadena6"};

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &proc);
    MPI_Comm_size(MPI_COMM_WORLD, &maq);

    if (maq < 3) {
        printf("Se necesitan al menos 3 procesadores.\n");
        MPI_Finalize();
        return 0;
    }

    if (proc == 0) {
        MPI_Send(vector, n * max, MPI_CHAR, 1, 0, MPI_COMM_WORLD);
        MPI_Send(vector, n * max, MPI_CHAR, 2, 0, MPI_COMM_WORLD);
    } else if (proc == 1) {
        char res[n][max];
        MPI_Recv(res, n * max, MPI_CHAR, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

        printf("Procesador 1 (pares):\n");
        for (int i = 0; i < n; i += 2) {
            printf("Posición %d: %s\n", i, res[i]);
        }
    } else if (proc == 2) {
        char res[n][max];
        MPI_Recv(res, n * max, MPI_CHAR, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

        printf("Procesador 2 (impares):\n");
        for (int i = 1; i < n; i += 2) {
            printf("Posición %d: %s\n", i, res[i]);
        }
    }
    MPI_Finalize();
    return 0;
}

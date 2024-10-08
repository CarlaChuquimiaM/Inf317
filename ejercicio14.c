#include <stdio.h>
#include <mpi.h>

#define N 4

int main(int argc, char** argv) {
    int proc, maq;
    int A[N][N] = {
        {1, 2, 3, 4},
        {5, 6, 7, 8},
        {9, 10, 11, 12},
        {13, 14, 15, 16} };
    int B[N][N] = {
        {1, 0, 0, 1},
        {0, 1, 1, 0},
        {0, 1, 0, 1},
        {1, 0, 0, 1} };
    int C[N][N] = {0};
    int i, j, k;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &proc);
    MPI_Comm_size(MPI_COMM_WORLD, &maq);

    if (maq < 2) {
        if (proc == 0) {
            printf("Se requieren al menos 2 procesadores.\n");
        }
        MPI_Finalize();
        return 0;
    }

    if (proc == 0) {
        for (i = 1; i < maq; i++) {
            MPI_Send(B, N * N, MPI_INT, i, 0, MPI_COMM_WORLD);
        }
        int m = N / maq;
        for (i = 1; i < maq; i++) {
            MPI_Send(&A[i * m], m * N, MPI_INT, i, 0, MPI_COMM_WORLD);
        }
        for (i = 0; i < m; i++) {
            for (j = 0; j < N; j++) {
                for (k = 0; k < N; k++) {
                    C[i][j] += A[i][k] * B[k][j];
                }
            }
        }
        for (i = 1; i < maq; i++) {
            MPI_Recv(&C[i * m], m * N, MPI_INT, i, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        }

        printf("Resultado de A * B:\n");
        for (i = 0; i < N; i++) {
            for (j = 0; j < N; j++) {
                printf("%d ", C[i][j]);
            }
            printf("\n");
        }
    }
    else {
        MPI_Recv(B, N * N, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

        int m = N / maq;
        int A_local[m][N];
        MPI_Recv(A_local, m * N, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        int C_local[m][N];
        for (i = 0; i < m; i++) {
            for (j = 0; j < N; j++) {
                C_local[i][j] = 0;
                for (k = 0; k < N; k++) {
                    C_local[i][j] += A_local[i][k] * B[k][j];
                }
            }
        }
        MPI_Send(C_local, m * N, MPI_INT, 0, 0, MPI_COMM_WORLD);
    }
    MPI_Finalize();
    return 0;
}

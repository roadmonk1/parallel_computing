#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

int main(int argc, char *argv[]) {
    int rank, size;
    const int N = 8;  // total elements (must be divisible by size)
    
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (N % size != 0) {
        if (rank == 0)
            printf("Error: N (%d) must be divisible by number of processes (%d)\n", N, size);
        MPI_Finalize();
        return 1;
    }

    int chunk_size = N / size;

    // Dynamic memory allocation
    int *data = NULL;
    int *recv_chunk = (int*)malloc(chunk_size * sizeof(int));
    int *squared_chunk = (int*)malloc(chunk_size * sizeof(int));

    if (recv_chunk == NULL || squared_chunk == NULL) {
        printf("Memory allocation failed on process %d\n", rank);
        MPI_Finalize();
        return 1;
    }

    if (rank == 0) {
        data = (int*)malloc(N * sizeof(int));
        if (data == NULL) {
            printf("Memory allocation failed on process 0\n");
            free(recv_chunk);
            free(squared_chunk);
            MPI_Finalize();
            return 1;
        }
        printf("Process 0 original array: ");
        for (int i = 0; i < N; i++) {
            data[i] = i + 1;
            printf("%d ", data[i]);
        }
        printf("\n");
    }

    MPI_Scatter(data, chunk_size, MPI_INT, recv_chunk, chunk_size, MPI_INT, 0, MPI_COMM_WORLD);

    // Square the received chunk
    for (int i = 0; i < chunk_size; i++) {
        squared_chunk[i] = recv_chunk[i] * recv_chunk[i];
    }

    MPI_Gather(squared_chunk, chunk_size, MPI_INT, data, chunk_size, MPI_INT, 0, MPI_COMM_WORLD);

    if (rank == 0) {
        printf("Process 0 gathered squared array: ");
        for (int i = 0; i < N; i++) {
            printf("%d ", data[i]);
        }
        printf("\n");
        free(data);
    }

    free(recv_chunk);
    free(squared_chunk);

    MPI_Finalize();
    return 0;
}

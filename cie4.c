#include <stdio.h>
#include <mpi.h>

#define ARRAY_SIZE 5

int main(int argc, char *argv[]) {
    int rank, size;
    int data[ARRAY_SIZE];

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (rank == 0) {
        // Process 0 reads the array
        printf("Enter %d integers: ", ARRAY_SIZE);
        for (int i = 0; i < ARRAY_SIZE; i++) {
            scanf("%d", &data[i]);
        }
    }

    // Broadcast the array from process 0 to all other processes
    MPI_Bcast(data, ARRAY_SIZE, MPI_INT, 0, MPI_COMM_WORLD);

    // Each process prints the received array
    printf("Process %d received array: ", rank);
    for (int i = 0; i < ARRAY_SIZE; i++) {
        printf("%d ", data[i]);
    }
    printf("\n");

    MPI_Finalize();
    return 0;
}

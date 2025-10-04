#include <stdio.h>
#include <mpi.h>

int main(int argc, char *argv[]) {
    int rank, size;
    int value;

    // Initialize MPI
    MPI_Init(&argc, &argv);

    // Get current process rank
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    // Get total number of processes
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (size < 2) {
        if (rank == 0) {
            printf("This program needs at least 2 processes.\n");
        }
        MPI_Finalize();
        return 0;
    }

    if (rank == 0) {
        // Process 0 sends a value
        value = 10;  // You can change this value
        printf("Process 0 sending value %d to process 1\n", value);
        MPI_Send(&value, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);
    } else if (rank == 1) {
        // Process 1 receives the value
        MPI_Recv(&value, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        value *= 2;
        printf("Process 1 received value and multiplied by 2: %d\n", value);
    }

    // Finalize MPI
    MPI_Finalize();
    return 0;
}

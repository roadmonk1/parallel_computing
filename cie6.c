#include <stdio.h>
#include <mpi.h>

int main(int argc, char *argv[]) {
    int rank, size;
    int rank_value;
    int sum_at_root;
    int sum_all;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    rank_value = rank;  // Each process sets number to its rank

    // MPI_Reduce to sum all ranks, result only at process 0
    MPI_Reduce(&rank_value, &sum_at_root, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

    if (rank == 0) {
        printf("Sum of ranks at process 0 using MPI_Reduce: %d\n", sum_at_root);
    }

    // MPI_Allreduce to sum all ranks and share result with all processes
    MPI_Allreduce(&rank_value, &sum_all, 1, MPI_INT, MPI_SUM, MPI_COMM_WORLD);

    printf("Process %d received sum of all ranks using MPI_Allreduce: %d\n", rank, sum_all);

    MPI_Finalize();
    return 0;
}

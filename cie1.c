#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>

// Function to check if a number is prime
int is_prime(int num) {
    if (num <= 1) return 0;
    if (num == 2) return 1;
    if (num % 2 == 0) return 0;
    int sqrtn = (int)sqrt(num);
    for (int i = 3; i <= sqrtn; i += 2) {
        if (num % i == 0) return 0;
    }
    return 1;
}

int main() {
    int n;
    printf("Enter the value of n: ");
    scanf("%d", &n);

    int count_serial = 0;
    int count_parallel = 0;
    double start_time, end_time;

    // Serial version
    start_time = omp_get_wtime();
    for (int i = 1; i <= n; i++) {
        if (is_prime(i)) {
            count_serial++;
        }
    }
    end_time = omp_get_wtime();
    double time_serial = end_time - start_time;

    // Parallel version with dynamic scheduling
    count_parallel = 0;
    start_time = omp_get_wtime();

    #pragma omp parallel for schedule(dynamic, 100) reduction(+:count_parallel)
    for (int i = 1; i <= n; i++) {
        if (is_prime(i)) {
            count_parallel++;
        }
    }

    end_time = omp_get_wtime();
    double time_parallel = end_time - start_time;

    // Results
    printf("\n--- Results ---\n");
    printf("Serial count     : %d\n", count_serial);
    printf("Parallel count   : %d\n", count_parallel);
    printf("Serial time      : %.6f seconds\n", time_serial);
    printf("Parallel time    : %.6f seconds\n", time_parallel);

    return 0;
}

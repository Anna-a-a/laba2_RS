#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>

int main() {
    const int N = 1000000;  // Array size
    int* arr = (int*)malloc(N * sizeof(int));
    
    // Initialize array with random values
    srand(time(NULL));
    for (int i = 0; i < N; i++) {
        arr[i] = rand() % 100;  // Random values between 0 and 99
    }
    
    // Get number of threads from environment variable or use default
    int num_threads = omp_get_max_threads();
    if (getenv("OMP_NUM_THREADS")) {
        num_threads = atoi(getenv("OMP_NUM_THREADS"));
    }
    omp_set_num_threads(num_threads);
    
    long long sum = 0;
    double start_time = omp_get_wtime();

    // Parallel sum with reduction
    #pragma omp parallel for reduction(+:sum)
    for (int i = 0; i < N; i++) {
        sum += arr[i];
    }

    double end_time = omp_get_wtime();
    double time_elapsed = end_time - start_time;

    printf("Number of threads: %d\n", num_threads);
    printf("Parallel sum: %lld\n", sum);
    printf("Time elapsed: %f seconds\n", time_elapsed);

    free(arr);
    return 0;
} 
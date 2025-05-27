#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    const int N = 1000000;  // Array size
    int* arr = (int*)malloc(N * sizeof(int));
    
    // Initialize array with random values
    srand(time(NULL));
    for (int i = 0; i < N; i++) {
        arr[i] = rand() % 100;  // Random values between 0 and 99
    }
    
    long long sum = 0;
    clock_t start_time = clock();

    // Sequential sum
    for (int i = 0; i < N; i++) {
        sum += arr[i];
    }

    clock_t end_time = clock();
    double time_elapsed = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;

    printf("Sequential sum: %lld\n", sum);
    printf("Time elapsed: %f seconds\n", time_elapsed);

    free(arr);
    return 0;
} 
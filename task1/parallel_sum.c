#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Usage: %s <array_size> <number_of_threads>\n", argv[0]);
        return 1;
    }

    const int N = atoi(argv[1]);  // Размер массива из аргумента командной строки
    if (N <= 0) {
        printf("Error: Array size must be positive\n");
        return 1;
    }

    int* arr = (int*)malloc(N * sizeof(int));
    
    // Инициализация массива случайными значениями
    srand(time(NULL));
    for (int i = 0; i < N; i++) {
        arr[i] = rand() % 100;  // Случайные значения от 0 до 99
    }
    
    // Получение количества потоков из аргумента командной строки
    int num_threads = atoi(argv[2]);
    if (num_threads <= 0) {
        printf("Error: Number of threads must be positive\n");
        free(arr);
        return 1;
    }
    omp_set_num_threads(num_threads);
    
    long long sum = 0;
    double start_time = omp_get_wtime();

    // Параллельное суммирование с редукцией
    #pragma omp parallel for reduction(+:sum)
    for (int i = 0; i < N; i++) {
        sum += arr[i];
    }

    double end_time = omp_get_wtime();
    double time_elapsed = end_time - start_time;

    printf("Array size: %d\n", N);
    printf("Number of threads: %d\n", num_threads);
    printf("Parallel sum: %lld\n", sum);
    printf("Time elapsed: %f seconds\n", time_elapsed);

    free(arr);
    return 0;
} 
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    const int N = 1000000;  // Размер массива
    int* arr = (int*)malloc(N * sizeof(int));
    
    // Инициализация массива случайными значениями
    srand(time(NULL));
    for (int i = 0; i < N; i++) {
        arr[i] = rand() % 100;  // Случайные значения от 0 до 99
    }
    
    long long sum = 0;
    clock_t start_time = clock();

    // Последовательное суммирование
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